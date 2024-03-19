
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
float speed=1500;  //风扇转速变量
u8 gear=0; // 风扇挡位
u8 mode=0;  //运行模式，手动和自动
u8 set_temp = 20; //初始设定的温度值
int main(void)
{
	/* led 端口配置 */ 
	LED_GPIO_Config();
	Key_GPIO_Config(); //按键初始化
	/* 定时器初始化 */
	GENERAL_TIM_Init();  //选用PA6作为输出电机
	CCR1_Val = 1500;  //电机初始默认为1500，停转
	Delay_Timer_Init();  
	DS18B20_Init();  //温度传感器初始化 PB8引脚
	
	while(1)
	{     
		DS18B20_GetTemp(); //轮询不断获取温度值
		/*  电机限幅放在前面 */
 		if(speed < 1500)  // 电机转速限幅，保证正转
		{
			speed = 1500;
		}
		if(speed > 2000)
		{
			speed = 2000;
		}
		
		/* 进行按键2的检测，因为按键2控制手动自动挡的调节 */
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )  //按键2按下
		{
			/*按键2进行手动和自动挡的切换*/
			/*默认0为手动挡，初始为手动挡*/
			mode++;
			if(mode > 1)
			{
				mode = 0;
			}
		}
		/*---------手动模式------------*/
		if(mode == 0)  //只有当手动挡模式的时候才检测按键1是否按下
		{
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )  //按键1按下
			{
				/*每次按下按键1，挡位加1*/
				gear++;
				if(gear > 3)  //当挡位大于3挡时，回到0挡，关闭
				{
					gear = 0;
				}
			}
			switch(gear)  //挡位对照
			{
			case 0:
				speed = 1500;
				break;
			case 1:
				speed = 1600;
				break;
			case 2:
				speed = 1700;
				break;
			case 3:
				speed = 1800;
				break;
			}
		TIM_SetCompare1(TIM3,speed);  //将各个挡位的速度值输出给PWM
		}
		/*---------自动模式------------*/
		if(mode == 1)  // 1为自动挡模式
		{
			/*此处为自动控温代码,自动控温则不使用挡位调节，使用pwm值来控制*/
			if(temp > set_temp)  // 若实际温度大于设定的温度，则增加电机转速
			{
				Delay_us(10000);
				speed += 10;
				TIM_SetCompare1(TIM3,speed);
			}
			else if(temp < set_temp)
			{
				Delay_us(10000);
				speed -= 10;
				TIM_SetCompare1(TIM3,speed);
			}

		}


	}
}
/*********************************************END OF FILE**********************/
