#include <time.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "Schedule.h"

Date::Date(){
    init(0,0,0);
}

Date::Date(int _year, int _month, int _day){
    init( _year, _month, _day );
}

Date::Date(const std::string &date){
    int y,m,d;
    int ret = sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d);
    if(ret != 3){
        init(0,0,0);
        return;
    }
    init(y,m,d);
}
void Date::init(int _year, int _month, int _day){
    year = 0;
    month = 0;
    day = 0;
    wday = 0;

    if( _year<1900 ) return;
    if( _month<1 || _month>12 ) return;
    if( _day<1 || _day>31 ) return;

    struct tm t;
    memset( &t, 0, sizeof(t) );
    t.tm_year = _year-1900;
    t.tm_mon = _month-1;
    t.tm_mday = _day;

    time_t ret = mktime( &t );
    if(ret == (time_t)(-1) ){
        return;
    }

    year = _year;
    month = _month;
    day = _day;
    wday = t.tm_wday;
    if( wday==0 ) wday = 7;

}

/* 获取星期几 */
int Date::getWDay() const{
    return wday;
}

/* 是否时有效的日期 */
bool Date::isValid() const{
    return !(year==0&&month==0&&day==0);
}

/* 获取年月日 */
int Date::getYear() const{
    return year;
}

int Date::getMonth() const{
    return month;
}

int Date::getDay() const{
    return day;
}

std::string Date::toString() const{
    char buf[32];
    sprintf(buf, "%d-%02d-%02d", year, month, day);
    return std::string(buf);
}

bool Date::operator<( const Date &date ) const{
    if( !isValid() ) return false;
    if( !date.isValid() ) return true;

    return year*10000+month*100+day < date.year*10000+date.month*100+date.day;
}

bool Date::operator==( const Date &date ) const{
    return year==date.year&&month==date.month&&day==date.day;
}

ScheduleItem::ScheduleItem(const std::string &_user, int _begin,int _end, float _price, bool _canceled){
    this->userId   = _user;
    this->begin    = _begin;
    this->end      = _end;
    this->canceled = _canceled;
    this->price    = _price;
}

bool ScheduleItem::operator==(const ScheduleItem &item) const{
    return ((begin==item.begin) && (end==item.end) && (userId==item.userId));
}

bool ScheduleItem::operator<(const ScheduleItem &item) const{
    if( begin == item.begin ){
        return userId<item.userId;
    }
    return begin<item.begin;
}

ScheduleOfDay::ScheduleOfDay(){
    memset(used,0,24);
    items.clear();
}

ScheduleOfDay::~ScheduleOfDay(){

}

Date ScheduleOfDay::getDate() const{
    return date;
}

void ScheduleOfDay::setDate(const Date &_date){
    this->date = _date;
}

std::vector<ScheduleItem> ScheduleOfDay::getItems(){
    std::vector<ScheduleItem> result;

    std::multiset<ScheduleItem>::iterator ite;
    for(ite=items.begin(); ite!=items.end(); ++ite){
        result.push_back( *ite );
    }
    return result;
}

bool ScheduleOfDay::operator==(const ScheduleOfDay &day){
    return ( date==day.date );
}

bool ScheduleOfDay::operator <(const ScheduleOfDay &day) const{
    return date<day.date;
}

bool ScheduleOfDay::add(const ScheduleItem &item){
    if( item.userId.empty() ) return false;
    if( item.end<=item.begin ) return false;

    for(int i=item.begin; i<item.end; i++){
        if(used[i]!=0) return false;
    }

    /* 查找是否存在cancel记录 */
    std::multiset<ScheduleItem>::iterator ite = items.find( item );
    if( ite!=items.end() && ite->canceled ){
        #if 1
        /* 不允许取消再预约 */
            return false;
        #else
        /* 允许取消再预约 */
            items.erase( ite );
        #endif
    }
 
    for(int i=item.begin; i<item.end; i++){
        used[i] = 1;
    }

    items.insert( item );
    return true;
}

bool ScheduleOfDay::cancel( const ScheduleItem &item ){
    std::multiset<ScheduleItem>::iterator ite = std::find(items.begin(),items.end(),item);
    if(ite == items.end()) return false;
    if( ite->canceled ) return false;

    for(int i=item.begin; i<item.end; i++){
        used[i] = 0;
    }

    ScheduleItem _item = *ite;
    _item.canceled = true;
    _item.price = item.price;

    items.erase( ite );
    items.insert( _item );
    return true;
}

Schedule::Schedule(){

}

Schedule::~Schedule(){

}

bool Schedule::add(const Date &date,const ScheduleItem &item){
    ScheduleOfDay dummy;
    dummy.setDate( date );
    std::set<ScheduleOfDay>::iterator ite = days.find(dummy);
    if( ite==days.end() ){
        ScheduleOfDay day;
        day.setDate( date );
        if( day.add( item ) ){
            days.insert( day );
            return true;
        }
        return false;
    }
    else{
        ScheduleOfDay sod = *ite;
        if( !sod.add( item ) ){
            return false;
        }

        days.erase( ite );
        days.insert( sod );
        return true;
    }
}

bool Schedule::cancel(const Date &date,const ScheduleItem &item){
    ScheduleOfDay sod;
    sod.setDate( date );
    std::set<ScheduleOfDay>::iterator ite = days.find( sod );
    if( ite==days.end() ) return false;

    sod = *ite;
    if( !sod.cancel(item) ){
        return false;
    }

    days.erase( ite );
    days.insert( sod );

    return true;
}

std::vector<Date> Schedule::getDates(){
    std::vector<Date> allDates;

    std::set<ScheduleOfDay>::iterator ite;
    for(ite=days.begin(); ite!=days.end(); ite++){
        allDates.push_back( ite->getDate() );
    }
    return allDates;
}

ScheduleOfDay Schedule::getScheduleOfDay( const Date &date ){
    ScheduleOfDay sod;
    sod.setDate( date );

    std::set<ScheduleOfDay>::iterator ite = days.find( sod );
    if( ite==days.end() ){
        return ScheduleOfDay();
    }
    return *ite;
}
