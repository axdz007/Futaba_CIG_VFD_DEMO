#include "FUTABA_VFD.h"
#include "delay.h"
#include "stm32f0xx_gpio.h"

#define RST_H	GPIO_WriteBit(VFD_RST_PORT,VFD_RST_PIN,Bit_SET) 
#define RST_L	GPIO_WriteBit(VFD_RST_PORT,VFD_RST_PIN,Bit_RESET)

#define CS_H	GPIO_WriteBit(VFD_CS_PORT,VFD_CS_PIN,Bit_SET)
#define CS_L	GPIO_WriteBit(VFD_CS_PORT,VFD_CS_PIN,Bit_RESET)

#define CLK_H	GPIO_WriteBit(VFD_CLK_PORT,VFD_CLK_PIN,Bit_SET)
#define CLK_L	GPIO_WriteBit(VFD_CLK_PORT,VFD_CLK_PIN,Bit_RESET)

#define DIN_H	GPIO_WriteBit(VFD_DIN_PORT,VFD_DIN_PIN,Bit_SET)
#define DIN_L	GPIO_WriteBit(VFD_DIN_PORT,VFD_DIN_PIN,Bit_RESET)

static unsigned char VSTAB[5]={0X00,0X00,0X00,0X00,0X00};

	uint8_t 
	Vs_power=1,
	Vs_sat=1,
	Vs_rec=1,
	Vs_radio=1,
	Vs_tea=1,
	Vs_tv=1,
	Vs_file=1,
	Vs_S1=1,
	Vs_S2=1,
	Vs_S3,
	Vs_S4,
	Vs_S5,
	Vs_S6,
	Vs_S7,
	Vs_S8,
	Vs_S9,
	Vs_S10,
	Vs_1080p=1,
	Vs_1080i=1,
	Vs_720p=1,
	Vs_576=1,
	Vs_i576=1,
	Vs_p576=1,
	Vs_480=1,
	Vs_i480=1,
	Vs_p480=1;

uint8_t
VAnim_En=1,
VAnim_Mode,
VAnim_Dir;

uint8_t Vfd_Timer_Tick;
uint8_t Vfd_Anim_Tick;
uint8_t Vfd_Anim_En;
uint8_t Vfd_Anim_Count;


void VSy_Calc(void)
{
	switch(Vfd_Anim_Count)
	{/*
		case 0:Vs_S3=1;Vs_S5=0;Vs_S7=0;Vs_S9=0;Vs_S10=0;Vs_S8=0;Vs_S6=0;Vs_S4=0;break;
		case 1:Vs_S3=0;Vs_S5=1;Vs_S7=0;Vs_S9=0;Vs_S10=0;Vs_S8=0;Vs_S6=0;Vs_S4=0;break;
		case 2:Vs_S3=0;Vs_S5=0;Vs_S7=1;Vs_S9=0;Vs_S10=0;Vs_S8=0;Vs_S6=0;Vs_S4=0;break;
		case 3:Vs_S3=0;Vs_S5=0;Vs_S7=0;Vs_S9=1;Vs_S10=0;Vs_S8=0;Vs_S6=0;Vs_S4=0;break;
		case 4:Vs_S3=0;Vs_S5=0;Vs_S7=0;Vs_S9=0;Vs_S10=1;Vs_S8=0;Vs_S6=0;Vs_S4=0;break;
		case 5:Vs_S3=0;Vs_S5=0;Vs_S7=0;Vs_S9=0;Vs_S10=0;Vs_S8=1;Vs_S6=0;Vs_S4=0;break;
		case 6:Vs_S3=0;Vs_S5=0;Vs_S7=0;Vs_S9=0;Vs_S10=0;Vs_S8=0;Vs_S6=1;Vs_S4=0;break;
		case 7:Vs_S3=0;Vs_S5=0;Vs_S7=0;Vs_S9=0;Vs_S10=0;Vs_S8=0;Vs_S6=0;Vs_S4=1;break;
		*/
		case 0:Vs_S3=0;Vs_S5=1;Vs_S7=1;Vs_S9=1;Vs_S10=1;Vs_S8=1;Vs_S6=1;Vs_S4=1;Vs_1080p=1;Vs_1080i=1;Vs_720p=1;Vs_576=1;Vs_i576=1;Vs_p576=1;Vs_480=1;Vs_i480=1;Vs_p480=1;Vs_power=1;Vs_rec=1;Vs_radio=1;Vs_tv=1;Vs_sat=1;Vs_tea=1;Vs_file=1;break;
		case 1:Vs_S3=1;Vs_S5=0;Vs_S7=1;Vs_S9=1;Vs_S10=1;Vs_S8=1;Vs_S6=1;Vs_S4=1;break;
		case 2:Vs_S3=1;Vs_S5=1;Vs_S7=0;Vs_S9=1;Vs_S10=1;Vs_S8=1;Vs_S6=1;Vs_S4=1;break;
		case 3:Vs_S3=1;Vs_S5=1;Vs_S7=1;Vs_S9=0;Vs_S10=1;Vs_S8=1;Vs_S6=1;Vs_S4=1;break;
		case 4:Vs_S3=1;Vs_S5=1;Vs_S7=1;Vs_S9=1;Vs_S10=0;Vs_S8=1;Vs_S6=1;Vs_S4=1;Vs_1080p=0;Vs_1080i=0;Vs_720p=0;Vs_576=0;Vs_i576=0;Vs_p576=0;Vs_480=0;Vs_i480=0;Vs_p480=0;Vs_power=0;Vs_rec=0;Vs_radio=0;Vs_tv=0;Vs_sat=0;Vs_tea=0;Vs_file=0;break;
		case 5:Vs_S3=1;Vs_S5=1;Vs_S7=1;Vs_S9=1;Vs_S10=1;Vs_S8=0;Vs_S6=1;Vs_S4=1;break;
		case 6:Vs_S3=1;Vs_S5=1;Vs_S7=1;Vs_S9=1;Vs_S10=1;Vs_S8=1;Vs_S6=0;Vs_S4=1;break;
		case 7:Vs_S3=1;Vs_S5=1;Vs_S7=1;Vs_S9=1;Vs_S10=1;Vs_S8=1;Vs_S6=1;Vs_S4=0;break;
	}
	
	VSTAB[0]=(0x01*Vs_power)	+	(0x02*Vs_tv)	+	(0X04*Vs_S4)	+	(0X08*Vs_S9)		+	(0x10*Vs_576)	+	(0x20*Vs_p480);
	VSTAB[1]=(0x01*Vs_sat)		+	(0x02*Vs_file)+	(0X04*Vs_S5)	+	(0X08*Vs_S10)		+	(0x10*Vs_i576);
	VSTAB[2]=(0x01*Vs_rec)		+	(0x02*Vs_S1)	+	(0X04*Vs_S6)	+	(0X08*Vs_1080p)	+	(0x10*Vs_p576);
	VSTAB[3]=(0x01*Vs_tv)			+	(0x02*Vs_S2)	+	(0X04*Vs_S7)	+	(0X08*Vs_1080i)	+	(0x10*Vs_480);
	VSTAB[4]=(0x01*Vs_tea)		+	(0x02*Vs_S3)+	(0X04*Vs_S8)	+	(0X08*Vs_720p)		+	(0x10*Vs_i480);

}



void VFD_GPIO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(VFD_CS_RCC|VFD_RST_RCC|VFD_CLK_RCC|VFD_DIN_RCC, ENABLE);

	/*CS\*/
  GPIO_InitStructure.GPIO_Pin = VFD_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = VFD_CS_SPEED;
  GPIO_Init(VFD_CS_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(VFD_CS_PORT,VFD_CS_PIN,Bit_SET);
	
  /*RST*/
  GPIO_InitStructure.GPIO_Pin = VFD_RST_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = VFD_RST_SPEED;
  GPIO_Init(VFD_RST_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(VFD_RST_PORT,VFD_RST_PIN,Bit_SET);
	
	/*CLK*/
	GPIO_InitStructure.GPIO_Pin = VFD_CLK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = VFD_CLK_SPEED;
  GPIO_Init(VFD_CLK_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(VFD_CLK_PORT,VFD_CLK_PIN,Bit_SET);
	
	/*DIN*/
	GPIO_InitStructure.GPIO_Pin = VFD_DIN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = VFD_DIN_SPEED;
  GPIO_Init(VFD_DIN_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(VFD_DIN_PORT,VFD_DIN_PIN,Bit_SET);
}

void vfd_reset(void)
{
	RST_H;
	RST_L;
	delay_ms(10);
	RST_H;
	delay_ms(20);
}

void vfd_start(void)
{
	CS_L;
	delay_us(2);
}

void vfd_stop(void)
{
	delay_us(2);
	CS_H;
	delay_us(2);
}

void vfd_send_data(uint8_t data)
{
	uint8_t i;
	delay_us(1);
	for(i=0;i<8;i++)
	{
		CLK_L;
		delay_us(1);
		if(data&0x01)
		{
		DIN_H;
		}
		else
		{
			DIN_L;
		}
		delay_us(1);
		CLK_H;
		delay_us(1);
		data>>=1;	
	}
	delay_us(2);
}

void vfd_send_cmd1(uint8_t cmd1)
{
	vfd_start();
	vfd_send_data(cmd1);
	vfd_stop();
}
void vfd_send_cmd2(uint8_t cmd1,uint8_t cmd2)
{
	vfd_start();
	vfd_send_data(cmd1);
	vfd_send_data(cmd2);
	vfd_stop();
}

void vfd_send_cmd3(uint8_t cmd1,uint8_t cmd2,uint8_t cmd3)
{
	vfd_start();
	vfd_send_data(cmd1);
	vfd_send_data(cmd2);
	vfd_send_data(cmd3);
	vfd_stop();
}
void vfd_send8b(uint8_t data)
{
	vfd_start();
	vfd_send_data(data);
	vfd_stop();
}

void Futaba_VFD_TICK(void)
{
	Vfd_Timer_Tick=1;
	Vfd_Anim_Tick+=1;
	if(Vfd_Anim_Tick>125)
	{
		Vfd_Anim_Tick=0;
		if(VAnim_En)
		{
			
			if(Vfd_Anim_Count<7)
			{
				Vfd_Anim_Count++;
			}
			else
			{
				Vfd_Anim_Count=0;
			}
			VSy_Calc();
			vfd_start();//图标中转GCRAM
			vfd_send_data(0X47);
			vfd_send_data(VSTAB[0]);//03H	自定义笑脸
			vfd_send_data(VSTAB[1]);
			vfd_send_data(VSTAB[2]);
			vfd_send_data(VSTAB[3]);
			vfd_send_data(VSTAB[4]);
			vfd_stop();
			
			vfd_start();//DCRAM
			vfd_send_data(0X20);//地址				相对	绝对
			vfd_send_data(0X07);//1G-SEG			00H		0X20
			vfd_stop();
			
			
				
		}
	}
}

void Futaba_VFD_Init(void)
{
  VFD_GPIO_init();
	vfd_reset();

	vfd_send_cmd2(0xe0,0xac);//设定驱动时序
	
	vfd_start();//URAM
	vfd_send_data(0X80);
	
	vfd_send_data(0XC0);//7G,8G
	vfd_send_data(0X00);
	
	vfd_send_data(0X00);//9G,10G
	vfd_send_data(0X03);
	
	vfd_send_data(0X00);//T3
	vfd_send_data(0X0C);
	
	vfd_stop();
  
  vfd_send_cmd2(0x00,0x00);//DISPLAY_MODE
 	vfd_send_cmd2(0xe4,0xFF);//DIMING 0-240
	
	vfd_start();//GRAY DATA
	vfd_send_data(0Xa0);
	vfd_send_data(0XFF);//00H
	vfd_send_data(0XFF);//01H
	vfd_send_data(0XFF);//02H

	vfd_stop();
	
	vfd_start();//GRAY ON/OFF
	vfd_send_data(0XC0);
	vfd_send_data(0X00);//00H
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_stop();
	
	vfd_start();//GCRAM
	vfd_send_data(0X40);
	vfd_send_data(0X0C);//00H	自定义闪电
	vfd_send_data(0X4E);
	vfd_send_data(0X6B);
	vfd_send_data(0X39);
	vfd_send_data(0X18);
	
	
	vfd_send_data(0X9C);//01H	自定义插头
	vfd_send_data(0XBF);
	vfd_send_data(0XFC);
	vfd_send_data(0XBF);
	vfd_send_data(0X9C);
	
	vfd_send_data(0X98);//02H	自定义笑脸
	vfd_send_data(0XA2);
	vfd_send_data(0XA0);
	vfd_send_data(0XA2);
	vfd_send_data(0X98);
	vfd_stop();
	
	vfd_start();//图标中转GCRAM
	vfd_send_data(0X47);
	vfd_send_data(0X02);//03H	自定义笑脸
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_send_data(0X00);
	vfd_stop();
	
	
	
	vfd_start();//DCRAM
	vfd_send_data(0X20);//地址				相对	绝对
	vfd_send_data(0X07);//1G-SEG			00H		0X20
	vfd_send_data(0X01);//GCRAM-01H		01H		0X21
	vfd_send_data(0X54);//T						02H		0X22
	vfd_send_data(0X65);//e						03H		0X23
	vfd_send_data(0X73);//s						04H		0X24
	vfd_send_data(0X74);//t						05H		0X25
	vfd_send_data(0X00);//GCRAM-00H		06H		0X26
	vfd_send_data(0X47);//G						07H		0X27
	vfd_send_data(0X54);//T						08H		0X28
	vfd_send_data(0X58);//X						09H		0X29
	vfd_send_data(0X59);//Y						0AH		0X2A
	vfd_send_data(0X4A);//J						0BH		0X2B
	vfd_send_data(0X02);//GCRAM-02H		0CH		0X2C
	vfd_send_data(0X00);//NONE				0DH		0X2D
	vfd_send_data(0X00);//NONE				0EH		0X2E
	vfd_send_data(0X00);//NONE				0FH		0X2F
	vfd_send_data(0X20);//NONE				10H		0X30
	vfd_send_data(0X20);//NONE				11H		0X31
	vfd_send_data(0X20);//NONE				12H		0X32
	vfd_stop();
	
	
	
	vfd_start();//ADRAM
  vfd_send_data(0X60);//地址		相对	绝对
	vfd_send_data(0X00);//NONE		00H		0X60
	vfd_send_data(0X02);//TIME		01H		0X61	0X02:ON 0X00:0FF
	vfd_send_data(0X02);//SHIFT		02H		0X62
	vfd_send_data(0X02);//CLOCK		03H		0X63
	vfd_send_data(0X02);//HD			04H		0X64
	vfd_send_data(0X02);//USB			05H		0X65
	vfd_send_data(0X02);//LOCK		06H		0X66	
	vfd_send_data(0X02);//DOLBY		07H		0X67	
	vfd_send_data(0X02);//MUTE		08H		0X68
	vfd_send_data(0X02);//TU1			09H		0X69
	vfd_send_data(0X02);//TU2			0AH		0X6A
	vfd_send_data(0X02);//MP3			0BH		0X6B
	vfd_send_data(0X02);//LOOP		0CH		0X6C
	vfd_send_data(0X00);//NONE		0DH		0X6D
	vfd_send_data(0X00);//NONE		0EH		0X6E
	vfd_send_data(0X00);//NONE		0FH		0X6F
	vfd_send_data(0X01);//COLON11	10H		0X70	0X01:ON 0X00:0FF
	vfd_send_data(0X01);//COLON2	11H		0X71	0X01:ON 0X00:0FF
	vfd_send_data(0X01);//COLON33	12H		0X72	0X01:ON 0X00:0FF
	vfd_stop();
	
	
	
	vfd_send_cmd1(0XE8);//LIGHT UP
	
}

void vfd_tst(void)
{
	vfd_start();//DCRAM
	vfd_send_data(0X20);//地址				相对	绝对
	vfd_send_data(0X7f);//1G-SEG			00H		0X20
	vfd_send_data(0X01);//GCRAM-01H		01H		0X21
	vfd_send_data(0X54);//T						02H		0X22
	vfd_send_data(0X65);//e						03H		0X23
	vfd_send_data(0X73);//s						04H		0X24
	vfd_send_data(0X74);//t						05H		0X25
	vfd_send_data(0X00);//GCRAM-00H		06H		0X26
	vfd_send_data(0X47);//G						07H		0X27
	vfd_send_data(0X54);//T						08H		0X28
	vfd_send_data(0X58);//X						09H		0X29
	vfd_send_data(0X59);//Y						0AH		0X2A
	vfd_send_data(0X4A);//J						0BH		0X2B
	vfd_send_data(0X02);//GCRAM-02H		0CH		0X2C
	vfd_send_data(0X00);//NONE				0DH		0X2D
	vfd_send_data(0X00);//NONE				0EH		0X2E
	vfd_send_data(0X00);//NONE				0FH		0X2F
	vfd_send_data(0X20);//NONE				10H		0X30
	vfd_send_data(0X20);//NONE				11H		0X31
	vfd_send_data(0X20);//NONE				12H		0X32
	vfd_stop();
}
