/*
 * Car_Information.c
 *
 *  Created on: 2021年4月10日
 *      Author: Javelin
 */


#include "headfile.h"



void car_information_init(int mode)
{
      if(mode == 0)
      {
/*
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 */
          myCar.base_speed1 = 60;//基础速度
          myCar.base_speed2 = 60;//基础速度
//          myCar.Threshold_Error = 10;
          myCar.nolight_speed_high = 60;
          myCar.nolight_speed_low = 40;
          myCar.FlashHandle = 10;

          myThreshold.Threshold_0_4 = 40;
          myThreshold.Threshold_5_9 = 40;
          myThreshold.Threshold_10_14 = 40;
          myThreshold.Threshold_15_19 = 40;
          myThreshold.Threshold_20_24 = 40;
          myThreshold.Threshold_25_29 = 45;
          myThreshold.Threshold_30_34 = 50;
          myThreshold.Threshold_35_39 = 50;
          myThreshold.Threshold_40_44 = 50;
          myThreshold.Threshold_45_49 = 50;
          myThreshold.Threshold_50_54 = 50;
          myThreshold.Threshold_55_59 = 50;
          myThreshold.Threshold_60_64 = 50;

          L_Error.L_ERROR_1_5 = 5;
          L_Error.L_ERROR_6_10 = 5;
          L_Error.L_ERROR_11_15 = 5;
          L_Error.L_ERROR_16_20 = 5;
          L_Error.L_ERROR_21_25 = 15;
          L_Error.L_ERROR_26_30 = 25;
          L_Error.L_ERROR_31_35 = 29;
          L_Error.L_ERROR_36_40 = 39;
          L_Error.L_ERROR_41_45 = 45;
          L_Error.L_ERROR_46_50 = 50;
          L_Error.L_ERROR_51_55 = 55;
          L_Error.L_ERROR_56_60 = 57;
          L_Error.L_ERROR_61_65 = 60;

          R_Error.R_ERROR_1_5 = 5;
          R_Error.R_ERROR_6_10 = 5;
          R_Error.R_ERROR_11_15 = 5;
          R_Error.R_ERROR_16_20 = 5;
          R_Error.R_ERROR_21_25 = 15;
          R_Error.R_ERROR_26_30 = 25;
          R_Error.R_ERROR_31_35 = 29;
          R_Error.R_ERROR_36_40 = 39;
          R_Error.R_ERROR_41_45 = 45;
          R_Error.R_ERROR_46_50 = 50;
          R_Error.R_ERROR_51_55 = 55;
          R_Error.R_ERROR_56_60 = 57;
          R_Error.R_ERROR_61_65 = 60;



          myCar.Aspeed_kp = 0.75;      //角速度环kp
          myCar.Aspeed_kd = 0.10;     //角速度环kd
          myCar.Kp_Roll = 0;
          myCar.Kd_Roll = 0;

//          myCar.Kp_Radius = 6;
//          myCar.Ki_Radius = 0;
//          myCar.Kd_Radius = 0;


          myCar.SpeedPA = 55.36;  //可以
          myCar.SpeedIA = 1.10;//0.8;
          myCar.SpeedDA = 0;

          myCar.SpeedPB = 55.36;
          myCar.SpeedIB = 1.10;
          myCar.SpeedDB = 0;

          myCar.Kp_position1 = 0.12;
          myCar.Kd_position1 = 0.02;
          myCar.Kp_position2 = 0.14;
          myCar.Kd_position2 = 0.02;
          myCar.Kp_position3 = 0.16;
          myCar.Kd_position3 = 0.02;
          myCar.Kp_position4 = 0.18;
          myCar.Kd_position4 = 0.02;
          myCar.Kp_position5 = 0.20;
          myCar.Kd_position5 = 0.02;


//          myCar.Kp_Infrared=1.0;
//          myCar.Ki_Infrared=0;
//          myCar.Kd_Infrared=0;


      }
      else if(mode == 1)
      {
/*
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 */
          myCar.base_speed1 = 140;//基础速度
          myCar.base_speed2 = 100;//基础速度
          myCar.base_speed3 = 80;//基础速度
          myCar.base_speed4 = 80;//基础速度


          myThreshold.Threshold_0_4 = 7;
          myThreshold.Threshold_5_9 = 30;
          myThreshold.Threshold_10_14 = 25;
          myThreshold.Threshold_15_19 = 25;
          myThreshold.Threshold_20_24 = 30;
          myThreshold.Threshold_25_29 = 35;
          myThreshold.Threshold_30_34 = 40;
          myThreshold.Threshold_35_39 = 43;
          myThreshold.Threshold_40_44 = 46;
          myThreshold.Threshold_45_49 = 47;
          myThreshold.Threshold_50_54 = 50;
          myThreshold.Threshold_55_59 = 50;
          myThreshold.Threshold_60_64 = 50;

          myCar.exposure_time = 82;

          L_Error.L_ERROR_1_5 = 0;
          L_Error.L_ERROR_6_10 = 0;
          L_Error.L_ERROR_11_15 = 0;
          L_Error.L_ERROR_16_20 = 0;
          L_Error.L_ERROR_21_25 = 0;
          L_Error.L_ERROR_26_30 = 0;
          L_Error.L_ERROR_31_35 = 0;
          L_Error.L_ERROR_36_40 = 0;
          L_Error.L_ERROR_41_45 = 0;
          L_Error.L_ERROR_46_50 = 0;
          L_Error.L_ERROR_51_55 = 0;
          L_Error.L_ERROR_56_60 = 0;
          L_Error.L_ERROR_61_65 = 0;

          R_Error.R_ERROR_1_5 = 0;
          R_Error.R_ERROR_6_10 = 0;
          R_Error.R_ERROR_11_15 = 0;
          R_Error.R_ERROR_16_20 = 0;
          R_Error.R_ERROR_21_25 = 0;
          R_Error.R_ERROR_26_30 = 0;
          R_Error.R_ERROR_31_35 = 0;
          R_Error.R_ERROR_36_40 = 0;
          R_Error.R_ERROR_41_45 = 0;
          R_Error.R_ERROR_46_50 = 0;
          R_Error.R_ERROR_51_55 = 0;
          R_Error.R_ERROR_56_60 = 0;
          R_Error.R_ERROR_61_65 = 0;



          myCar.Aspeed_kp = 2.83;      //角速度环kp
          myCar.Aspeed_kd = 0.20;     //角速度环kd
          myCar.Kp_Roll = 0;
          myCar.Kd_Roll = 0;
          myCar.begin_V = 10.5;
          myCar.recharge_V = 5;
          myCar.recharge_V = 9;

          myCar.Kp_position1 = 1.35;
          myCar.Kd_position1 = 2.50;
          myCar.Kp_position2 = 1.34;
          myCar.Kd_position2 = 2.50;
          myCar.Kp_position3 = 1.35;
          myCar.Kd_position3 = 2.50;
          myCar.Kp_position4 = 1.35;
          myCar.Kd_position4 = 3;
          myCar.Kp_position5 = 1.35;
          myCar.Kd_position5 = 3;


//          myCar.Kp_Radius = 6;
//          myCar.Ki_Radius = 0;
//          myCar.Kd_Radius = 0;


          myCar.SpeedPA = 4.35;  //可以
          myCar.SpeedIA = 1.20;//0.8;
          myCar.SpeedDA = 0;

          myCar.SpeedPB = 4.35;
          myCar.SpeedIB = 1.20;
          myCar.SpeedDB = 0;




      }
      else if(mode == 3)
      {
/*
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 *              每一次flash改完参数这个地方的初始化一定要改成跟现在的一样
 *              止float里面的bug刷新flash！！！！！
 */
          myCar.base_speed1 = 200;//基础速度
          myCar.base_speed2 = 120;//基础速度
          myCar.base_speed3 = 80;//基础速度
          myCar.base_speed4 = 80;//基础速度


          myThreshold.Threshold_0_4=flash_read(FLASHSECTOR,420,uint8);
          myThreshold.Threshold_5_9 = flash_read(FLASHSECTOR,421,uint8);;
          myThreshold.Threshold_10_14 = 25;
          myThreshold.Threshold_15_19 = 25;
          myThreshold.Threshold_20_24 = 30;
          myThreshold.Threshold_25_29 = 35;
          myThreshold.Threshold_30_34 = 40;
          myThreshold.Threshold_35_39 = 43;
          myThreshold.Threshold_40_44 = 46;
          myThreshold.Threshold_45_49 = 47;


          myCar.exposure_time=flash_read(FLASHSECTOR,430,uint16);

          L_Error.L_ERROR_1_5 = 0;
          L_Error.L_ERROR_6_10 = 0;
          L_Error.L_ERROR_11_15 = 0;
          L_Error.L_ERROR_16_20 = 0;
          L_Error.L_ERROR_21_25 = 0;
          L_Error.L_ERROR_26_30 = 0;
          L_Error.L_ERROR_31_35 = 0;
          L_Error.L_ERROR_36_40 = 0;
          L_Error.L_ERROR_41_45 = 0;
          L_Error.L_ERROR_46_50 = 0;
          L_Error.L_ERROR_51_55 = 0;
          L_Error.L_ERROR_56_60 = 0;
          L_Error.L_ERROR_61_65 = 0;

          R_Error.R_ERROR_1_5 = 0;
          R_Error.R_ERROR_6_10 = 0;
          R_Error.R_ERROR_11_15 = 0;
          R_Error.R_ERROR_16_20 = 0;
          R_Error.R_ERROR_21_25 = 0;
          R_Error.R_ERROR_26_30 = 0;
          R_Error.R_ERROR_31_35 = 0;
          R_Error.R_ERROR_36_40 = 0;
          R_Error.R_ERROR_41_45 = 0;
          R_Error.R_ERROR_46_50 = 0;
          R_Error.R_ERROR_51_55 = 0;
          R_Error.R_ERROR_56_60 = 0;
          R_Error.R_ERROR_61_65 = 0;



          myCar.Aspeed_kp = 3.50;      //角速度环kp
          myCar.Aspeed_kd = 0.20;     //角速度环kd
          myCar.Kp_Roll = 0;
          myCar.Kd_Roll = 0;
          myCar.begin_V = ((float)flash_read(FLASHSECTOR,484,uint32))/100;
          myCar.recharge_V = ((float)flash_read(FLASHSECTOR,485,uint32))/100;;
          myCar.recharge_target = ((float)flash_read(FLASHSECTOR,486,uint32))/100;;

          myCar.Kp_position1 = 1.35;
          myCar.Kd_position1 = 1.00;
          myCar.Kp_position2 = 1.35;
          myCar.Kd_position2 = 1.00;
          myCar.Kp_position3 = 1.35;
          myCar.Kd_position3 = 1.00;
          myCar.Kp_position4 = 1.35;
          myCar.Kd_position4 = 1.00;
          myCar.Kp_position5 = 1.35;
          myCar.Kd_position5 = 1.00;


//          myCar.Kp_Radius = 6;
//          myCar.Ki_Radius = 0;
//          myCar.Kd_Radius = 0;


          myCar.SpeedPA = 4.25;  //可以
          myCar.SpeedIA = 1.85;//0.8;
          myCar.SpeedDA = 0;

          myCar.SpeedPB = 4.25;
          myCar.SpeedIB = 1.85;
          myCar.SpeedDB = 0;




      }
      else//第一次用flash读写模式需先用赋值模式，进DEBUG_UI擦写每个扇区将数据写入，再用flash模式就有初值了
      {
          int Flash_Addr_Now=410;//给定第一个参数所在的页，随后每一次读取加一页
          /*int类型参数读取*/
          myCar.base_speed1=flash_read(FLASHSECTOR,Flash_Addr_Now,sint16);Flash_Addr_Now++;
          myCar.base_speed2=flash_read(FLASHSECTOR,Flash_Addr_Now,sint16);Flash_Addr_Now++;
          myCar.base_speed3=flash_read(FLASHSECTOR,Flash_Addr_Now,sint16);Flash_Addr_Now++;
          myCar.base_speed4=flash_read(FLASHSECTOR,Flash_Addr_Now,sint16);Flash_Addr_Now++;

          Flash_Addr_Now = 420;
          myThreshold.Threshold_0_4=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_5_9=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_10_14=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_15_19=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_20_24=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_25_29=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_30_34=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_35_39=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_40_44=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          myThreshold.Threshold_45_49=flash_read(FLASHSECTOR,Flash_Addr_Now,uint8);Flash_Addr_Now++;
          Flash_Addr_Now = 430;
          myCar.exposure_time=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;

          Flash_Addr_Now = 440;

            L_Error.L_ERROR_1_5=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_6_10=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_11_15=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_16_20=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_21_25=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_26_30=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_31_35=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_36_40=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_41_45=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_46_50=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_51_55=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_56_60=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            L_Error.L_ERROR_61_65=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            Flash_Addr_Now = 460;
            R_Error.R_ERROR_1_5=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_6_10=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_11_15=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_16_20=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_21_25=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_26_30=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_31_35=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_36_40=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_41_45=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_46_50=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_51_55=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_56_60=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            R_Error.R_ERROR_61_65=flash_read(FLASHSECTOR,Flash_Addr_Now,uint16);Flash_Addr_Now++;
            Flash_Addr_Now=480;
//          myCar.threshold=flash_read(FLASHSECTOR,Flash_Addr_Now,uint32);Flash_Addr_Now++;
//            Flash_Addr_Now=480;
            myCar.Aspeed_kp=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
            myCar.Aspeed_kd=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
            myCar.Kp_Roll=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
            myCar.Kd_Roll=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
            myCar.begin_V=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
            myCar.recharge_V=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
            myCar.recharge_target=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
//            myCar.Kp_Radius=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
//            myCar.Ki_Radius=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
//            myCar.Kd_Radius=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          Flash_Addr_Now=490;
          /* float类型参数*/
          myCar.Kp_position1=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kd_position1=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kp_position2=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kd_position2=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kp_position3=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kd_position3=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kp_position4=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kd_position4=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kp_position5=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.Kd_position5=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          Flash_Addr_Now=500;
          myCar.SpeedPA=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.SpeedIA=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.SpeedDA=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          Flash_Addr_Now=506;
          myCar.SpeedPB=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.SpeedIB=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;
          myCar.SpeedDB=((float)flash_read(FLASHSECTOR,Flash_Addr_Now,uint32))/100;Flash_Addr_Now++;


      }
}

