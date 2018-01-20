#include "Key.h"

uint32_t keyLineMask[16]={0x000001,0x000002,0x000010,0x000100,0x000200,0x000400,0x004000,0x008000,0x010000,0x020000,0x080000,0x100000,0x200000,0x400000,0x800000,0x1000000}; //列扫描线
uint8_t  keyBuff[KEY_MAX_NUM] ={0xFF,0xFF,0xFF};  //记录按键
uint8_t  tgcLastVal[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	//对应八个通道的ad值
uint8_t  mutKeyPressCnt = 0;      //多个按键同时按下，计数按键	
uint8_t  KeyHoldFlag = 0;         
uint8_t  KeyTypeMaticEN = 0;
uint32_t encoderValue = 0;

/*矩阵键盘
 *行列间对应的按键功能是约定好的
*/
const uint8_t KeyCodeNum[KEY_COL_NUM*KEY_ROW_NUM]=
{
	  Windows,     FunShift1,   KeyEnter,       review,     bigBracketRight, KeyAddAmount,  patient,         ToolBar5,
	  Del,         LetterN,     LetterJ,        PDI,        LetterU,         number7,       F4Key,           ToolBar3,
	  Space,       LetterC,     LetterD,        Mode4D,     LetterE,         number3,       saveIP,          Angle,
	  Ins,         reserve1,    LetterH,        TDI,        LetterY,         number6,       F3Key,           Volume,
	  Arrow,       LetterB,     LetterG,        CW,         LetterT,         number5,       F2Key,           ToolBar2,
	  RightShift,  BigThan,     SemicolonColon, HI,         LetterP,         number0,       Biopsy,          ToolBar4,
	  DownShift,   LessThan,    LetterL,        Update,     LetterO,         number9,       Station,         BModeKey,
	  DepthInc,    Dual,        AUTO,           set,        Freze,           DepthAdd,      Saveimg,         ZOOM,
	  Fn,          LetterZ,     LetterA,        P2Key,      LetterQ,         number1,       help,            ToolBar1,
	  Commit,      LetterV,     LetterF,        ClearKey,   LetterR,         number4,       F1Key,           MModeKey,
	  LeftShift,   LetterM,     LetterK,        CursorKey,  LetterI,         number8,       ECG,             PWModeKey,
	  Caliper,     FocusAdd,    Cine,           reportKey,  KeySlash,        BackSpace,     ProbeExam,       CModeKey,
	  FocusInc,    KeyQuestion, quotation,      MeasureKey, bigBracketLeft,  KeySubtract,   MENU,            CtrlAndL,
	  Alt,         LetterX,     LetterS,        EndExam,    LetterW,         number2,       preset,          Mode3D,
	  Ctrl,        FunShift2,   CapsLock,       P1Key,      Tab,             KeyWave,       esc,             reserve4,
	  SelectUp,    SelectDown,  SelectLeft,     SelectRight,UnlinkedKey,     UnlinkedKey,   UnlinkedKey,     UnlinkedKey
};


void KeyPress(void)
{
   	uint32_t i,j;

	static uint32_t  keyVal;
	static uint8_t   keyState=0;
	uint8_t  timeDly = 50;
	uint32_t keyTmp = 0;
	uint32_t keyCode = 0;
	 
	switch(keyState)
	{
		case 0:
		{
			LPC_GPIO1->FIOSET = COL_PORT_MASK;		//列线全部拉高,检测行线
			keyVal = ((LPC_GPIO0->FIOPIN)>>KEY_ROW_OFFSET)&0xff;
			if( KEYVAL_DEFAULT != keyVal) 			//有按键按下，状态转移
			{
				keyState++; 		
			}
		}
		break;

		case 1:
		{	
			if(keyVal == ((LPC_GPIO0->FIOPIN >> KEY_ROW_OFFSET)&0xff) ) //确实有按键按下
			{
				for(i=0;i<KEY_COL_NUM;i++)  					   		//寻找按键的位置 列扫描
				{
					LPC_GPIO1->FIOCLR =	COL_PORT_MASK;   				//清零
					while(timeDly--);									//us级短延时
					LPC_GPIO1->FIOSET = keyLineMask[i];			   		//依此列扫描
					while(timeDly--);									//us级短延时
					keyTmp = (LPC_GPIO0->FIOPIN>>KEY_ROW_OFFSET) & 0xff;
					if( keyTmp != KEYVAL_DEFAULT )			  	   		//表示这列对应行有按键按下
					{
						for(j=0;j<KEY_ROW_NUM;j++)	
						{
							if((keyTmp&(1<<j))==(1<<j))  			    //寻找行的位置，这一行有按键按下 
							{
								keyCode = j+i*KEY_ROW_NUM; 	 	        //计算按键的位置
								if(mutKeyPressCnt<KEY_MAX_NUM) 			//按键小于3个
								{
									if( (keyCode != keyBuff[0]) && (keyCode != keyBuff[1]) && (keyCode != keyBuff[2])) //有新的按键按下
									{
										keyBuff[mutKeyPressCnt++] = keyCode;  
										if(KeyCodeNum[keyCode]>PC_KEY_CODE_MIN && KeyCodeNum[keyCode]<PC_KEY_CODE_MAX )   //PC键盘有键按下
										{
											KeyHoldFlag=1;             	//添加长按处理
											KeyTypeMaticEN = 0;
										}

										SetInFrame(KeyPressCode,1,(uint8_t *)&KeyCodeNum[keyCode]);	 //发送按键值
										SendInFrameToEndpoint();
									}		
								}
								else
								{
									keyState=0;	   //无法检测
									return;		
								}
							}
						 }
					}
				}	
			  }
			  keyState=0; 
	    }
	    break;

	   default:
	   		break;
	}	 
}

void KeyRelease(void)
{
	static uint8_t keyState=0;
	uint8_t temp[KEY_MAX_NUM]={0xff,0xff,0xff};
	uint8_t flag=0;
	uint8_t i=0;
	uint8_t j = 0;
	uint32_t tmp = 0;
	uint8_t  timeDly = 50;

	switch(keyState)
	{	
		case 0:
		{
			for(i=0;i<KEY_MAX_NUM;i++)
			{
				if(keyBuff[i]!= 0xff)
				{
					LPC_GPIO1->FIOCLR =	COL_PORT_MASK;   				//清零
					while(timeDly--);
					LPC_GPIO1->FIOSET = keyLineMask[(keyBuff[i]/KEY_ROW_NUM)];  //拉高列线
					while(timeDly--);
					tmp = (1<<((keyBuff[i]%KEY_ROW_NUM) + KEY_ROW_OFFSET));		//寻找行线的位置，并将其置1	
					if((LPC_GPIO0->FIOPIN & tmp)!= tmp) 					    //有按键释放
					{
						keyState++;
						break;
					}
				}
			}
		}
		break;

		case 1:
		{
			for(i=0;i<KEY_MAX_NUM;i++)
			{
				if(keyBuff[i]!= 0xff)
				{
					tmp = (1<<((keyBuff[i]%KEY_ROW_NUM) + KEY_ROW_OFFSET));	
					if((LPC_GPIO0->FIOPIN & tmp) != tmp )
					{
						flag=1; //确实有按键释放，做按键释放处理
 						SetInFrame(KeyReleaseCode,1,(uint8_t *)&KeyCodeNum[keyBuff[i]]);
						SendInFrameToEndpoint();
						KeyHoldFlag=0;
						KeyTypeMaticEN=0;
						keyBuff[i] = 0xff;
						mutKeyPressCnt--;
					}
				}	
			}

			if(flag)
			{
				for(i=0;i<KEY_MAX_NUM;i++)
				{
					if(keyBuff[i]!= 0xff)
					{
						temp[j++]=keyBuff[i];//保存还没有释放的
					}		
				}
				for(i=0;i<KEY_MAX_NUM;i++)
				{
					keyBuff[i]=temp[i];	   //更新按键扫描码缓冲区,没有释放的前移
				}
				flag=0;
			}
				
			keyState=0;					
		}
		break;
	}	
}

void KeyHold(void)
{
	static uint32_t KeyHoldCounter = 0;
	static uint32_t KeyTypeMaticCounter = 0;
	
	if(KeyHoldFlag)  //有键按住
	{
		KeyHoldCounter++;
		if(KeyHoldCounter == KEY_HOLD_CNT ) //检测是否长按
		{
			KeyTypeMaticEN = 1;
		}
		if(KeyTypeMaticEN) //在长按
		{
			KeyTypeMaticCounter++;
			if(KeyTypeMaticCounter==KEY_MATIC_CNT) //每100ms发一次数据
			{
    			SetInFrame(KeyPressCode,1,(uint8_t *)&KeyCodeNum[keyBuff[mutKeyPressCnt-1]]);
				SendInFrameToEndpoint();
	  			KeyTypeMaticCounter=0;	
			}
		}
	}	
	else
	{
	 	KeyHoldCounter=0;
	 	KeyTypeMaticCounter=0;
	 	KeyTypeMaticEN=0;
	}
}

/************** for encode *****************/
static void ReadEncoderValue(void)
{
	uint8_t tmp = 0;
	uint8_t delay = 100;
	
	//锁存按键值
	SetPinValue(PINSEL_PORT_0, 1<<PINSEL_PIN_5, 0);
	while(delay--);
	SetPinValue(PINSEL_PORT_0, 1<<PINSEL_PIN_5, 1);	 
	
	encoderValue = SPIReadOneByte(LPC_SSP1); 	
	tmp = SPIReadOneByte(LPC_SSP1);
	encoderValue = (encoderValue<<8)+ tmp;
	tmp = SPIReadOneByte(LPC_SSP1); 
	encoderValue = (encoderValue<<8)+tmp;

	return;
}


static void ReadEndcoder(uint8_t num, uint32_t encoderValueS)
{
  static uint8_t lastVal[12];
  uint8_t value;
  uint8_t trdat[2];

  value = (encoderValueS >> ( num << 1)) & 0x03;  

  switch(value)
  {
  	case 0x00:
	{
		if( lastVal[num] == 0x01 )
		{
			trdat[0]=num;
			trdat[1]=0x55;
			SetInFrame(Encorder_SCAN,2,trdat);
			SendInFrameToEndpoint();
		}
		else if( lastVal[num] == 0x02 )
		{
			trdat[0]=num;
			trdat[1]=0xaa;
			SetInFrame(Encorder_SCAN,2,trdat);
			SendInFrameToEndpoint();
		}																						   
		else
		{
			break;
		}		
	}
	break;

	case 0x03:
	{
	   	if( lastVal[num] == 0x02 )
		{
			trdat[0]=num;
			trdat[1]=0x55;
			SetInFrame(Encorder_SCAN,2,trdat);
			SendInFrameToEndpoint();
		}
		else if( lastVal[num] == 0x01 )
		{
			trdat[0]=num;
			trdat[1]=0xaa;
			SetInFrame(Encorder_SCAN,2,trdat);
			SendInFrameToEndpoint();
		}
		else
		{
			break;
		}		
    }
	break;

	default:
		break;
  }

  lastVal[num] = value;
}

void ScanEncoder(void)
{
   uint8_t i;

   ReadEncoderValue();

   for(i=0;i<12;i++)
   {
   	  ReadEndcoder(i,encoderValue);
   }
 
   return;
}

/**************** for DTGC *****************/
static void SelectDTGCCh(uint8_t ch)
{
	 switch(ch)
	 {
	 	case 0:
		{
		 	SetPinValue(2,8,0);
			SetPinValue(2,7,0);
		}
		break;

		case 1:
		{
		 	SetPinValue(2,8,0);
			SetPinValue(2,7,1);		 	
		}
		break;

		case 2:
		{
		 	SetPinValue(2,8,1);
			SetPinValue(2,7,0);		 	
		}
		break;

		case 3:
		{
		 	SetPinValue(2,8,1);
			SetPinValue(2,7,1);			
		}
		break;

		default:
			break;
	 }

	 return;
}


/*
adch  tgcch 
 7		0	  0
        1	  1
		2	  2
		3 	  3
 6	    0	  4
        1	  5
		2	  6
		3	  7
*/
static uint32_t GetDTGCVal(uint8_t adCh, uint8_t tgcCh)
{
	 uint32_t tmpVal=0;

	 SelectDTGCCh(tgcCh);
	 StartADC(adCh);
	 tmpVal = GetADCData(adCh);
	 StopADC(adCh);
	 
	 return tmpVal; 
}

void ScanDTGC(void)
{

  uint32_t i=0;
  uint32_t tmpVal0 = 0;
  uint32_t tmpVal1 = 0;
  uint8_t txdat1[2];
  uint8_t txdat2[2];

  for(i=0;i<TGC_CHN/2;i++)
  {
	tmpVal0 = GetDTGCVal(ADC_INA,i);
	tmpVal0 = 0x100*tmpVal0/4095;
	if(tmpVal0 > 0xff)
	{
	   tmpVal0 = 0xff;
	}	
	if((tgcLastVal[i] != tmpVal0)&&(tgcLastVal[i] != (tmpVal0-1))&&(tgcLastVal[i] != (tmpVal0+1)))
	{
		txdat1[0] = i;
		txdat1[1] = tmpVal0;
		SetInFrame(DTGCCODE,2,txdat1);
		SendInFrameToEndpoint();
		tgcLastVal[i] = tmpVal0;
	}
	
	tmpVal1 = GetDTGCVal(ADC_INB,i);	
	tmpVal1 = 0x100*tmpVal1/4095; 
	if(tmpVal1 > 0xff)
	{
	   tmpVal1 = 0xff;
	}

	if((tgcLastVal[i+4] != tmpVal1)&&(tgcLastVal[i+4] != (tmpVal1-1))&&(tgcLastVal[i+4] != (tmpVal1+1)))
	{
		txdat2[0] = i+4;
		txdat2[1] = tmpVal1;
		SetInFrame(DTGCCODE,2,txdat2);
		SendInFrameToEndpoint();
		tgcLastVal[i+4] = tmpVal1;
	}
  }
 
  return ;

}


void DTGCInit(void)
{

  uint32_t i=0;
  uint32_t tmpVal0 = 0;
  uint32_t tmpVal1 = 0;

  for(i=0;i<TGC_CHN/2;i++)
  {
  	tmpVal0 = GetDTGCVal(ADC_INA,i);
	tmpVal1 = GetDTGCVal(ADC_INB,i);	
	tmpVal0 = 0x100*tmpVal0/4095;
	tmpVal1 = 0x100*tmpVal1/4095; 	

	if(tmpVal0 > 0xff)
	{
	   tmpVal0 = 0xff;
	}

	if(tmpVal1 > 0xff)
	{
	   tmpVal1 = 0xff;
	}

	tgcLastVal[i] = tmpVal0;	
	tgcLastVal[i+4] = tmpVal1;	

  }

  SetInFrame(INIT_TGC, 2, tgcLastVal);
  SendInFrameToEndpoint();

  return ;

}


