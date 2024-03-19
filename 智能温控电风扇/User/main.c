
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
float speed;  //����ת�ٱ���
u8 gear=0; // ���ȵ�λ

int main(void)
{
	/* led �˿����� */ 
	LED_GPIO_Config();
	
	/* ��ʱ����ʼ�� */
	GENERAL_TIM_Init();  //ѡ��PA6��Ϊ������
	CCR1_Val = 1500;  //�����ʼĬ��Ϊ1500��ͣת
	Delay_Timer_Init();  
	DS18B20_Init();  //�¶ȴ�������ʼ�� PB8����
	
	while(1)
	{     
		DS18B20_GetTemp(); //��ѯ���ϻ�ȡ�¶�ֵ
		TIM_SetCompare1(TIM3,speed);  //PA6��PWM�������
	}
}
/*********************************************END OF FILE**********************/
