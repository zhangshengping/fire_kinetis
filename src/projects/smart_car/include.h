#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */

#include  "gpio.h"       //IO口操作
#include  "uart.h"      //串口
#include  "lptmr.h"     //低功耗定时器(延时)
#include  "delay.h"		//延时函数
#include  "exti.h"		//exti外部中断
#include  "mcg.h"
#include  "wdog.h"		//看门狗
#include  "PIT.h"			//PIT定时器中断模块
#include  "dma.h"
#include  "LED.h"
//#include  "nokia_5110.h"

#define ROW 320
#define COL 200

#endif  //__INCLUDE_H__
