#ifndef _H_SCHDULE_
#define _H_SCHDULE_

#include <set>
#include <string>
#include <list>
#include <vector>
#include <stdint.h>

class Date{
public:
    Date();
    /* year: 指定年，大于1900年
     * month: 指定月，1-12
     * day: 指定日，1-31
     */
    Date( int year, int month, int day );
    /* 2017-09-10 */
    Date( const std::string &date );

    /* 获取星期几 */
    int getWDay() const;
    /* 是否时有效的日期 */
    bool isValid() const;
    /* 获取年月日 */
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    std::string toString() const;

    bool operator<( const Date &date ) const;
    bool operator==( const Date &date ) const;

private:
    void init( int y, int m, int d );

private:
    int year;
    int month;
    int day;
    int wday; /* 星期几 */
};

class ScheduleItem{
public:
    ScheduleItem( const std::string &user=std::string(), int begin=0,int end=0, float price=0, bool canceled=false);
    bool operator == ( const ScheduleItem & ) const;
    bool operator <  ( const ScheduleItem & ) const;

    int begin;
    int end;
    std::string userId;
    float price;
    bool canceled;
};

class ScheduleOfDay{
public:
    ScheduleOfDay();
    ~ScheduleOfDay();
    bool add(const ScheduleItem &item);
    bool cancel(const ScheduleItem &item);

    bool operator == (const ScheduleOfDay &);
    bool operator <(const ScheduleOfDay &) const;

    Date getDate() const;
    void setDate( const Date &date );

    std::vector<ScheduleItem> getItems();

private:
    uint8_t used[24];
    std::set<ScheduleItem> items;
    Date date;
};

class Schedule{
public:
    Schedule();
    ~Schedule();
    bool add(const Date &date,const ScheduleItem &item);
    bool cancel(const Date &date,const ScheduleItem &item);

    /* 返回有序日期列表 */
    std::vector<Date> getDates();
    ScheduleOfDay getScheduleOfDay( const Date &day );
private:
    std::set<ScheduleOfDay> days;
};

#endif
