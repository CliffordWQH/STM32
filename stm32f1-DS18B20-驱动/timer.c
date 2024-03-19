/**
  ******************************************************************************
  * @project 便携式测控实验站
  * @file    timer.h
  * @author  hhy/wattercutter
  * @date    2020/1/19
  * @brief   延时函数相关
	
  * @UpdateTime 
			2021/1/19 hhy/wattercutter
  ******************************************************************************
*/ 
#include "timer.h"


/**
  * @brief  初始化时序控制定时器
  * @param   无
  * @retval  无
  */
void Delay_Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInitStruct.TIM_Period = 100-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = (84-1);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    while((TIM3->SR & TIM_FLAG_Update)!=SET);
    TIM3->SR = (uint16_t)~TIM_FLAG_Update;
}
/**
  * @brief  微秒级延时函数
  * @param   us_cnt 延时的微秒数
  * @retval  无
  */
void Delay_us(uint32_t us_cnt)
{
    TIM3->CNT = us_cnt-1;
    TIM3->CR1 |= TIM_CR1_CEN;
    while((TIM3->SR & TIM_FLAG_Update)!=SET);
    TIM3->SR = (uint16_t)~TIM_FLAG_Update;
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

