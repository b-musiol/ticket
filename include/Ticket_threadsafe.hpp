/**
 * Threadsafe Ticket Class
 *
 * Author: Bartek Musiol (bmusiol@proton.me)
 *
 * See LICENSE
 */

#ifndef _TICKET_THREADSAFE__HPP_
#define _TICKET_THREADSAFE__HPP_

#include <atomic>
class Ticket_Threadsafe
{
  public:
    explicit Ticket_Threadsafe(int init_ctr = 0) : ctr(init_ctr)
    {
    }

    int pull()
    {
        return ctr.fetch_add(1);
    }

    int peek_next()
    {
        return ctr.load();
    }

    int peek_last()
    {
        return ctr.load() - 1;
    }

  private:
    std::atomic<int> ctr;
};

#endif // _TICKET_THREADSAFE__HPP_