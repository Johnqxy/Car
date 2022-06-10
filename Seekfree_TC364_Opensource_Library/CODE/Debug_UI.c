#include "headfile.h"//各个模块的头文件

//如果需要修改页数和行数的话
//需要修改名字数组和指针变量数组
#define  PAGENUM        10      //定义DebugUI页数
#define  FLASHSECTOR    11      //定义存入扇区码数
#define  LINENUM        10      //定义DebugUI行数

static int    scanMode   = 0;    
static int    scanPeriod = 0;
static int    keySameTimes = 0;
static MYKEY_STATE_e keyValue = 0;
static MYKEY_STATE_e keyValueLast = 6;
static int      lockValue = 0;
static int      lockValueLast = 1;
static int      lineValue = 0;//设定首行
static int      lineValueLast = 1;
static int16    pageValue = 0; //设定首页
static int      pageValueLast = 1;
struct F_uint32Value F_32;
int             aa=0;

PIN_enum DIAL_PTxn[DIAL_MAX] = {P11_2,P13_2,P13_1,P13_0};
PIN_enum MYKEY_PTxn[MYKEY_MAX] = {P13_3, P11_9, P11_10, P11_6, P11_3};
char valueName[PAGENUM][LINENUM][13] =//各页数据名称
{

    {"base_speed1","base_speed2","base_speed3","base_speed4","0","0","0","0","0","0"},
    {"Shold_0_4","5_9","10_14","15_19","20_24","25_29","30_34","35_39","40_44","45_49"},
    {"exposure_time","0","0","0","0","0","0","0","0","0"},
    {"L_ERROR_1_5","L_6_10","L_11_15","L_16_20","L_21_25","L_26_30","L_31_35","L_36_40","L_41_45","L_46_50"},
    {"L_51_55","L_56_60","L_61_65","0","0","0","0","0","0","0"},
    {"R_ERROR_1_5","R_6_10","R_11_15","R_16_20","R_21_25","R_26_30","R_31_35","R_36_40","R_41_45","R_46_50"},
    {"R_51_55","R_56_60","R_61_65","0","0","0","0","0","0","0"},
    {"Aspeed_kp","Aspeed_kd","Kp_Roll","Kp_Roll","begin_V","recharge_V","re_target","0","0","0"},
    {"Kp_position1","Kd_position1","Kp_position2","Kd_position2","Kp_position3","Kd_position3","Kp_position4","Kd_position4","Kp_position5","Kd_position5",},
    {"SpeedPA","SpeedIA","SpeedDA","SpeedPB","SpeedIB","SpeedDB","0","0","0","0"},
};


uint32 *uint32Value[PAGENUM][LINENUM] =//int类型数据
{

    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},

};


uint16 *uint16Value[PAGENUM][LINENUM] =//int类型数据
{

    {&myCar.base_speed1, &myCar.base_speed2, &myCar.base_speed3, &myCar.base_speed4,NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {&myCar.exposure_time, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {&L_Error.L_ERROR_1_5, &L_Error.L_ERROR_6_10, &L_Error.L_ERROR_11_15,&L_Error.L_ERROR_16_20,&L_Error.L_ERROR_21_25,&L_Error.L_ERROR_26_30,&L_Error.L_ERROR_31_35,&L_Error.L_ERROR_36_40,&L_Error.L_ERROR_41_45,&L_Error.L_ERROR_46_50},
    {&L_Error.L_ERROR_51_55, &L_Error.L_ERROR_56_60, &L_Error.L_ERROR_61_65, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {&R_Error.R_ERROR_1_5, &R_Error.R_ERROR_6_10, &R_Error.R_ERROR_11_15,&R_Error.R_ERROR_16_20,&R_Error.R_ERROR_21_25,&R_Error.R_ERROR_26_30,&R_Error.R_ERROR_31_35,&R_Error.R_ERROR_36_40,&R_Error.R_ERROR_41_45,&R_Error.R_ERROR_46_50},
    {&R_Error.R_ERROR_51_55, &R_Error.R_ERROR_56_60, &R_Error.R_ERROR_61_65, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},

};

uint8 *uint8Value[PAGENUM][LINENUM] =//int类型数据
{

    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {&myThreshold.Threshold_0_4, &myThreshold.Threshold_5_9, &myThreshold.Threshold_10_14, &myThreshold.Threshold_15_19, &myThreshold.Threshold_20_24, &myThreshold.Threshold_25_29, &myThreshold.Threshold_30_34, &myThreshold.Threshold_35_39, &myThreshold.Threshold_40_44, &myThreshold.Threshold_45_49},
    {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},

};


uint32 *F_uint32Value[PAGENUM][LINENUM]=
{

        {&F_32.base_speed1, &F_32.base_speed2, &F_32.base_speed3, &F_32.base_speed4,NULL, NULL, NULL, NULL, NULL, NULL},
        {&F_32.Threshold_0_4, &F_32.Threshold_5_9, &F_32.Threshold_10_14, &F_32.Threshold_15_19, &F_32.Threshold_20_24, &F_32.Threshold_25_29, &F_32.Threshold_30_34, &F_32.Threshold_35_39, &F_32.Threshold_40_44, &F_32.Threshold_45_49},
        {&F_32.exposure_time, NULL, NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {&F_32.L_ERROR_1_5, &F_32.L_ERROR_6_10, &F_32.L_ERROR_11_15,&F_32.L_ERROR_16_20,&F_32.L_ERROR_21_25,&F_32.L_ERROR_26_30,&F_32.L_ERROR_31_35,&F_32.L_ERROR_36_40,&F_32.L_ERROR_41_45,&F_32.L_ERROR_46_50},
        {&F_32.L_ERROR_51_55, &F_32.L_ERROR_56_60, &F_32.L_ERROR_61_65, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {&F_32.R_ERROR_1_5, &F_32.R_ERROR_6_10, &F_32.R_ERROR_11_15,&F_32.R_ERROR_16_20,&F_32.R_ERROR_21_25,&F_32.R_ERROR_26_30,&F_32.R_ERROR_31_35,&F_32.R_ERROR_36_40,&F_32.R_ERROR_41_45,&F_32.R_ERROR_46_50},
        {&F_32.R_ERROR_51_55, &F_32.R_ERROR_56_60, &F_32.R_ERROR_61_65, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {&F_32.Aspeed_kp, &F_32.Aspeed_kd, &F_32.Kp_Roll, &F_32.Kd_Roll, &F_32.begin_V, &F_32.recharge_V, &F_32.recharge_target, NULL, NULL, NULL},
        {&F_32.Kp_position1, &F_32.Kd_position1, &F_32.Kp_position2,&F_32.Kd_position2, &F_32.Kp_position3, &F_32.Kd_position3,  &F_32.Kp_position4,  &F_32.Kd_position4,  &F_32.Kp_position5, &F_32.Kd_position5},
        {&F_32.SpeedPA,&F_32.SpeedIA,  &F_32.SpeedDA, &F_32.SpeedPB, &F_32.SpeedPB, &F_32.SpeedPB, NULL, NULL, NULL, NULL},

};//用于转换float数据类型


float *fValue[PAGENUM][LINENUM] =//float类型数据
{

    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {&myCar.Aspeed_kp, &myCar.Aspeed_kd, &myCar.Kp_Roll, &myCar.Kd_Roll,&myCar.begin_V, &myCar.recharge_V, &myCar.recharge_target, NULL, NULL, NULL},
    {&myCar.Kp_position1, &myCar.Kd_position1, &myCar.Kp_position2, &myCar.Kd_position2, &myCar.Kp_position3,&myCar.Kd_position3,&myCar.Kp_position4, &myCar.Kd_position4, &myCar.Kp_position5,&myCar.Kd_position5},
    {&myCar.SpeedPA,&myCar.SpeedIA, &myCar.SpeedDA, &myCar.SpeedPB,&myCar.SpeedIB, &myCar.SpeedDB, NULL, NULL, NULL, NULL},
};

unsigned short int FlashPAGESector[PAGENUM][LINENUM]=
{
        {410,411,412,413,414,415,416,417,418,419},
        {420,421,422,423,424,425,426,427,428,429},
        {430,431,432,433,434,435,436,437,438,439},
        {440,441,442,443,444,445,446,447,448,449},
        {450,451,452,453,454,455,456,457,458,459},
        {460,461,462,463,464,465,466,467,468,469},
        {470,471,472,473,474,475,476,477,478,479},
        {480,481,482,483,484,485,486,487,488,489},
        {490,491,492,493,494,495,496,497,498,499},
        {500,501,502,503,504,505,506,507,508,509},
};      //920-979页，每一页存一个数据


/**********************拨码功能区*************************/
void DialInit()
{  
    DIAL_e dial = DIAL_MAX;//从最后一个拨码开始扫描
    while(dial--)
    {
        gpio_init(DIAL_PTxn[dial], GPI, 1, PULLDOWN);
    }
}

uint8  GetDial()//获取拨码状态
{
    uint8 Value = 0;
    DIAL_e dial = 4;//从最后一个拨码开始扫描
    while(dial--)
    {
        if(gpio_get(DIAL_PTxn[dial]) == 0)
        {
                Value |= 1 << dial;
        }
    }
    return Value;//返回拨码状态
}

/**********************按键功能区*************************/
void MyKeyInit()
{
    MYKEY_e myKey = MYKEY_MAX;
    while(myKey--)
    {
        gpio_init(MYKEY_PTxn[myKey], GPI, 1,PULLDOWN);
    }
}

MYKEY_STATE_e GetMyKey()//MYKEY_STATE_e
{
    MYKEY_STATE_e keyState=0;
    //MYKEY_STATE_e keyState = 0;
    if((gpio_get(MYKEY_PTxn[0]) == 0)||
       (gpio_get(MYKEY_PTxn[1]) == 0)||
       (gpio_get(MYKEY_PTxn[2]) == 0)||
       (gpio_get(MYKEY_PTxn[3]) == 0)||
       (gpio_get(MYKEY_PTxn[4]) == 0))
    {
        if(gpio_get(MYKEY_PTxn[0]) == 0)      keyState = LPRESS;//LPRESS;
        if(gpio_get(MYKEY_PTxn[1]) == 0)      keyState = RPRESS;//RPRESS;
        if(gpio_get(MYKEY_PTxn[2]) == 0)      keyState = UPRESS;//UPRESS;
        if(gpio_get(MYKEY_PTxn[3]) == 0)      keyState = DPRESS;//DPRESS;
        if(gpio_get(MYKEY_PTxn[4]) == 0)      keyState = MPRESS;//MPRESS;
    }
    else                                        keyState = ALLFREE;//ALLFREE;
    return keyState;
}

void KeyScan(int Period)//输入检测按键时长
{

        if(scanPeriod == Period)
        {
            keyValue = GetMyKey();
            //检测是否长按模式切换
            if((keyValue != ALLFREE) && (keyValue == keyValueLast))
            {
                if(++keySameTimes == (100/Period))
                {
                    if(  scanMode != 2)
                        scanMode++;
                    keySameTimes = 0;
                }
            }
            else
            {
                scanMode = 0;
                keySameTimes = 0;
            }
            //按键动作
            if(keyValue != ALLFREE)
            {
                IfxCpu_disableInterrupts();//关闭中断

                if(keyValue == MPRESS)
                {
                    if(lockValue == 1)//解除锁定后才会写入flash
                    {
                          eeprom_erase_sector(FLASHSECTOR);//擦除扇区
                          for(int j=0;j<10;j++)
                          {
                              for(int i = 0; i < 10; i++)
                              {
                                  if(uint32Value[j][i] != NULL)
                                  {
                                     eeprom_page_program(FLASHSECTOR, FlashPAGESector[j][i], uint32Value[j][i]);
                                  }
                                  else if(uint16Value[j][i]!=NULL)
                                  {
                                      (*F_uint32Value[j][i])=(uint32)((*uint16Value[j][i]));
                                      eeprom_page_program(FLASHSECTOR, FlashPAGESector[j][i], F_uint32Value[j][i]);
                                  }
                                  else if(uint8Value[j][i]!=NULL)
                                  {
                                      (*F_uint32Value[j][i])=(uint32)((*uint8Value[j][i]));
                                      eeprom_page_program(FLASHSECTOR, FlashPAGESector[j][i], F_uint32Value[j][i]);
                                  }
                                  else if(fValue[j][i]!=NULL)
                                  {
                                      (*F_uint32Value[j][i])=(uint32)((*fValue[j][i])*100);
                                      eeprom_page_program(FLASHSECTOR, FlashPAGESector[j][i], F_uint32Value[j][i]);
                                  }
                              }
                          }
                          lockValue = 0;
                    }
                    else
                    {
                          lockValue = 1;
                    }
                }
                if(keyValue == UPRESS)
                {
                    if(--lineValue == -1)
                    {
                        lineValue += LINENUM;
                    }
                }
                if(keyValue == DPRESS)
                {
                    if(++lineValue ==  LINENUM)
                    {
                        lineValue -= LINENUM;
                    }
                }
                if(lockValue == 1 && pageValue < 10)
                {
                    if(pageValue <= 6)//前3页显示int参数
                    {
                        if(uint32Value[pageValue][lineValue] != NULL)
                        {
                            if(keyValue == LPRESS)
                            {
                                (*(uint32Value[pageValue][lineValue]))--;
    //                          {
                                /***************************************************************/
                            }
                                /********！！！！！！！！！！！！！！！！！！！！！！！！！！！！**/
    //                              不能一次性对页里面所有元素一次性全部写入，因为此处没有NULL指针判断，如果页内有元素为NULL
    //                            eeprom_page_program函数对buf解引用时会出错，NULL指针无法解引用，会出错。
    //                            用到哪个元素就写入哪个元素
                             if(keyValue == RPRESS)
                            {
                                (*(uint32Value[pageValue][lineValue]))++;
                            }
                        }

                        else if(uint16Value[pageValue][lineValue] != NULL)
                        {
                            if(keyValue == LPRESS)
                            {
                                (*(uint16Value[pageValue][lineValue]))--;
    //                          {
                                /***************************************************************/
                            }
                            else if(keyValue == RPRESS)
                            {
                                (*(uint16Value[pageValue][lineValue]))++;
                            }
                        }

                        else if(uint8Value[pageValue][lineValue] != NULL)
                        {
                           if(keyValue == LPRESS)
                           {
                               (*(uint8Value[pageValue][lineValue]))--;
   //                          {
                               /***************************************************************/
                           }
                           if(keyValue == RPRESS)
                           {
                               (*(uint8Value[pageValue][lineValue]))++;
                           }
                        }
                    }
                    else//后面为float参数
                    {
                        if(fValue[pageValue][lineValue] != NULL)
                        {
                            if(keyValue == LPRESS)
                            {
                              //以前的学长用的是将浮点数乘100转为int类型存入，取出后除以100（保留两位小数），但偶有出现最后一位小数变动的情况，估计是跟浮点类型在单片机内部存储方式有关，所以我直接存浮点数，虽然第一次存入数据会有最后一位数的波动，后期还待检验
                                (*(fValue[pageValue][lineValue])) -= 0.01 * powf(10, (float)scanMode/2);
                            }
                            if(keyValue == RPRESS)
                            {
                                (*(fValue[pageValue][lineValue])) += 0.01 * powf(10, (float)scanMode/2);
                            }
                        }
                    }
                }
                else
                {
                    if(keyValue == LPRESS)
                    {
                        if(--pageValue == -1)
                        {
                            pageValue += PAGENUM + 2;
                        }
                    }
                    if(keyValue == RPRESS)
                    {
                        if(++pageValue == PAGENUM + 2)
                        {
                            pageValue -= PAGENUM + 2;
                        }
                    }
                    if(lockValue == 1)
                    {
                        lockValue = 0;
                    }
                }
            IfxCpu_enableInterrupts();//开启CPU总中断
            }
            scanPeriod = 0;
            keyValueLast = keyValue;
        }
//        if(mt9v03x_finish_flag)
//        {
//          if(pageValue==6)//一帧图像刷新一次，参数优先显示,防止卡屏
//         {
//          systick_start(STM0);
//          mt9v03x_finish_flag=0;
//          img_extract();
//          //g_centre_line=Camera_Analyze();
//          //Black_show();
//          Oled_Show_Camera(&image_cache[0][0],MT9V03X_W,MT9V03X_H);
//          aa=systick_getval(STM0);
//          oled_int16(5,6,aa);
//         }
//        }
}


/**********************UI功能区*************************/
void PageUI(int mode)
{
    int lineJump = 0;
    int pageTurn = 6 * (lineValue / 6);
    if(lockValue == 1)
        oled_p6x8str(0, 0, "PAGE#");
    else
        oled_p6x8str(0, 0, "PAGE ");
    oled_printf_int32(30, 0, pageValue, 2);

    for(int line = 0; line < 6; line++)
    {
        if((pageTurn + line) == LINENUM)
        {
            break;
        }
        if(mode == 0)
        {
            if(line == lineValue - pageTurn)
            {
                oled_p6x8str(0, line + 1, ">");
                oled_p6x8str(6, line + 1, valueName[pageValue][lineValue]);
                if(uint16Value[pageValue][line + pageTurn] == NULL)
                {
                    oled_printf_int32(90, line + 1, 0, 5);
                }
                else
                {
                    if(*uint16Value[pageValue][lineValue] >= 0)
                    {
                        oled_p6x8str(75, line + 1, " ");
                        oled_printf_int32(86, line + 1, *uint16Value[pageValue][lineValue], 5);
                    }
                    else
                    {
                        oled_p6x8str(75, line + 1, "-");
                        oled_printf_int32(86, line + 1, *uint16Value[pageValue][lineValue], 5);
                    }
                }

                lineJump = 1;
            }
            else
            {
                oled_p6x8str( 6, line + lineJump + 1, valueName[pageValue][line + pageTurn]);
                if(uint16Value[pageValue][line + pageTurn] == NULL)
                {
                    oled_p6x8str(75, line + lineJump + 1, " ");
                    oled_printf_int32(86, line + lineJump + 1, 0, 5);
                }
                else
                {
                    if(*uint16Value[pageValue][line + pageTurn] >= 0)
                    {
                        oled_p6x8str(84, line + lineJump + 1, " ");
                        oled_printf_int32(86, line + lineJump + 1, *uint16Value[pageValue][line + pageTurn], 5);
                    }
                    else
                    {
                        oled_p6x8str(84, line + lineJump + 1, "-");
                        oled_printf_int32(86, line + lineJump + 1, *uint16Value[pageValue][line + pageTurn], 5);
                    }
                }


            }
        }
        else if(mode == 1)
        {
            if(line == lineValue - pageTurn)
            {
                oled_p6x8str(0, line + 1, ">");
                oled_p6x8str( 8, line + 1, valueName[pageValue][lineValue]);
                if(fValue[pageValue][line + pageTurn] == NULL)
                {
                    oled_printf_int32(86, line + 1, 0, 5);
                }
                else
                {
                    oled_printf_float(86, line + 1, *fValue[pageValue][line + pageTurn], 3, 2);
                }
                lineJump = 1;
            }
            else
            {
                oled_p6x8str( 8, line + lineJump + 1, valueName[pageValue][line + pageTurn]);
                if(fValue[pageValue][line + pageTurn] == NULL)
                {
                    oled_printf_int32(86, line +lineJump+ 1, 0, 5);
                }
                else
                {
                    oled_printf_float(86, line + lineJump + 1, *fValue[pageValue][line + pageTurn], 3, 2);
                }

            }
        }
        else if(mode == 2)
        {
            if(line == lineValue - pageTurn)
            {
                oled_p6x8str(0, line + 1, ">");
                oled_p6x8str(6, line + 1, valueName[pageValue][lineValue]);
                if(uint8Value[pageValue][line + pageTurn] == NULL)
                {
                    oled_printf_int32(90, line + 1, 0, 5);
                }
                else
                {
                    if(*uint8Value[pageValue][lineValue] >= 0)
                    {
                        oled_p6x8str(75, line + 1, " ");
                        oled_printf_int32(86, line + 1, *uint8Value[pageValue][lineValue], 5);
                    }
                    else
                    {
                        oled_p6x8str(75, line + 1, "-");
                        oled_printf_int32(86, line + 1, *uint8Value[pageValue][lineValue], 5);
                    }
                }

                lineJump = 1;
            }
            else
            {
                oled_p6x8str( 6, line + lineJump + 1, valueName[pageValue][line + pageTurn]);
                if(uint8Value[pageValue][line + pageTurn] == NULL)
                {
                    oled_p6x8str(75, line + lineJump + 1, " ");
                    oled_printf_int32(86, line + lineJump + 1, 0, 5);
                }
                else
                {
                    if(*uint8Value[pageValue][line + pageTurn] >= 0)
                    {
                        oled_p6x8str(84, line + lineJump + 1, " ");
                        oled_printf_int32(86, line + lineJump + 1, *uint8Value[pageValue][line + pageTurn], 5);
                    }
                    else
                    {
                        oled_p6x8str(84, line + lineJump + 1, "-");
                        oled_printf_int32(86, line + lineJump + 1, *uint8Value[pageValue][line + pageTurn], 5);
                    }
                }


            }
        }
    }
}

uint8 dial = 0;
uint8 dial_last=0;
uint8 boma_flag=0;
void DebugUI()
{

    scanPeriod++;
//    dial_last = dial;


    switch(scanMode)
    {
        case 0:
            KeyScan(40);
            break;
        case 1:
            KeyScan(20);
            break;
        case 2:
            KeyScan(10);
            break;
    }
    if((pageValue != pageValueLast)||(lineValueLast != lineValue)||(lockValue != lockValueLast) )
    {
        oled_fill(0x00); //清屏
    }

    switch(pageValue)
    {
       case 0:                 //可改flash int类型参数
            PageUI(0);
            break;
        case 1:                 //可改flash int类型参数
            PageUI(2);
            break;
        case 2:                 //可改flash int类型参数
            PageUI(0);
            break;
        case 3:                 //可改flash float类型参数
            PageUI(0);
            break;
        case 4:                 //可改flash float类型参数
            PageUI(0);
            break;
        case 5:                 //可改flash float类型参数
            PageUI(0);
            break;
        case 6:                 //可改flash float类型参数
            PageUI(0);
            break;
        case 7:
            PageUI(1);
            break;
        case 8:
            PageUI(1);
            break;
        case 9:
            PageUI(1);
            break;
        case 10:
            oled_dis_bmp(64,128,ov7725_oled_bmp[0],0);
          break;
    default:break;
    }
//    if(mt9v03x_finish_flag)//一帧图像刷新一次，参数优先显示,防止卡屏
//   {
//      mt9v03x_finish_flag=0;
//   }
    lineValueLast = lineValue;
    pageValueLast = pageValue;
    lockValueLast = lockValue;

}


void dial_scan(void)
{
    dial = GetDial();
//    ips114_showint32(90,0,dial,3);
    if(dial != dial_last)
    {
        ips114_clear(GREEN); //清屏
    }
//            if(mt9v03x_finish_flag)//一帧图像刷新一次，参数优先显示,防止卡屏
//            {
//               mt9v03x_finish_flag=0;
//               Oled_Show_Camera(&image_cache[0][0],MT9V03X_W,MT9V03X_H);
//               oled_printf_int32(7,9,g_SpeedGet,3);//右最下为右后轮编码器获取值
//
//            }


//            if(mt9v03x_finish_flag)//一帧图像刷新一次，参数优先显示,防止卡屏
//            {
//               mt9v03x_finish_flag=0;
//               Oled_Show_Camera(&image_cache[0][0],MT9V03X_W,MT9V03X_H);
//               oled_printf_int32(7,9,g_SpeedGet,3);//右最下为右后轮编码器获取值
//               oled_printf_int32(5,3,abs(Road-g_centre_line),4);
//            }

//            oled_printf_int32(50,0,dial,3);

  if(dial == 0x00)
  {
//              oled_printf_int32(50,0,Threshold,3);
      ips114_displayimage032(mt9v03x_image[0],MT9V03X_W,MT9V03X_H);
      ips114_showstr(190,0,"Roltw");
      ips114_showfloat(190,1,Roltw,1,2);
      ips114_showstr(190,2,"Threshold");
      ips114_showint32(190,3,Threshold,3);
      ips114_showstr(190,4,"x");
      ips114_showint32(200,4,g_u8BeaconLocation,3);
      ips114_showstr(190,5,"y");
      ips114_showint32(200,5,g_u8Top,3);
      ips114_showstr(190,6,"Los");
      ips114_showint32(225,6,loseBeacon,2);
      ips114_showstr(225,7,"ms");
      ips114_showint32(0,7,Image_processing_time,5);


//      ips114_showstr(70,7,"width");
//      ips114_showint32(108,7,width,3);

//      ips114_displayimage032_zoom1(Pixle[0], MT9V03X_W, MT9V03X_H, MT9V03X_W,0,120,77);

//              oled_show_Infrared();
//              oled_show_position();
//              oled_show_gyroscope();
  }
  else if(dial == 0x01)
  {
      oled_show_Enclder();
      ips114_showint32(0,2,duty1,4);
      ips114_showstr(95,2,"duty");
      ips114_showint32(190,2,duty2,4);
      ips114_showstr(0,3,"error_x");
//      ips114_showint32(100,2,Image_processing_time,5);
      ips114_showint32(100,3,error_x,5);
//      oled_show_Pid();
      oled_show_base_speed();
      ips114_showint32(0,5,Left_inductance,4);
      ips114_showstr(95,5,"Inductive");
      ips114_showint32(190,5,Right_inductance,4);
      ips114_showstr(0,6,"average_inductance");
      ips114_showint32(190,6,average_inductance,3);
      ips114_showstr(0,7,"Inductive_error");
      ips114_showfloat(190,7,Inductive_error,1,2);



//              oled_ov7725_bmp(ov7725_oled_bmp[0], ov7725_uart_image_dec[0]);
//      oled_dis_bmp(MT9V03X_H,MT9V03X_W,Pixle[0],0 );
//              ips114_displayimage032(Pixle[0],MT9V03X_W,MT9V03X_H);
  }
  else if(dial == 0x02)
  {
        ips114_showstr(0,1,"Roltw");
        ips114_showfloat(90,1,Roltw,1,2);
        ips114_showstr(0,2,"Threshold");
        ips114_showint32(90,2,Threshold,3);
        ips114_showstr(0,3,"x");
        ips114_showint32(90,3,g_u8BeaconLocation,3);
        ips114_showstr(0,4,"y");
        ips114_showint32(90,4,g_u8Top,3);
        ips114_showstr(0,5,"GetBeacon");
        ips114_showint32(90,5,g_u8GetBeacon,2);
        ips114_showstr(0,6,"width");
        ips114_showint32(90,6,width,3);
        ips114_showstr(0,7,"car_state");
        ips114_showint32(90,7,car_state,3);

  }
  else if(dial == 0x04)
  {
      oled_show_gyroscope();
//              oled_show_pwm();
  }
  else if(dial == 0x08)
  {
      oled_printf_MT9V03X();
      ips114_showstr(0,4,"exposure_time");
      ips114_showint32(100,4,exposure_time_last,3);

  }
  else if(dial == 0x03)
  {
//              oled_printf_int32(50,0,Threshold,3);
//      ips114_displayimage032(mt9v03x_image[0],MT9V03X_W,MT9V03X_H);
      ips114_displayimage032(image_cache[0], MT9V03X_W, MT9V03X_H);
      ips114_showstr(190,0,"offset");
      ips114_showfloat(190,1,offset,2,2);
      ips114_showint32(190,3,voltage,4);
//      ips114_showstr(190,2,"Threshold");
//      ips114_showint32(190,3,Threshold,3);
//      ips114_showstr(190,4,"x");
//
//      ips114_showint32(190,5,g_u8BeaconLocation,3);
//      ips114_showstr(190,6,"y");
//      ips114_showint32(190,7,g_u8Top,3);
//      ips114_showstr(0,7,"GetBeacon");
//      ips114_showint32(210,6,g_u8GetBeacon,2);
//      ips114_showint32(0,6,g_u8Top_y1,3);
//      ips114_showint32(100,6,g_u8Top_y2,3);

//              oled_show_Infrared();
//              oled_show_position();
//              oled_show_gyroscope();
  }
  dial_last = dial;

  
}

void oled_show_code_switch(void)
{
    oled_printf_int32(60,0,dial ,1);
}






