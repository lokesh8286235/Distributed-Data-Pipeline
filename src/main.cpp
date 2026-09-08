#include "pipeline.h"

#include <chrono>
#include <iostream>
#include <numeric>

int main() {
    constexpr std::size_t tasks = 100'000;
    constexpr std::size_t producers = 4;
    constexpr std::size_t workers = 4;

    const auto start = std::chrono::steady_clock::now();
    const auto processed = pipeline::run<int>(
        producers,
        workers,
        tasks,
        [](int value) {
            // Simulate a small CPU-side unit of work while keeping the
            // pipeline implementation independent from the workload.
            volatile int result = value * 31 + 7;
            (void)result;
        });
    const auto elapsed = std::chrono::duration<double>(
        std::chrono::steady_clock::now() - start).count();

    std::cout << "processed=" << processed << "\n"
              << "elapsed_seconds=" << elapsed << "\n";
    return processed == tasks ? 0 : 1;
}
