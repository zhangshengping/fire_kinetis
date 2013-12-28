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
#include "nokia_5110.h"

extern u32 i,j;
extern u8 image[40][40];
extern u8 finish_flag;
u8 cow = 0, row = 0, line = 0;
u32 hang,chang;

void image_us()
{
   int i =0;
   int j=0;
   for(i=0;i<25;i++)
   for(j=0;j<22;j++)
       asm("nop");

}




void PORTD_IRQHandler()  //行中断处理函数
{
    u8 dly;
     PORTD_ISFR |= 1<<10;
     image_us();
     if(line < 200)
     {
       if(line%5 == 0)
       {
         dly = 9;
         for(row = 0; row < 40; row++)
          image[cow][row] = GPIOD_PDIR & 0xff;
         while(dly--)
         {
           asm("nop");
         }
         cow++;
       }
       line++;
     }
     else
     {
       disable_irq(90);
       finish_flag = 1;
     }
     Light4_turn();
}

void PORTE_IRQHandler()  //场中断处理函数
{
  PORTE_PCR0 |= PORT_PCR_ISF_MASK;
  disable_irq(91);
  enable_irq(90);
  cow = 0;
  line = 0;
  Light3_turn();
}






void USART1_IRQHandler(void)
{
   
}
    
//void PORTA_IRQHandler()
//  {
//    
//    if(PORTA_ISFR & 1<<9)
//    {
//      PORTA_ISFR |= 1<<9;
//      //行中断信号触发的程序
//    LCD_write_num(0,0,i);
//    i++;
//      
//      
//    }
//    if(PORTA_ISFR & 1<<27)
//    {
//      PORTA_ISFR |= 1<<27;
//      //场中断信号触发的程序
//      
//    }
//  }