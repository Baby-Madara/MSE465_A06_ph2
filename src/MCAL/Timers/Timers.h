#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>
#include <util/delay.h>
#include "../../UTILS/STD_Types.h"



extern volatile u64	milliSecs,
					Secs 	 ,
					minutes	 ,
                    hours    ,
                    days     ;

volatile u64  		milliSecs ,
					Secs      ,
					minutes	  ,
                    hours     ,
                    days      ;



#define TIMERS_ENABLE_T0_WATCH                  \
void WatchUpdate(){                             \
    ++milliSecs;                                \
    if(milliSecs==((u64)4e9))   {milliSecs =0;} \
    Secs    =milliSecs/1000;                    \
    minutes =Secs     /60  ;                    \
    hours   =minutes  /60  ;                    \
    days    =hours    /24  ;                    \
}                                               \
void(*Timers_T0__OCfPtr)() = WatchUpdate;






#endif