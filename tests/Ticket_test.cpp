/**
 * Ticket Class test
 *
 * Author: Bartek Musiol (bmusiol@proton.me)
 *
 * See LICENSE
 */

#include <gtest/gtest.h>

#include <barrier>
#include <thread>
#include <vector>
#include <algorithm>
#include "../include/Ticket.hpp"
#include "../include/Ticket_threadsafe.hpp"

TEST(Ticket, regular)
{
    Ticket t;
    EXPECT_EQ(t.peek_next(), 0);
    EXPECT_EQ(t.pull(), 0);
    EXPECT_EQ(t.pull(), 1);
    EXPECT_EQ(t.pull(), 2);
    EXPECT_EQ(t.pull(), 3);
    EXPECT_EQ(t.peek_next(), 4);
    EXPECT_EQ(t.peek_next(), 4);
    EXPECT_EQ(t.peek_last(), 3);
    EXPECT_EQ(t.pull(), 4);
}

TEST(Ticket, Threadsafe)
{
    Ticket_Threadsafe t;
    EXPECT_EQ(t.peek_next(), 0);
    EXPECT_EQ(t.pull(), 0);
    EXPECT_EQ(t.pull(), 1);
    EXPECT_EQ(t.pull(), 2);
    EXPECT_EQ(t.pull(), 3);
    EXPECT_EQ(t.peek_next(), 4);
    EXPECT_EQ(t.peek_next(), 4);
    EXPECT_EQ(t.peek_last(), 3);
    EXPECT_EQ(t.pull(), 4);
}

TEST(Ticket, ThreadsafeConcurrentPull)
{
    constexpr int thread_count = 16;
    constexpr int pulls_per_thread = 10000;
    constexpr int total_pulls = thread_count * pulls_per_thread;

    Ticket_Threadsafe t;

    std::vector<int> results(total_pulls);

    // Ensures all worker threads begin pulling at roughly the same time.
    std::barrier sync_point(thread_count);

    std::vector<std::thread> threads;

    for (int tid = 0; tid < thread_count; ++tid)
    {
        threads.emplace_back([&, tid]
        {
            sync_point.arrive_and_wait();

            int base = tid * pulls_per_thread;

            for (int i = 0; i < pulls_per_thread; ++i)
            {
                results[base + i] = t.pull();
            }
        });
    }

    for (auto& th : threads)
    {
        th.join();
    }

    // Verify final state.
    EXPECT_EQ(t.peek_next(), total_pulls);
    EXPECT_EQ(t.peek_last(), total_pulls - 1);

    // Verify all ticket numbers are unique and contiguous.
    std::sort(results.begin(), results.end());

    for (int i = 0; i < total_pulls; ++i)
    {
        EXPECT_EQ(results[i], i);
    }
}