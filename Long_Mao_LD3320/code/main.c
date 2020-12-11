/***************************绿深旗舰店****************************
**	CPU: STC11L08XE
**	晶振：22.1184MHZ
**	波特率：9600 bit/S
**  口令模式： 即每次识别时都需要说“小杰”这个口令 ，才能够进行下一级的识别
/****************************绿深旗舰店*****************************/


#include "config.h"
/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
uint8 idata nAsrStatus=0;
void MCU_init();
void ProcessInt0(); //识别处理函数
void delay(unsigned long uldata);
void User_handle(uint8 dat);//用户执行操作函数
void Delay200ms();
void Led_test(void);//单片机工作指示
uint8_t G0_flag=DISABLE;//运行标志，ENABLE:运行。DISABLE:禁止运行

sbit LED=P4^2;//信号指示灯

sbit SRD1 = P1^7;
sbit SRD2 = P1^6;
sbit SRD3 = P1^5;
sbit SRD4 = P1^4;

//BY8301
sbit OUT1=P2^7;
sbit OUT2=P2^6;
sbit OUT3=P2^5;

//Arduino
sbit OUT4=P3^4;
sbit OUT5=P3^3;
sbit OUT6=P2^3;
sbit OUT7=P2^4;

/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void  main(void)
{
  uint8 idata nAsrRes;
  uint8 i=0;
  P1M0 = 0xFF;
  P1M1 = 0x00;
  SRD1 = SRD2 = SRD3 = SRD4 =0;
  Led_test();
  MCU_init();
  LD_Reset();
  UartIni(); /*串口初始化*/
  nAsrStatus = LD_ASR_NONE;		//	初始状态：没有在作ASR

  while(1)
  {
    switch(nAsrStatus)
    {
    case LD_ASR_RUNING:
    case LD_ASR_ERROR:
      break;
    case LD_ASR_NONE:
    {
      nAsrStatus=LD_ASR_RUNING;
      if (RunASR()==0)	/*	启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算*/
      {
        nAsrStatus = LD_ASR_ERROR;
      }
      break;
    }
    case LD_ASR_FOUNDOK: /*	一次ASR识别流程结束，去取ASR识别结果*/
    {
      nAsrRes = LD_GetResult();		/*获取结果*/
      User_handle(nAsrRes);//用户执行函数
      nAsrStatus = LD_ASR_NONE;
      break;
    }
    case LD_ASR_FOUNDZERO:
    default:
    {
      nAsrStatus = LD_ASR_NONE;
      break;
    }
    }// switch
  }// while

}
/***********************************************************
* 名    称： 	 LED灯测试
* 功    能： 单片机是否工作指示
* 入口参数： 无
* 出口参数：无
* 说    明：
**********************************************************/
void Led_test(void)
{
  LED=~ LED;
  Delay200ms();
  LED=~ LED;
  Delay200ms();
  LED=~ LED;
  Delay200ms();
  LED=~ LED;
  Delay200ms();
  LED=~ LED;
  Delay200ms();
  LED=~ LED;
}
/***********************************************************
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void MCU_init()
{
  P0 = 0xff;
  P1 = 0x00;
  P2 = 0xff;
  P3 = 0xff;
  P4 = 0xff;


  LD_MODE = 0;		//	设置MD管脚为低，并行模式读写
  IE0=1;
  EX0=1;
  EA=1;
}
/***********************************************************
* 名    称：	延时函数
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void Delay200us()		//@22.1184MHz
{
  unsigned char i, j;
  _nop_();
  _nop_();
  i = 5;
  j = 73;
  do
  {
    while (--j);
  }
  while (--i);
}

void  delay(unsigned long uldata)
{
  unsigned int j  =  0;
  unsigned int g  =  0;
  while(uldata--)
    Delay200us();
}

void Delay200ms()		//@22.1184MHz
{
  unsigned char i, j, k;

  i = 17;
  j = 208;
  k = 27;
  do
  {
    do
    {
      while (--k);
    }
    while (--j);
  }
  while (--i);
}

/***********************************************************
* 名    称： 中断处理函数
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void ExtInt0Handler(void) interrupt 0
{
  ProcessInt0();
}
/***********************************************************
* 名    称：用户执行函数
* 功    能：识别成功后，执行动作可在此进行修改
* 入口参数： 无
* 出口参数：无
* 说    明：
**********************************************************/
void 	User_handle(uint8 dat)
{
  if(0==dat)
  {
    G0_flag=ENABLE;
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 0;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		PrintCom("我在\r\n");
		LED = 0;
  }
  else if(ENABLE==G0_flag)
  {
    G0_flag=DISABLE;
    LED=1;
    switch(dat)
		{
		case CODE_1:	 /*bo fang yin yue*/
    OUT1 = 0;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_2:	 /*shi fen zhong*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 0;
		OUT6 = 0;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_3:		/*wan shang hao*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 0;
		OUT6 = 1;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_4:		/*wo ai ni*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 0;
		OUT6 = 1;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_5:		/*wo shi shei*/
    OUT1 = 1;
		OUT2 = 0;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_6:		/*deng guang xiu*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 1;
		OUT6 = 0;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_7:		/*da kai deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 1;
		OUT6 = 0;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_8:		/*guan deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
	case CODE_9:	 /*liang yi dian*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 0;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_10:	 /*an yi dian*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 0;
		OUT6 = 0;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_11:		/*cai de deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 0;
		OUT6 = 0;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_12:		/*cheng se deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 0;
		OUT6 = 1;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_13:		/*lv se deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 0;
		OUT6 = 1;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_14:		/*lan se deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 0;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_15:		/*fen se deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 0;
		OUT7 = 1;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
  case CODE_16:		/*zi se deng*/
    OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
		OUT2 = 1;
		OUT3 = 1;
		OUT4 = 1;
		OUT5 = 1;
		OUT6 = 1;
		OUT7 = 1;
		LED = 1;
    break;
		default:/*text.....*/
			break;
		}
  }
  else
  {
    PrintCom("ERR0R\r\n");
		LED = 1;
  }
}
