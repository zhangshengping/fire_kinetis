

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


//INT8U a[4] = {1,2,3,4};
//INT8U b[4] = {5,6,7,8};




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
OS_EVENT * Queue;

void * Queuel[5];

INT8U a[10]={1,2,3,4,5,6,7,8,9,0};

INT8U b[10]={1+10,2+10,3+10,4+10,5+10,6+10,7+10,8+10,9+10,0+10};




/*****************************************************
*                                                    *
*                  任务函数定义                      *
*                                                    *
******************************************************/
void task1(void *p_arg)
{
  INT8U i;
  (void) p_arg;
  (INT8U *) b;
   while(1)
  {
    for(i = 0; i< 10;i++)
    {
      OSQPost(Queue,b+i);
      OSTimeDlyHMSM(0,0,0,103);
    }
  }
}

void task3(void * p_arg)
{
  INT8U * msg;
  INT8U err;
  while(1)
  {
    msg = (INT8U *)OSQPend(Queue, 0, &err);
    LCD_write_num(0,0,(int)*msg);
    OSTimeDlyHMSM(0,0,0,200);
  }
}

void task2(void * p_arg)
{
  Queue = OSQCreate(Queuel,5);
  INT8U i;
  (INT8U *)a;
  while(1)
  {
    for(i= 0 ;i <10;i++)
    {
      OSQPost(Queue, a+i);
      LCD_write_english_string(0,3,"OSQPosted");
      OSTimeDlyHMSM(0,0,0,158);
    }
    
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
        GPIO_PTOR_REG(PTB_BASE_PTR) |= 1;
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


