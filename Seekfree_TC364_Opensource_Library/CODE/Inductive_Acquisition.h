/*
 * Inductive_Acquisition.h
 *
 *  Created on: 2021Äê7ÔÂ9ÈÕ
 *      Author: Javelin
 */

#ifndef CODE_INDUCTIVE_ACQUISITION_H_
#define CODE_INDUCTIVE_ACQUISITION_H_
#include "common.h"

extern uint16 Left_inductance;
extern uint16 Right_inductance;
extern float Inductive_error;
extern uint16 average_inductance;

void Inductive_Acquisition_init(void);
void Inductive_Acquisition(void);

#endif /* CODE_INDUCTIVE_ACQUISITION_H_ */
