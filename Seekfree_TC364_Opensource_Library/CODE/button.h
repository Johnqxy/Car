#ifndef CODE_BUTTON_H
#define CODE_BUTTON_H

// **************************** 宏定义 ****************************
typedef enum
{
    PKEY_L,  //左P11_9
    PKEY_R,  //右P13_3
    PKEY_U,  //上P11_6
    PKEY_D,  //下P11_10
    PKEY_M,  //中P11_3
    PKEY_MAX,
} PKEY_e;

//#define Beep P33_11
#define Beep_on 1
#define Beep_off 0

void PKeyInit(void);
void OLED_UI(void);

#endif
