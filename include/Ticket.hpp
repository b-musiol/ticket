/**
 * Ticket Class
 * If you need Threadsafe tickets, define TICKET_THREADSAFE before include.
 *
 * Author: Bartek Musiol (bmusiol@proton.me)
 *
 * See LICENSE
 */

#ifndef _TICKET__HPP_
#define _TICKET__HPP_

#ifdef TICKET_THREADSAFE
#include <atomic>
class Ticket
{
  public:
    explicit Ticket(int init_ctr = 0) : ctr(init_ctr)
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

#else

class Ticket
{
  public:
    explicit Ticket(int init_ctr = 0) : ctr(init_ctr)
    {
    }

    int pull()
    {
        int to_return = ctr;
        ctr++;
        return to_return;
    }

    int peek_next()
    {
        return ctr;
    }

    int peek_last()
    {
        return ctr - 1;
    }

  private:
    int ctr;
};

#endif

#endif // _TICKET__HPP_