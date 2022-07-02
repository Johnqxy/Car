
#include "Camera.h"//��ɫΪ0��ɫΪ1
#include "headfile.h"

float k1 = 0;
uint8 l3 = 0;
uint8 l1 = 0;
uint8 l2 = 0;
uint8 start_flag = 0;
uint8 finish_flag = 0;
uint8 p = 0;
uint8 flag_starting_line_last = 0;
uint8 flag_starting_line = 0;
uint8 starting_line_cnt = 0;
uint8 break_hangshu;
uint8 centerline[120];
uint8 leftline[120];
uint8 rightline[120];
uint8 leftfindflag[120];  //�������������Ƿ��ҵ�
uint8 rightfindflag[120];
uint8 road_width[120];
uint8 road_type[120];
uint8 part_type[MT9V03X_H];         //�ֶ�����
uint8 part_index[MT9V03X_H];        //�ֶ��յ��±�
uint8 part_num;
uint8 img_mode = 0;
uint8 start = 1;
uint8 cirsud_i;                     //�����뻷ʱ�������i���꣬�����Ϊ������߽���ֱ���߽�Ľ��㣨�˽������������˴�ָ�뻷ʱ�ĵ㣩
float error = 0;                    //λ�û�ƫ����

uint8 FOK_OUT_FLAG_1 = 0;
uint8 FOK_OUT_FLAG_2 = 0;

uint8 flag = 0;
int max = 93;
int min = 93;
uint8 old = 93;
uint8 i, j;
float offset_S5 = 0;                //����S5�׶εĿ���ƫ��ֵ
float weight_S5 = 0;                //����S5�׶εĿ���ƫ���ۼӼ�����offset_S5/weight_S5Ϊ������ƫ��ֵ
uint8 code_mode = 1;
uint8 upside = 0;                   //����S3�׶ε��б��
int a = 0;
uint8 S3S4_flag = 0;                //����S3��S4�׶εı�־λ����ֵΪ1ʱ˵����S3����S4����һ֡
int degree = 0;
uint8 FOK_S3_FLAG = 0;
int yaw_last = 0;
uint8 CURSE_OFFSET_1 = 5;           //����Ĺ̶�ƫ����������ʱ������ģλ��
uint8 UPSIDE_M = 39;                //������upside��ֵ����upside������ʱ�������S2�׶ν���S3
uint8 UPSIDE_S = 41;                //�ӻ���upside��ֵ
uint8 last;
float offset = 0;
image_parameter image_para;
uint8 ls_std[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 79, 79, 78, 78, 78, 77, 77, 77, 75, 74, 74, 74, 74, 74, 73, 72,
                  71, 71, 71, 70, 70, 69, 69, 68, 68, 67, 67, 66, 66, 66, 64, 64, 63, 63, 63, 62, 61, 61, 61, 60, 59,
                  59, 58, 58, 57, 57, 56, 55, 55, 55, 54, 54, 53, 53, 52, 52, 51, 50, 50, 49, 49, 48, 47, 47, 46, 46,
                  46, 44, 43, 42, 41, 40, 40, 40, 39, 39, 38, 37, 37};
uint8 rs_std[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 108, 109, 109, 110, 110, 110, 111, 112, 112, 113, 114, 114, 115, 115,
                  115, 115, 116, 117, 117, 117, 118, 118, 120, 120, 121, 121, 122, 122, 123, 123, 123, 124, 125, 125,
                  125, 126, 126, 127, 127, 127, 128, 128, 129, 130, 130, 131, 131, 131, 132, 133, 133, 134, 134, 135,
                  135, 135, 135, 136, 137, 137, 138, 139, 139, 140, 141, 141, 141, 141, 142, 143, 143, 144, 145, 145,
                  145, 146, 146, 147, 148, 148};

void Basic_line_scan(void) {

    for (j = MT9V03X_H - 1; j > 10; j--) {
        leftfindflag[j] = 0;  //�������������Ƿ��ҵ�
        rightfindflag[j] = 0;
        centerline[j] = 0;
        leftline[j] = 0;
        rightline[j] = 187;
        road_width[j] = 0;
        road_type[j] = 0;
        part_type[MT9V03X_H] = 0;         //�ֶ�����
        part_index[MT9V03X_H] = 0;        //�ֶ��յ��±�
        part_num = 0;
        break_hangshu = 0;
    }
    check_starting_line();
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
            if (break_hangshu <= MT9V03X_H - 21)    //��ֹ��һ��ʼ��break
            {
                if (img_mode != 2) {
                    break;
                }
            }
        }
        if (img_mode == 0 || img_mode == 1) {
            old = centerline[j];
        }
        if (image_para.imgtype == RCIR_W_S2 || image_para.imgtype == RCIR_W_S2_5 ||
            image_para.imgtype == RCIR_W_S3 || image_para.imgtype == RCIR_W_S6 ||
            image_para.imgtype == RCIR_W_S7 || image_para.imgtype == LCIR_W_S4 ||
            image_para.imgtype == LCIR_W_S5 || (image_para.imgtype == GARAGE_R && j < 60)) {
            old = leftline[j] + 10;

        }
        if (image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
            image_para.imgtype == LCIR_W_S3 || image_para.imgtype == LCIR_W_S6 ||
            image_para.imgtype == LCIR_W_S7 || image_para.imgtype == RCIR_W_S4 ||
            image_para.imgtype == RCIR_W_S5 || (image_para.imgtype == GARAGE_L && j < 60)) {
            old = rightline[j] - 10;
        }
        if (img_mode == 3) {
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
//    if (start_flag == 0) {
//        start=0;
////        for (uint8 i = 110; i > 20; i--) {
////            if (centerline[i-2]-centerline[i]>10||centerline[i-2]-centerline[i]<-10) {
////                l1 = i;
////                l2 = rightline[i + 5];
////                break;
////            }
////        }
////        for (uint8 i = l1; i > 20; i--) {
////            if (image_cache[i][l2] == 255 && image_cache[i - 1][l2] == 0 & image_cache[i - 2][l2] == 0) {
////                l3 = i;
////                break;
////            }
////        }
////        k1 = (float)(l2 - leftline[i + 5]) / (float)(l1 - l3);
////        for (uint8 l = l1+5; l > l3; l--) {
////            leftline[l] = leftline[l + 1] + k1-0.5;
////            centerline[l] = (uint8)((rightline[l] + leftline[l]) / 2);
////        }
//        bench_v=30;
//        for (uint8 k = 80; k >10 ; --k) {
//            leftline[k]=ls_std[k];
//            centerline[k]=(uint8)((leftline[k]+rightline[k])/2);
//        }
//    }


}//����ɨ����ϣ���old���¸�ֵ


void Advanced_line_scan(void) {
    Basic_line_scan();
    uint8 i;
    float dl, dr;           //�������һ�е����ұ߽�仯��ע��iֵ�Ӵ�С�仯
    uint8 w_min;            //֮ǰ�е���С���
    uint8 dw[MT9V03X_H];    //�������һ�е��п�ȱ仯
    uint8 flag_sud = 0;     //ͻ��ı�־

    w_min = 130;

    for (i = MT9V03X_H - 2; i >= 10; i -= 1) {
        if (road_type[i] != -1) {
            if (road_width[i] < w_min && i > 10)          //������С�п��
                w_min = road_width[i];
            else if (i % 2 == 0)                          //����Խ���ϣ�����𽥼�С�������Ҫ�ֶ������п��
                w_min -= 1;

            dw[i] = road_width[i] - road_width[i + 1];        //����һ�еĿ�Ȳ�
            dl = leftline[i] - leftline[i + 1];             //����һ�е���߽���
            dr = rightline[i] - rightline[i + 1];           //����һ�е���߽���

            //��ʼ�ж�����
            if (image_para.imgtype == LCIR_W_S2_5 || image_para.imgtype == LCIR_W_S3) {
                if (flag_sud == 0 && dr <= NSUD_TH && dr >= -SSUD_TH &&
                    dl >= 3 * SSUD_TH) //7���ͱ�ʾ��߽�����ͻ�䣬���������ͻ��Ϊ������߽磬˵��ͻ���Ϊ�뻷�������
                {
                    road_type[i] = 7;
                    flag_sud = 7;
                } else if (flag_sud == 7 && dl < SSUD_TH && dl > -SSUD_TH && dr <= NSUD_TH && dr >= -SSUD_TH)
                    road_type[i] = 7;
                else if (flag_sud == 0 && dr <= NSUD_TH && dr >= -SSUD_TH &&
                         dl < -SSUD_TH)  //0ͻ�䵽5˵�����������У���ʱҪ��flag_sud��¼��ͻ�䷢�����ˣ����ص�����ֵʱ5���Ϊ0���Ӷ�������Ϊͼ��ĳһ�еı߽���������յĴ���
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
                //����ģʽ�� ��ͼ���������ж�
            else {
                if ((dw[i] > SUD_TH && dl < -SSUD_TH && dr > NSUD_TH) ||
                    (dw[i] > SUD_TH && dl < -NSUD_TH && dr > SSUD_TH))  //��ʾ���ͻ���ˣ��ұ߽߱绹�����ߣ�����б��ʮ�֣�˵��������3����
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
                           dw[i] > 0)   //�ж�Ϊ���߽߱��ڷ�ɢ��������ͻ��������˵������������
                {
                    road_type[i] = 4;
                }
            }
        }
    }

    //�˲��㷨���ѵ��м�˫�е�����ȥ��
    for (i = MT9V03X_H - 2; i >= 1; i--) {
        if (road_type[i - 1] == road_type[i + 1] && road_type[i - 2] == road_type[i + 1] &&
            road_type[i] != road_type[i + 1]) {
            road_type[i] = road_type[i + 1];
        }
        if (road_type[i + 1] == road_type[i - 2] && road_type[i + 1] == road_type[i - 3] &&
            road_type[i] != road_type[i + 1] && road_type[i - 1] != road_type[i + 1])//����һ��������
        {
            road_type[i] = road_type[i + 1];
            road_type[i - 1] = road_type[i + 1];
        }
    }
}

void Boundary_part(void) {
    Advanced_line_scan();
    int16 i;
    int16 part_i, part_flag, part_mi;   //part_iΪ��ʱ��part_type���±꣬part_flagΪ�������ͣ�part_miΪ�Ͳ�����±�
    int16 partcnt;                      //ͬ������м���

    //�ֶ������ж�
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

    //�߽�ֶκϲ�����Ϊ���ϼ�����������ֶο��ܻ������ͬ���͵������������ֵ����������0��0��1����ʱҪ����ϲ�����
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
    uint8 a = 50, b = 35, c = 15;//��ѡ���еĳ�ʼֵ
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
    image_type img_type = none;         //Ĭ������Ϊnone

    //���������ʶ��ģʽΪ0ʱ
    if (img_mode == 0 && start == 1) {
        //�������ķֶ���Ϊ1ʱ
        if (part_num == 1) {
            if (part_type[0] == 3)       //����3���࣬˵����ʮ��·��S1�׶�
                img_type = CRS_W_S1;
            else if (part_type[0] == 0)  //����0���࣬˵����ֱ����С��
                img_type = STR_W;
        }
            //�������ķֶ���Ϊ2ʱ
        else if (part_num == 2) {
            if (part_type[0] == 0 && part_type[1] == 3)      //������ֱ��0Ȼ��հ�����3��˵��ǰ����ʮ��·��S1�׶�
                img_type = CRS_W_S1;
            else if (part_type[0] == 3 && part_type[1] == 0) //�����ȿհ�����3��ֱ��0��˵��ǰ���ǳ�ʮ�ֵ�S2�׶�
                img_type = CRS_W_S2;
            else if (part_type[0] == 0 && part_type[1] == 5 &&
                     cur_circle(1) >= CUR_CIRTH)   //���������0Ȼ����߽�ͻ��5�����ұ���ֱ�ı߽磬˵����Ԥ�����󻷵�
            {
                img_type = LCIR_W_S1;

                img_mode = 1;           //Ԥ���뻷��ģʽ���޸�ͼ��ʶ��ģʽΪ1

            } else if (part_type[0] == 0 && part_type[1] == 6 &&
                       cur_circle(0) >= CUR_CIRTH)   //���������0Ȼ���ұ߽�ͻ��6���������ֱ�ı߽磬˵����Ԥ�����һ���
            {
                img_type = RCIR_W_S1;

                img_mode = 1;           //Ԥ���뻷��ģʽ���޸�ͼ��ʶ��ģʽΪ1

            } else if (part_type[0] == 0 && part_type[1] == 4 &&
                       part_index[0] - part_index[1] > 10) //�����������0��˫�߽緢ɢ4���ҷ�ɢ���ȳ���10�У�˵������������S1�׶�
            {
                img_type = FOK_W_S1;
                flag = 1;
                img_mode = 3;           //����ģʽ���޸�ͼ��ʶ��ģʽΪ3
            }
        }
            //�������ķֶ������ڵ���3ʱ
        else {
            if (part_type[0] == 0 && part_type[1] == 3)
                img_type = CRS_W_S1;
            else if (part_type[0] == 0 && (part_type[1] == 5 || part_type[1] == 6) &&
                     part_type[2] == 3) //����б��ʮ�ֵ�����
                img_type = CRS_W_S1;
            else if (part_type[0] == 3 && part_type[1] == 0)
                img_type = CRS_W_S2;
            else if (part_type[0] == 3 && (part_type[1] == 5 || part_type[1] == 6) &&
                     part_type[2] == 0) //����б��ʮ�ֵ�����
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

        //��ͼ��ʶ��ģʽΪ1������Ԥʶ�����Ѿ�����
    else if (img_mode == 1 && start == 1) {
        if (part_num == 1) {
            if (part_type[0] == 0) {
                img_type = STR_W;
                img_mode = 0;           //��ʾǰ�������ǻ�������Ҫ�˳�1ģʽ������0ģʽ
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
            } else if (part_type[0] == 1 && part_type[1] == 0) //�����뻷��һ���ؾ��׶Σ�����1ģʽ�¿����˽׶Σ�˵��ȷ�Ͻ��뻷��
            {
                img_type = LCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;       //���뻷��S2�׶κ���������㣬����S3�׶ε��������ڼ仹�ᾭ��һ��S2_5�׶Σ�Ϊ��ֹ�������S3�׶Σ�
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
        //��ͼ��ʶ��ģʽΪ2�����������Ѿ�����
    else if (img_mode == 2 && start == 1) {
        if (image_para.imgtype == LCIR_W_S2 &&
            part_type[0] == 0)    //����S2�׶κ󿴵�ֱ����˵����ʹ������ֱ�����м䣬���Խ���S3�׶��ˣ����������S2_5�Ĺ��ɽ׶�
        {
            img_type = LCIR_W_S2_5;
        } else if (image_para.imgtype == LCIR_W_S2_5 && part_num >= 2 && part_type[0] == 0 &&
                   part_type[1] == 7)           //������7�׶�ʱ��˵���Ѿ����Կ��������ֱ���ˣ���ʱ���Ը���7�׶εĳ��ֵ�ȷ����Ϊ����㣬�����ô˵㲹��
        {
            img_type = LCIR_W_S3;
        } else if (image_para.imgtype == RCIR_W_S2 && part_type[0] == 0) {
            img_type = RCIR_W_S2_5;
        } else if (image_para.imgtype == RCIR_W_S2_5 && part_num >= 2 && part_type[0] == 0 &&
                   part_type[1] == 8) {
            img_type = RCIR_W_S3;
        } else if (image_para.imgtype == LCIR_W_S3 && ((part_type[1] == 7 && part_index[0] >= 50) ||
                                                       part_type[0] == 7))   //�����׶������ܵ�ʱ��˵�����������뻷�ڣ�����Ϊ����S4�׶�
        {
            img_type = LCIR_W_S4;
            S3S4_flag = 1;          //˵���ǽ���S4�׶εĵ�һ֡����Ҫ�������⴦��
        } else if (image_para.imgtype == RCIR_W_S3 &&
                   ((part_type[1] == 8 && part_index[0] >= 50) || part_type[0] == 8)) {
            img_type = RCIR_W_S4;
            S3S4_flag = 1;
        } else if (image_para.imgtype == LCIR_W_S4 && part_num == 2 &&
                   (part_type[1] == 3 || part_type[1] == 6 || part_type[1] == 1) &&
                   degree > 10000)    //������������ͼ�񣬵�ת��һ��ĽǶȣ����ܿ���������ͼ��ʱ����ΪS5�׶�
        {
            img_type = LCIR_W_S5;
        } else if (image_para.imgtype == LCIR_W_S4 && part_num >= 3 &&
                   (part_type[1] == 3 || part_type[1] == 6 || part_type[1] == 1 || part_type[2] == 3 ||
                    part_type[2] == 1 || part_type[2] == 6) &&
                   degree > 10000) {
            img_type = LCIR_W_S5;
        } else if (image_para.imgtype == RCIR_W_S4 && part_num == 2 &&
                   (part_type[1] == 3 || part_type[1] == 5 || part_type[1] == 2) && degree < -10000) {
            img_type = RCIR_W_S5;
        } else if (image_para.imgtype == RCIR_W_S4 && part_num >= 3 &&
                   (part_type[1] == 3 || part_type[1] == 5 || part_type[1] == 2 || part_type[2] == 3 ||
                    part_type[2] == 5 || part_type[2] == 2) && degree < -10000) {
            img_type = RCIR_W_S5;
        } else if (image_para.imgtype == LCIR_W_S5 && degree > 15000)        //��ת������һ�ܵĽǶ�ʱ����Ϊ�Լ����������ô�ʱΪS6�׶�
        {
            img_type = LCIR_W_S6;
        } else if (image_para.imgtype == RCIR_W_S5 && degree < -15000) {
            img_type = RCIR_W_S6;
        } else if (image_para.imgtype == LCIR_W_S6 && part_num >= 2 &&
                   (part_type[0] == 1 || part_type[0] == 5) &&
                   part_type[1] == 0)  //��S6�׶���ʹ���ڶ����뻷λ��ʱ�������뻷�ˣ���Ҫ��Ϊ������S7�׶Σ���������ʻ������
        {
            img_type = LCIR_W_S7;
        } else if (image_para.imgtype == RCIR_W_S6 && part_num >= 2 &&
                   (part_type[0] == 2 || part_type[0] == 6) &&
                   part_type[1] == 0) {
            img_type = RCIR_W_S7;
        } else if (image_para.imgtype == LCIR_W_S7 &&
                   (part_type[0] == 0 || part_type[0] == 2))    //������S7�׶ο��Կ����ǻ����ڵ�ͼ��ʱ��˵���Ѿ������˻�������ʱ�˳�����ģʽ
        {
            img_type = STR_W;
            img_mode = 0;
        } else if (image_para.imgtype == RCIR_W_S7 && (part_type[0] == 0 || part_type[0] == 1)) {
            img_type = STR_W;
            img_mode = 0;
        }
            //���汣֤�ڽ��뻷��ĳһ�׶κ����˳�����ֹ���ڸ��ӵ�ͼ��Ӱ�죬�������Ҳ���뾭��1ģʽ����ȷ����������ʶ����ͼ��Ϊ����
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

        //��ͼ��ʶ��ģʽΪ3���������Ѿ����⣬������Ҫ�񻷵�һ����ȷ�ϲ�������Ϊ��ͼ��ʶ���������������������Ѿ������˶��ȷ��
    else if (img_mode == 3 && start == 1) {

        if (a > 200) {
            img_mode = 0;
            img_type = STR_W;
        }
        if (image_para.imgtype == FOK_W_S1 &&
            upside >= UPSIDE_M)   //������S2�׶δ��м����ϲ��ң����ҵ��ı߽��iֵ��Ԥ��ֵ��ʱ��˵�������ʵ�λ���ˣ����Խ���S3�׶Σ�����ͣ����Ԥ��ֵ���Ե���ͣ����λ��
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
        if (a > 30) {
            img_mode = 0;
            FOK_OUT_FLAG_1 = 0;
            FOK_OUT_FLAG_2 = 0;

            img_type = STR_W;
        }

    }
    if (starting_line_cnt >= 3 && finish_flag == 0) {
        if (image_cache[64][0] == 0 && image_cache[64][2] == 0 && image_cache[64][4] == 0 && image_cache[64][6] == 0 &&
            image_cache[64][8] == 0 && image_cache[64][10] == 0) {
            img_type = GARAGE_R;
            img_mode = 0;
        } else if (image_para.imgtype == GARAGE_R) {
            img_type = GARAGE_R;
        } else {
            img_type = GARAGE_L;
            img_mode = 0;
        }
    }
    if (image_para.imgtype == GARAGE_R && degree < -3000) {
        img_type = FINISH;
        finish_flag = 1;

    }
    if (finish_flag == 1) {
        img_type = FINISH;
    }
    image_para.imgtype = img_type;
}


float offset_process(void) {
    int16 i;

    offset = 0;
    float weight = 0;

    int16 offset_si;        //����ƫ��ֵ����ʼ��iֵ
    int16 offset_ei;        //����ƫ��ֵ����ֹ��iֵ��ע��i�Ӵ�СΪ���µ���

    offset_si = 50;
    offset_ei = 35;

    if (image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
        image_para.imgtype == LCIR_W_S4 || image_para.imgtype == LCIR_W_S5 ||
        image_para.imgtype == LCIR_W_S6 || image_para.imgtype == RCIR_W_S1 || image_para.imgtype == RCIR_W_S2 ||
        image_para.imgtype == RCIR_W_S2_5 || image_para.imgtype == RCIR_W_S4 ||
        image_para.imgtype == RCIR_W_S5 || image_para.imgtype == RCIR_W_S6 || break_hangshu > 35) {
        offset_si = 75;
        offset_ei = 55;
//    } else if (break_hangshu > 35) {
//        offset_ei = break_hangshu;
//        offset_si = break_hangshu + 15;
    } else if (image_para.imgtype == LCIR_W_S3 || image_para.imgtype == RCIR_W_S3) {
        offset_si = 70;
        offset_ei = 50;
    } else {
        offset_si = 55;
        offset_ei = 35;
    }
    if (image_para.imgtype == LCIR_W_S1 || image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
        image_para.imgtype == LCIR_W_S3 || image_para.imgtype == LCIR_W_S4 || image_para.imgtype == LCIR_W_S5 ||
        image_para.imgtype == RCIR_W_S1 || image_para.imgtype == RCIR_W_S2 || image_para.imgtype == RCIR_W_S2_5 ||
        image_para.imgtype == RCIR_W_S3 || image_para.imgtype == RCIR_W_S4 || image_para.imgtype == RCIR_W_S5) {
        bench_v = 55;
    } else {
        bench_v = 70;
    }

    //�����µ�ʱ����ȡ�ͣ���ֹ��ΪԶ����ͼ������¶�����
//    if(flag_ramp > 20)
//    {
//        offset_si = 49;
//        offset_ei = 45;
//    }


    if (image_para.imgtype == FOK_W_S1)  //����S1�׶ε�λ��ƫ�����
    {
        //������S1�׶ο�ʼ�����������������ڰױ߽�upside
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

        //����λ��ƫ��
        for (i = MT9V03X_H - 1; i >= 30; i -= 1) {
            offset += (float) (centerline[i] - MT9V03X_W / 2);
            weight += 1;
        }
    } else if (image_para.imgtype == FOK_W_S2) //����S2�׶�
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

        //�˴��߽������Ƚ����⣬�����ҵ�ͼ���ϲ��м�Ϊ��ɫ���������Ǳ߽磬��ȷ�������Ƿ�����
        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {
            if (mt9v03x_image[i][MT9V03X_W / 2] == 0) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            }
        }
    } else if (image_para.imgtype == CRS_W_S1) //ʮ��·��S1�׶�
    {
        //ȫͼ��������˫�߽�ĸ��������ͼ�����ߵ�ƫ����Ϊλ��ƫ��ֵ
        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {
            if (road_type[i] == 0) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            }
        }

        //ʮ��ƫ������
        if (offset > CRS_OFFSET_TH * weight)
            offset = CRS_OFFSET_TH * weight;
        else if (offset < -CRS_OFFSET_TH * weight)
            offset = -CRS_OFFSET_TH * weight;
    } else if (image_para.imgtype == CRS_W_S2) //ʮ��·��S2�׶�
    {
        for (i = MT9V03X_H - 1; i >= 10; i -= 1) {
            if (road_type[i] == 0) {
                offset += (float) (centerline[i] - MT9V03X_W / 2);
                weight += 1;
            }
        }

        //ʮ��ƫ������
        if (offset > CRS_OFFSET_TH * weight)
            offset = 10 * weight;
        else if (offset < -10 * weight)
            offset = -CRS_OFFSET_TH * weight;
    } else if (image_para.imgtype == LCIR_W_S1 || image_para.imgtype == LCIR_W_S6 ||
               image_para.imgtype == LCIR_W_S7)  //�󻷲��ֽ׶ΰ����ұ߽�ѭ��
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
               image_para.imgtype == RCIR_W_S7)  //�һ����ֽ׶ΰ�����߽�ѭ��
    {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (leftline[i] - ls_std[i]);
            weight += 1;
        }
    } else if (image_para.imgtype == LCIR_W_S2)   //��S2��S2_5�׶��ڲ���ʱ������߽�ѭ��������ʱ�����ұ߽�ѭ��
    {

        for (i = offset_si; i >= offset_ei; i -= 1) {

            offset += (float) (rightline[i] - rs_std[i] - 10);
            weight += 1;

        }
    } else if (image_para.imgtype == LCIR_W_S2_5)   //��S2��S2_5�׶��ڲ���ʱ������߽�ѭ��������ʱ�����ұ߽�ѭ��
    {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (leftline[i] - ls_std[i] - 15);
            weight += 1;
        }
    } else if (image_para.imgtype == RCIR_W_S2) {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (leftline[i] - ls_std[i] + 10);
            weight += 1;
        }

    } else if (image_para.imgtype == RCIR_W_S2_5) {
        for (i = offset_si; i >= offset_ei; i -= 1) {
            offset += (float) (rightline[i] - rs_std[i] + 15);
            weight += 1;
        }
    } else if (image_para.imgtype == LCIR_W_S3) {

        if (part_type[1] == 7)
            cirsud_i = part_index[0] - 1;
        for (i = offset_si; i >= offset_ei; i -= 1) {

            offset += (float) (leftline[i] - ls_std[i] - 10);
            weight += 1;

        }

    } else if (image_para.imgtype == RCIR_W_S3) {
        if (part_type[1] == 8)
            cirsud_i = part_index[0] - 1;
        for (i = offset_si; i >= offset_ei; i -= 1) {


            offset += (float) (rightline[i] - rs_std[i] + 10);
            weight += 1;

        }
    } else if (image_para.imgtype == LCIR_W_S4) {
        if (S3S4_flag == 1)  //����һ�ν���S4�׶�ʱ����֡ͼ��ĸ��������жϲ����˻���S3�׶ε��жϷ����������Ҫ���⴦��
        {
            S3S4_flag = 0;
            for (i = offset_si; i >= offset_ei; i -= 1) {

                //����һ��߽磬��ֹ��Ϊ��ʼ�㵼�±߽���Ҵ���
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
            //����S4�׶ε�offset��ƽ��ֵ����ΪS5�׶ε�ֵ
            if (weight != 0)
                offset_S5 = offset / weight - 10;
            else
                offset_S5 = -45;
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
                offset_S5 = 45;
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
    } else if (image_para.imgtype == LCIR_W_S5 || image_para.imgtype == RCIR_W_S5) //����S5�׶β���S4�׶ε�ƽ��ֵ��Ϊ�俪��ֵ
    {
        offset = offset_S5;
        weight = weight_S5;

        if (weight_S5 < 3) {
            if (image_para.imgtype == LCIR_W_S5)
                offset = -45;
            else if (image_para.imgtype == RCIR_W_S5)
                offset = 45;
            weight = 1;
        }
        if (offset_S5 / weight_S5 >= 45 || offset_S5 / weight_S5 <= -45) {
            if (image_para.imgtype == LCIR_W_S5)
                offset = -45;
            else if (image_para.imgtype == RCIR_W_S5)
                offset = 45;
            weight = 1;
        }

    } else    //������ͨ·�ε�ѭ��
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

    //��ֹ����Ϊ0
    if (weight == 0) {
        weight = 1;
    }
    offset = offset / weight;
    if (flag_starting_line == 1 && (image_para.imgtype != GARAGE_L || image_para.imgtype != GARAGE_R)) {
        if (offset > 5) offset = 5;
        if (offset < -5)offset = -5;
    }
    if (image_para.imgtype == GARAGE_R) {
        bench_v = 30;
        float k = 0;
        for (uint8 k = 30; k < 80; ++k) {
            if (rightline[k + 2] - rightline[k] > 10) {
                p = k;
                break;
            }
        }
        k = (rightline[p] - leftline[119]) / (119 - p);
        for (int l = 119; l > p + 1; --l) {
            leftline[l - 1] = (int) (leftline[l] + k);
            centerline[l - 1] = (int) (rightline[l - 1] + leftline[l - 1]) / 2;
        }
        for (int i = p; i < p + 10; ++i) {
            offset += (float) (centerline[i] - MT9V03X_W / 2);
            weight += 1;
        }
    }

    if (image_para.imgtype == GARAGE_L) {
        offset = -50;
        bench_v = 1;
    }
    if (image_para.imgtype == FINISH) {
        offset = 0;
        bench_v = 0;
        start = 0;
    }
    //�µ�����
//    if(flag_ramp > 20 && offset > 10)
//        offset = 10;
//    else if(flag_ramp > 20 && offset < -10)
//        offset = -10;

    Pixle_ADD_My_Midline();
    Pixle_ADD_My_hengxian(10);
    //Pixle_ADD_My_Leftline();
    error = -offset;
    return offset;
}

void calc_angle() {
    if (image_para.imgtype == LCIR_W_S1 || image_para.imgtype == LCIR_W_S2 || image_para.imgtype == LCIR_W_S2_5 ||
        image_para.imgtype == LCIR_W_S3 || image_para.imgtype == LCIR_W_S4 || image_para.imgtype == LCIR_W_S5 ||
        image_para.imgtype == LCIR_W_S6 || image_para.imgtype == RCIR_W_S1 || image_para.imgtype == RCIR_W_S2 ||
        image_para.imgtype == RCIR_W_S2_5 || image_para.imgtype == RCIR_W_S3 || image_para.imgtype == RCIR_W_S4 ||
        image_para.imgtype == RCIR_W_S5 || image_para.imgtype == RCIR_W_S6 || image_para.imgtype == GARAGE_R ||
        image_para.imgtype == GARAGE_L) {
        degree += yaw_rate;
    } else {
        degree = 0;
    }
}

void check_starting_line() {

    uint8 times = 0;
    uint8 start_point = 85;
    uint8 end_point = 75;

    for (uint8 y = start_point; y >= end_point; y--) {

        uint8 black_blocks = 0;
        uint8 cursor = 0;    //ָ��ջ�����α�
        //int sum_liezuobiao = 0;
        for (uint8 x = 0; x <= 120; x++) {
            if (image_cache[y][x] == 0) {
                if (cursor >= 20) {


                } else {
                    cursor++;;
                }
            } else {
                if (cursor >= 2 && cursor <= 7) {
                    black_blocks++;

                    cursor = 0;
                } else {
                    cursor = 0;

                }
            }
        }

        if (black_blocks >= 5 && black_blocks <= 11) {
            times++;

        }
    }
    if (times >= 4) {
        flag_starting_line = 1;
    } else {
        flag_starting_line = 0;
    }
    if (flag_starting_line == 1 && flag_starting_line_last == 0) {
        starting_line_cnt++;
    }
    flag_starting_line_last = flag_starting_line;
}

void Img_type_test() {

    Boundary_part();

    image_distinguish();
    offset_process();
    calc_angle();

}

/***************ͼ��Ҷ��ж�*************************/
/////////��ֵ�ָ��Լ���ֵ��///////////////
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
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++) HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for (j = 0; j < MT9V03X_H; j++) {
        for (i = 0; i < MT9V03X_W; i++) {
            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue) return MaxValue;         // ͼ����ֻ��һ����ɫ
    if (MinValue + 1 == MaxValue) return MinValue;        // ͼ����ֻ�ж�����ɫ

    for (j = MinValue; j <= MaxValue; j++) Amount += HistoGram[j];        //  ��������

    PixelIntegral = 0;
    for (j = MinValue; j <= MaxValue; j++) {
        PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++) {
        PixelBack = PixelBack + HistoGram[j];   //ǰ�����ص���
        PixelFore = Amount - PixelBack;         //�������ص���
        OmegaBack = (float) PixelBack / Amount;//ǰ�����ذٷֱ�
        OmegaFore = (float) PixelFore / Amount;//�������ذٷֱ�
        PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
        MicroBack = (float) PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
        MicroFore = (float) PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}

//////////ͼ���ѹ////////////
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

