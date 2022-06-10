#include "Camera.h"//黑色为0白色为1
#include "headfile.h"

uint8 break_hangshu;
uint8 centerline[120];
uint8 leftline[120];
uint8 rightline[120];
uint8 leftfindflag[120];  //用来标记左黑线是否找到
uint8 rightfindflag[120];
uint8 road_width[120];
uint8 road_type[120];
uint8 part_type[MT9V03X_H];         //分段类型
uint8 part_index[MT9V03X_H];        //分段终点下标
uint8 part_num;
uint8 img_mode = 0;
uint8 start = 1;
uint8 cirsud_i;                     //环岛入环时的特殊点i坐标，特殊点为环岛外边界与直道边界的交点（此交点有两个，此处指入环时的点）
float error = 0;                    //位置环偏移量
uint8 break_flag = 0;
uint8 FOK_OUT_FLAG_1 = 0;
uint8 FOK_OUT_FLAG_2 = 0;
uint8 FOK_S3_FLAG = 0;
uint8 flag = 0;
int max = 93;
int min = 93;
uint8 old = 93;
uint8 i, j;
float offset_S5 = 0;                //环岛S5阶段的开环偏差值
float weight_S5 = 0;                //环岛S5阶段的开环偏差累加计数，offset_S5/weight_S5为真正的偏差值
uint8 code_mode = 1;
uint8 upside = 0;                   //三岔S3阶段的判别点
int a = 0;
uint8 S3S4_flag = 0;                //环岛S3到S4阶段的标志位，当值为1时说明从S3跳到S4的那一帧
int degree = 0;

int yaw_last = 0;
uint8 CURSE_OFFSET_1 = 0;           //弯道的固定偏差，用于在弯道时调整车模位置
uint8 UPSIDE_M = 39;                //主机的upside阈值，当upside大于其时，三岔从S2阶段进入S3
uint8 UPSIDE_S = 41;                //从机的upside阈值
uint8 last;
float offset = 0;
image_parameter image_para;
uint8 ls_std[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 37, 38, 39, 39, 40, 40, 40, 41, 42, 43, 44, 46, 46, 46, 47, 47,
                  48,
                  49, 49, 50, 50, 51, 52, 52, 53, 53, 54, 54, 55, 55, 55, 56, 57, 57, 58, 58, 59, 59, 60, 61, 61, 61,
                  62, 63, 63, 63, 64, 64, 66, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71, 71, 72, 73, 74, 74, 74,
                  74, 74, 75, 77, 77, 77, 78, 78, 78, 79, 79, 80};
uint8 rs_std[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 108, 109, 109, 110, 110, 110, 111, 112, 112, 113, 114, 114, 115, 115,
                  115, 115, 116, 117, 117, 117, 118, 118, 120, 120, 121, 121, 122, 122, 123, 123, 123, 124, 125, 125,
                  125, 126, 126, 127, 127, 127, 128, 128, 129, 130, 130, 131, 131, 131, 132, 133, 133, 134, 134, 135,
                  135, 135, 135, 136, 137, 137, 138, 139, 139, 140, 141, 141, 141, 141, 142, 143, 143, 144, 145, 145,
                  145, 146, 146, 147, 148, 148};

void Basic_line_scan(void) {

    for (j = MT9V03X_H - 1; j > 10; j--) {
        leftfindflag[j] = 0;  //用来标记左黑线是否找到
        rightfindflag[j] = 0;
        centerline[j] = 0;
        leftline[j] = 0;
        rightline[j] = 187;
        road_width[j] = 0;
        road_type[j] = 0;
        part_type[MT9V03X_H] = 0;         //分段类型
        part_index[MT9V03X_H] = 0;        //分段终点下标
        part_num = 0;
        break_hangshu = 0;
    }

    for (j = MT9V03X_H - 1; j > 10; j--) {
        for (i = (uint8) old; i >= 0 && i < MT9V03X_W - 1; i++) {
            road_width[j]++;
            if (image_cache[j][i + 1] == 0 && image_cache[j][i] == 0) {
                rightfindflag[j] = 1;
                rightline[j] = (uint8) (i + 1);
                break;
            }

        }
        for (i = (uint8) old; i <= MT9V03X_W && i > 1; i--) {
            road_width[j]++;
            if (image_cache[j][i - 1] == 0 && image_cache[j][i] == 0) {
                leftfindflag[j] = 1;
                leftline[j] = (uint8) (i - 1);
                break;
            }
        }

        centerline[j] = (uint8) ((leftline[j] + rightline[j]) / 2);
        if ((image_cache[j][centerline[j]]) == 0 && (image_cache[j - 1][centerline[j]]) == 0) {
            break_hangshu = j;
            if (break_hangshu <= MT9V03X_H - 21)    //防止在一开始就break
            {
                if (img_mode != 2) { break; }
                else { break_flag = 1; }
            }
        }
        if (img_mode == 0 || img_mode == 1) {
            old = centerline[j];
        } else if (image_para.imgtype == RCIR_W_S2 || image_para.imgtype == RCIR_W_S2_5 ||
                   image_para.imgtype == RCIR_W_S3 || image_para.imgtype == RCIR_W_S6 ||
                   image_para.imgtype == RCIR_W_S7 || image_para.imgtype == LCIR_W_S4 ||
                   image_para.imgtype == LCIR_W_S5) {
            old = leftline[j] + 10;

        } else if (image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
                   image_para.imgtype == LCIR_W_S3 || image_para.imgtype == LCIR_W_S6 ||
                   image_para.imgtype == LCIR_W_S7 || image_para.imgtype == RCIR_W_S4 ||
                   image_para.imgtype == RCIR_W_S5) {
            old = rightline[j] - 10;
        } else if (img_mode == 3) {
            old = rightline[j] - 10;
        }
    }


    for (j = MT9V03X_H - 1; j > 10; j--) {
        if (leftfindflag[j] == 0 && rightfindflag[j] == 1) {
            road_type[j] = 1;
        }
        if (leftfindflag[j] == 1 && rightfindflag[j] == 0) {
            road_type[j] = 2;

        }
        if (leftfindflag[j] == 0 && rightfindflag[j] == 0) {
            road_type[j] = 3;
            //enter_flag=4;
        }
    }
    old = centerline[MT9V03X_H - 1];
    Pixle_ADD_My_Midline();
    Pixle_ADD_My_hengxian(10);
    Pixle_ADD_My_hengxian(30);
    Pixle_ADD_My_hengxian(50);
    Pixle_ADD_My_hengxian(85);
    Pixle_ADD_My_hengxian(70);
}//初次扫线完毕，将old重新赋值


void Advanced_line_scan(void) {
    Basic_line_scan();
    uint8 i;
    float dl, dr;           //相对于上一行的左右边界变化，注意i值从大到小变化
    uint8 w_min;            //之前行的最小宽度
    uint8 dw[MT9V03X_H];    //相对于上一行的行宽度变化
    uint8 flag_sud = 0;     //突变的标志

    w_min = 130;

    for (i = MT9V03X_H - 2; i >= 10; i -= 1) {
        if (road_type[i] != -1) {
            if (road_width[i] < w_min && i > 10)          //更新最小行宽度
                w_min = road_width[i];
            else if (i % 2 == 0)                          //行数越往上，宽度逐渐减小，因此需要手动减少行宽度
                w_min -= 1;

            dw[i] = road_width[i] - road_width[i + 1];        //与上一行的宽度差
            dl = leftline[i] - leftline[i + 1];             //与上一行的左边界差距
            dr = rightline[i] - rightline[i + 1];           //与上一行的左边界差距

            //开始判断类型
            if (image_para.imgtype == LCIR_W_S2_5 || image_para.imgtype == LCIR_W_S3) {
                if (flag_sud == 0 && dr <= NSUD_TH && dr >= -SSUD_TH &&
                    dl >= 3 * SSUD_TH) //7类型表示左边界向内突变，从特殊情况突变为正常左边界，说明突变点为入环的特殊点
                {
                    road_type[i] = 7;
                    flag_sud = 7;
                } else if (flag_sud == 7 && dl < SSUD_TH && dl > -SSUD_TH && dr <= NSUD_TH && dr >= -SSUD_TH)
                    road_type[i] = 7;
                else if (flag_sud == 0 && dr <= NSUD_TH && dr >= -SSUD_TH &&
                         dl <
                         -SSUD_TH)  //0突变到5说明出现了误判，此时要用flag_sud记录好突变发生过了，当回到正常值时5会变为0，从而消除因为图像某一行的边界错误导致最终的错误
                {
                    road_type[i] = 5;
                    flag_sud = 5;
                } else if (flag_sud == 5 && dl < SSUD_TH && dl > -SSUD_TH)
                    road_type[i] = 5;
                else if (flag_sud == 5 && dl > SSUD_TH) {
                    road_type[i] = 0;
                    flag_sud = 0;
                } else {
                    road_type[i] = 0;
                    flag_sud = 0;
                }
            } else if (image_para.imgtype == RCIR_W_S2_5 || image_para.imgtype == RCIR_W_S3) {
                if (flag_sud == 0 && dl <= SSUD_TH && dl >= -NSUD_TH && dr <= -4 * SSUD_TH) {
                    road_type[i] = 8;
                    flag_sud = 8;
                } else if (flag_sud == 8 && dr < SSUD_TH && dr > -SSUD_TH && dl <= SSUD_TH && dl >= -NSUD_TH)
                    road_type[i] = 8;
                else if (flag_sud == 0 && dl <= SSUD_TH && dl >= -NSUD_TH && dr > SSUD_TH) {
                    road_type[i] = 6;
                    flag_sud = 6;
                } else if (flag_sud == 6 && dr < SSUD_TH && dr > -SSUD_TH)
                    road_type[i] = 6;
                else if (flag_sud == 6 && dr < -SSUD_TH) {
                    road_type[i] = 0;
                    flag_sud = 0;
                } else {
                    road_type[i] = 0;
                    flag_sud = 0;
                }
            }
                //正常模式下 的图像行类型判断
            else {
                if ((dw[i] > SUD_TH && dl < -SSUD_TH && dr > NSUD_TH) ||
                    (dw[i] > SUD_TH && dl < -NSUD_TH && dr > SSUD_TH))  //表示左边突变了，右边边界还向右走，类似斜入十字，说明此行是3类型
                {
                    road_type[i] = 3;
                    flag_sud = 3;
                } else if (road_type[i] == 3 || (road_type[i] == 1 && dr > SSUD_TH && flag_sud == 0) ||
                           (road_type[i] == 2 && dl < -SSUD_TH && flag_sud == 0)) {
                    road_type[i] = 3;
                    flag_sud = 3;
                } else if (dl < -SSUD_TH && dr < NSUD_TH && flag_sud == 0) {
                    road_type[i] = 5;
                    flag_sud = 5;
                } else if (dr > SSUD_TH && dl > -NSUD_TH && flag_sud == 0) {
                    road_type[i] = 6;
                    flag_sud = 6;
                } else if (flag_sud == 5 && dl < 5 && dl > -5 && dr < NSUD_TH && road_width[i] > w_min) {
                    road_type[i] = 5;
                } else if (flag_sud == 6 && dr < 5 && dr > -5 && dl > -NSUD_TH && road_width[i] > w_min) {
                    road_type[i] = 6;
                } else if (flag_sud == 5 && dl < NSUD_TH && dl > -NSUD_TH && dr >= NSUD_TH) {
                    road_type[i] = 3;
                    flag_sud = 3;
                } else if (flag_sud == 6 && dr < NSUD_TH && dr > -NSUD_TH && dl <= -NSUD_TH) {
                    road_type[i] = 3;
                    flag_sud = 3;
                } else if (flag_sud == 3 && dr < SSUD_TH && dr > -SSUD_TH && dl < SSUD_TH && dl > -SSUD_TH &&
                           road_width[i] > w_min) {
                    road_type[i] = 3;
                } else if (flag_sud == 3 && (dr < -SSUD_TH || dl > SSUD_TH || road_width[i] < w_min) &&
                           road_type[i] == 0) {
                    flag_sud = 0;
                } else if ((flag_sud == 3) && (((dl > -NSUD_TH && dl < NSUD_TH) && dr <= -SSUD_TH) ||
                                               (road_type[i] == 1 && road_width[i] <= w_min))) {
                    road_type[i] = 5;
                    flag_sud = 5;
                } else if ((flag_sud == 3) && (((dr > -NSUD_TH && dr < NSUD_TH) && dl >= SSUD_TH) ||
                                               (road_type[i] == 2 && road_width[i] <= w_min))) {
                    road_type[i] = 6;
                    flag_sud = 6;
                } else if (flag_sud == 5 && (dl > 15 || road_width[i] < w_min)) {
                    flag_sud = 0;
                } else if (flag_sud == 6 && (dr < -15 || road_width[i] < w_min)) {
                    flag_sud = 0;
                } else if (dl <= 0 && dl >= -SSUD_TH && dr >= 0 && dr <= SSUD_TH && flag_sud == 0 &&
                           dw[i] > 0)   //判断为两边边界在发散，但不是突变的情况，说明是三岔类型
                {
                    road_type[i] = 4;
                }
            }
        }
    }

    //滤波算法，把单行及双行的误判去掉
    for (i = MT9V03X_H - 2; i >= 1; i--) {
        if (road_type[i - 1] == road_type[i + 1] && road_type[i - 2] == road_type[i + 1] &&
            road_type[i] != road_type[i + 1]) {
            road_type[i] = road_type[i + 1];
        }
        if (road_type[i + 1] == road_type[i - 2] && road_type[i + 1] == road_type[i - 3] &&
            road_type[i] != road_type[i + 1] && road_type[i - 1] != road_type[i + 1])//若这一行是误判
        {
            road_type[i] = road_type[i + 1];
            road_type[i - 1] = road_type[i + 1];
        }
    }
}

void Boundary_part(void) {
    Advanced_line_scan();
    int16 i;
    int16 part_i, part_flag, part_mi;   //part_i为此时的part_type的下标，part_flag为此行类型，part_mi为和并后的下标
    int16 partcnt;                      //同种类的行计数

    //分段类型判断
    part_i = 0;
    part_flag = road_type[MT9V03X_H - 1];
    partcnt = 1;

    for (i = MT9V03X_H - 1; i > 10; i -= 1) {
        if (part_flag == road_type[i])
            partcnt += 1;
        else {
            if (partcnt > C_TH) {
                part_type[part_i] = part_flag;
                part_index[part_i] = i + 1;
                part_i += 1;
                part_flag = road_type[i];
                partcnt = 1;
            } else {
                part_flag = road_type[i];
                partcnt = 1;
            }
        }
    }
    if (partcnt > C_TH) {
        part_type[part_i] = part_flag;
        part_index[part_i] = i + 1;
        part_num = part_i + 1;
    } else {
        part_num = part_i;
        part_index[part_i - 1] = i + 1;
    }

    //边界分段合并，因为以上计算出的赛道分段可能会出现相同类型的两段连续出现的情况，比如0，0，1，此时要把这合并起来
    part_mi = 1;
    for (part_i = 1; part_i < part_num; part_i += 1) {
        if (part_type[part_i] == part_type[part_mi - 1])
            part_index[part_mi - 1] = part_index[part_i];
        else {
            part_type[part_mi] = part_type[part_i];
            part_index[part_mi] = part_index[part_i];
            part_mi += 1;
        }
    }
    part_num = part_mi;

}


float angle_caculate(float x1, float y1, float x2, float y2, float x3, float y3) {
    float cosA2;

    y1 = 2.115 * y1;
    y2 = 2.115 * y2;
    y3 = 2.115 * y3;
    cosA2 = ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1)) * ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1)) /
            (((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) * ((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)));

    return cosA2;
}

float cur_circle(uint8 m) {
    uint8 i;
    uint8 a = 50, b = 35, c = 15;//所选三行的初始值
    uint8 num = 0;
    float cur = 0;

    if (m == 0) {
        for (i = 0; i <= 5; i++) {
            if ((road_type[b + i] == 0 || road_type[b + i] == 2 || road_type[b + i] == 4 ||
                 road_type[b + i] == 6) &&
                (road_type[a + i] == 0 || road_type[a + i] == 2 || road_type[a + i] == 4 ||
                 road_type[a + i] == 6) &&
                (road_type[c + i] == 0 || road_type[c + i] == 2 || road_type[c + i] == 4 ||
                 road_type[c + i] == 6)) {
                num += 1;
                cur += angle_caculate(leftline[b + i], b + i, leftline[a + i], a + i, leftline[c + i], c + i);
            }
        }
    }
    if (m == 1) {
        for (i = 0; i <= 5; i++) {
            if ((road_type[b + i] == 0 || road_type[b + i] == 1 || road_type[b + i] == 4 ||
                 road_type[b + i] == 5) &&
                (road_type[a + i] == 0 || road_type[a + i] == 1 || road_type[a + i] == 4 ||
                 road_type[a + i] == 5) &&
                (road_type[c + i] == 0 || road_type[c + i] == 1 || road_type[c + i] == 4 ||
                 road_type[c + i] == 5)) {
                num += 1;
                cur += angle_caculate(rightline[b + i], b + i, rightline[a + i], a + i, rightline[c + i],
                                      c + i);
            }
        }
    }

    if (num == 0)
        return 0;
    else
        return cur / num;
}

void image_distinguish(void) {
    image_type img_type = none;         //默认种类为none

    //出库结束且识别模式为0时
    if (img_mode == 0 && start == 1) {
        //当赛道的分段数为1时
        if (part_num == 1) {
            if (part_type[0] == 3)       //出现3种类，说明是十字路口S1阶段
                img_type = CRS_W_S1;
            else if (part_type[0] == 0)  //出现0种类，说明是直道或小弯
                img_type = STR_W;
        }
            //当赛道的分段数为2时
        else if (part_num == 2) {
            if (part_type[0] == 0 && part_type[1] == 3)      //出现先直道0然后空白区域3，说明前方是十字路口S1阶段
                img_type = CRS_W_S1;
            else if (part_type[0] == 3 && part_type[1] == 0) //出现先空白区域3后直道0，说明前方是出十字的S2阶段
                img_type = CRS_W_S2;
            else if (part_type[0] == 0 && part_type[1] == 5 &&
                     cur_circle(1) >= CUR_CIRTH)   //如果出现先0然后左边界突变5并且右边是直的边界，说明是预进入左环岛
            {
                img_type = LCIR_W_S1;

                img_mode = 1;           //预进入环岛模式，修改图像识别模式为1

            } else if (part_type[0] == 0 && part_type[1] == 6 &&
                       cur_circle(0) >= CUR_CIRTH)   //如果出现先0然后右边界突变6并且左边是直的边界，说明是预进入右环岛
            {
                img_type = RCIR_W_S1;

                img_mode = 1;           //预进入环岛模式，修改图像识别模式为1

            } else if (part_type[0] == 0 && part_type[1] == 4 &&
                       part_index[0] - part_index[1] > 10) //如果出现了先0后双边界发散4并且发散长度超过10行，说明看到了三岔S1阶段
            {
                img_type = FOK_W_S1;
                flag = 1;
                img_mode = 3;           //三岔模式，修改图像识别模式为3
            }
        }
            //当赛道的分段数大于等于3时
        else {
            if (part_type[0] == 0 && part_type[1] == 3)
                img_type = CRS_W_S1;
            else if (part_type[0] == 0 && (part_type[1] == 5 || part_type[1] == 6) &&
                     part_type[2] == 3) //这是斜入十字的情形
                img_type = CRS_W_S1;
            else if (part_type[0] == 3 && part_type[1] == 0)
                img_type = CRS_W_S2;
            else if (part_type[0] == 3 && (part_type[1] == 5 || part_type[1] == 6) &&
                     part_type[2] == 0) //这是斜出十字的情形
                img_type = CRS_W_S2;
            else if (part_type[0] == 0 && part_type[1] == 5 && cur_circle(1) >= CUR_CIRTH) {
                img_type = LCIR_W_S1;

                img_mode = 1;

            } else if (part_type[0] == 0 && part_type[1] == 6 && cur_circle(0) >= CUR_CIRTH) {
                img_type = RCIR_W_S1;

                img_mode = 1;

            } else if (part_type[1] == 0 && part_type[2] == 5 && cur_circle(1) >= CUR_CIRTH) {
                img_type = LCIR_W_S1;

                img_mode = 1;

            } else if (part_type[1] == 0 && part_type[2] == 6 && cur_circle(0) >= CUR_CIRTH) {
                img_type = RCIR_W_S1;

                img_mode = 1;

            } else if (part_type[0] == 0 && part_type[1] == 4 && part_index[0] - part_index[1] > 10) {
                img_type = FOK_W_S1;
                img_mode = 3;
            } else if ((part_type[0] == 1 || part_type[0] == 2) && part_type[1] == 0 && part_type[2] == 4 &&
                       part_index[0] - part_index[1] > 10) {
                img_type = FOK_W_S1;
                img_mode = 3;
            }
        }
    }

        //当图像识别模式为1（环岛预识别）且已经出库
    else if (img_mode == 1 && start == 1) {
        if (part_num == 1) {
            if (part_type[0] == 0) {
                img_type = STR_W;
                img_mode = 0;           //表示前方并不是环岛，需要退出1模式，返回0模式
            } else if (part_type[0] == 3) {
                img_type = CRS_W_S1;
                img_mode = 0;
            } else if (part_type[0] == -1) {
                img_type = none;
                img_mode = 0;
            }
        } else if (part_num == 2) {
            if (part_type[0] == 0 && part_type[1] == 5)
                img_type = LCIR_W_S1;
            else if (part_type[0] == 0 && part_type[1] == 6)
                img_type = RCIR_W_S1;
            else if (part_type[1] == 0 && part_type[2] == 5)
                img_type = LCIR_W_S1;
            else if (part_type[1] == 0 && part_type[2] == 6)
                img_type = RCIR_W_S1;
            else if (part_type[0] == 0 && (part_type[1] == 1 || part_type[1] == 2)) {
                img_type = CUR_W;
                img_mode = 0;
            } else if (part_type[0] == 0 && part_type[1] == 3) {
                img_type = CRS_W_S1;
                img_mode = 0;
            } else if (part_type[0] == 0 && part_type[1] == 4 && part_index[0] - part_index[1] > 10) {
                img_type = FOK_W_S1;
                img_mode = 3;
            } else if (part_type[0] == 1 && part_type[1] == 0) //这是入环的一个必经阶段，当在1模式下看到此阶段，说明确认进入环岛
            {
                img_type = LCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;       //进入环岛S2阶段后将特殊点清零，进行S3阶段的搜索（期间还会经过一个S2_5阶段，为防止错误进入S3阶段）
            } else if (part_type[0] == 5 && part_type[1] == 0) {
                img_type = LCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;
            } else if (part_type[0] == 2 && part_type[1] == 0) {
                img_type = RCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;
            } else if (part_type[0] == 6 && part_type[1] == 0) {
                img_type = RCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;
            } else if (part_type[0] == -1) {
                img_type = none;
                img_mode = 0;
            }
        } else {
            if (part_type[0] == 0 && part_type[1] == 3) {
                img_type = CRS_W_S1;
                img_mode = 0;
            } else if (part_type[0] == 0 && (part_type[1] == 5 || part_type[1] == 6) && part_type[2] == 3) {
                img_type = CRS_W_S1;
                img_mode = 0;
            } else if (part_type[0] == 3 && part_type[1] == 0) {
                img_type = CRS_W_S2;
                img_mode = 0;
            } else if (part_type[0] == 3 && (part_type[1] == 5 || part_type[1] == 6) && part_type[2] == 0) {
                img_type = CRS_W_S2;
                img_mode = 0;
            } else if (part_type[0] == 0 && part_type[1] == 5)
                img_type = LCIR_W_S1;
            else if (part_type[0] == 0 && part_type[1] == 6)
                img_type = RCIR_W_S1;
            else if (part_type[1] == 0 && part_type[2] == 5)
                img_type = LCIR_W_S1;
            else if (part_type[1] == 0 && part_type[2] == 6)
                img_type = RCIR_W_S1;
            else if (part_type[0] == 0 && part_type[1] == 4 && part_index[0] - part_index[1] > 10) {
                img_type = FOK_W_S1;
                img_mode = 3;
            } else if ((part_type[0] == 1 || part_type[0] == 2) && part_type[1] == 4 &&
                       part_index[0] - part_index[1] > 10) {
                img_type = FOK_W_S1;
                img_mode = 3;
            } else if (part_type[0] == 1 && part_type[1] == 0) {
                img_type = LCIR_W_S2;
                img_mode = 2;
            } else if (part_type[0] == 2 && part_type[1] == 0) {
                img_type = RCIR_W_S2;
                img_mode = 2;
            } else if (part_type[0] == -1) {
                img_type = none;
                img_mode = 0;
            }
        }
    }
        //当图像识别模式为2（环岛）且已经出库
    else if (img_mode == 2 && start == 1) {
        if (image_para.imgtype == LCIR_W_S2 &&
            part_type[0] == 0)    //当在S2阶段后看到直道，说明行使到环岛直道的中间，可以进入S3阶段了，因此设置了S2_5的过渡阶段
        {
            img_type = LCIR_W_S2_5;
        } else if (image_para.imgtype == LCIR_W_S2_5 && part_num >= 2 && part_type[0] == 0 &&
                   part_type[1] == 7)           //当出现7阶段时，说明已经可以看到环外的直道了，此时可以根据7阶段的出现点确定其为特殊点，并利用此点补线
        {
            img_type = LCIR_W_S3;
        } else if (image_para.imgtype == RCIR_W_S2 && part_type[0] == 0) {
            img_type = RCIR_W_S2_5;
        } else if (image_para.imgtype == RCIR_W_S2_5 && part_num >= 2 && part_type[0] == 0 &&
                   part_type[1] == 8) {
            img_type = RCIR_W_S3;
        } else if (image_para.imgtype == LCIR_W_S3 && ((part_type[1] == 7 && part_index[0] >= 45) ||
                                                       part_type[0] == 7))   //当三阶段特殊点很低时，说明车身即将进入环内，设置为环内S4阶段
        {
            img_type = LCIR_W_S4;
            S3S4_flag = 1;          //说明是进入S4阶段的第一帧，需要进行特殊处理
        } else if (image_para.imgtype == RCIR_W_S3 &&
                   ((part_type[1] == 8 && part_index[0] >= 45) || part_type[0] == 8)) {
            img_type = RCIR_W_S4;
            S3S4_flag = 1;
        } else if (image_para.imgtype == LCIR_W_S4 && part_num == 2 &&
                   (part_type[1] == 3 || part_type[1] == 6) && degree > 13000)    //利用陀螺仪与图像，当转过一般的角度，且能看到出环的图像时，置为S5阶段
        {
            img_type = LCIR_W_S5;
        } else if (image_para.imgtype == LCIR_W_S4 && part_num >= 3 &&
                   (part_type[1] == 3 || part_type[1] == 6 || part_type[2] == 3 || part_type[2] == 6) &&
                   degree > 13000) {
            img_type = LCIR_W_S5;
        } else if (image_para.imgtype == RCIR_W_S4 && part_num == 2 &&
                   (part_type[1] == 3 || part_type[1] == 5)) {
            img_type = RCIR_W_S5;
        } else if (image_para.imgtype == RCIR_W_S4 && part_num >= 3 &&
                   (part_type[1] == 3 || part_type[1] == 5 || part_type[2] == 3 || part_type[2] == 5)) {
            img_type = RCIR_W_S5;
        } else if (image_para.imgtype == LCIR_W_S5 && degree > 13000)        //当转过几乎一周的角度时，认为以及出环，设置此时为S6阶段
        {
            img_type = LCIR_W_S6;
        } else if (image_para.imgtype == RCIR_W_S5) {
            img_type = RCIR_W_S6;
        } else if (image_para.imgtype == LCIR_W_S6 && part_num >= 2 &&
                   (part_type[0] == 1 || part_type[0] == 5) &&
                   part_type[1] == 0)  //当S6阶段行使到第二次入环位置时，不能入环了，需要置为环岛的S7阶段，用来彻底驶出环岛
        {
            img_type = LCIR_W_S7;
        } else if (image_para.imgtype == RCIR_W_S6 && part_num >= 2 &&
                   (part_type[0] == 2 || part_type[0] == 6) &&
                   part_type[1] == 0) {
            img_type = RCIR_W_S7;
        } else if (image_para.imgtype == LCIR_W_S7 &&
                   (part_type[0] == 0 || part_type[0] == 2))    //当环岛S7阶段可以看到非环岛内的图像时，说明已经经过了环岛，此时退出环岛模式
        {
            img_type = STR_W;
            img_mode = 0;
        } else if (image_para.imgtype == RCIR_W_S7 && part_type[0] == 0) {
            img_type = STR_W;
            img_mode = 0;
        }
            //后面保证在进入环岛某一阶段后不能退出，防止环内复杂的图像影响，因此我们也必须经过1模式，来确保不会错误的识别别的图像为环岛
        else if (image_para.imgtype == LCIR_W_S2) {
            img_type = LCIR_W_S2;
        } else if (image_para.imgtype == RCIR_W_S2) {
            img_type = RCIR_W_S2;
        } else if (image_para.imgtype == LCIR_W_S2_5) {
            img_type = LCIR_W_S2_5;
        } else if (image_para.imgtype == RCIR_W_S2_5) {
            img_type = RCIR_W_S2_5;
        } else if (image_para.imgtype == LCIR_W_S3) {
            img_type = LCIR_W_S3;
        } else if (image_para.imgtype == RCIR_W_S3) {
            img_type = RCIR_W_S3;
        } else if (image_para.imgtype == LCIR_W_S4) {
            img_type = LCIR_W_S4;
        } else if (image_para.imgtype == RCIR_W_S4) {
            img_type = RCIR_W_S4;
        } else if (image_para.imgtype == LCIR_W_S5) {
            img_type = LCIR_W_S5;
        } else if (image_para.imgtype == RCIR_W_S5) {
            img_type = RCIR_W_S5;
        } else if (image_para.imgtype == LCIR_W_S6)
            img_type = LCIR_W_S6;
        else if (image_para.imgtype == RCIR_W_S6)
            img_type = RCIR_W_S6;
        else if (image_para.imgtype == LCIR_W_S7)
            img_type = LCIR_W_S7;
        else if (image_para.imgtype == RCIR_W_S7)
            img_type = RCIR_W_S7;
    }

        //当图像识别模式为3（三岔）且已经出库，三岔不需要像环岛一样的确认步骤是因为，图像识别把三岔放在了最后，因此它已经经过了多次确认
    else if (img_mode == 3 && start == 1) {

        if (a > 200) {
            img_mode = 0;
            img_type = STR_W;
        }
        if (image_para.imgtype == FOK_W_S1 &&
            upside >= UPSIDE_M)   //当三岔S2阶段从中间向上查找，查找到的边界的i值比预定值大时，说明到了适当位置了，可以进入S3阶段，用来停车，预定值可以调整停车的位置
        {
            img_type = FOK_W_S3;
            FOK_S3_FLAG = 1;
        } else { img_type = FOK_W_S1; }
        if (image_para.imgtype == FOK_W_S3 && (part_type[0] == 0 || part_type[0] == 1) && part_type[1] == 4) {
            FOK_OUT_FLAG_1 = 1;
        }
        if (image_para.imgtype == FOK_W_S3 && (part_type[0] == 4 || part_type[0] == 3 || part_type[1] == 3) &&
            FOK_OUT_FLAG_1 == 1) {
            FOK_OUT_FLAG_2 = 1;
        }
        if (image_para.imgtype == FOK_W_S3 &&
            (part_type[0] == 0 || part_type[0] == 1) && FOK_OUT_FLAG_2 == 1) {
            img_mode = 0;
            FOK_OUT_FLAG_1 = 0;
            FOK_OUT_FLAG_2 = 0;

            img_type = STR_W;
        }
        if (image_para.imgtype == FOK_W_S3) {
            a++;
        }
        if (a > 70) {
            img_mode = 0;
            FOK_OUT_FLAG_1 = 0;
            FOK_OUT_FLAG_2 = 0;

            img_type = STR_W;
        }

    }
//    Pixle_ADD_My_hengxian(part_index[0]);
//    Pixle_ADD_My_hengxian(part_index[1]);
//    Pixle_ADD_My_hengxian(part_index[2]);
//    Pixle_ADD_My_hengxian(part_index[3]);
    image_para.imgtype = img_type;
}


float offset_process(void) {
    int16 i;

    offset = 0;
    float weight = 0;
    int16 gain_up;
    float x, y;

    int16 offset_si;        //计算偏差值的起始行i值
    int16 offset_ei;        //计算偏差值的终止行i值，注意i从大到小为从下到上

    offset_si = 50;
    offset_ei = 35;
    if (image_para.imgtype == LCIR_W_S1 || image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
        image_para.imgtype == LCIR_W_S3 || image_para.imgtype == LCIR_W_S4 || image_para.imgtype == LCIR_W_S5 ||
        image_para.imgtype == LCIR_W_S6 || image_para.imgtype == RCIR_W_S1 || image_para.imgtype == RCIR_W_S2 ||
        image_para.imgtype == RCIR_W_S2_5 || image_para.imgtype == RCIR_W_S3 || image_para.imgtype == RCIR_W_S4 ||
        image_para.imgtype == RCIR_W_S5 || image_para.imgtype == RCIR_W_S6) {
        offset_si = 60;
        offset_ei = 45;
    }
    //处于坡道时行数取低，防止因为远处的图像而在坡顶掉落
//    if(flag_ramp > 20)
//    {
//        offset_si = 49;
//        offset_ei = 45;
//    }


    if (image_para.imgtype == FOK_W_S1)  //三岔S1阶段的位置偏差计算
    {
        //从三岔S1阶段开始，在中线向上搜索黑白边界upside
        if (image_cache[MT9V03X_H - 1][MT9V03X_W / 2] == 255 &&
            image_cache[MT9V03X_H - 2][MT9V03X_W / 2] == 255 &&
            mt9v03x_image[MT9V03X_H - 3][MT9V03X_W / 2] == 255)
            upside = 0;
        else
            upside = 49;

        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {

            if (image_cache[i][93] == 255 && image_cache[i - 1][93] == 255 && image_cache[i - 2][93] == 0) {
                upside = i;
                break;
            }
        }

        //计算位置偏差
        for (i = MT9V03X_H - 1; i >= 30; i -= 1) {
            offset += (float) (centerline[i] - MT9V03X_W / 2);
            weight += 1;
        }
    } else if (image_para.imgtype == FOK_W_S2) //三岔S2阶段
    {
        if (image_cache[MT9V03X_H - 1][MT9V03X_W / 2] == 255 &&
            image_cache[MT9V03X_H - 2][MT9V03X_W / 2] == 255 &&
            mt9v03x_image[MT9V03X_H - 3][MT9V03X_W / 2] == 255)
            upside = 0;
        else
            upside = 49;

        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {

            if (image_cache[i][93] == 255 && image_cache[i - 1][93] == 255 && image_cache[i - 2][93] == 0) {
                upside = i;
                break;
            }
        }

        //此处边界搜索比较特殊，可以找到图像上部中间为黑色的两条三角边界，以确定车身是否走正
        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {
            if (mt9v03x_image[i][MT9V03X_W / 2] == 0) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            }
        }
    } else if (image_para.imgtype == CRS_W_S1) //十字路口S1阶段
    {
        //全图搜索，用双边界的各行相对于图像中线的偏差作为位置偏差值
        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {
            if (road_type[i] == 0) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            }
        }

        //十字偏差限制
        if (offset > CRS_OFFSET_TH * weight)
            offset = CRS_OFFSET_TH * weight;
        else if (offset < -CRS_OFFSET_TH * weight)
            offset = -CRS_OFFSET_TH * weight;
    } else if (image_para.imgtype == CRS_W_S2) //十字路口S2阶段
    {
        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {
            if (road_type[i] == 0) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            }
        }

        //十字偏差限制
        if (offset > CRS_OFFSET_TH * weight)
            offset = 10 * weight;
        else if (offset < -10 * weight)
            offset = -CRS_OFFSET_TH * weight;
    } else if (image_para.imgtype == LCIR_W_S1 || image_para.imgtype == LCIR_W_S6 ||
               image_para.imgtype == LCIR_W_S7)  //左环部分阶段按照右边界循迹
    {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (rightline[i] - rs_std[i]);
            weight += 1;
        }
        if (image_para.imgtype == LCIR_W_S6 && offset / weight > 40) {
            offset = -30;
            weight = 1;
        }
    } else if (image_para.imgtype == RCIR_W_S1 || image_para.imgtype == RCIR_W_S6 ||
               image_para.imgtype == RCIR_W_S7)  //右环部分阶段按照左边界循迹
    {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (leftline[i] - ls_std[i]);
            weight += 1;
        }
    } else if (image_para.imgtype == LCIR_W_S2 ||
               image_para.imgtype == LCIR_W_S2_5)   //左环S2与S2_5阶段在部分时候按照左边界循迹，部分时候按照右边界循迹
    {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            if (leftline[i] - leftline[i + 1] < 0 && part_type[0] == 0 &&
                leftline[i] - leftline[i + 1] > -SSUD_TH) {
                //速度方案不同采用不同处理，为了顺利进环
                offset += (float) (leftline[i] - ls_std[i] - 5);
                weight += 1;
            } else {
                offset += (float) (rightline[i] - rs_std[i] + CURSE_OFFSET_1);
                weight += 1;
            }
        }
    } else if (image_para.imgtype == RCIR_W_S2 || image_para.imgtype == RCIR_W_S2_5) {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            if (rightline[i] - rightline[i + 1] > 0 && part_type[0] == 0 &&
                rightline[i] - rightline[i + 1] < SSUD_TH) {
                offset += (float) (rightline[i] - rs_std[i]);
                weight += 1;
            } else {
                offset += (float) (leftline[i] - ls_std[i] - CURSE_OFFSET_1);
                weight += 1;
            }
        }
    } else if (image_para.imgtype == RCIR_W_S2_5) {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (leftline[i] - ls_std[i] - CURSE_OFFSET_1);
            weight += 1;
        }
    } else if (image_para.imgtype == LCIR_W_S3) {
        if (part_type[1] == 7)
            cirsud_i = part_index[0] - 1;
        for (i = offset_si; i >= offset_ei; i -= 1) {
            if (i > cirsud_i) {
                if (code_mode == 1) {

                    if (leftline[i] - ls_std[i] < 0) {
                        offset += (float) (leftline[i] - ls_std[i] - 5);
                        weight += 1;
                    }
                }

            } else {

                if (rightline[i] - rs_std[i] < 0) {
                    offset += (float) (rightline[i] - rs_std[i]);
                    weight += 1;
                }
            }
        }
    } else if (image_para.imgtype == RCIR_W_S3) {
        if (part_type[1] == 8)
            cirsud_i = part_index[0] - 1;
        for (i = offset_si; i >= offset_ei; i -= 1) {
            if (i > cirsud_i) {
                if (code_mode == 1) {

                    if (rightline[i] - rs_std[i] > 0) {
                        offset += (float) (rightline[i] - rs_std[i]);
                        weight += 1;
                    }
                } else if (code_mode == 2) {
                    offset += 20;
                    weight += 1;
                }
            } else {

                if (leftline[i] - ls_std[i] > 0) {
                    offset += (float) (leftline[i] - ls_std[i]);
                    weight += 1;
                }
            }
        }
    } else if (image_para.imgtype == LCIR_W_S4) {
        if (S3S4_flag == 1)  //当第一次进入S4阶段时，该帧图像的各行类型判断采用了环岛S3阶段的判断方法，因此需要特殊处理
        {
            S3S4_flag = 0;
            for (i = offset_si; i >= offset_ei; i -= 1) {

                //重算一遍边界，防止因为起始点导致边界查找错误
                if (road_type[i] == 0 || road_type[i] == 4) {
                    offset += (float) (centerline[i] - MT9V03X_W / 2);
                    weight += 1;
                } else if (road_type[i] == 1 || road_type[i] == 5) {
                    offset += (float) (rightline[i] - rs_std[i]);
                    weight += 1;
                } else if (road_type[i] == 2 || road_type[i] == 6) {
                    offset += (float) (leftline[i] - ls_std[i]);
                    weight += 1;
                }
            }
            //计算S4阶段的offset的平均值，作为S5阶段的值
            if (weight != 0)
                offset_S5 = offset / weight;
            else
                offset_S5 = -25;
            weight_S5 = 1;
        } else {
            for (i = offset_si; i >= offset_ei; i -= 1) {
                if (road_type[i] == 0 || road_type[i] == 4) {
                    offset += (float) (centerline[i] - MT9V03X_W / 2);
                    weight += 1;
                } else if (road_type[i] == 1 || road_type[i] == 5) {
                    offset += (float) (rightline[i] - rs_std[i]);
                    weight += 1;
                } else if (road_type[i] == 2 || road_type[i] == 6) {
                    offset += (float) (leftline[i] - ls_std[i]);
                    weight += 1;
                }
            }
            if (weight == 0)
                weight = 1;
            if (weight_S5 <= 2000 && weight != 0 && offset / weight <= -20) {
                offset_S5 += offset / weight;
                weight_S5 += 1;
            }
        }
    } else if (image_para.imgtype == RCIR_W_S4) {
        if (S3S4_flag == 1) {
            S3S4_flag = 0;
            for (i = offset_si; i >= offset_ei; i -= 1) {

                for (i = offset_si; i >= offset_ei; i -= 1) {
                    if (road_type[i] == 0 || road_type[i] == 4) {
                        offset += (float) (centerline[i] - MT9V03X_W / 2);
                        weight += 1;
                    } else if (road_type[i] == 1 || road_type[i] == 5) {
                        offset += (float) (rightline[i] - rs_std[i]);
                        weight += 1;
                    } else if (road_type[i] == 2 || road_type[i] == 6) {
                        offset += (float) (leftline[i] - ls_std[i]);
                        weight += 1;
                    }
                }
            }
            if (weight != 0)
                offset_S5 = offset / weight;
            else
                offset_S5 = 25;
            weight_S5 = 1;
        } else {
            for (i = offset_si; i >= offset_ei; i -= 1) {
                for (i = offset_si; i >= offset_ei; i -= 1) {
                    if (road_type[i] == 0 || road_type[i] == 4) {
                        offset += (float) (centerline[i] - MT9V03X_W / 2);
                        weight += 1;
                    } else if (road_type[i] == 1 || road_type[i] == 5) {
                        offset += (float) (rightline[i] - rs_std[i]);
                        weight += 1;
                    } else if (road_type[i] == 2 || road_type[i] == 6) {
                        offset += (float) (leftline[i] - ls_std[i]);
                        weight += 1;
                    }
                }
            }
            if (weight == 0)
                weight = 1;
            if (weight_S5 <= 2000 && weight != 0 && offset / weight >= 20) {
                offset_S5 += offset / weight;
                weight_S5 += 1;
            }
        }
    } else if (image_para.imgtype == LCIR_W_S5 || image_para.imgtype == RCIR_W_S5) //环岛S5阶段采用S4阶段的平均值作为其开环值
    {
        offset = offset_S5;
        weight = weight_S5;

        if (weight_S5 < 3) {
            if (image_para.imgtype == LCIR_W_S5)
                offset = -25;
            else if (image_para.imgtype == RCIR_W_S5)
                offset = 25;
            weight = 1;
        }
        if (offset_S5 / weight_S5 >= 32 || offset_S5 / weight_S5 <= -32) {
            if (image_para.imgtype == LCIR_W_S5)
                offset = -32;
            else if (image_para.imgtype == RCIR_W_S5)
                offset = 32;
            weight = 1;
        }
        if (offset_S5 / weight_S5 <= 25 || offset_S5 / weight_S5 >= -25) {
            if (image_para.imgtype == LCIR_W_S5)
                offset = -25;
            else if (image_para.imgtype == RCIR_W_S5)
                offset = 25;
            weight = 1;
        }
    } else    //正常普通路段的循迹
    {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            if (road_type[i] == 0 || road_type[i] == 4) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            } else if (road_type[i] == 1 || road_type[i] == 5) {
                offset += (float) (rightline[i] - rs_std[i]);
                weight += 1;
            } else if (road_type[i] == 2 || road_type[i] == 6) {
                offset += (float) (leftline[i] - ls_std[i]);
                weight += 1;
            }
        }
    }

    //防止除数为0
    if (weight == 0) {
        weight = 1;
    }
    offset = offset / weight;

    //坡道处理
//    if(flag_ramp > 20 && offset > 10)
//        offset = 10;
//    else if(flag_ramp > 20 && offset < -10)
//        offset = -10;
    error = -offset;
    return offset;
}

void calc_angle() {
    if (image_para.imgtype == LCIR_W_S1 || image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
        image_para.imgtype == LCIR_W_S3 || image_para.imgtype == LCIR_W_S4 || image_para.imgtype == LCIR_W_S5 ||
        image_para.imgtype == LCIR_W_S6 || image_para.imgtype == RCIR_W_S1 || image_para.imgtype == RCIR_W_S2 ||
        image_para.imgtype == RCIR_W_S2_5 || image_para.imgtype == RCIR_W_S3 || image_para.imgtype == RCIR_W_S4 ||
        image_para.imgtype == RCIR_W_S5 || image_para.imgtype == RCIR_W_S6) {
        degree += yaw_rate;
    } else {
        degree = 0;
    }
}

void Img_type_test() {
    Boundary_part();
    image_distinguish();
    offset_process();
    calc_angle();
}

/***************图像灰度判断*************************/
/////////阈值分割以及二值化///////////////
#define GrayScale 256
int pixelCount[GrayScale];
float pixelPro[GrayScale];


int GetOTSU(unsigned char tmImage[MT9V03X_H][MT9V03X_W]) {
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelIntegralBack = 0;
    unsigned long PixelIntegral = 0;
    signed long PixelIntegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++) HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < MT9V03X_H; j++) {
        for (i = 0; i < MT9V03X_W; i++) {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue) return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue) return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++) Amount += HistoGram[j];        //  像素总数

    PixelIntegral = 0;
    for (j = MinValue; j <= MaxValue; j++) {
        PixelIntegral += HistoGram[j] * j;//灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++) {
        PixelBack = PixelBack + HistoGram[j];   //前景像素点数
        PixelFore = Amount - PixelBack;         //背景像素点数
        OmegaBack = (float) PixelBack / Amount;//前景像素百分比
        OmegaFore = (float) PixelFore / Amount;//背景像素百分比
        PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
        PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
        MicroBack = (float) PixelIntegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelIntegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}

//////////图像解压////////////
int image_threshold[3] = {0, 0, 0};
int threshold;
uint8 image_cache1[120][188];

void img_extract() {
    image_threshold[0] = GetOTSU(&mt9v03x_image[0][0]);
    threshold = image_threshold[0];
    memset(image_cache, 0, sizeof(image_cache));
    for (int y = 0; y < MT9V03X_H; y++) {
        for (int x = 0; x < MT9V03X_W; x++) {
            image_cache[y][x] = mt9v03x_image[y][x] > threshold ? 255 : 0;
        }
    }
}

