#include "PlayGround.h"
#include "Schedule.h"

PlayGround::PlayGround(BillingRule *_prices){
    this->prices = _prices; 
}

PlayGround::~PlayGround(){

}

float PlayGround::revenue(){
    std::vector<Date> dates;
    dates = schedule.getDates();

    float result = 0;
    
    std::vector<Date>::iterator ite;
    for( ite=dates.begin(); ite!=dates.end(); ++ite ){
        ScheduleOfDay sod = schedule.getScheduleOfDay( *ite );
        
        std::vector<ScheduleItem> items = sod.getItems();
        std::vector<ScheduleItem>::iterator item_ite;
        for( item_ite=items.begin(); item_ite!=items.end(); ++item_ite ){
            result += item_ite->price;
        }
    }

    return result;
}

Schedule &PlayGround::getSchedule(){
    return this->schedule;
}

PlayGround::ErrCode PlayGround::add( const Date &date, const ScheduleItem &item ){
    if( !date.isValid() ) return ERR_INVAL;
    if( item.begin>=item.end ) return ERR_INVAL;
    float price = 0;

    for( int idx=item.begin; idx<item.end; ++idx ){
        int ret = prices->getBilling( date.getWDay(), idx );
        if( ret<0 ){
            /* 无效的时间段 */
            return ERR_INVAL;
        }
        price += ret;
    }

    ScheduleItem _item = item;
    _item.price = price;
    if( !schedule.add( date, _item ) ){
        /* 冲突 */
        return ERR_CONFLICT;
    }
    return NOERR;
}

PlayGround::ErrCode PlayGround::cancel( const Date &date, const ScheduleItem &item ){
    if( !date.isValid() ) return ERR_INVAL;
    if( item.begin>=item.end ) return ERR_INVAL;

    float price = 0;
    for( int idx=item.begin; idx<item.end; ++idx ){
        float ret = prices->getPenalty( date.getWDay(), idx );
        if( ret<0 ){
            /* 无效的时间段 */
            return ERR_INVAL;
        }
        price += ret;
    }

    ScheduleItem _item = item;
    _item.price = price;
    if( !schedule.cancel( date, _item ) ){
        /* 预定不存在 */
        return ERR_NEXIST;
    }
    return NOERR;
}