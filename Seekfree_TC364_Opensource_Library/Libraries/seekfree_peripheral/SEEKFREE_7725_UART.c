/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            7725_UART
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
 * @Software        ADS v1.2.2
 * @Target core     TC364DP
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-11-23
 * @note
					OV7725接线定义：
                    ------------------------------------
                                        模块管脚                     			单片机管脚
                    SDA(51的RX)             		查看MK60DN1_port_cfg.h文件内的UART3_TX_PIN 宏定义
                    SCL(51的TX)       			查看MK60DN1_port_cfg.h文件内的UART3_RX_PIN  宏定义
                                        场中断(VSY)           		查看SEEKFREE_7725_UART.h中的OV7725_UART_VSYNC     宏定义
                                        行中断(HREF)          		未使用，因此不接
                                        像素中断(PCLK)   			查看SEEKFREE_7725_UART.h中的OV7725_UART_PCLK   宏定义
                                        数据口(D0-D7)         		查看SEEKFREE_7725_UART.h中的OV7725_UART_DATAPORT  宏定义
                                        默认分辨率              			 	160*120
                  	默认FPS                  	50帧
                    ------------------------------------
 ********************************************************************************************************************/


#include "IfxDma.h"
#include "IfxScuEru.h"
#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_eru.h"
#include "zf_eru_dma.h"
#include "SEEKFREE_7725_UART.h"
#include "SEEKFREE_OLED.h"
#include "camera_process.h"
IFX_ALIGN(4) uint8 ov7725_uart_image_bin[OV7725_UART_H][OV7725_UART_W/8];	//定义存储接收图像的数组
uint8 ov7725_uart_image_dec[OV7725_UART_H][OV7725_UART_W];


//需要配置到摄像头的数据
uint16 OV7725_CFG[OV7725_CONFIG_FINISH][2]=
{
	{OV7725_RESERVE,           0},
    {OV7725_CONTRAST,       0x30},    	//对比度0x00-0xff(改变这个值 间接实现阈值修改的效果)
    {OV7725_FPS,              50},    	//帧率设置 只支持50 75 100 112 150
    {OV7725_COL,   OV7725_UART_W},    	//只能是80 160 240 320 宽度和高度务必一一对应，例如宽度设置为80，高度只能设置为60。
	{OV7725_ROW,   OV7725_UART_H},    	//只能是60 120 180 240
	
    {OV7725_INIT,              0}     	//摄像头开始初始化
};


//从摄像头内部获取到的配置数据
uint16 OV7725_GET_CFG[OV7725_CONFIG_FINISH-1][2]= 
{
	{OV7725_RESERVE,    	   0},
    {OV7725_CONTRAST,   	   0}, 		
    {OV7725_FPS,        	   0}, 		
    {OV7725_COL,   			   0},    	
	{OV7725_ROW,   			   0}    	
};




uint8   ov7725_uart_receive[3];
uint8   ov7725_uart_receive_num = 0;
uint8   ov7725_uart_receive_flag = 0;




//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风摄像头串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口3中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_callback(void)
{
    uart_getchar(OV7725_COF_UART, &ov7725_uart_receive[ov7725_uart_receive_num]);;
    ov7725_uart_receive_num++;
    
    if(1==ov7725_uart_receive_num && 0XA5!=ov7725_uart_receive[0])	ov7725_uart_receive_num = 0;
    if(3 == ov7725_uart_receive_num)
    {
        ov7725_uart_receive_num = 0;
        ov7725_uart_receive_flag = 1;
    }
        
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风对摄像头内部寄存器进行写操作
//  @param      UARTN_enum   摄像头串口
//  @param      buff    需要写入的数据
//  @return     void  
//  @since      v1.0
//  Sample usage:		调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
void ov7725_set_all_config(UARTN_enum uartn, uint16 buff[OV7725_CONFIG_FINISH-1][2])
{
    uint16 temp, i;
    uint8  send_buffer[4];

    ov7725_uart_receive_flag = 0;
    
    //设置参数  具体请参看问题锦集手册
    //开始配置摄像头并重新初始化
    for(i=0; i<OV7725_CONFIG_FINISH; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = (uint8)buff[i][0];
        temp           = buff[i][1];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(uartn, send_buffer,4);
        systick_delay_ms(STM0, 2);
    }
    //等待摄像头初始化成功
    while(!ov7725_uart_receive_flag);
    ov7725_uart_receive_flag = 0;
    while((0xff != ov7725_uart_receive[1]) || (0xff != ov7725_uart_receive[2]));
    //以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
}

void ov7725_set_CONTRAST(UARTN_enum uartn, uint16 CONTRAST)
{
    uint16 temp;
    uint8  send_buffer[4];

    ov7725_uart_receive_flag = 0;

    send_buffer[0] = 0xA5;
    send_buffer[1] = (uint8)CONTRAST;
    temp           = CONTRAST;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    uart_putbuff(uartn, send_buffer,4);
    systick_delay_ms(STM0, 2);

//    systick_delay_ms(STM0, 2);
//    while(!ov7725_uart_receive_flag);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风获取摄像头内部配置信息
//  @param      UARTN_enum   摄像头串口
//  @param      buff    需要读取的数据
//  @return     void
//  @since      v1.0
//  Sample usage:		调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
void ov7725_get_all_config(UARTN_enum uartn, uint16 buff[OV7725_CONFIG_FINISH-1][2])
{
    uint16 temp, i;
    uint8  send_buffer[4];
    
    for(i=0; i<OV7725_CONFIG_FINISH-1; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = OV7725_GET_STATUS;
        temp           = buff[i][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(uartn, send_buffer,4);
        
        //等待接受回传数据
        while(!ov7725_uart_receive_flag);
        ov7725_uart_receive_flag = 0;
        
        buff[i][1] = ov7725_uart_receive[1]<<8 | ov7725_uart_receive[2];
    }
}


void ov7725_get_config(UARTN_enum uartn, uint16 buff[OV7725_CONFIG_FINISH-1][2])
{
    uint16 temp;
    uint8  send_buffer[4];

        send_buffer[0] = 0xA5;
        send_buffer[1] = OV7725_GET_STATUS;
        temp           = buff[2][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;

        uart_putbuff(uartn, send_buffer,4);

        //等待接受回传数据
        while(!ov7725_uart_receive_flag);
        ov7725_uart_receive_flag = 0;
        buff[2][1] = ov7725_uart_receive[1]<<8 | ov7725_uart_receive[2];
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风获取摄像头固件版本
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:		调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
uint16 ov7725_get_id(UARTN_enum uartn)
{
	uint16 temp;
    uint8  send_buffer[4];
	
    send_buffer[0] = 0xA5;
    send_buffer[1] = OV7725_GET_WHO_AM_I;
    temp           = 0;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn, send_buffer,4);
        
    //等待接受回传数据
    while(!ov7725_uart_receive_flag);
    ov7725_uart_receive_flag = 0;
    
    return ((uint16)(ov7725_uart_receive[1]<<8) | ov7725_uart_receive[2]);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风获取摄像头固件版本
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart3
//-------------------------------------------------------------------------------------------------------------------
uint16 ov7725_get_version(UARTN_enum uartn)
{
    uint16 temp;
    uint8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = OV7725_GET_STATUS;
    temp           = OV7725_GET_VERSION;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn, send_buffer,4);
        
    //等待接受回传数据
    while(!ov7725_uart_receive_flag);
    ov7725_uart_receive_flag = 0;
    
    return ((uint16)(ov7725_uart_receive[1]<<8) | ov7725_uart_receive[2]);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风摄像头初始化(调用之后设置好相关中断函数即可采集图像)
//  @param      NULL
//  @return     0
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_init(void)
{
	uint8 i;

	camera_type = CAMERA_BIN_UART;//设置连接摄像头类型
	camera_buffer_addr = ov7725_uart_image_bin[0];

	boolean interrupt_state = disableInterrupts();

	uart_init (OV7725_COF_UART, 9600, OV7725_COF_UART_TX, OV7725_COF_UART_RX);	//初始换串口 配置摄像头
	enableInterrupts();//开启中断

	ov7725_uart_receive_flag = 0;
	//等待摄像头上电初始化成功 方式有两种：延时或者通过获取配置的方式 二选一
    //systick_delay_ms(STM0, 1000);//延时方式
    ov7725_get_all_config(OV7725_COF_UART, OV7725_GET_CFG);//获取配置的方式

	ov7725_uart_receive_flag = 0;
    ov7725_set_all_config(OV7725_COF_UART, OV7725_CFG);

	//获取配置便于查看配置是否正确
    ov7725_get_all_config(OV7725_COF_UART, OV7725_GET_CFG);
	disableInterrupts();

    //摄像头采集初始化
	//初始化 数据引脚
	for(i=0; i<8; i++)
	{
		gpio_init((PIN_enum)(OV7725_UART_DATA_PIN+i), GPI, 0, PULLUP);
	}

	eru_dma_init(OV7725_UART_DMA_CH, GET_PORT_IN_ADDR(OV7725_UART_DATA_PIN), camera_buffer_addr, OV7725_UART_PCLK_PIN, FALLING, OV7725_UART_DMA_NUM);
	eru_init(OV7725_UART_VSYNC_PIN, FALLING);	//初始化场中断，并设置为下降沿触发中断

	restoreInterrupts(interrupt_state);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风摄像头场中断
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:					在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_vsync(void) 
{
	CLEAR_GPIO_FLAG(OV7725_UART_VSYNC_PIN);

	if(!ov7725_uart_finish_flag)//查看图像数组是否使用完毕，如果未使用完毕则不开始采集，避免出现访问冲突
	{
		DMA_SET_DESTINATION(OV7725_UART_DMA_CH, camera_buffer_addr);
		dma_start(OV7725_UART_DMA_CH);
	}
}


uint8 ov7725_uart_finish_flag = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风摄像头DMA完成中断
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:					在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_dma(void)
{
    CLEAR_DMA_FLAG(OV7725_UART_DMA_CH);
	ov7725_uart_finish_flag = 1;
	dma_stop(OV7725_UART_DMA_CH);

//        GetThreshold();
//        ov7725_set_CONTRAST(UART_1,50);
//        ov7725_get_config(OV7725_COF_UART, OV7725_GET_CFG);
//        oled_printf_OV7725();
        image_decompression(ov7725_uart_image_bin[0],ov7725_uart_image_dec[0]);
//        EagalCameraBeaconHandleGraduateAYear(ov7725_uart_image_dec);
//        FlashHandle();
//        img_extract(ov7725_uart_image_dec,ov7725_uart_image_bin+OV7725_UART_SIZE/12*5,OV7725_UART_SIZE/2);
//        image_decompression(&ov7725_uart_image_bin[0][0],&ov7725_uart_image_dec[0][0]);

//        seekfree_sendimg_7725(UART_2, ov7725_uart_image_dec[0], OV7725_UART_W, OV7725_UART_H/2);
//            seekfree_sendimg_03x(UART_2, &ov7725_uart_image_dec[0][0], OV7725_W, OV7725_H);

        ov7725_uart_finish_flag = 0;
}       


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风摄像头数据解压函数
//  @param      *data1				源地址
//  @param      *data2				目的地址
//  @return     void
//  @since      v1.0
//  Sample usage:					Image_Decompression(da1,dat2[0]);//将一维数组dat1的内容解压到二维数组dat2里.
//-------------------------------------------------------------------------------------------------------------------
void image_decompression(uint8 *data1,uint8 *data2)
{
    uint8  temp[2] = {0,255};
    uint16 lenth = OV7725_UART_SIZE;
    uint8  i = 8;


    while(lenth--)
    {
        i = 8;
        while(i--)
        {
            *data2++ = temp[(*data1 >> i) & 0x01];
        }
        data1++;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风摄像头未解压图像发送至上位机查看图像
//  @param      uartn				使用的串口号
//  @param      image				需要发送的图像地址
//  @param      width				图像的列
//  @param      height				图像的行
//  @return     void
//  @since      v1.0
//  Sample usage:					调用该函数前请先初始化uart2
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_7725(UARTN_enum uartn, uint8 *image, uint16 width, uint16 height)
{
    uart_putchar(uartn, 0x00);uart_putchar(uartn, 0xff);uart_putchar(uartn, 0x01);uart_putchar(uartn, 0x01);//发送四个字节命令
    uart_putbuff(uartn, image, width*height/8);   //再发送图像
}


void oled_printf_OV7725(void)
{
    oled_p6x8str(0,1,"OV7725_RESERVE");
    oled_printf_int32(100,1,OV7725_GET_CFG[0][1],3);
    oled_p6x8str(0,2,"OV7725_CONTRAST");
    oled_printf_int32(100,2,OV7725_GET_CFG[1][1],3);
    oled_p6x8str(0,3,"OV7725_FPS");
    oled_printf_int32(100,3,OV7725_GET_CFG[2][1],3);
    oled_p6x8str(0,4,"OV7725_COL");
    oled_printf_int32(100,4,OV7725_GET_CFG[3][1],3);
    oled_p6x8str(0,5,"OV7725_ROW");
    oled_printf_int32(100,5,OV7725_GET_CFG[4][1],3);
}





//压缩二值化图像解压（空间 换 时间 解压）
//srclen 是二值化图像的占用空间大小
//【鹰眼解压】鹰眼图像解压，转为 二维数组 - 智能车资料区 - 山外论坛 http://vcan123.com/forum.php?mod=viewthread&tid=17&ctid=6
//解压的时候，里面有个数组，配置黑、白对应的值是多少。
//void img_extract(void *dst, void *src, uint32 srclen)
//{
//    uint8 colour[2] = {0, 255}; //0 和 1 分别对应的颜色
//    uint8 * mdst = dst;
//    uint8 * msrc = src;
//    uint8 tmpsrc;
//
//    uint8  temp[2] = {0,255};
//    uint16 lenth = OV7725_UART_SIZE;
//    uint8  i = 8;
//
//
//
//    while(srclen --)
//    {
//        tmpsrc = *msrc++;
//        *mdst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
//        *mdst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
//    }
//}

uint8 ov7725_oled_bmp[OLED_OV7725_H][OLED_OV7725_W];


void oled_ov7725_bmp(uint8 *oled_bmp, uint8 *ov7725_bmp)
{
    uint8 i = 0,j = 0;
//    static uint8 original_image_H = MT9V03X_H;
    static uint8 original_image_W = MT9V03X_W;
//    uint8 * my_oled_bmp = oled_bmp;
//    uint8 * my_ov7725_bmp = ov7725_bmp;
    for(i=0;i<OLED_OV7725_H-1;i++)
    {
        for(j=0;j<OLED_OV7725_W-1;j++)
        {
            *(oled_bmp+i*OLED_OV7725_W+j) = *(ov7725_bmp+i*original_image_W+j+(original_image_W-OLED_OV7725_W)/2);
        }
    }
}
