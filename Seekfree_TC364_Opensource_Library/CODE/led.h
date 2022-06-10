#ifndef CODE_LED_H_
#define CODE_LED_H_

#include "Voltage_Acquisition.h"

// **************************** 宏定义 ****************************
//定义接口
#define L1 P15_7
#define L2 P15_6
#define L3 P15_5

#define LA P15_4
#define LB P15_3
#define LC P15_2
#define LD P15_1
#define LE P15_0


void led_init(void);
void light_up(void);

#endif
