/*
 * motor.h
 *
 *  Created on: 2020年8月20日
 *      Author: Javelin
 */

#ifndef SRC_APPSW_TRICORE_USER_MOTOR_H_
#define SRC_APPSW_TRICORE_USER_MOTOR_H_
//
//// 轮子pwm 最大占空比 可自行修改
//#define MOTOR_PWM_MAX  5000
//
//// 轮子pwm 最大变化占空比 可自行修改
//#define MOTOR_PWM_CHANGE_MAX  3000

extern int bench_v;
extern int duty_left;
extern int duty_right;




void motor_init(void);
void motor_direction_left(int duty1);
void motor_direction_right(int duty2);
void motor_limited(sint16 duty1,sint16 duty2);
int constrain_int(int amt, int low, int high);

#endif /* SRC_APPSW_TRICORE_USER_MOTOR_H_ */
