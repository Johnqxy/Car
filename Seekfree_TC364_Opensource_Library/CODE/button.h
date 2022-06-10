#ifndef CODE_BUTTON_H
#define CODE_BUTTON_H

// **************************** �궨�� ****************************
typedef enum
{
    PKEY_L,  //��P11_9
    PKEY_R,  //��P13_3
    PKEY_U,  //��P11_6
    PKEY_D,  //��P11_10
    PKEY_M,  //��P11_3
    PKEY_MAX,
} PKEY_e;

//#define Beep P33_11
#define Beep_on 1
#define Beep_off 0

void PKeyInit(void);
void OLED_UI(void);

#endif
