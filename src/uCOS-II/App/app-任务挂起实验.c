

#include "app.h"

/*****************************************************
*                                                    *
*                  头文件包含区                      *
*                                                    *
******************************************************/
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



/*****************************************************
*                                                    *
*                  任务堆栈定义区                    *
*                                                    *
******************************************************/
OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		    

OS_STK task1_stk[task1_stk_size];

OS_STK task2_stk[task2_stk_size];

OS_STK task3_stk[task3_stk_size];



/*****************************************************
*                                                    *
*                  系统组件变量定义                  *
*                                                    *
******************************************************/
OS_EVENT * sem_LED;
OS_EVENT * sem_I;





/*****************************************************
*                                                    *
*                  任务函数定义                      *
*                                                    *
******************************************************/
void task1(void * p_arg)
{
  (void) p_arg;
  while(1)
  {
   if(PTC2_IN == 1) OSTaskSuspend(task2_prio);
   else OSTaskResume(task2_prio);
   Light1_turn();
   OSTimeDly(900);
//    Light2_turn();
//    Light3_turn();
//    Light4_turn();
  }
}

void task2(void * p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light2_turn();
    OSTimeDlyHMSM(0,0,0,700);
    
//    Light2_turn();
//    Light3_turn();
//    Light4_turn();
  }
}

void task3(void * p_arg)
{
  (void) p_arg;
  while(1)
  {
    Light3_turn();
    OSTimeDlyHMSM(0,0,0,500);
//    Light2_turn();
//    Light3_turn();
//    Light4_turn();
  }
}
















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
    
    
    (void)p_arg;   // 'p_arg' 并没有用到，防止编译器提示警告                 				
    
    BSP_Init();  //初始化开发板,建议所有初始化在这里完成                                               
    
    /*******************用户任务创建区************************/
    OSTaskCreate(task1,(void *)0,
                 &task1_stk[task1_stk_size - 1], task1_prio); 
    OSTaskCreate(task2, (void *)0,
                 &task2_stk[task2_stk_size - 1], task2_prio);
    OSTaskCreate(task3, (void *)0,
                 &task3_stk[task3_stk_size - 1], task3_prio);
    while (1)
    {
        Light4_turn();                                         //LED0闪烁
	OSTimeDlyHMSM(0, 0,0,500); 
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


