
// TIM—通用定时器-4路PWM输出应用
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_GeneralTim.h"  
#include "DS18b20.h"


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
float speed;  //风扇转速变量
u8 gear=0; // 风扇挡位

int main(void)
{
	/* led 端口配置 */ 
	LED_GPIO_Config();
	
	/* 定时器初始化 */
	GENERAL_TIM_Init();  //选用PA6作为输出电机
	CCR1_Val = 1500;  //电机初始默认为1500，停转
	Delay_Timer_Init();  
	DS18B20_Init();  //温度传感器初始化 PB8引脚
	
	while(1)
	{     
		DS18B20_GetTemp(); //轮询不断获取温度值
		TIM_SetCompare1(TIM3,speed);  //PA6的PWM输出函数
	}
}
/*********************************************END OF FILE**********************/
