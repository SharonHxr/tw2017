#include <assert.h>
#include "BillingRule.h"

BillingRule::BillingRule(){ 

}

BillingRule::~BillingRule(){

}

CommonBillingRule::CommonBillingRule(){

}

CommonBillingRule::~CommonBillingRule(){

}

int CommonBillingRule::getBilling(int day,int hour){
    if(day<1 || day>7) return -1;
    if(hour<0 || hour>23) return -1;

    if(day>=1 && day<=5){
        if(hour>=9  && hour<12) return 30;
        if(hour>=12 && hour<18) return 50;
        if(hour>=18 && hour<20) return 80;
        if(hour>=20 && hour<22) return 60;
        return -1;
    }
    else{
        if(hour>=9  && hour<12) return 40;
        if(hour>=12 && hour<18) return 50;
        if(hour>=18 && hour<22) return 60;
        return -1;
    }
}

float CommonBillingRule::getPenalty(int day,int hour){
    int result;
    result = getBilling(day,hour);
    if(result==-1) return -1;
    if(day>=1 && day<=5){
        return result*0.5f;
    }
    else{
        return result*0.25f;
    }
}
