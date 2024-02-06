#ifndef STM_TB6600_H_
#define STM_TB6600_H_


/*
  Author:     Muhammad Tayyab
  WebSite:    https://github.com/MuhammadTayyab1002   
  
  Version:    0.2
  * Added Movement  with millimeter function
  * Added Manual Speed Function
  * Fix Speed Option increased
  
*/

#ifdef __cplusplus
extern "C" {
#endif
  
#include "main.h"
//#include "stm32f0xx_hal.h"
//#include "stm32f0xx_hal_tim.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal.h"
//####################################################################################################################
typedef struct
{
  GPIO_TypeDef  *enable_gpio;
  GPIO_TypeDef  *direction_gpio;
	GPIO_TypeDef  *pulse_gpio;
	TIM_HandleTypeDef timer;
  uint16_t      enable_pin;
  uint16_t      direction_pin;
	uint16_t      pulse_pin;
	uint16_t			PulsePerRev;
	uint16_t			Speed;
}tb6600_t;


typedef enum
    {
				CW = GPIO_PIN_SET,  ///< Counter-Clockwise
        CCW  = GPIO_PIN_RESET  ///< Clockwise
    } Direction;

typedef enum
    {
				VFast 	= 50,  //12mm/sec (Dia=8mm)
				Fast 		= 75,	 //8mm/sec (Dia=8mm)
        Medium  = 150, //4mm/sec (Dia=8mm)   
				Slow		= 300, //2mm/sec (Dia=8mm)
				VSlow		= 600  //1mm/sec (Dia=8mm)
		} Speed;
		
//####################################################################################################################
		
void tb6600_init(tb6600_t *tb6600, GPIO_TypeDef  *enable_gpio, uint16_t enable_pin, GPIO_TypeDef  *direction_gpio, uint16_t direction_pin,GPIO_TypeDef  *pulse_gpio,uint16_t pulse_pin,TIM_HandleTypeDef htimx);
void tb6600_Set(tb6600_t *tb6600,Direction direction,Speed speed,uint16_t PulsePerRev,uint16_t Clock);
void tb6600_AngleMove(tb6600_t *tb6600,uint16_t Degree);
void tb6600_Enable(tb6600_t *tb6600);
void tb6600_Disable(tb6600_t *tb6600);
void tb6600_ChangeDirection(tb6600_t *tb6600,Direction direction);
void tb6600_ChangeSpeed(tb6600_t *tb6600,Speed speed);
void tb6600_ChangePulsePerRev(tb6600_t *tb6600,uint16_t PulsePerRev);
void tb6600_cont(tb6600_t *tb6600);
void tb6600_Movemm(tb6600_t *tb6600,uint16_t Millimeters);
void tb6600_ManualSpeed(tb6600_t *tb6600,uint16_t mmpersec);
		
//####################################################################################################################
		
#endif