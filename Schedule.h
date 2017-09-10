#ifndef _H_SCHDULE_
#define _H_SCHDULE_

#include <map>
#include <string>
#include <list>
#include <vector>

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
    int getWDay();
    /* 是否时有效的日期 */
    bool isValid() const;
    /* 获取年月日 */
    int getYear();
    int getMonth();
    int getDay();

    bool operator<( const Date &date );

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
    bool operator == (const ScheduleItem &);

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

    std::list<ScheduleItem> getItems();

private:
    uint8_t used[24];
    std::list<ScheduleItem> items;
};

class Schedule{
public:
    Schedule();
    ~Schedule();
    bool add(std::string date,const ScheduleItem &item);
    bool cancel(std::string date,const ScheduleItem &item);

    std::vector<ScheduleItem>  getScheduleItems();
    std::vector<std::string>   getDates();
    ScheduleOfDay getScheduleOfDay( std::string day );
private:
    std::map<std::string,ScheduleOfDay > days;
};

#endif
