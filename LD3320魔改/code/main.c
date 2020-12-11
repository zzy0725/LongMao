#include "config.h"
/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
uint8 idata nAsrStatus=0;
void MCU_init();
void ProcessInt0(); //ʶ������
void delay(unsigned long uldata);
void User_handle(uint8 dat);//�û�ִ�в�������
void Delay200ms();
void Led_test(void);//��Ƭ������ָʾ
uint8_t G0_flag=DISABLE;//���б�־��ENABLE:���С�DISABLE:��ֹ����
sbit LED=P4^2;//�ź�ָʾ��

//�����BY8301�ĵ�ƽ
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
* ��    �ƣ� void  main(void)
* ��    �ܣ� ������	�������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
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
  UartIni(); /*���ڳ�ʼ��*/
  nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR

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
      if (RunASR()==0)	/*	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����*/
      {
        nAsrStatus = LD_ASR_ERROR;
      }
      break;
    }
    case LD_ASR_FOUNDOK: /*	һ��ASRʶ�����̽�����ȥȡASRʶ����*/
    {
      nAsrRes = LD_GetResult();		/*��ȡ���*/
      User_handle(nAsrRes);//�û�ִ�к���
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
* ��    �ƣ� 	 LED�Ʋ���
* ��    �ܣ� ��Ƭ���Ƿ���ָʾ
* ��ڲ����� ��
* ���ڲ�������
* ˵    ����
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


  LD_MODE = 0;		//	����MD�ܽ�Ϊ�ͣ�����ģʽ��д
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
* ��    �ƣ� �жϴ�����
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
**********************************************************/
void ExtInt0Handler(void) interrupt 0
{
  ProcessInt0();
}
//������������޸�COM���ص�ָ��
void 	User_handle(uint8 dat)
{
  if(0==dat)
  {
    G0_flag=ENABLE;
		PrintCom("����\r\n");
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
		case CODE_1:	 /*�����ᳪ����*/
			SRD1 = 1;
			PrintCom("��\r\n");
			OUT2 = 0;
			Delay200ms();
			Delay200ms();
			OUT2 = 1;
			break;
		case CODE_2:	 /*��������衱*/
			SRD1 = 0;
			PrintCom("�⻰��û����\r\n");
			OUT3 = 0;
			Delay200ms();
			Delay200ms();
			OUT3 = 1;
			break;
		case CODE_3:		/*����������ˡ�*/
			SRD2 = 1;
			PrintCom("˵�õ����������\r\n");
			OUT4 = 0;
			Delay200ms();
			Delay200ms();
			OUT4 = 1;
			break;
		case CODE_4:		/*����رյ��ӡ�*/
			SRD2 = 0;
			PrintCom("04���ӻ��ѹر�\r\n");
			break;
		case CODE_5:		/*����򿪷��ȡ�*/
			SRD3 = 1;
			PrintCom("05�����Ѵ�\r\n");
			break;
		case CODE_6:		/*����رշ��ȡ�*/
			SRD3 = 0;
			PrintCom("06�����ѹر�\r\n");
			break;
		case CODE_7:		/*����򿪿յ���*/
			SRD4 = 1;
			PrintCom("07�յ��Ѵ�\r\n");
			break;
		case CODE_8:		/*����رտյ���*/
			SRD4 = 0;
			PrintCom("08�յ��ѹر�\r\n");
			break;
		case CODE_9:		/*���ȫ���򿪡�*/
			SRD1 = 1;
			SRD2 = 1;
			SRD3 = 1;
			SRD4 = 1;
			PrintCom("09��ȫ����\r\n");
			break;
		case CODE_10:		/*���ȫ���رա�*/
			SRD1 = 0;
			SRD2 = 0;
			SRD3 = 0;
			SRD4 = 0;
			PrintCom("10��ȫ���ر�\r\n");
			break;
		//����������Ӻö࣬���19��
		default:/*text.....*/
			break;
		}
  }
  else
  {
    PrintCom("��˵��һ������\r\n"); /*text.....*/
	//û˵һ������
  }
}
