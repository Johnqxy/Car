/*
 * pid.h
 *
 *  Created on: 2020年8月18日
 *      Author: Javelin
 */

#ifndef SRC_APPSW_TRICORE_USER_PID_H_
#define SRC_APPSW_TRICORE_USER_PID_H_


extern sint16 encValue_1;
extern sint16 encValue_2;


extern sint16 Average_encValue;
extern sint16 base_speed;//速度占空比输出

extern sint16 left_target_speed;
extern sint16 right_target_speed;

extern sint16 duty1;
extern sint16 duty2;

#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )

void speed_control(void);
void oled_show_pwm(void);
void oled_show_base_speed(void);
void base_speed_ctrl(void);
void get_encoder(void);
void encoder_init(void);
void oled_show_Enclder(void);
void pid_adjust_motor(sint16 pid1,sint16 pid2);
void MotorAPID (int speedA);
void MotorBPID (sint16 speedB);
//void MotorBPID (sint16 speedB);
#endif /* SRC_APPSW_TRICORE_USER_PID_H_ */
