#ifndef _H_INPUTOUTPUT_
#define _H_INPUTOUTPUT_

#include <string>
#include <stdio.h>
#include "Schedule.h"
#include "PlayGround.h"

class InputOutput{
public:
    static bool parse(const std::string &str, Date &date,ScheduleItem &item,char &ground,bool &cancel);
    static void showInputInvalid();
    static void showBookingSuccessed();
    static void showBookingConflict();
    static void showCancelNotExist();
    static void showPlayGround( const std::string &name, PlayGround &pg );
};


#endif