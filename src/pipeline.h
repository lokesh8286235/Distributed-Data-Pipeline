#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <optional>
#include <queue>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

namespace pipeline {

template <typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity) : capacity_(capacity) {
        if (capacity_ == 0) throw std::invalid_argument("capacity must be > 0");
    }

    bool push(T value) {
        std::unique_lock lock(mutex_);
        not_full_.wait(lock, [this] { return closed_ || queue_.size() < capacity_; });
        if (closed_) return false;
        queue_.push(std::move(value));
        not_empty_.notify_one();
        return true;
    }

    std::optional<T> pop() {
        std::unique_lock lock(mutex_);
        not_empty_.wait(lock, [this] { return closed_ || !queue_.empty(); });
        if (queue_.empty()) return std::nullopt;
        T value = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return value;
    }

    void close() {
        std::lock_guard lock(mutex_);
        closed_ = true;
        not_empty_.notify_all();
        not_full_.notify_all();
    }

    std::size_t size() const {
        std::lock_guard lock(mutex_);
        return queue_.size();
    }

private:
    std::size_t capacity_;
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    bool closed_{false};
};

template <typename T, typename Fn>
std::size_t run(std::size_t producers, std::size_t workers, std::size_t tasks, Fn fn) {
    if (producers == 0 || workers == 0) return 0;

    BoundedQueue<T> queue(256);
    std::vector<std::thread> producer_threads;
    std::vector<std::thread> worker_threads;
    std::atomic<std::size_t> processed{0};

    const std::size_t base = tasks / producers;
    const std::size_t remainder = tasks % producers;
    std::size_t next_task = 0;
    std::mutex task_mutex;

    for (std::size_t p = 0; p < producers; ++p) {
        producer_threads.emplace_back([&, p] {
            const std::size_t count = base + (p < remainder ? 1 : 0);
            std::size_t start = 0;
            {
                std::lock_guard lock(task_mutex);
                start = next_task;
                next_task += count;
            }
            for (std::size_t i = 0; i < count; ++i) {
                queue.push(static_cast<T>(start + i));
            }
        });
    }

    for (std::size_t w = 0; w < workers; ++w) {
        worker_threads.emplace_back([&] {
            while (auto item = queue.pop()) {
                fn(*item);
                processed.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }

    for (auto& thread : producer_threads) thread.join();
    queue.close();
    for (auto& thread : worker_threads) thread.join();
    return processed.load(std::memory_order_relaxed);
}

}  // namespace pipeline
