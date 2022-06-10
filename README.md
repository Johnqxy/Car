# 浙大方案

## 基础巡线----基于钱玄宇修改

基础思想：从中间向两边扫。

原方案为使用和差比算法计算灰度值判断边界从中间向两边扫，可能是考虑单片机性能较弱，本方案使用大津法进行二值化处理，获得边界更为简单。

源代码相关变量：

```c
int16 leftside[MT9V03X_H];      //左边界j值数组，0表示左边界丢失
int16 rightside[MT9V03X_H];     //右边界j值数组，MT9V03X_W-1表示右边界丢失
int16 centerline[MT9V03X_H];    //中心线数组
int16 roweff_flag[MT9V03X_H];   //行有效标志位，（初步类型判断）0表示行左右边界均存在，1表示左边界缺失，2表示行右边界缺失，3表示行左右边界均缺失，-1表示该行无效
//（完整类型判断）0表示双边界均存在，1表示左边界只是看不见了但不是突变缺失，2表示有边界看不见了但不是突变缺失，3表示双边界都没有，但中间都是赛道，一般用于十字路口判断
//4表示三岔的发散类型，5表示左边界（相对于正常左边界）突变缺失，6表示右边界（相对于正常右边界）突变缺失，7表示左边界向内突变，8表示右边界向内突变，-1表示该行无效（其中7和8只在环岛内使用）

//左边界标准数组，表示当车模处于赛道正中间时看到的左边界数组，用来计算当车模偏离赛道中心时的偏差值
int16 ls_std[MT9V03X_H];

//右边界标准数组，表示当车模处于赛道正中间时看到的右边界数组，用来计算当车模偏离赛道中心时的偏差值，以上两个数组数据靠实测取得
int16 rs_std[MT9V03X_H];
//最后两个我们不用
```

## 赛道分段

获得赛道的段数与每段的种类，便于元素识别。

```c
part_flag = roweff_flag[MT9V03X_H-1];//第一段为最下方的种类
```

```c
for(i = MT9V03X_H-2; i > END_I; i -= 1)
{
    if(part_flag == roweff_flag[i])
        partcnt += 1;//如果等于，则段长度计数一直增加。
    else{//如果发生跳变
        if(partcnt > C_TH)//计数长度大于段最小长度（滤波）
        {
            part_type[part_i] = part_flag;//段种类
            part_index[part_i] = i+1;//段长度下标
            part_i += 1;//段号
            part_flag = roweff_flag[i];//新的段号
            partcnt = 1;//段长度计数清零
        }
        else{//计数长度小于段最小长度（滤波）
            part_flag = roweff_flag[i];//
            partcnt = 1;//段长度计数清零
        }
    }
}
//
1
1
1
1
1
0 假设小于cth跳变
0 flag=0->1
0 段不会被记录
1 假设大于cth跳变
1 flag=1->0
1 段被记录
1
//
if(partcnt > C_TH)//屏幕最后一段判断
{
    part_type[part_i] = part_flag;
    part_index[part_i] = i+1;
    part_num = part_i+1;
}
else
{
    part_num = part_i;
    part_index[part_i-1] = i+1;
}
```

```c
part_mi = 1;
for(part_i = 1; part_i < part_num; part_i += 1)
{
    if(part_type[part_i] == part_type[part_mi-1])//1=0? 第0段下标转变为第1段下标 (前一段变为下一段
        part_index[part_mi-1] = part_index[part_i];
    else
    {
        part_type[part_mi] = part_type[part_i];//不变
        part_index[part_mi] = part_index[part_i];
        part_mi += 1;
    }
}
part_num = part_mi;
```

## 元素识别

相关变量:

```c
int16 img_mode = 0;                 //图像识别模数，0表示正常模式，1表示环岛预识别模式，2表示环岛模式，3表示三岔模式

typedef enum
{
    none = 0,               //无类型

    STR_W,                  //直道
    CUR_W,                  //弯道（好像没用到）

    CRS_W_S1,               //十字阶段1（入十字）
    CRS_W_S2,               //十字阶段2（出十字）

    FOK_W_S1,               //三岔阶段1（入三岔，可以看到三岔下面的直道）
    FOK_W_S2,               //三岔阶段2（看不到直道了）
    FOK_W_S3,               //三岔阶段3（停车旋转）

    //左环
    LCIR_W_S1,              //环岛阶段1（初入左环岛，看到了直道后左边界缺失了但有边界是直线，可能会误判）
    LCIR_W_S2,              //环岛阶段2（环岛确认，发现S1阶段后出现了最下面一段是左边界没有了）
    LCIR_W_S2_5,            //环岛阶段2.5（S3的准备阶段，看到双边界都有时进入，说明在环岛直道的中间）
    LCIR_W_S3,              //环岛阶段3（入环阶段，寻找特殊点，补线入环）
    LCIR_W_S4,              //环岛阶段4（环内阶段）
    LCIR_W_S5,              //环岛阶段5（出环阶段，发现边界出现了类型为3或6的段）
    LCIR_W_S6,              //环岛阶段6（出环结束，在圆环的直道上，通过陀螺仪判断）
    LCIR_W_S7,              //环岛阶段7（准备彻底驶出环岛，再次走到了S3阶段的位置，但判断条件是，第二段为正常边界）

    //右环
    RCIR_W_S1,              //环岛阶段1
    RCIR_W_S2,              //环岛阶段2
    RCIR_W_S2_5,            //环岛阶段2.5
    RCIR_W_S3,              //环岛阶段3
    RCIR_W_S4,              //环岛阶段4
    RCIR_W_S5,              //环岛阶段5
    RCIR_W_S6,              //环岛阶段6
    RCIR_W_S7,              //环岛阶段7
} image_type;

//从图像中提取出的信息结构体
typedef struct
{
    image_type imgtype;     //图像类型
    float offset;           //位置偏差
} image_parameter;
```

一步步来

```c
if(img_mode == 0 && start == 1)
{
    //当赛道的分段数为1时
    if(part_num == 1)
    {
        if(part_type[0] == 3)       //出现3种类，说明是十字路口S1阶段 在路口中间两边全丢,且只有一段,我们逆透视后效果未知
            img_type = CRS_W_S1;
        else if(part_type[0] == 0)  //出现0种类，说明是直道或小弯 好理解
            img_type = STR_W;
    }
    //当赛道的分段数为2时
    else if(part_num == 2)
    {
        if(part_type[0] == 0 && part_type[1] == 3)      //出现先直道0然后空白区域3，说明前方是十字路口S1阶段
            img_type = CRS_W_S1;
        else if(part_type[0] == 3 && part_type[1] == 0) //出现先空白区域3后直道0，说明前方是出十字的S2阶段
            img_type = CRS_W_S2;
        else if(part_type[0] == 0 && part_type[1] == 5 && cur_circle(1) >= CUR_CIRTH)   //如果出现先0然后左边界突变5并且右边是直的边界，说明是预进入左环岛
        	{
            img_type = LCIR_W_S1;
#ifdef MASTER
                img_mode = 1;           //预进入环岛模式，修改图像识别模式为1
#endif
         	}
        else if(part_type[0] == 0 && part_type[1] == 6 && cur_circle(0) >= CUR_CIRTH)   //如果出现先0然后右边界突变6并且左边是直的边界，说明是预进入右环岛
            {
                img_type = RCIR_W_S1;
#ifdef MASTER
                img_mode = 1;           //预进入环岛模式，修改图像识别模式为1
#endif
            }
        else if(part_type[0] == 0 && part_type[1] == 4 && part_index[0]-part_index[1] > 10) //如果出现了先0后双边界发散4并且发散长度超过10行，说明看到了三岔S1阶段
            {
                img_type = FOK_W_S1;
                img_mode = 3;           //三岔模式，修改图像识别模式为3
            }
        }
    	//当赛道的分段数大于等于3时
        else
        {
            if(part_type[0] == 0 && part_type[1] == 3)
                img_type = CRS_W_S1;
            else if(part_type[0] == 0 && (part_type[1] == 5 || part_type[1] == 6) && part_type[2] == 3) //这是斜入十字的情形
                img_type = CRS_W_S1;
            else if(part_type[0] == 3 && part_type[1] == 0)
                img_type = CRS_W_S2;
            else if(part_type[0] == 3 && (part_type[1] == 5 || part_type[1] == 6) && part_type[2] == 0) //这是斜出十字的情形
                img_type = CRS_W_S2;
            else if(part_type[0] == 0 && part_type[1] == 5 && cur_circle(1) >= CUR_CIRTH)//同上 预备进环岛
            {
                img_type = LCIR_W_S1;
#ifdef MASTER
                img_mode = 1;
#endif
            }
            else if(part_type[0] == 0 && part_type[1] == 6 && cur_circle(0) >= CUR_CIRTH)
            {
                img_type = RCIR_W_S1;
#ifdef MASTER
                img_mode = 1;
#endif
            }//右环岛
            else if(part_type[1] == 0 && part_type[2] == 5 && cur_circle(1) >= CUR_CIRTH)
            {
                img_type = LCIR_W_S1;
#ifdef MASTER
                img_mode = 1;
#endif
            }
            else if(part_type[1] == 0 && part_type[2] == 6 && cur_circle(0) >= CUR_CIRTH)
            {
                img_type = RCIR_W_S1;
#ifdef MASTER
                img_mode = 1;
#endif
            }//上面应该是靠近车体的第一段有什么东西,从第二段开始看
            else if(part_type[0] == 0 && part_type[1] == 4 && part_index[0]-part_index[1] > 10)
            {
                img_type = FOK_W_S1;
                img_mode = 3;
            }//入三叉
            else if((part_type[0] == 1 || part_type[0] == 2) && part_type[1] == 0 && part_type[2] == 4 && part_index[0]-part_index[1] > 10)
            {
                img_type = FOK_W_S1;
                img_mode = 3;
            }//斜入三叉
        }
    }
else if(img_mode == 1 && start == 1)
    {
        if(part_num == 1)
        {
            if(part_type[0] == 0)
            {
                img_type = STR_W;
                img_mode = 0;           //表示前方并不是环岛，需要退出1模式，返回0模式
            }
            else if(part_type[0] == 3)//如果斜入十字误识别
            {
                img_type = CRS_W_S1;
                img_mode = 0;
            }
            else if(part_type[0] == -1)//冗余
            {
                img_type = none;
                img_mode = 0;
            }
        }
        else if(part_num == 2)
        {
            if(part_type[0] == 0 && part_type[1] == 5)
                img_type = LCIR_W_S1;
            else if(part_type[0] == 0 && part_type[1] == 6)
                img_type = RCIR_W_S1;
            else if(part_type[1] == 0 && part_type[2] == 5)
                img_type = LCIR_W_S1;
            else if(part_type[1] == 0 && part_type[2] == 6)
                img_type = RCIR_W_S1;//上面没什么
            else if(part_type[0] == 0 && (part_type[1] == 1 || part_type[1] == 2))
            {
                img_type = CUR_W;
                img_mode = 0;
            }//弯道,据说没用到
            else if(part_type[0] == 0 && part_type[1] == 3)//入十字误识别
            {
                img_type = CRS_W_S1;
                img_mode = 0;
            }
            else if(part_type[0] == 0 && part_type[1] == 4 && part_index[0]-part_index[1] > 10)//入三叉误识别
            {
                img_type = FOK_W_S1;
                img_mode = 3;
            }
            else if(part_type[0] == 1 && part_type[1] == 0) //这是入环的一个必经阶段，当在1模式下看到此阶段，说明确认进入环岛 环岛的中间阶段
            {
                img_type = LCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;       //进入环岛S2阶段后将特殊点清零，进行S3阶段的搜索（期间还会经过一个S2_5阶段，为防止错误进入S3阶段）
            }
            else if(part_type[0] == 5 && part_type[1] == 0)
            {
                img_type = LCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;
            }
            else if(part_type[0] == 2 && part_type[1] == 0)
            {
                img_type = RCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;
            }
            else if(part_type[0] == 6 && part_type[1] == 0)
            {
                img_type = RCIR_W_S2;
                img_mode = 2;
                cirsud_i = 0;
            }
            else if(part_type[0] == -1)
            {
                img_type = none;
                img_mode = 0;
            }
        }    
    	else//对于有更多段的冗余
        {
            if(part_type[0] == 0 && part_type[1] == 3)
            {
                img_type = CRS_W_S1;
                img_mode = 0;
            }
            else if(part_type[0] == 0 && (part_type[1] == 5 || part_type[1] == 6) && part_type[2] == 3)
            {
                img_type = CRS_W_S1;
                img_mode = 0;
            }
            else if(part_type[0] == 3 && part_type[1] == 0)
            {
                img_type = CRS_W_S2;
                img_mode = 0;
            }
            else if(part_type[0] == 3 && (part_type[1] == 5 || part_type[1] == 6) && part_type[2] == 0)
            {
                img_type = CRS_W_S2;
                img_mode = 0;
            }
            else if(part_type[0] == 0 && part_type[1] == 5)
                img_type = LCIR_W_S1;
            else if(part_type[0] == 0 && part_type[1] == 6)
                img_type = RCIR_W_S1;
            else if(part_type[1] == 0 && part_type[2] == 5)
                img_type = LCIR_W_S1;
            else if(part_type[1] == 0 && part_type[2] == 6)
                img_type = RCIR_W_S1;
            else if(part_type[0] == 0 && part_type[1] == 4 && part_index[0]-part_index[1] > 10)
            {
                img_type = FOK_W_S1;
                img_mode = 3;
            }
            else if((part_type[0] == 1 || part_type[0] == 2) && part_type[1] == 4 && part_index[0]-part_index[1] > 10)
            {
                img_type = FOK_W_S1;
                img_mode = 3;
            }
            else if(part_type[0] == 1 && part_type[1] == 0)
            {
                img_type = LCIR_W_S2;
                img_mode = 2;
            }
            else if(part_type[0] == 2 && part_type[1] == 0)
            {
                img_type = RCIR_W_S2;
                img_mode = 2;
            }
            else if(part_type[0] == -1)
            {
                img_type = none;
                img_mode = 0;
            }
        }
	}
```