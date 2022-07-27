#include "headfile.h"

// **************************** 全局变量 ****************************
int kflag = 0;

/**********************按键功能区*************************/
void PKeyInit(void) {
    gpio_init(P11_10, GPI, 1, PULLDOWN);
    gpio_init(P11_6, GPI, 1, PULLDOWN);
    gpio_init(P11_3, GPI, 1, PULLDOWN);
    gpio_init(Beep, GPO, Beep_off, PUSHPULL);
}

void OLED_UI(void) {

    if (kflag == 0) {
        oled_p6x8str(0, 0, "seekfree.taobao.com");//显示字符串
        oled_printf_float(50, 1, error, 2, 2);
        oled_p6x8str(0, 1, "error");
        oled_p6x8str(0, 2, "bench_v");
        oled_int16(50, 2, bench_v);

        oled_p6x8str(0, 3, "duty_err");
        oled_int16(50, 3, error_x);
        oled_p6x8str(0, 4, "duty_left");
        oled_int16(50, 4, duty_left);
        oled_p6x8str(0, 5, "duty_right");
        oled_int16(50, 5, duty_right);

        oled_p6x8str(0, 6, "L_enc");
        oled_int16(50, 6, encValue_1);
        oled_p6x8str(0, 7, "R_enc");
        oled_int16(50, 7, encValue_2);

    }
    if (kflag == 1) {
        oled_show_voltage();
        oled_p6x8str(0, 2, "R_ind");
//        oled_int16(50, 2, Right_inductance);
        oled_p6x8str(0, 3, "L_ind");
//        oled_int16(50, 3, Left_inductance);
        oled_p6x8str(0, 4, "ave_ind");
//        oled_int16(50, 4, average_inductance);

        oled_p6x8str(0, 5, "stop");
        oled_int16(50, 5, stop_sign);
        oled_p6x8str(0, 6, "mode");
        oled_int16(50, 6, car_mode);

    }
    if (kflag == 2) {
        oled_p6x8str(0, 0, "l100");
        oled_int16(80, 0, ls_std[100]);
        oled_p6x8str(0, 1, "l100");
        oled_int16(80, 1, leftline[100]);
        oled_p6x8str(0, 2, "r100");
        oled_int16(80, 2, rs_std[100]);
        oled_p6x8str(0, 3, "r100");
        oled_int16(80, 3, rightline[100]);
        oled_p6x8str(0, 4, "l50");
        oled_int16(80, 4, ls_std[50]);
        oled_p6x8str(0, 5, "l50");
        oled_int16(80, 5, leftline[50]);
        oled_p6x8str(0, 6, "r50");
        oled_int16(80, 6, rs_std[50]);
        oled_p6x8str(0, 7, "r50");
        oled_int16(80, 7, rightline[50]);
//        oled_p6x8str(0, 0, "part num");
//        oled_int16(80, 0, part_num);
//        oled_p6x8str(0, 1, "part type0");
//        oled_int16(80, 1, part_type[0]);
//        oled_p6x8str(0, 2, "part type1");
//        oled_int16(80, 2, part_type[1]);
//        oled_p6x8str(0, 3, "part type2");
//        oled_int16(80, 3, part_type[2]);
//        oled_p6x8str(0, 4, "img_mode");
//        oled_int16(80, 4, img_mode);
//        oled_p6x8str(0, 4, "l80");
//        oled_int16(80,4,leftline[80]);
//        oled_p6x8str(0, 5, "l1");
//        oled_int16(80, 5, l1);
//        oled_p6x8str(0, 6, "l2");
//        oled_int16(80, 6, l2);
//        oled_p6x8str(0, 7, "l3");
//        oled_int16(80, 7, l3);

//        oled_p6x8str(0, 5, "img_type");
//        oled_int16(80, 5, image_para.imgtype);
//        oled_p6x8str(0, 4, "leftline");
//        oled_int16(80, 4, leftline[65]);
//        oled_p6x8str(0, 5, "lstd");
//        oled_int16(80, 5, ls_std[65]);
//        oled_p6x8str(0, 6, "rightline");
//        oled_int16(80, 6, rightline[65]);
//        oled_p6x8str(0, 7, "rstd");
//        oled_int16(80, 7, rs_std[65]);
//        oled_p6x8str(0, 6, "yaw rate");
//        oled_int16(80, 6, yaw_rate);
//        oled_p6x8str(0, 6, "yaw");
//        oled_int16(80, 6, yaw);
//        oled_p6x8str(0, 6, "degree");
//        oled_int16(80, 6, degree);
        oled_p6x8str(0, 6, "enter");
        oled_int16(80, 6, enter_flag);
        oled_p6x8str(0, 7, "flag6");
        oled_int16(80, 7, type6_flag);
//        oled_p6x8str(0, 7, "bench");
//        oled_int16(80, 7, bench_v);
//        oled_p6x8str(0, 6, "p");
//        oled_int16(50, 6    , p);
//        oled_p6x8str(0, 7, "sl_cnt");
//        oled_int16(80, 7, starting_line_cnt);
//        oled_p6x8str(0, 6, "yaw rate");
//        oled_int16(80, 6, yaw_rate);
//        oled_p6x8str(0,6,"curv");
//        oled_printf_float(80, 6, cur_circle(0),1,3);
//        oled_p6x8str(0,7,"enter");
//        oled_int16(80, 7, enter_flag);
//        oled_p6x8str(0,8,"r1");
//        oled_int16(80, 8, rightline[100]);
    }

    if (gpio_get(P11_10) != 1) {
        kflag = 0;
        oled_fill(0x00);
        gpio_set(Beep, Beep_on);
        gpio_set(Beep, Beep_off);
    }
    if (gpio_get(P11_6) != 1) {
        kflag = 1;
        oled_fill(0x00);
        gpio_set(Beep, Beep_on);
        gpio_set(Beep, Beep_off);
    }
    if (gpio_get(P11_3) != 1) {
        kflag = 2;
        oled_fill(0x00);
        gpio_set(Beep, Beep_on);
        gpio_set(Beep, Beep_off);
    }

}
