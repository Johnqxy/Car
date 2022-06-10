/*!
  * @file     ANO_DT.h
  *
  * @brief    
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020��6��5��
  */ 
#ifndef SRC_APPSW_TRICORE_USER_ANO_DT_H_
#define SRC_APPSW_TRICORE_USER_ANO_DT_H_

#include "headfile.h"//����ģ���ͷ�ļ�


void ANO_DT_Send_Data(uint8 *dataToSend , uint16 length);

/*!
  * @brief    ����λ�����ͷ���8��int16_t����
  *
  * @param    data1 - data8  �� ���͸���λ����ʾ����
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 ���ڶ�
  */
//void ANO_DT_send_int16(sint16 data1, sint16 data2, sint16 data3, sint16 data4, sint16 data5, sint16 data6, sint16 data7, sint16 data8 );
void ANO_DT_send_int16(int data1, int data2, int data3, int data4);
#endif /* SRC_APPSW_TRICORE_USER_ANO_DT_H_ */
