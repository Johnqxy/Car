/*********************************************************************************************************************
 *
 * @file       		BMX055
 * @author     		Alex
 * @version    		v1.0
 * @Software 		IAR 8.1
 * @date       		2017-11-9
 ********************************************************************************************************************/

////////更改使用为模拟I2C
#include "headfile.h"
#include "SEEKFREE_IIC.h"

extern float QZAngle,AccZAngle;
float GYRO_Speed_Z=0;

float pitch = 0;
float roll  = 0;
float yaw   = 0;
float pitch_rate = 0;
float roll_rate  = 0;
float yaw_rate   = 0;

//    S_FLOAT_XYZ
//	GYRO_Real,		// 陀螺仪转化后的数据
//	ACC_Real,		// 加速度计转化后的数据
//	Attitude_Angle,	// 当前角度
//	Last_Angle,		// 上次角度
//	Target_Angle;	// 目标角度

uint8 testid= 0;
uint8  BMX055_init(void)//引脚的配置在逐飞模拟iic的库里
{
  uint8 ErrCount = 0;
  

   /************************************/
  /*加速度配置*/
  /************************************/
  while(simiic_read_reg(IIC_BMX055_ACC_ADR, BMX055_ACC_ID,SIMIIC) != 0xFA)   /////确认芯片ID
  {
     ErrCount++;
    if(ErrCount > 5)
      return 0;
  }
  simiic_write_reg(IIC_BMX055_ACC_ADR, BMX055_ACC_PMURANGE, 0x05);  ///4G
  simiic_delay();
  simiic_write_reg(IIC_BMX055_ACC_ADR, BMX055_ACC_PMUBW, 0x0F);   ///1000HZ
  simiic_delay();
  simiic_write_reg(IIC_BMX055_ACC_ADR, BMX055_ACC_PMULPM, 0x00);  ///Normal MODE
  
  
   /************************************/
  /*陀螺仪配置*/
  /************************************/ 
  ErrCount = 0;
  while(simiic_read_reg(IIC_BMX055_GYRO_ADR, BMX055_GYRO_ID,SIMIIC) != 0x0F)   /////确认芯片ID
  {
    ErrCount++;
    if(ErrCount > 5)
      return 0;
   }
  simiic_write_reg(IIC_BMX055_GYRO_ADR, BMX055_GYRO_RANGE, 0x01);   ///+-1000
  simiic_delay();
  simiic_write_reg(IIC_BMX055_GYRO_ADR, BMX055_GYRO_BW, 0x02);     ///1000HZ
  simiic_delay();
  simiic_write_reg(IIC_BMX055_GYRO_ADR, BMX055_GYRO_LPM, 0x00);   ///Normal MODE
  simiic_delay();
  simiic_write_reg(IIC_BMX055_GYRO_ADR, BMX055_GYRO_RATEHBW, 0x08);   ///高通滤波 ，可以不要
  simiic_delay();
  
  
  /************************************/
  /*磁力计配置*/
  /************************************/
  ErrCount = 0;
  simiic_write_reg(IIC_BMX055_MAG_ADR, BMX055_MAG_POM, 0x81);
  simiic_delay();
  while(simiic_read_reg(IIC_BMX055_MAG_ADR, BMX055_MAG_ID,SIMIIC) != 0x32)   /////确认芯片ID
  {
    ErrCount++;
    if(ErrCount > 5)
      return 0;
  }  
  simiic_write_reg(IIC_BMX055_MAG_ADR, BMX055_MAG_DATARATE, 0x38);   ///输出速率30HZ
  simiic_delay();
  simiic_write_reg(IIC_BMX055_MAG_ADR, BMX055_MAG_INTEN, 0x00);      ///不使能中断
  simiic_delay();

  return 1;
}

//////错误读取将返回false
uint8 BMX055_DataRead(BMX055Datatypedef *Q, uint8 type)
{
  uint8 datatemp[6] = {0};

  simiic_read_regs(IIC_BMX055_GYRO_ADR, BMX055_GYRO_XDATALSB, datatemp, 6,SIMIIC);
  Q->GYROXdata = (float)((int16)((datatemp[1] << 8) | datatemp[0]));
  Q->GYROYdata = (float)((int16)((datatemp[3] << 8) | datatemp[2]));
  Q->GYROZdata = (float)((int16)((datatemp[5] << 8) | datatemp[4]));
  simiic_read_regs(IIC_BMX055_ACC_ADR, BMX055_ACC_XDATALSB, datatemp, 6,SIMIIC);
  Q->ACCXdata = (float)((int16)((datatemp[1] << 8) | datatemp[0]) >> 4);
  Q->ACCYdata = (float)((int16)((datatemp[3] << 8) | datatemp[2]) >> 4);
  Q->ACCZdata = (float)((int16)((datatemp[5] << 8) | datatemp[4]) >> 4);
  /************************************/
  /*磁力计数据读取*/
  /************************************/
  if(type)
  {
    simiic_read_regs(IIC_BMX055_MAG_ADR, BMX055_MAG_XDATALSB, datatemp, 6,SIMIIC);
    Q->MAGXdata = (float)((int16)((datatemp[1] << 8) | datatemp[0]) >> 3);
    Q->MAGYdata = (float)((int16)((datatemp[3] << 8) | datatemp[2]) >> 3);
    Q->MAGZdata = (float)((int16)((datatemp[5] << 8) | datatemp[4]) >> 1);
  }

  return 1;
}




unsigned short int    enter_circle;
BMX055Datatypedef      BMX055_data;
EulerAngleTypedef      SystemAttitude;            /////姿态角
EulerAngleTypedef      SystemAttitudeRate;        /////姿态角速度
AttitudeDatatypedef    GyroOffset;
float AccZAngle = 0;//加速度计反正切角度
float QZAngle = 0; //欧拉角
void GyroOffset_init(void)      /////////陀螺仪零飘初始化
{
  static uint16 Count = 0;
  if(Count == 0)
  {
    GyroOffset.Xdata = 0;
    GyroOffset.Ydata = 0;
    GyroOffset.Zdata = 0;
  }
  
  if(Count == 1000)
  {
    GyroOffset.Xdata /= 1000;
    GyroOffset.Ydata /= 1000;
    GyroOffset.Zdata /= 1000;
   // IsGyroOffsetReset = false;
    Count = 0;
  }
  else
  {
    BMX055_DataRead(&BMX055_data, 0);
    GyroOffset.Xdata = BMX055_data.GYROXdata;
    GyroOffset.Ydata = BMX055_data.GYROYdata;
    GyroOffset.Zdata = BMX055_data.GYROZdata;
    Count++;
  }
}

void Negative_treatment()//将值加成正数方便使用
{
    pitch = SystemAttitude.Pitch + 180;
    roll  = SystemAttitude.Roll  + 180;
    yaw   = SystemAttitude.Yaw   + 180;

    pitch_rate = SystemAttitudeRate.Pitch;
    roll_rate  = SystemAttitudeRate.Roll;
    yaw_rate   = -SystemAttitudeRate.Yaw;

}

void Get_Car_Angle(void)           //获取陀螺仪角度（完成）
{
    static uint8 IsAttitudeinit = 0;
    BMX055_DataRead(&BMX055_data, 0);
    GYRO_Speed_Z=(BMX055_data.GYROZdata - GyroOffset.Zdata);
    BMX055_data.GYROXdata = (BMX055_data.GYROXdata - GyroOffset.Xdata) * 0.030517578;   //下面这六段就是单位换算
    BMX055_data.GYROYdata = (BMX055_data.GYROYdata - GyroOffset.Ydata) * 0.030517578;
    BMX055_data.GYROZdata = (BMX055_data.GYROZdata - GyroOffset.Zdata) * 0.030517578;
  ///////1000 / 32768     //////BMX055本身零飘几乎可以忽略不计，但是安全起见还是矫正一下
    BMX055_data.ACCXdata *= 0.001953125;    ///////4 / 2048
    BMX055_data.ACCYdata *= 0.001953125;
    BMX055_data.ACCZdata *= 0.001953125;
   
    Acc.Xdata = BMX055_data.ACCXdata;
    Acc.Ydata = BMX055_data.ACCYdata;
    Acc.Zdata = BMX055_data.ACCZdata;
    Gyro.Xdata = BMX055_data.GYROXdata;
    Gyro.Ydata = BMX055_data.GYROYdata;
    Gyro.Zdata = BMX055_data.GYROZdata;  
    if(IsAttitudeinit == 0)
    {
      Quaternion_init();                    ////姿态解算初始化        
      IsAttitudeinit = 1;
    }
    else
    {
      Attitude_UpdateGyro();                /////快速更新
      Attitude_UpdateAcc();                 /////深度融合更新
      SystemAttitude.Pitch = -EulerAngle.Roll / PI * 180;         ////转为角度
      SystemAttitude.Roll = EulerAngle.Pitch / PI * 180;
      SystemAttitude.Yaw = EulerAngle.Yaw / PI * 180;
      SystemAttitudeRate.Pitch = -EulerAngleRate.Roll/ PI * 180;
      SystemAttitudeRate.Roll = EulerAngleRate.Pitch / PI * 180;
      SystemAttitudeRate.Yaw = EulerAngleRate.Yaw / PI * 180;//正负号需要根据芯片摆放修改
    /////为了更精准的获得俯仰角，再次进行互补滤波
     float AccZ = 0, AccZAdjust = 0;    
      AccZ = -Acc.Zdata;
     if (AccZ > 1)
	AccZ = 1;
     if (AccZ < -1)
	AccZ = -1;            
     AccZAngle = asinf(AccZ) * 180 / PI;
     QZAngle = SystemAttitude.Pitch;
     AccZAdjust = (AccZAngle - SystemAttitude.Pitch);
     SystemAttitude.Pitch += (-Gyro.Ydata + AccZAdjust) * PERIODS;
    }
    
    Negative_treatment();//把角度转成0~360（原来是-180 ~ 180）
}
void Get_Car_GYRO(void)           //获取陀螺仪角度（完成）
{
   BMX055_data.GYROXdata = (BMX055_data.GYROYdata - GyroOffset.Ydata) * 0.030517578;   
   Gyro.Ydata = BMX055_data.GYROYdata;
}

void oled_show_gyroscope(void)
{

//            ips114_showfloat(45,1,pitch_rate,3,2);
//            ips114_showfloat(45,2,roll_rate,3,2);
            ips114_showstr(0,1,"pitch");
            ips114_showfloat(70,1,pitch,3,2);
            ips114_showstr(0,2,"roll");
            ips114_showfloat(70,2,roll,3,2);
            ips114_showstr(0,3,"yaw");
            ips114_showfloat(70,3,yaw,3,2);
            ips114_showstr(0,4,"pitch_rate");
            ips114_showfloat(70,4,pitch_rate,3,2);
            ips114_showstr(0,5,"roll_rate");
            ips114_showfloat(70,5,roll_rate,3,2);
            ips114_showstr(0,6,"yaw_rate");
            ips114_showfloat(70,6,yaw_rate,3,2);
}


