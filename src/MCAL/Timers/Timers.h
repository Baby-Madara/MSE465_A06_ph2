#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>
#include <util/delay.h>
#include "../../UTILS/STD_Types.h"



extern void (*Timers_T0__OCfPtr)(void) ;
extern void (*Timers_T0__OVfPtr)(void) ;

void (*Timers_T0__OCfPtr)(void) ;
void (*Timers_T0__OVfPtr)(void) ;

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

// ***************************  Timer0  *************************** //

// in TCCR0: [ CS02:0 ] Clock select & prescalers
#define TIMERS_T0_CLK_DISABLE				0
#define TIMERS_T0_CLK_PS_1					1
#define TIMERS_T0_CLK_PS_8					2
#define TIMERS_T0_CLK_PS_64					3
#define TIMERS_T0_CLK_PS_256				4
#define TIMERS_T0_CLK_PS_1024				5
#define TIMERS_T0_COUNT_EXT_ON_FALLING_B0	6
#define TIMERS_T0_COUNT_EXT_ON_RISING_B0	7

// in TCCR0: [ WGM00 - WGM01 ]
#define TIMERS_T0_MODE_NORMAL	0
#define TIMERS_T0_MODE_PCPWM	1
#define TIMERS_T0_MODE_CTC		2	//clear timer on compare match (for wave generation)
#define TIMERS_T0_MODE_FASTPWM	3

// in TCCR0: [ COM00:1 ] Compare output modes
#define TIMERS_T0_OCPIN_DISCONNECT 				0
#define TIMERS_T0_OCPIN_TOGGLE_ON_COMP_MTCH 	1 	//doesnt work while PWM Modes
#define TIMERS_T0_OCPIN_NON_INVERTING_MODE		2	
#define TIMERS_T0_OCPIN_INVERTING_MODE 			3





void Timers_T0_SetClkSrcandPreScaler(u8 ps);
void Timers_T0_SetMode              (u8 mode);
void Timers_T0_CompareVal           (u8 OC);
void Timers_T0_setCompareOutputMode	(u8 outputCompareMode);

void Timers_T0_Init					(u8 ps, u8 mode, u8 outputCompareMode, u8 OutputCompareVal);
void Timers_T0_Disable				();

void Timers_T0_WG__PWM_B3			(u8 outCompVal);
void Timers_T0_IntCompMtchEnable	();
void Timers_T0_IntOverFlowEnable	();
void Timers_T0_IntCompMtchDisable	();
void Timers_T0_IntOverFlowDisable	();
u8   Timers_T0_ReturnCounter    	();
void Timers_T0_ForceOutputCompare	();

void Timers_T0_IntOverFlowSetCallBack (void (*ptr)(void));
void Timers_T0_IntCompMtchSetCallBack (void (*ptr)(void));

void TIMER0_OVF_vect (void) __attribute__ ((used)) __attribute__ ((signal));

void TIMER0_COMP_vect (void) __attribute__ ((used)) __attribute__ ((signal));



void Timers_T0_WatchInit();

u64  Timers_T0_milliSecs			();
u64  Timers_T0_secs					();
u64  Timers_T0_minutes				();
u64  Timers_T0_hours				();
u64  Timers_T0_days 				();

// void (*Timers_T0__OCfPtr)(void) ;               

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