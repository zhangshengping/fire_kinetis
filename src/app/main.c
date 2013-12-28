/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：main.c
 * 描述         ：UART串口发送实验
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


void main()
{
	u32	i;
	FTM_PWM_init(FTM1,CH0,35000,100);
	while(1)
	{
		for(i=10;i>1;i--)
		{
			FTM_PWM_Duty(FTM1,CH0,i*10);
			time_delay_ms(100);
		}
	}
}