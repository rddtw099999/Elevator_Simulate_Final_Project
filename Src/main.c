/**
  ******************************************************************************
    File Name          : main.c
    Description        : Main program body
  ******************************************************************************

    COPYRIGHT(c) 2016 STMicroelectronics

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:
      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.
      2. Redistributions in binary form must reproduce the above copyright notice,
         this list of conditions and the following disclaimer in the documentation
         and/or other materials provided with the distribution.
      3. Neither the name of STMicroelectronics nor the names of its contributors
         may be used to endorse or promote products derived from this software
         without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "LCD.h"
#include "main.h"
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE BEGIN Includes */

void floor1(void);
void floor2(void);
void floor3(void);
void floor4(void);
void uparrow(int i);
void downarrow(int i);

unsigned char Str1_1[]={122,123,124,125,126,127,128,129};
unsigned char Str1_2[]={130,131,132,133,134,135,136,137};
unsigned char Str1_3[]={138,139,140,141,142,143,144,145};
unsigned char Str1_4[]={146,147,148,149,150,151,152,153};

unsigned char Str2_1[]={154,155,156,157,158,159,160,161};
unsigned char Str2_2[]={162,163,164,165,166,167,168,169};
unsigned char Str2_3[]={170,171,172,173,174,175,176,177};
unsigned char Str2_4[]={178,179,180,181,182,183,184,185};

unsigned char Str3_1[]={186,187,188,189,190,191,192,193};
unsigned char Str3_2[]={194,195,196,197,198,199,200,201};
unsigned char Str3_3[]={202,203,204,205,206,207,208,209};
unsigned char Str3_4[]={210,211,212,213,214,215,216,217};

unsigned char Str4_1[]={218,219,220,221,222,223,224,225};
unsigned char Str4_2[]={226,227,228,229,230,231,232,233};
unsigned char Str4_3[]={234,235,236,237,238,239,240,241};
unsigned char Str4_4[]={242,243,244,245,246,247,248,249};

unsigned char Str5_1[]={58,59,60,61,62,63,64,65};
unsigned char Str5_2[]={66,67,68,69,70,71,72,73};
unsigned char Str5_3[]={74,75,76,77,78,79,80,81};
unsigned char Str5_4[]={82,83,84,85,86,87,88,89};

unsigned char Str6_1[]={90, 91, 92, 93, 94, 95, 96, 97 };
unsigned char Str6_2[]={98, 99, 100,101,102,103,104,105};
unsigned char Str6_3[]={106,107,108,109,110,111,112,113};
unsigned char Str6_4[]={114,115,116,117,118,119,120,121};

unsigned char prt[1] = {0};
unsigned char btn[1] = {0};
unsigned char cnn[1] = {56};
int currentfloor = 1;       //current on 1F
int aimfloor = 1;           //default aim floor is 0
int upordown = 1;           //Up means 1 ,downer means -1,zero means no need to move;
int timetick = 0;           //a timer counter
int floorstatus[4];         //record which floor has been click
int enabled = 0;
int dataCount=0;
int connected=0;
int connSt=0;
int connStTmp=0;
int receivenow;
int floorANI=0;
void operation(void);
void display(void);
void button_detection(void);
void LED_DISP(void);
void sendData(void);
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart1;
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static GPIO_InitTypeDef  GPIO_InitStruct;

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

unsigned char a;
int main(void)
{
	
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  LCD_Init();

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

/////////////////////////////////////////////////////

  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin = LED1_PIN;
  HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);             //LED 's Definition.

  GPIO_InitStruct.Pin = LED3_PIN;
  HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LED4_PIN;
  HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStruct);



  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;           //button wakeup definition (1F)
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;           //button Tamper definition (2F)
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;           //button select definition (3F)

  GPIO_InitStruct.Pin = GPIO_PIN_11;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                 //button key definition (4F)
/////////////////////////////////////////////////////


  HAL_TIM_Base_Start_IT(&htim1);
  LCD_Clear();
	
  while (1)
  {
		if(receivenow){
			HAL_UART_Receive(&huart1, (uint8_t *)&connected, 1, 0xFFFF);
			connected=1;
			receivenow=0;
			connSt=timetick;
		}

				////////////////////do not write here ///////////////////////
						
								//  Reserved for UART Communcation 
						
										// Do not write anything in here.
						
						
				/////////////////////////////////////////////////////////////
  }
}
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
	
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);

  return ch;
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

/* TIM1 init function */

void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7200;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 5;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim1);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

}

/** Configure pins as
          Analog
          Input
          Output
          EVENT_OUT
          EXTI
*/


void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  __GPIOA_CLK_ENABLE();
  /* GPIO Ports Clock Enable */
  __GPIOF_CLK_ENABLE();

  /*Configure GPIO pins : PF6 PF7 PF8 PF9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

}
extern TIM_HandleTypeDef htim1;

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
  @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  @brief This function handles TIM1 update interrupt.
*/

void TIM1_UP_IRQHandler(void)
{
  timetick++;

  if (timetick >= 6000) {      //means every 3s do something
    timetick = 0;
	
    operation();                 //do operation after num changed;
  }
  if (timetick % 200 == 0) {
		if(connStTmp==connSt)connected=0;
		connStTmp=connSt;
    display();                  //every 100ms refresh LCD
			if(connected==0)
		{
			connSt=0;
		}
		else
			connSt=1;
		LED_DISP();
  }
	if(timetick%250==0){
	floorANI++;
		if(floorANI>5)floorANI=0;
		
	}
	if(timetick%40 ==0)
	{
		sendData();
		dataCount++;
		if(dataCount>8)dataCount=0;
	}
  button_detection();         //scan buttons per 0.5ms
  HAL_TIM_IRQHandler(&htim1);

}

void sendData(void){
	switch(dataCount){
		case 0:	
			printf("%c",9);
		break;
		case 1:
			printf("%c",upordown+1);
		break;
		case 2:
			printf("%c",currentfloor);
		break;
		case 3:
			printf("%c",aimfloor);
		break;
		case 4:
			printf("%c",floorstatus[0]);
		break;
		case 5:
			printf("%c",floorstatus[1]);
		break;
		case 6:
			printf("%c",floorstatus[2]);
		break;
		case 7:
			printf("%c",floorstatus[3]);
		break;
		case 8:
			printf("%c",8);
			receivenow=1;
		break;
		}


}
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

void operation(void) {


  if (enabled) {
    currentfloor += upordown;
    if (aimfloor == currentfloor)
    {
      floorstatus[currentfloor - 1] = 0;
    }
  }

  //
  int floorusage = 0;
  for (int a = 0; a < 4; a += 1) {
    if (floorstatus[a] == 1)floorusage = 1;
  }
  if (floorusage == 0) {                     //checking if there no floor has been usage .
    enabled = 0;
    upordown = -upordown;                    //no usage meens elevator arrived all floor and if now been upper than chanege to downer otherwise , be upper.
  } else
    enabled = 1;
}

void button_detection(void) {
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)           //Thinking no need to debounce Right?,because button just need to check if pressed.
  {
		if(currentfloor!=1)          //if now on 1F ,you don't need to go to 1F,Right?.
    floorstatus[0] = 1;
  }
  else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)
  {
		if(currentfloor!=2)
    floorstatus[1] = 1;
  }
  else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0)
  {
		if(currentfloor!=3)
    floorstatus[2] = 1;
  }
  else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0)
  {
		if(currentfloor!=4)
    floorstatus[3] = 1;
  }
	
	//////////////////////////////////////////////////
	
    if (upordown == 1) {
      for (int a = 0; a < 4; a += 1) {
        if (floorstatus[a] == 1)
        {
					if(a+1>=currentfloor)
          aimfloor = a + 1;
					else
					floorstatus[a]=0;
          break;
        }
      }
    }
    else if (upordown == -1) {                             //here checks . for example :
                                                           //Now the elevelator is upper. and current on 2F and it is going to 4F ,you can't press 1F ,Right?
      for (int a = 3; a > -1; a -= 1) {                    //you need to waiting elevelator is arrived 4F,and elevalator is downee then you can press 1F right?
        if (floorstatus[a] == 1)                           //like a normal elevelator.
        {
					if(a+1<=currentfloor)
          aimfloor = a + 1;
					else
          floorstatus[a]=0;
          break;
        }
      }
    
    }
		//////////////////////////////////////////////////
	}

void display(void) {
  LCD_Clear();
	if(currentfloor==1){
		floor1();
	}
	else if(currentfloor==2){
		floor2();
	}
	else if(currentfloor==3){
		floor3();
	}
	else if(currentfloor==4){
		floor4();
	}

  if(currentfloor==aimfloor);
  else if (upordown == 1)uparrow(floorANI);      //UP or DOWN?  (76 means UP,59 meand down.
  else if (upordown == -1)downarrow(floorANI);
          //it now moving?   (82 is no usage .just a space)
       //Draw the status.

 
	if(connected==1)
		cnn[0]=56;
	else 
		cnn[0]=57;
		LCD_DrawString(0, 120, cnn, 1);
}

void LED_DISP(void){
    if (floorstatus[3] == 1) {                  
      HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,1);	
    }
		else  HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,0);
  	 if (floorstatus[2] == 1) {                  
      HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,1);	
    }
		else  HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,0);
		 if (floorstatus[1] == 1) {                  
      HAL_GPIO_WritePin(LED3_GPIO_PORT,LED3_PIN,1);	
    }
		else  HAL_GPIO_WritePin(LED3_GPIO_PORT,LED3_PIN,0);
	  if (floorstatus[0] == 1) {                  
      HAL_GPIO_WritePin(LED4_GPIO_PORT,LED4_PIN,1);	
    }
		else  HAL_GPIO_WritePin(LED4_GPIO_PORT,LED4_PIN,0);

  
}

void floor1(void)
{
		LCD_DrawString(0 , 64 , Str1_1,sizeof(Str1_1));
		LCD_DrawString(2 , 64 , Str1_2,sizeof(Str1_2));
		LCD_DrawString(4 , 64 , Str1_3,sizeof(Str1_3));
		LCD_DrawString(6 , 64 , Str1_4,sizeof(Str1_4));
}
void floor2(void)
{
		LCD_DrawString(0 , 64 , Str2_1,sizeof(Str2_1));
		LCD_DrawString(2 , 64 , Str2_2,sizeof(Str2_2));
		LCD_DrawString(4 , 64 , Str2_3,sizeof(Str2_3));
		LCD_DrawString(6 , 64 , Str2_4,sizeof(Str2_4));
}
void floor3(void)
{
		LCD_DrawString(0 , 64 , Str3_1,sizeof(Str3_1));
		LCD_DrawString(2 , 64 , Str3_2,sizeof(Str3_2));
		LCD_DrawString(4 , 64 , Str3_3,sizeof(Str3_3));
		LCD_DrawString(6 , 64 , Str3_4,sizeof(Str3_4));
}
void floor4(void)
{
		LCD_DrawString(0 , 64 , Str4_1,sizeof(Str4_1));
		LCD_DrawString(2 , 64 , Str4_2,sizeof(Str4_2));
		LCD_DrawString(4 , 64 , Str4_3,sizeof(Str4_3));
		LCD_DrawString(6 , 64 , Str4_4,sizeof(Str4_4));
}
void uparrow(int i)
{
	switch (i)
		{
			case 0 :{
		
				LCD_DrawString(0 , 0 , Str6_1,sizeof(Str6_1));
				LCD_DrawString(2 , 0 , Str6_2,sizeof(Str6_2));
				LCD_DrawString(4 , 0 , Str6_3,sizeof(Str6_3));		
				LCD_DrawString(6 , 0 , Str6_4,sizeof(Str6_4));			
			}break;                                   
			                                          
			case 1 :{                                 
		                           
				LCD_DrawString(0 , 0 , Str6_2,sizeof(Str6_2));
				LCD_DrawString(2 , 0 , Str6_3,sizeof(Str6_3));		
				LCD_DrawString(4 , 0 , Str6_4,sizeof(Str6_4));			
			}break;                                   
			                                          
			case 2 :{                                 
				                           
				LCD_DrawString(0 , 0 , Str6_3,sizeof(Str6_3));		
				LCD_DrawString(2 , 0 , Str6_4,sizeof(Str6_4));					
			}break;                                   
			                                          
			case 3 :{                                 
				
				LCD_DrawString(0 , 0 , Str6_4,sizeof(Str6_4));
				LCD_DrawString(6 , 0 , Str6_1,sizeof(Str6_1));				
			}break;
			
			case 4 :{                                 
		
				LCD_DrawString(4 , 0 , Str6_1,sizeof(Str6_1));	
				LCD_DrawString(6 , 0 , Str6_2,sizeof(Str6_2));							
			}break;
			
			case 5 :{                                 
				
				LCD_DrawString(2 , 0 , Str6_1,sizeof(Str6_1));	
				LCD_DrawString(4 , 0 , Str6_2,sizeof(Str6_2));
				LCD_DrawString(6 , 0 , Str6_3,sizeof(Str6_3));							
			}break;
		}	
}
void downarrow(int i)
{
	switch (i)
		{
			case 0 :{
		
				LCD_DrawString(0 , 0 , Str5_1,sizeof(Str5_1));
				LCD_DrawString(2 , 0 , Str5_2,sizeof(Str5_2));
				LCD_DrawString(4 , 0 , Str5_3,sizeof(Str5_3));		
				LCD_DrawString(6 , 0 , Str5_4,sizeof(Str5_4));
			}break;	
			
			case 1 :{
			
				LCD_DrawString(2 , 0 , Str5_1,sizeof(Str5_1));
				LCD_DrawString(4 , 0 , Str5_2,sizeof(Str5_2));
				LCD_DrawString(6 , 0 , Str5_3,sizeof(Str5_3));												
			}break;		
			
			case 2 :{
		
				LCD_DrawString(4 , 0 , Str5_1,sizeof(Str5_1));
				LCD_DrawString(6 , 0 , Str5_2,sizeof(Str5_2));				
			}break;		
			
			case 3 :{
				
				LCD_DrawString(0 , 0 , Str5_4,sizeof(Str5_4));
				LCD_DrawString(6 , 0 , Str5_1,sizeof(Str5_1));										
			}break;		
			
			case 4 :{
													
				LCD_DrawString(0 , 0 , Str5_3,sizeof(Str5_3));
				LCD_DrawString(2 , 0 , Str5_4,sizeof(Str5_4));				
			}break;	
			
			case 5 :{
		
        LCD_DrawString(0 , 0 , Str5_2,sizeof(Str5_2));				
				LCD_DrawString(2 , 0 , Str5_3,sizeof(Str5_3));
				LCD_DrawString(4 , 0 , Str5_4,sizeof(Str5_4));								
			}break;			
		}	
}

#ifdef USE_FULL_ASSERT

/**
     @brief Reports the name of the source file and the source line number
     where the assert_param error has occurred.
     @param file: pointer to the source file name
     @param line: assert_param error line source number
     @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
    @}
*/

/**
    @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
