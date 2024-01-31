#include "STM_TB6600.h"
#include "STM_TB6600Config.h"
#include "main.h"
//#include "stm32f0xx_hal_tim.h"
#include "stm32l4xx_hal_tim.h"
//#############################################################################################
 
//#############################################################################################
void delay_us (tb6600_t *tb6600)
{
	__HAL_TIM_SET_COUNTER(&tb6600->timer,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&tb6600->timer) < tb6600->Speed);  // wait for the counter to reach the us input in the parameter
}
//#############################################################################################


//#############################################################################################

//#############################################################################################
void tb6600_init(tb6600_t *tb6600, GPIO_TypeDef  *enable_gpio, uint16_t enable_pin, GPIO_TypeDef  *direction_gpio, uint16_t direction_pin,GPIO_TypeDef  *pulse_gpio,uint16_t pulse_pin,TIM_HandleTypeDef timer)
{

	tb6600->enable_gpio = enable_gpio;
	tb6600->enable_pin = enable_pin;
	tb6600->direction_gpio = direction_gpio;
	tb6600->direction_pin = direction_pin;
	tb6600->pulse_gpio = pulse_gpio;
	tb6600->pulse_pin = pulse_pin;
	tb6600->timer=timer;
}
//#############################################################################################

//#############################################################################################
void tb6600_Set(tb6600_t *tb6600,Direction direction,Speed speed,uint16_t PulsePerRev,uint16_t Clock)
{
	if(direction==CW)
	{HAL_GPIO_WritePin(tb6600->direction_gpio,tb6600->direction_pin,GPIO_PIN_SET);}
	else if(direction==CCW)
	{HAL_GPIO_WritePin(tb6600->direction_gpio,tb6600->direction_pin,GPIO_PIN_RESET);}
	tb6600->PulsePerRev=PulsePerRev;
	tb6600->Speed=speed;
	__HAL_TIM_SET_PRESCALER(&tb6600->timer,Clock-1);
}
//#############################################################################################

//#############################################################################################
void tb6600_AngleMove(tb6600_t *tb6600,uint16_t Degree)
{
	for(int i=0;i<=(tb6600->PulsePerRev)*(Degree/360);i++)
	{
		HAL_GPIO_WritePin(tb6600->pulse_gpio,tb6600->pulse_pin,GPIO_PIN_SET);
		delay_us(tb6600);
		HAL_GPIO_WritePin(tb6600->pulse_gpio,tb6600->pulse_pin,GPIO_PIN_RESET);
		delay_us(tb6600);   
	}
}
//#############################################################################################

//#############################################################################################
void tb6600_Enable(tb6600_t *tb6600)
{
	HAL_GPIO_WritePin(tb6600->enable_gpio,tb6600->enable_pin,1);//Enable
}
//#############################################################################################

//#############################################################################################
void tb6600_Disable(tb6600_t *tb6600)
{
	HAL_GPIO_WritePin(tb6600->enable_gpio,tb6600->enable_pin,GPIO_PIN_RESET);
}
//#############################################################################################

//#############################################################################################
void tb6600_ChangeDirection(tb6600_t *tb6600,Direction direction)
{
	if(direction==CW)
	{HAL_GPIO_WritePin(tb6600->direction_gpio,tb6600->direction_pin,GPIO_PIN_SET);}
	else if(direction==CCW)
	{HAL_GPIO_WritePin(tb6600->direction_gpio,tb6600->direction_pin,GPIO_PIN_RESET);}
}
//#############################################################################################

//#############################################################################################
void tb6600_ChangeSpeed(tb6600_t *tb6600,Speed speed)
{
	tb6600->Speed=speed;
}
//#############################################################################################

//#############################################################################################
void tb6600_ChangePulsePerRev(tb6600_t *tb6600,uint16_t PulsePerRev)
{
	tb6600->PulsePerRev=PulsePerRev;
}
//#############################################################################################

//#############################################################################################
void tb6600_cont(tb6600_t *tb6600)
{
	while(1)
	{
		HAL_GPIO_WritePin(tb6600->pulse_gpio,tb6600->pulse_pin,GPIO_PIN_SET);
		delay_us(tb6600);
		HAL_GPIO_WritePin(tb6600->pulse_gpio,tb6600->pulse_pin,GPIO_PIN_RESET);
		delay_us(tb6600);   
	}
}