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

//输出到BY8301的电平
sbit OUT1=P2^7;
sbit OUT2=P2^6;
sbit OUT3=P2^5;
sbit OUT4=P2^4;
sbit OUT5=P2^3;
sbit OUT6=P3^3;

sbit SRD1 = P1^7;
sbit SRD2 = P1^6;
sbit SRD3 = P1^5;
sbit SRD4 = P1^4;


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
  Delay200ms();
  LED=~ LED;
  Delay200ms();
  LED=~ LED;
}

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
//这个函数用来修改COM返回的指令
void 	User_handle(uint8 dat)
{
  if(0==dat)
  {
    G0_flag=ENABLE;
		PrintCom("我在\r\n");
		OUT1 = 0;
		Delay200ms();
		Delay200ms();
		OUT1 = 1;
    LED=0;
  }
  else if(ENABLE==G0_flag)
  {
    G0_flag=DISABLE;
    LED=1;
    switch(dat)
		{
		case CODE_1:	 /*命令“你会唱歌吗”*/
			SRD1 = 1;
			PrintCom("好\r\n");
			OUT2 = 0;
			Delay200ms();
			Delay200ms();
			OUT2 = 1;
			break;
		case CODE_2:	 /*命令“操你妈”*/
			SRD1 = 0;
			PrintCom("这话我没法接\r\n");
			OUT3 = 0;
			Delay200ms();
			Delay200ms();
			OUT3 = 1;
			break;
		case CODE_3:		/*命令“你妈死了”*/
			SRD2 = 1;
			PrintCom("说好的以礼相待呢\r\n");
			OUT4 = 0;
			Delay200ms();
			Delay200ms();
			OUT4 = 1;
			break;
		case CODE_4:		/*命令“关闭电视”*/
			SRD2 = 0;
			PrintCom("04电视机已关闭\r\n");
			break;
		case CODE_5:		/*命令“打开风扇”*/
			SRD3 = 1;
			PrintCom("05风扇已打开\r\n");
			break;
		case CODE_6:		/*命令“关闭风扇”*/
			SRD3 = 0;
			PrintCom("06风扇已关闭\r\n");
			break;
		case CODE_7:		/*命令“打开空调”*/
			SRD4 = 1;
			PrintCom("07空调已打开\r\n");
			break;
		case CODE_8:		/*命令“关闭空调”*/
			SRD4 = 0;
			PrintCom("08空调已关闭\r\n");
			break;
		case CODE_9:		/*命令“全部打开”*/
			SRD1 = 1;
			SRD2 = 1;
			SRD3 = 1;
			SRD4 = 1;
			PrintCom("09已全部打开\r\n");
			break;
		case CODE_10:		/*命令“全部关闭”*/
			SRD1 = 0;
			SRD2 = 0;
			SRD3 = 0;
			SRD4 = 0;
			PrintCom("10已全部关闭\r\n");
			break;
		//这里可以增加好多，最多19个
		default:/*text.....*/
			break;
		}
  }
  else
  {
    PrintCom("请说出一级口令\r\n"); /*text.....*/
	//没说一级口令
  }
}
