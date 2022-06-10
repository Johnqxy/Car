/*
 * Infrared_receiving_tube.h
 *
 *  Created on: 2021Äê1ÔÂ20ÈÕ
 *      Author: Javelin
 */

#ifndef SRC_APPSW_TRICORE_USER_INFRARED_RECEIVING_TUBE_H_
#define SRC_APPSW_TRICORE_USER_INFRARED_RECEIVING_TUBE_H_




extern uint8 Infrared_fitered[8];
extern sint8 Infrared_error;
extern float voltageA;

void Infrared_init(void);
void Infrared_receiving_tube(void);
void oled_show_Infrared(void);



#endif /* SRC_APPSW_TRICORE_USER_INFRARED_RECEIVING_TUBE_H_ */
