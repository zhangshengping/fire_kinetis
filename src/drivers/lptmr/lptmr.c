/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：lptmr.c 
 * 描述         ：lptmr定功耗定时器，目前只有一个定时器延时函数
 * 备注         ：官方例程
 *          
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 * 
 * 作者         ：飞思卡尔公司
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008   
**********************************************************************************/	

#include "common.h"
#include "lptmr.h"

/*************************************************************************
*                             野火嵌入式开发工作室
*  
*  函数名称：time_delay_ms
*  功能说明：延时函数，使用定功耗定时器延时，准确
*  参数说明：ms   延时时间，单位为ms
*  函数返回：无
*  修改时间：2012-1-20
*  备    注：官方例程自带
*************************************************************************/
void time_delay_ms(uint32 ms)
{
    /* Make sure the clock to the LPTMR is enabled */
    SIM_SCGC5|=SIM_SCGC5_LPTIMER_MASK; 
    
    /* Set the compare value to the number of ms to delay */
    LPTMR0_CMR = ms; 
    
    /* Set up LPTMR to use 1kHz LPO with no prescaler as its clock source */
    LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK; 
    
    /* Start the timer */
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; 
    
    /* Wait for counter to reach compare value */
    while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK));
    
    /* Clear Timer Compare Flag */
    LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;
    
    return;
}