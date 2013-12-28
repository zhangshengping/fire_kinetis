/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：app.c
 * 描述         ：uC/OS的用户任务函数头文件
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	

#ifndef _APP_H_
#define _APP_H_


#include <stdint.h>
#include <app.h>
#include  "ucos_ii.h"  		//uC/OS-II系统函数头文件
#include  "LED.h"
#include  "sysinit.h"          //系统配置
#include <BSP.h>
#include "LED_CORE.h"
#include "common.h"
#include "include.h"
#include "nokia_5110.h"








/**************** 用户任务声明 *******************/
void Task_Start(void *p_arg);

void app_task(void *p_arg);

void app_task1(void *p_arg);

void app_task2(void *p_arg);

void State_Get(void *p_arg);



#endif    //_APP_H_
