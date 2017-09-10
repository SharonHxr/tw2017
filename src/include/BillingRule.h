#ifndef _H_BILLINGRULE_
#define _H_BILLINGRULE_

class BillingRule{
public:
    BillingRule();
    virtual ~BillingRule();
    /* 获取预约时间段费用，day表示星期，取值1～7，hour表示一小时时间段 */
    virtual int getBilling( int day, int hour ) = 0;
    /* 获取取消预约的违约金，day表示星期，取值1～7，hour表示时间段 */
    virtual float getPenalty( int day, int hour ) = 0;
};

class CommonBillingRule : public BillingRule{
public:
    CommonBillingRule();
    virtual ~CommonBillingRule();

    int getBilling( int day, int hour );
    float getPenalty( int day, int hour );
};

#endif