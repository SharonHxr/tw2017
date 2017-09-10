#include <time.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "Schedule.h"

Date::Date(){
    init( 0,0,0 );
}

Date::Date( int _year, int _month, int _day ){
    init( _year, _month, _day );
}

Date::Date( const std::string &date ){
    int y,m,d;
    int ret = sscanf( date.c_str(), "%d-%d-%d", &y, &m, &d );
    if( ret != 3 ){
        init( 0,0,0 );
        return;
    }
    init( y,m,d );
}
void Date::init( int _year, int _month, int _day ){
    year = 0;
    month = 0;
    day = 0;

    if( _year<1900 ) return;
    if( _month<1 || _month>12 ) return;
    if( _day<1 || _day>31 ) return;

    struct tm t;
    memset( &t, 0, sizeof(t) );
    t.tm_year = _year-1900;
    t.tm_mon = _month-1;
    t.tm_mday = _day;

    time_t ret = mktime( &t );
    if( ret == (time_t)(-1) ){
        return;
    }

    year = _year;
    month = _month;
    day = _day;
    wday = t.tm_wday;
    if( wday==0 ) wday = 7;

}

/* 获取星期几 */
int Date::getWDay(){
    return wday;
}

/* 是否时有效的日期 */
bool Date::isValid() const{
    return !(year==0&&month==0&&day==0);
}

/* 获取年月日 */
int Date::getYear(){
    return year;
}

int Date::getMonth(){
    return month;
}

int Date::getDay(){
    return day;
}

bool Date::operator<( const Date &date ){
    if( !isValid() ) return false;
    if( !date.isValid() ) return true;

    return year*10000+month*100+day < date.year*10000+date.month*100+date.day;
}

ScheduleItem::ScheduleItem( const std::string &_user, int _begin,int _end, float _price, bool _canceled){
    this->userId   = _user;
    this->begin    = _begin;
    this->end      = _end;
    this->canceled = _canceled;
    this->price    = _price;
}

bool ScheduleItem::operator==(const ScheduleItem &item){
    return ((begin==item.begin) && (end==item.end) && (userId==item.userId));
}

ScheduleOfDay::ScheduleOfDay(){
    memset(used,0,24);
    items.clear();
}

ScheduleOfDay::~ScheduleOfDay(){

}

std::list<ScheduleItem> ScheduleOfDay::getItems(){
    return items;
}

bool ScheduleOfDay::add(const ScheduleItem &item){
    if(item.userId.empty()) return false;
    if(item.end <= item.begin) return false;
    
    for(int i=item.begin; i<item.end; i++){
        if(used[i]!=0) return false;
    }
    for(int i=item.begin; i<item.end; i++){
        used[i] = 1;
    }

    items.push_back(item);
    return true;
}

bool ScheduleOfDay::cancel( const ScheduleItem &item ){
    std::list<ScheduleItem>::iterator ite = std::find(items.begin(),items.end(),item);
    if(ite == items.end()) return false;
    if( ite->canceled ) return false;

    for(int i=item.begin; i<item.end; i++){
        used[i] = 0;
    }
    ite->canceled = true;
    ite->price = item.price;
    return true;
}

Schedule::Schedule(){

}

Schedule::~Schedule(){

}

bool Schedule::add(std::string date,const ScheduleItem &item){
    std::map<std::string,ScheduleOfDay>::iterator ite = days.find(date);
    if( ite==days.end() ){
        ScheduleOfDay day;
        if( day.add( item ) ){
            days.insert( std::make_pair(date,day) );
            return true;
        }
        return false;
    }
    else{
        return ite->second.add( item );
    }
}

bool Schedule::cancel(std::string date,const ScheduleItem &item){
    std::map<std::string,ScheduleOfDay>::iterator ite = days.find(date);
    if(ite==days.end()) return false;

    return ite->second.cancel(item);
}

std::vector<std::string> Schedule::getDates(){
    std::vector<std::string> allDates;

    std::map<std::string,ScheduleOfDay>::iterator ite;
    for(ite=days.begin(); ite!=days.end(); ite++){
        allDates.push_back(ite->first);
    }
    return allDates;
}

ScheduleOfDay Schedule::getScheduleOfDay(std::string day){
    std::map<std::string,ScheduleOfDay>::iterator ite = days.find(day);

    if(ite==days.end()) return ScheduleOfDay();

    return ite->second;
}