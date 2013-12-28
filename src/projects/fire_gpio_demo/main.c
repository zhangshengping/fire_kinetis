//-----------------------------------------------------------------------
// 工 程 名: SDHC                           
// 硬件连接: 将K60核心板与二层小板                                       
// 程序描述: 用于测试SDHC构件
// 目    的: 初步掌握SDHC模块的编程方法       
// 说    明: 波特率为115200,使用UART3口
// 版权所有: 苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
// 版本更新:    时间                         版本                             修改
//           2011-12-14     V1.0      SDHC构件初始版本
//---------------苏州大学飞思卡尔嵌入式系统实验室2011年--------------------

//头文件
#include "includes.h"

//全局变量声明
extern int periph_clk_khz;
uint8 InitSD(uint8 verbose);

//SD卡操作可能返回结果
enum
{
	SD_OK,
	NO_SD_CARD,
	INIT_SD_FAILS
};

//主函数
void main(void)
{
    //1 主程序使用的变量定义
    uint32 runcount,i;		//运行计数器
    uint8  SDHCReceiveBuff[512];
    //2 关中断
    DisableInterrupts;      //禁止总中断

    //3 模块初始化
    light_init(Light_Run_PORT,Light_Run1,Light_OFF); //指示灯初始化
    hw_uart_init (UART4,periph_clk_khz,115200);			 //串口初始化

    InitSD(VERBOSE_ON);
    //4 开中断
    //enable_uart_re_int(UART4,UART5irq);		//开串口3接收中断
    EnableInterrupts;			        //开总中断

    hw_uart_send_string(UART4,(uint8*)"\r\n");
    
    if(disk_read (0,SDHCReceiveBuff,0,1) == RES_OK)
    {
    	for(i = 0;i < 512;i++)
    	{
    		hw_uart_send_hex_number(UART4,(uint32)SDHCReceiveBuff[i]);
    		hw_uart_send_string(UART4,(uint8*)" ");
    	}
		hw_uart_send_string(UART4,(uint8*)"\r\n");
    }
    else
    {
    	hw_uart_send_string(UART4,(uint8*)"Read disk failed!\r\n");
    }
    
    for(i = 0;i < 512;i++)
    {
    	SDHCReceiveBuff[i]++;
    }
    if(disk_write (0,SDHCReceiveBuff,0,1) == RES_OK)
    {
    	hw_uart_send_string(UART4,(uint8*)"Write disk successed!\r\n");
    }
    else
    {
    	hw_uart_send_string(UART4,(uint8*)"Write disk failed!\r\n");
    }
    for(i = 0;i < 512;i++)
    {
    	SDHCReceiveBuff[i] = 0;
    }
    if(disk_read (0,SDHCReceiveBuff,0,1) == RES_OK)
    {
    	for(i = 0;i < 512;i++)
    	{
    		hw_uart_send_hex_number(UART4,(uint32)SDHCReceiveBuff[i]);
    		hw_uart_send_string(UART4,(uint8*)" ");
    	}
		hw_uart_send_string(UART4,(uint8*)"\r\n");
    }
    else
    {
    	hw_uart_send_string(UART4,(uint8*)"Read disk failed!\r\n");
    }

    //主循环
    while(1)
    {
        //1 主循环计数到一定的值，使小灯的亮、暗状态切换
        runcount++;
        if(runcount>=5000000)
        {
            light_change(Light_Run_PORT,Light_Run1);//指示灯的亮、暗状态切换
            runcount=0;
        }
    }
}


uint8 InitSD(uint8 verbose)
{ 
  uint8  status;
  uint32 i;

  #define TF_PWR_PORT PORT_E
  #define TF_PWR      6
  hw_gpio_init(TF_PWR_PORT, TF_PWR, 1, 1);
  
  //等待信号稳定
  for(i = 0;i < 200000;i++)
  {
  }
  
  //判断SD是否已经打开
  if ((disk_status(0) & STA_NOINIT) != STA_NOINIT)
  {
		if (verbose == VERBOSE_ON)
		{
			hw_uart_send_string(UART4,(uint8 *)"\n\rSD card is already mounted!\n\r");
		}
		return SD_OK;
  }
  
  if (SDCARD_GPIO_DETECT == 0)
  {
		//等待SD卡初始化完成
		for(i = 0;i < 1000000;i++)
		{
		}
		
		//初始化磁盘0
		status = disk_initialize(0);
		if (status == RES_OK)
		{
			if (SDHC_Info.CARD == ESDHC_CARD_SD)
			{
				if (verbose == VERBOSE_ON)
				{
					hw_uart_send_string(UART4,(uint8 *)"\n\rSD card has been successfully initialized !!!\n\r");
				}
			}
			if (SDHC_Info.CARD == ESDHC_CARD_SDHC)
			{
				if (verbose == VERBOSE_ON)
				{
					hw_uart_send_string(UART4,(uint8 *)"\n\rSDHC card has been successfully initialized !!!\n\r");
				}
			}			
		}else
		{
			if (verbose == VERBOSE_ON)
			{
				hw_uart_send_string(UART4,(uint8 *)"\n\rSD card failure !!!\n\r");
			}
			return INIT_SD_FAILS;
		}
	}else
	{
		if (verbose == VERBOSE_ON)
		{
			hw_uart_send_string(UART4,(uint8 *)"\n\rNo SD card detected !!!\n\r");		
		}	
		return NO_SD_CARD;
	}
	return SD_OK;
}
