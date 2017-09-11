#ifndef _H_PLAYGROUND_
#define _H_PLAYGROUND_

#include "BillingRule.h"
#include "Schedule.h"

class PlayGround{
public:
    enum ErrCode{
        NOERR        = 0,  /* 没有错误 */
        ERR_INVAL    = -1, /* 无效参数 */
        ERR_CONFLICT = -2, /* 预定时间冲突 */
        ERR_NEXIST   = -3, /* 取消不存在 */
    };
public:
    PlayGround(BillingRule *prices);
    ~PlayGround();

    /* 获取总的收益 */
    float revenue();
    Schedule &getSchedule();

    /* 添加成功返回 NOERR
     * 参数非法返回 ERR_INVAL
     * 时间段冲突返回 ERR_CONFLICT
     */
    ErrCode add( const Date &date, const ScheduleItem &item );
    /* 取消成功返回 NOERR
     * 参数非法返回 ERR_INVAL
     * Item不存在返回 ERR_NEXIST
     */
    ErrCode cancel( const Date &date, const ScheduleItem &item );

private:
    BillingRule *prices;
    Schedule schedule;
};

#endif