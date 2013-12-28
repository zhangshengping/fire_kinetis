

#ifndef __LED_CORE_H__
#define __LED_CORE_H__


/*********************核心板上的LED灯驱动**************/

/*******************头文件包含***********************/
#include "gpio.h"

/********************核心板选择**********************/
#define   ENABLE     1
#define   DISABLE    0

#define   __QRSKFW__         DISABLE
#define   __FIRE_LIGHT__     DISABLE
#define   __LQ_LIGHT__       DISABLE
#define   __LQ_LIGHT_100P__  ENABLE

/*******************宏函数***************************/

#if  __QRSKFW__

#define Light_init gpio_init(PORTB,7,GPO,1);
#define Light1_on   PTB7_OUT = 0
#define Light1_off    PTB7_OUT = 1
#define Light1_ptor   GPIOB_PTOR_REG(PTB_BASE_PTR)
#define Light1_pin    7

#endif


/**************野火的核心板******************/
#if __FIRE_LIGHT__
#define Light_init gpio_init(PORTD,12,GPO,1);\
                   gpio_init(PORTD,13,GPO,1);\
                   gpio_init(PORTD,14,GPO,1);\
                   gpio_init(PORTD,15,GPO,1)
#define Light1_on   PTD12_OUT = 0
#define Light2_on   PTD13_OUT = 0
#define Light3_on   PTD14_OUT = 0
#define Light4_on   PTD15_OUT = 0  
#define Light1_off  PTD12_OUT = 1
#define Light2_off  PTD13_OUT = 1
#define Light3_off  PTD14_OUT = 1
#define Light4_off  PTD15_OUT = 1
                     
#define Light1_ptor GPIO_PTOR_REG(PTD_BASE_PTR)
#define Light2_ptor GPIO_PTOR_REG(PTD_BASE_PTR)
#define Light3_ptor GPIO_PTOR_REG(PTD_BASE_PTR)
#define Light4_ptor GPIO_PTOR_REG(PTD_BASE_PTR) 
#define Light1_pin  12                     
#define Light2_pin  13
#define Light3_pin  14
#define Light4_pin  15                     
#endif

#if __LQ_LIGHT__

#define Light_init gpio_init(PORTA,14,GPO,1);\
                      gpio_init(PORTA,15,GPO,1);\
                      gpio_init(PORTA,16,GPO,1);\
                      gpio_init(PORTA,17,GPO,1)
#define Light1_on   PTA14_OUT = 0
#define Light2_on   PTA15_OUT = 0
#define Light3_on   PTA16_OUT = 0
#define Light4_on   PTA17_OUT = 0  
#define Light1_off  PTA14_OUT = 1
#define Light2_off  PTA15_OUT = 1
#define Light3_off  PTA16_OUT = 1
#define Light4_off  PTA17_OUT = 1 
#define Light1_ptor GPIO_PTOR_REG(PTA_BASE_PTR)
#define Light2_ptor GPIO_PTOR_REG(PTA_BASE_PTR)
#define Light3_ptor GPIO_PTOR_REG(PTA_BASE_PTR)
#define Light4_ptor GPIO_PTOR_REG(PTA_BASE_PTR) 
#define Light1_pin  14                     
#define Light2_pin  15
#define Light3_pin  16
#define Light4_pin  17 
                        
#endif
                        
#if __LQ_LIGHT_100P__

#define Light_init gpio_init(PORTA,12,GPO,1);\
                      gpio_init(PORTA,13,GPO,1);\
                      gpio_init(PORTA,14,GPO,1);\
                      gpio_init(PORTA,15,GPO,1)
#define Light1_on   PTA12_OUT = 0
#define Light2_on   PTA13_OUT = 0
#define Light3_on   PTA14_OUT = 0
#define Light4_on   PTA15_OUT = 0  
#define Light1_off  PTA12_OUT = 1
#define Light2_off  PTA13_OUT = 1
#define Light3_off  PTA14_OUT = 1
#define Light4_off  PTA15_OUT = 1 
#define Light1_ptor GPIO_PTOR_REG(PTA_BASE_PTR)
#define Light2_ptor GPIO_PTOR_REG(PTA_BASE_PTR)
#define Light3_ptor GPIO_PTOR_REG(PTA_BASE_PTR)
#define Light4_ptor GPIO_PTOR_REG(PTA_BASE_PTR) 
#define Light1_pin  12                     
#define Light2_pin  13
#define Light3_pin  14
#define Light4_pin  15                         
#endif



void Light1_turn();

void Light2_turn();

void Light3_turn();

void Light4_turn();
                        
#endif