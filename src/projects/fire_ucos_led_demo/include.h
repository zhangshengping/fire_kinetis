#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */

#include  "gpio.h"       //IO口操作
#include  "LED.H"       //流水灯
#include  "uart.h"      //串口
#include  "adc.h"       //ADC模块
#include  "lptmr.h"     //低功耗定时器(延时)
#include  "exti.h"      //EXTI外部GPIO中断

/***************** ucos 专用 *****************/
#define USOC_EN 1u
#if USOC_EN > 0u
#include  "ucos_ii.h"  		        //uC/OS-II系统函数头文件
#include  "BSP.h"			//与开发板相关的函数
#include  "app.h"			//用户任务函数


#endif  //if  USOC_EN > 0


#endif  //__INCLUDE_H__
