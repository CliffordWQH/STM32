
// TIM��ͨ�ö�ʱ��-4·PWM���Ӧ��
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_GeneralTim.h"  
#include "DS18b20.h"


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
float speed=1500;  //����ת�ٱ���
u8 gear=0; // ���ȵ�λ
u8 mode=0;  //����ģʽ���ֶ����Զ�
u8 set_temp = 20; //��ʼ�趨���¶�ֵ
int main(void)
{
	/* led �˿����� */ 
	LED_GPIO_Config();
	Key_GPIO_Config(); //������ʼ��
	/* ��ʱ����ʼ�� */
	GENERAL_TIM_Init();  //ѡ��PA6��Ϊ������
	CCR1_Val = 1500;  //�����ʼĬ��Ϊ1500��ͣת
	Delay_Timer_Init();  
	DS18B20_Init();  //�¶ȴ�������ʼ�� PB8����
	
	while(1)
	{     
		DS18B20_GetTemp(); //��ѯ���ϻ�ȡ�¶�ֵ
		/*  ����޷�����ǰ�� */
 		if(speed < 1500)  // ���ת���޷�����֤��ת
		{
			speed = 1500;
		}
		if(speed > 2000)
		{
			speed = 2000;
		}
		
		/* ���а���2�ļ�⣬��Ϊ����2�����ֶ��Զ����ĵ��� */
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )  //����2����
		{
			/*����2�����ֶ����Զ������л�*/
			/*Ĭ��0Ϊ�ֶ�������ʼΪ�ֶ���*/
			mode++;
			if(mode > 1)
			{
				mode = 0;
			}
		}
		/*---------�ֶ�ģʽ------------*/
		if(mode == 0)  //ֻ�е��ֶ���ģʽ��ʱ��ż�ⰴ��1�Ƿ���
		{
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )  //����1����
			{
				/*ÿ�ΰ��°���1����λ��1*/
				gear++;
				if(gear > 3)  //����λ����3��ʱ���ص�0�����ر�
				{
					gear = 0;
				}
			}
			switch(gear)  //��λ����
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
		TIM_SetCompare1(TIM3,speed);  //��������λ���ٶ�ֵ�����PWM
		}
		/*---------�Զ�ģʽ------------*/
		if(mode == 1)  // 1Ϊ�Զ���ģʽ
		{
			/*�˴�Ϊ�Զ����´���,�Զ�������ʹ�õ�λ���ڣ�ʹ��pwmֵ������*/
			if(temp > set_temp)  // ��ʵ���¶ȴ����趨���¶ȣ������ӵ��ת��
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
