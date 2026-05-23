/**
 * Ticket Class
 *
 * Author: Bartek Musiol (bmusiol@proton.me)
 *
 * See LICENSE
 */

#ifndef _TICKET__HPP_
#define _TICKET__HPP_

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

#endif // _TICKET__HPP_