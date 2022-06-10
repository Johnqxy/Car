/*
 * Voltage_Acquisition.h
 *
 *  Created on: 2021年4月17日
 *      Author: Javelin
 */
#include "headfile.h"//各个模块的头文件
#ifndef CODE_VOLTAGE_ACQUISITION_H_
#define CODE_VOLTAGE_ACQUISITION_H_

#define voltage_filter 50
extern uint8 car_mode;
extern uint8 stop_sign;
extern uint16 voltage;
//extern uint8 restart_sign;
extern uint8 carstart;
extern float voltage_V;
extern uint8 car_state;
extern float voltage_proportion;
void voltage_acquisition_Init(void);
void voltage_acquisition(void);
void oled_show_voltage(void);


#endif /* CODE_VOLTAGE_ACQUISITION_H_ */
