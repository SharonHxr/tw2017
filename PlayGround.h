#ifndef _H_PLAYGROUND_
#define _H_PLAYGROUND_

#include "BillingRule.h"
#include "Schedule.h"

class PlayGround{
public:
    PlayGround(BillingRule *prices);
    ~PlayGround();

    /* 获取总的收益 */
    float revenue();
    Schedule &getSchedule();

    bool add( const Date &date, const ScheduleItem &item );
    bool cancel( const Date &date, const ScheduleItem &item );

private:
    BillingRule *prices;
    Schedule schedule;
};

#endif