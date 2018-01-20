
#ifndef _KEY_H
#define _KEY_H

#include "lpc17xx.h"
#include "hidio.h"
#include "spi.h"
#include "gpio.h"
#include "adc.h"

#define  COL_PORT_MASK     0x1FBC713 //((0x1<<0)|(0x1<<1)|(0x1<<4)|(0x7<<8)|(0xf<<14)|(0x3f<<19))		//列扫描掩码
#define  ROW_PORT_MASK     0x7F80000//(0xff<<19)	   													//行扫描掩码
#define  KEYVAL_DEFAULT    0x00
#define  NO_KEY            255
#define  KEY_COL_NUM       16
#define  KEY_ROW_NUM       8
#define  KEY_ROW_OFFSET    19
#define  KEY_MAX_NUM	   3
#define  PC_KEY_CODE_MIN   3  //文本按键编码最小值
#define  PC_KEY_CODE_MAX   175 //文本按键编码最大值
#define  KEY_NUM_DEBUG     0
#define  KEY_NUM_REALEASE  1
#define  KEY_SERIAL_DEBUG  1	  //////0--->1
#define  KEY_STATE_0       0
#define  KEY_STATE_1       1
#define  KEY_STATE_2       2

#define PowerFootPrintKeyGpioMask  (0x7<<4)
#define PowerFootPrintKeyMask      (0x7)

#define  KeyPressCode        0xF7	  //表示按下的按键
#define  KeyReleaseCode      0xF8	  //表示释放的按键
#define  Encorder_SCAN   	 0xFE
#define  INIT_TGC            0xF5
#define  DTGCCODE   		 0xF3

#define KEY_HOLD_CNT        20
#define KEY_MATIC_CNT       7

#define TGC_CHN  			8
#define ADC_INA 			7  
#define ADC_INB 			6

#define Del   				4	  //Del
#define Space   			5	  //SPACE
#define RightShift    		8	  //Right Shift
#define DownShift 		    9	  //Down Shift
#define DepthInc  			10	  //NUM-
#define LeftShift  			13	  //Left Shift
#define FocusInc  			15	  //NUM/
#define LetterN  			19	  //N
#define LetterC  			20	  //C
#define reserve1  			21	  //reserve
#define LetterB  			22	  //B
#define BigThan  			23	  //>
#define LessThan  			24	  //<
#define LetterZ  			26	  //Z
#define LetterV  			27	  //V
#define LetterM  			28	  //M
#define FocusAdd  		    29	  //NUM*
#define KeyQuestion  		30	  //?/
#define LetterX  			31	  //X
#define LetterJ  			34	  //J
#define KeyEnter  			33	  //Enter
#define LetterD  			35	  //D
#define LetterH 			36	  //H
#define LetterG  			37	  //G
#define SemicolonColon      38	  //;:
#define LetterL  		    39	  //L
#define LetterA  		    41	  //A
#define LetterF  		    42	  //F
#define LetterK  		    43	  //K
#define quotation  		    45	  //'"
#define LetterS  		    46	  //S
#define bigBracketRight     63	  //]}
#define LetterU  		    64	  //U
#define LetterE  		    65	  //E
#define LetterY  	   	    66	  //Y
#define LetterT  			67	  //T
#define LetterP  			68	  //P
#define LetterO  			69	  //O
#define LetterQ  			71	  //Q
#define LetterR  			72	  //R
#define LetterI  			73	  //I
#define KeySlash  			74	  //\|
#define bigBracketLeft  	75	  //[{
#define LetterW  			76	  //W
#define Tab  				77	  //Tab
#define KeyAddAmount 	    78	  //+=
#define number7  			79	  //&7
#define number3  			80	  //#3
#define number6 			81	  //^6
#define number5  			82	  //%5
#define number0  			83	  //)0
#define number9  			84	  //(9
#define DepthAdd  		    85	  //NUM+
#define number1  			86	  //!1
#define number4  			87	  //$4
#define number8  			88	  //*8
#define BackSpace  		    89	  //BackSpace
#define KeySubtract  		90	  //--
#define number2  			91	  //@2
#define KeyWave  			92	  //~` 
#define SelectUp            170
#define SelectDown          171
#define SelectLeft          172
#define SelectRight         173
#define UnlinkedKey         175

/*功能按键*/
#define patient             93		  //patient
#define F4Key               94		  //F4
#define saveIP              95		  //saveIP
#define F3Key               96		  //F3
#define F2Key               97		  //F2
#define Biopsy              98		  //Biopsy
#define Station             99		  //Station
#define Saveimg             100	      //Saveimg
#define help                101	      //help
#define F1Key               102	      //F1
#define ECG                 103	      //ECG
#define ProbeExam           104	      //probe/exam
#define MENU                105	      //MENU
#define preset              106	      //preset
#define esc                 107	      //esc
#define reserve2            108	      //reserve
#define reserve3            109	      //reserve
#define ToolBar5            110	      //ToolBar5
#define ToolBar3            111	      //ToolBar3
#define Angle               112	      //Angle
#define Volume              113	      //Volume
#define ToolBar2            114	      //ToolBar2
#define ToolBar4            115	      //ToolBar4
#define BModeKey            116	      //B
#define ZOOM                117	      //ZOOM
#define ToolBar1            118	      //ToolBar1
#define MModeKey            119	      //M
#define PWModeKey           120	      //PW
#define CModeKey            121	      //C
#define CtrlAndL            122	      //Ctrl+L
#define Mode3D              123	      //3D
#define reserve4            124	      //reserve
#define Windows             125	      //Windows
#define Ins                 126	      //Ins
#define Arrow               127	      //Arrow
#define Fn                  128	      //Fn
#define Commit              129	      //ABC/Commit
#define Caliper             130	      //Caliper
#define Alt                 131	      //Alt
#define Ctrl                132	      //Ctrl
#define FunShift1           133	      //Shift
#define Dual                134	      //Dual
#define FunShift2           135		  //Shift
#define AUTO                136		  //AUTO
#define Cine                137		  //Cine
#define CapsLock    	    138		  //CapsLock
#define review    		    139		  //review
#define PDI   			    140		  //PDI
#define Mode4D    		    141		  //4D
#define TDI    			    142		  //TDI
#define CW   			    143		  //CW
#define HI    			    144		  //HI
#define Update   		    145		  //Update
#define set    			    146		  //set
#define P2Key   		    147		  //P2
#define ClearKey    	    148	  	  //Clear
#define CursorKey   	    149		  //Cursor
#define reportKey    	    150		  //report
#define MeasureKey    	    151		  //Measure
#define EndExam    	        152		  //end exam
#define P1Key    		    153		  //P1
#define Freze    		    154		  //Freze
#define POWERKEY 	        160		  //POWER
#define FOOTKEY  		    161		  //FOOTKEY
#define VEDIOKEY 	        162


void MatrixKeyPress(void);
void MatrixKeyRelease(void);
void KeyLongPressHold(void);
void ScanEncoder(void);

#endif






