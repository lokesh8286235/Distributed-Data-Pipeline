#include "../pipeline.h"

#include <atomic>
#include <vector>

#include <gtest/gtest.h>

TEST(BoundedQueueTest, PushPopAndClose) {
    pipeline::BoundedQueue<int> queue(2);

    EXPECT_TRUE(queue.push(10));
    EXPECT_TRUE(queue.push(20));
    EXPECT_EQ(queue.size(), 2U);
    EXPECT_EQ(queue.pop().value(), 10);
    EXPECT_EQ(queue.pop().value(), 20);

    queue.close();
    EXPECT_FALSE(queue.push(30));
    EXPECT_FALSE(queue.pop().has_value());
}

TEST(PipelineTest, ProcessesEveryTaskExactlyOnce) {
    constexpr std::size_t tasks = 10'000;
    std::vector<std::atomic<int>> counts(tasks);
    for (auto& count : counts) count.store(0);

    const auto processed = pipeline::run<int>(
        4, 8, tasks,
        [&](int value) { counts.at(static_cast<std::size_t>(value)).fetch_add(1); });

    EXPECT_EQ(processed, tasks);
    for (const auto& count : counts) EXPECT_EQ(count.load(), 1);
}

TEST(PipelineTest, RejectsDegenerateWorkerConfiguration) {
    const auto processed = pipeline::run<int>(0, 4, 100, [](int) {});
    EXPECT_EQ(processed, 0U);
}
