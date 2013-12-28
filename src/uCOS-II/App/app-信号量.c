
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


unsigned int i = 0;

/*********************************任务堆栈区*****************************/
OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		    //定义任务Task_Start的栈

OS_STK app_task_stk[STARTUP_TASK_STK_SIZE];

OS_STK app_task1_stk[STARTUP_TASK_STK_SIZE];

OS_STK app_task2_stk[STARTUP_TASK_STK_SIZE];

OS_STK State_Get_stk[STARTUP_TASK_STK_SIZE];



/********************************系统组件变量定义区**********************/
OS_EVENT * sem_LED;





/******************************任务函数定义区*************************
*******************************任务函数定义区**************************
*******************************任务函数定义区*************************
*******************************任务函数定义区*************************
*******************************任务函数定义区*************************/



/*******************************系统初始化任务************************
* 功能：系统初始化，其他任务可以在这个任务中创建
*
*
*
*
*********************************************************************/
void Task_Start(void *p_arg)
{
    /**************** 初始化 系统滴答时钟 ：用于定时任务调度****************/
    u32  cnts;                                                                     
    cnts         = core_clk_mhz *( (u32)1000000u / (u32)OS_TICKS_PER_SEC );        /* Determine nbr SysTick increments.                    */
    OS_CPU_SysTickInit(cnts);                                                     /* Init uC/OS periodic time src (SysTick).              */

   
#if (OS_TASK_STAT_EN > 0)
     /*       开启统计任务           */
    OSStatInit();                                               
#endif
    
    
    (void)p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告    
    
    BSP_Init();                                                 //初始化开发板
//   CInt = OSSemCreate(0);                                      //创建信号量
    
    /******************* 用户任务区 ************************/
    OSTaskCreate(app_task1,(void *)0,
                 &app_task1_stk[STARTUP_TASK_STK_SIZE-1], APP_TASK1_PRIO);
    OSTaskCreate(State_Get,(void *)0,
                 &State_Get_stk[STARTUP_TASK_STK_SIZE-1], State_Get_PRIO);
    
    while (1)
    {
        LED_turn(LED0);                                         //LED0闪烁
	OSTimeDlyHMSM(0, 3,0,0); 
    }
}




/*******************************信号量发送测试************************
* 功能：信号量测试
*
*
*
*
*********************************************************************/
void State_Get(void *p_arg)
{
  uint8_t state;
  (void) p_arg;
  sem_LED = OSSemCreate(0);
  while(1)
  {
    state = PTC2_IN;
    if(state)
    {
      OSSemPost(sem_LED);
    }
    OSTimeDlyHMSM(0,0,6,0);
  }
}



/*******************************信号量等待************************
* 功能：信号量等待
*
*
*
*
*********************************************************************/
void app_task1(void *p_arg)
{
  INT8U ERR;
  (void) p_arg;
  while(1)
  {
    OSSemPend(sem_LED, 0, &ERR);
    Light3_on;
    OSTimeDlyHMSM(0,0,0,600);
    Light3_off;
  }
}



/*******************************信号量等待************************
* 功能：信号量等待
*
*
*
*
*********************************************************************/
void app_task(void *p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light2_on;
    OSTimeDlyHMSM(0,0,0,500);
    Light2_off;
    OSTimeDlyHMSM(0,0,0,500);
  }
}



/*******************************信号量等待************************
* 功能：信号量等待
*
*
*
*
*********************************************************************/
void app_task2(void *p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light4_on;
    OSTimeDlyHMSM(0,0,3,0);
    Light4_off;
    OSTimeDlyHMSM(0,0,3,0);
  }
}





/*******************************main************************
* 功能：main函数
*
*
*
*
*********************************************************************/
void main()
{
    
    OSInit();                                               //初始化uC/OS
    OSTaskCreate(Task_Start,(void *)0,
                 &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);    //创建任务
    OSStart();                                              //启动多任务管理
}


