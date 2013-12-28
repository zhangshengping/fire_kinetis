/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：isr.c
 * 描述         ：中断处理例程
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	



#include "common.h"
#include "include.h"
#include "isr.h"

extern unsigned int i;
extern OS_EVENT * sem_I;
//extern OS_EVENT  * CInt;

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  备    注：
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //关总中断

    //接收一个字节数据并回发
    ch=uart_getchar (UART1);        //接收到一个数据
    uart_sendStr  (UART1,"\n你发送的数据为：");
    uart_putchar (UART1,ch);        //就发送出去

    EnableInterrupts;		    //开总中断
}




/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：SysTick_Handler
*  功能说明：系统滴答定时器中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：ucos里用得到
*************************************************************************/
void SysTick_Handler(void)
{
        OSIntEnter();
        OSTimeTick();
        OSIntExit();
}


//void PORTD_IRQHandler()  //行中断处理函数
//{
//     OSIntEnter();
//     OSIntExit();
//}
//
void PORTE_IRQHandler()  //场中断处理函数
{
  PORTE_PCR0 |= PORT_PCR_ISF_MASK;
  OSIntEnter();
  i++;
  disable_irq(91);
  OSSemPost(sem_I);
  OSIntExit();
}





