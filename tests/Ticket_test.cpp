/**
 * Ticket Class test
 *
 * Author: Bartek Musiol (bmusiol@proton.me)
 *
 * See LICENSE
 */

#include <gtest/gtest.h>
// #define TICKET_THREADSAFE
#include "../include/Ticket.hpp"

TEST(Ticket, test)
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