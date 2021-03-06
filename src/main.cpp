#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "InputOutput.h"
#include "Schedule.h"
#include "PlayGround.h"

int main(){
    int ret;

    PlayGround pg_A( new CommonBillingRule() );
    PlayGround pg_B( new CommonBillingRule() );
    PlayGround pg_C( new CommonBillingRule() );
    PlayGround pg_D( new CommonBillingRule() );

    char input[64];
    memset(input,0,64);
    
    while(1){
        
        if( fgets(input,64,stdin) == NULL ){
            exit( 0 );
        }
        
        if(strlen(input) == 1 && (input[0]=='\n' || input[0] == '\r')){
            /* 输出收入汇总 */
            printf("> 收入汇总\n");
            printf("> ---\n");
            InputOutput::showPlayGround("A",pg_A);
            printf(">\n");
            InputOutput::showPlayGround("B",pg_B);
            printf(">\n");
            InputOutput::showPlayGround("C",pg_C);
            printf(">\n");
            InputOutput::showPlayGround("D",pg_D);
            printf("> ---\n");
            
            float allRevenue = pg_A.revenue()+pg_B.revenue()+pg_C.revenue()+pg_D.revenue();
            if((allRevenue - (int)allRevenue)<0.001)  
                printf( "> 总计: %.0f元\n", allRevenue);
            else
                printf( "> 总计: %.2f元\n", allRevenue);

            exit( 0 );
        }  
        else{
            Date date;
            ScheduleItem item;
            char ground;
            bool cancel;
            ret = InputOutput::parse(input,date,item,ground,cancel);
            if( !ret ){
                /* 解析失败 */
                InputOutput::showInputInvalid();
                continue;
            }
            PlayGround *pg = NULL;
            if( ground == 'A' ){
                pg = &pg_A;
            }
            else if( ground == 'B' ){
                pg = &pg_B;
            }
            else if( ground == 'C' ){
                pg = &pg_C;
            }
            else if( ground == 'D' ){
                pg = &pg_D;
            }
            else{
                /* 无效的运动场地 */
                InputOutput::showInputInvalid();
                continue;
            }

            if( !cancel ){
                ret = pg->add( date, item );
                if( ret == PlayGround::NOERR ){
                    InputOutput::showBookingSuccessed();
                }
                else if( ret == PlayGround::ERR_CONFLICT ){
                    InputOutput::showBookingConflict();
                }
                else if( ret == PlayGround::ERR_INVAL ){
                    InputOutput::showInputInvalid();
                }
            }
            else{
                ret = pg->cancel( date, item );
                if( ret == PlayGround::NOERR ){
                    InputOutput::showBookingSuccessed();
                }
                else if( ret == PlayGround::ERR_INVAL ){
                    InputOutput::showInputInvalid();
                }
                else if( ret == PlayGround::ERR_NEXIST ){
                    InputOutput::showCancelNotExist();
                }
            }   
        }

    }

    return 0;
}
