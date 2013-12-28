/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*                                  SonyCCD图像采集实验
*
*  实验说明：通过Kinetis的DMA和EXTI驱动SonyCCD摄像头
*
*  实验操作：Kinetis与SonyCCD接线方式：
*                       Kinetis            SonyCCD
*                        PTE7               PCLK
*                        PTD10              HREF
*                        PTE0               VSYN
*                        GND                GND
*             Kinetis与串口模块接线方式：
*                   PTC3接RX    PTC4接TX   默认串口1 波特率115200
*             分辨率输出320*240
*
*  说    明：数据的发送和采集并不同步进行，采集完一帧图像停止采集，将其发
*            送，发送完毕后才继续采集
*
*  修    改：聂晓艺
*************************************************************************/

#include "common.h"
#include "include.h"

u8 ImageBuf[ROW-200][COL];

volatile u32 rowCnt = 0 ;
volatile u8 SampleFlag = 0;



#if 0

/*-----------------使用串口猎人接受一幅图像数据的主程序-------------*/

void main()
{
    u16  i;
    u16  j;

//    LED_init();

    //----初始化图像数组----//
    for(i=0; i<ROW-200; i++)
    {
      for(j=0;j<COL ;j++)
      {
        ImageBuf[i][j] = 0;
      }
    }
    
    uart_init(UART1,115200);
    
    
    DisableInterrupts;  
    
    //----初始化外部中断---//
    exti_init(PORTD, 10, rising_down);       //HREF----PORTD10 端口外部中断初始化 ，上升沿触发中断，内部下拉
    exti_init(PORTE,  0, rising_down);       //VSYN----PORTE0 端口外部中断初始化 ，上升沿触发中断，内部下拉

    EnableInterrupts;

    while(SampleFlag != 2);

    for(i=0;i<ROW-200;i++)
    {
        for(j=0;j<COL;j++)
        {
            printf("%-4d",ImageBuf[i][j]);
        }
        printf("\n");
    }
    
    DisableInterrupts;
         
}



#elif 1

/*----------------使用上位机发送图像的主程序-----------------*/

void main()
{
    u16  i;
    u16  j;

//    LED_init();

    //----初始化图像数组----//
    for(i=0; i<ROW-200; i++)
    {
      for(j=0;j<COL ;j++)
      {
        ImageBuf[i][j] = 0;
      }
    }
    
    uart_init(UART1,115200);
    
    
    DisableInterrupts;  
    
    //----初始化外部中断---//
    exti_init(PORTD, 10, rising_down);       //HREF----PORTD10 端口外部中断初始化 ，上升沿触发中断，内部下拉
    exti_init(PORTE,  0, rising_down);       //VSYN----PORTE0 端口外部中断初始化 ，上升沿触发中断，内部下拉
    EnableInterrupts;
    
//    delayms(100);
    
//    enable_irq (91);
    for(;;)
    {
        while(SampleFlag == 2);
        
//        disable_irq (90);
//        disable_irq (91);
          
        uart_putchar (UART1,0);
        uart_putchar (UART1,255);
        uart_putchar (UART1,1);
        uart_putchar (UART1,0);        //发送上位机命令字
            
        for(i=0; i<ROW-200; i++)
        {
          for(j=0;j <COL; j++)
          {
            uart_putchar(UART1,ImageBuf[i][j]);
          }
        }
        
//        for(j=0; j<COL; j++)
//        {
            uart_putchar(UART1,255);
//        }
        
        SampleFlag = 0;
//        EnableInterrupts;
//        enable_irq (91);
//        enable_irq (90);
    }  
}



#else

/*---------------使用串口猎人发送N幅图像数据的主程序----------------*/
/*---------------------每幅图像数据以END结尾-----------------------*/

#define N 10

void main()
{
    u16  i;
    u16  j;
    u8   n;

//    LED_init();

    //----初始化图像数组----//
    for(i=0; i<ROW-200; i++)
    {
      for(j=0; j<COL ;j++)
      {
        ImageBuf[i][j] = 0;
      }
    }
    
    uart_init(UART1,115200);
    
    
    DisableInterrupts;  
    
    //----初始化外部中断---//
    exti_init(PORTD, 10, rising_down);       //HREF----PORTD10 端口外部中断初始化 ，上升沿触发中断，内部下拉
    exti_init(PORTE,  0, rising_down);       //VSYN----PORTE0 端口外部中断初始化 ，上升沿触发中断，内部下拉

    EnableInterrupts;

    for(n=0; n<N; n++)
    {
        while(SampleFlag != 2);

        for(i=0;i<ROW-200;i++)
        {
            for(j=0;j<COL;j++)
            {
                printf("%-4d",ImageBuf[i][j]);
            }
            printf("\n");
        }       
        printf("END\n");
        
        SampleFlag = 0;
        EnableInterrupts;
    }
}

#endif