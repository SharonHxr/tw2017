#include "PlayGround.h"
#include "Schedule.h"

PlayGround::PlayGround(BillingRule *_prices){
    this->prices = _prices; 
}

PlayGround::~PlayGround(){

}

float PlayGround::revenue(){
    std::vector<std::string> dates;
    dates = schedule.getDates();

    float result = 0;
    
    std::vector<std::string>::iterator ite;
    for( ite=dates.begin(); ite!=dates.end(); ++ite ){
        ScheduleOfDay sod = schedule.getScheduleOfDay( *ite );
        
        std::list<ScheduleItem> items = sod.getItems();
        std::list<ScheduleItem>::iterator item_ite;
        for( item_ite=items.begin(); item_ite!=items.end(); ++item_ite ){
            result += item_ite->price;
        }
    }

    return result;
}

Schedule &PlayGround::getSchedule(){
    return this->schedule;
}

bool PlayGround::add( const std::string &date, const ScheduleItem &item ){
    if( item.begin>=item.end ) return false;
    float price = 0;

    Date d( date );
    if( !d.isValid() ) return false;

    for( int idx=item.begin; idx<item.end; ++idx ){
        int ret = prices->getBilling( d.getWDay(), idx );
        if( ret<0 ){
            return false;
        }
        price += ret;
    }

    ScheduleItem _item = item;
    _item.price = price;
    return schedule.add( date, _item );
}

bool PlayGround::cancel( const std::string &date, const ScheduleItem &item ){
    if( item.begin>=item.end ) return false;
    float price = 0;

    Date d( date );
    if( !d.isValid() ) return false;

    for( int idx=item.begin; idx<item.end; ++idx ){
        float ret = prices->getPenalty( d.getWDay(), idx );
        if( ret<0 ){
            return false;
        }
        price += ret;
    }

    ScheduleItem _item = item;
    _item.price = price;
    return schedule.cancel( date, _item );
}