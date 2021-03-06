#include "InputOutput.h"

bool InputOutput::parse(const std::string &str,Date &date,ScheduleItem &item,char &ground,bool &cancel){
    int ret;
    int n;

    const char *p = str.c_str();
    if(p==NULL) return false;

    /* 解析用户id */
    while( *p == ' ' ) p++;
    item.userId.clear();
    while(*p!='\0' && *p!=' '){
        item.userId.push_back(*p);
        p++;
    }

    if(item.userId.empty()){
        return false;
    }

    /* 解析日期 */
    while( *p == ' ' ) p++;
    std::string tmp;
    while(*p!='\0' && *p!=' '){
        tmp.push_back(*p);
        p++;
    }

    date = Date( tmp );
    if( !date.isValid() ){
        return false;
    }

    /* 解析时间段 */
    while( *p == ' ' ) p++;
    ret = sscanf(p,"%d:00~%d:00%n",&item.begin,&item.end,&n);
    if( ret!=2 ){

        return false;
    }
    p += n;

    /* 解析场地 */
    while( *p == ' ' ) p++;
    if(*p!='\0'){
        ground = *p;
        p++;
    }
    else{
        return false;
    }

    /* 解析是否取消预约 */
    while( *p == ' ' ) p++;
    cancel = false;
    if(*p=='C'){
        cancel = true;
        p++;
    }

    while( *p == ' ' ) p++;
    if(*p=='\n'||*p=='\r') p++;
    if(*p!='\0'){
        return false;
    }
    
    return true;
}
void InputOutput::showInputInvalid(){
    printf("> Error: the booking is invalid!\n");
}

void InputOutput::showBookingSuccessed(){
    printf("> Success: the booking is accepted!\n");
}

void InputOutput::showBookingConflict(){
    printf("> Error: the booking conflicts with existing bookings!\n");
}

void InputOutput::showCancelNotExist(){
    printf("> Error: the booking being cancelled does not exist!\n");
}

void InputOutput::showPlayGround( const std::string &name, PlayGround &pg ){
    printf("> 场地:%s\n",name.c_str());

    Schedule schedule = pg.getSchedule();

    std::vector<Date> dates = schedule.getDates();

    std::vector<Date>::iterator ite;
    for(ite=dates.begin(); ite!=dates.end(); ite++){
        ScheduleOfDay day = schedule.getScheduleOfDay(*ite);

        std::vector<ScheduleItem> items = day.getItems();
        std::vector<ScheduleItem>::iterator items_ite;
        for(items_ite=items.begin(); items_ite!=items.end(); items_ite++){
            printf("> %s %d:00~%d:00 ",ite->toString().c_str(),items_ite->begin,items_ite->end);
            if(items_ite->canceled){
                printf("违约金 ");
            }
            if((items_ite->price - (int)items_ite->price)<0.001)
                printf("%.0f元\n",items_ite->price);
            else
                printf("%.2f元\n",items_ite->price);
        }
    }
    float re = pg.revenue();
    if((re-(int)re)<0.001)
        printf("> 小计: %.0f元\n",re);
    else
        printf("> 小计: %.2f元\n",re);

}