

#include "nokia_5110.h"
#include "english_6x8_pixel.h"
#include "write_chinese_string_pixel.h"


/*-----------------------------------------------------------------------
LCD_init          : NOKIA5110LCD 初始化

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/

void delay_1us(void)                 //1us延时函数
  {
   unsigned int i;
  for(i=0;i<1000;i++);
  }

  void delay_1ms(void)                 //1ms延时函数
  {
   unsigned int i;
   for (i=0;i<11400;i++);
  }
  
void delay_nms(unsigned int n)       //N ms延时函数
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }

  
void LCD_pin_config()
{
    gpio_init(PortSCLK, SCLK_Pin,GPO,HIGH);
    gpio_init(PortSDIN, SDIN_Pin,GPO,HIGH);
    gpio_init(PortLCD_DC, LCD_DC_Pin,GPO,HIGH);
    gpio_init(PortLCD_CE, LCD_CE_Pin,GPO,HIGH);
    gpio_init(PortLCD_RST, LCD_RST_Pin,GPO,HIGH);
}

void LCD_init(void)
  {
            // 产生一个让LCD复位的低电平脉冲
   LCD_pin_config();
   LCD_RST = 0;
   // delay_1us();    

   LCD_RST = 1;
    
		// 关闭LCD
   LCD_CE = 0;
  //  delay_1us();
		// 使能LCD
   LCD_CE = 1;
    delay_1us();

    LCD_write_byte(0x21, 0);	// 使用扩展命令设置LCD模式
    LCD_write_byte(0xc0, 0);	// 设置偏置电压   供电电压高时该值调小
    LCD_write_byte(0x07, 0);	// 温度校正
    LCD_write_byte(0x13, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// 使用基本命令
    LCD_clear();	        // 清屏
    LCD_write_byte(0x0c, 0);	// 设定显示模式，正常显示
        
           // 关闭LCD
   LCD_CE = 0;
  }

/*-----------------------------------------------------------------------
LCD_clear         : LCD清屏函数,并且将XY坐标清零

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void LCD_clear(void)
  {
    unsigned int i;

    LCD_write_byte(0x0c, 0);			
    LCD_write_byte(0x80, 0);			

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);
	LCD_set_XY(0,0);											//将XY坐标清零
  }

/*-----------------------------------------------------------------------
LCD_set_XY        : 设置LCD坐标函数

输入参数：X       ：0－83
          Y       ：0－5

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
  {
    LCD_write_byte(0x40 | Y, 0);								// column
    LCD_write_byte(0x80 | X, 0);          						// row
  }

/*-----------------------------------------------------------------------
LCD_write_char    : 显示英文字符

输入参数：c       ：显示的字符；

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 
-----------------------------------------------------------------------*/
void LCD_write_char(unsigned char c)
  {
    unsigned char line;

    c -= 32;

    for (line=0; line<6; line++)
      LCD_write_byte(font6x8[c][line], 1);
  }

/*-----------------------------------------------------------------------
LCD_write_english_String  : 英文字符串显示函数

输入参数：*s      ：英文字符串指针；
          X、Y    : 显示字符串的位置,x 0-83 ,y 0-5

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-10 		
-----------------------------------------------------------------------*/
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
  {
    LCD_set_XY(X,Y);
    while (*s) 
      {
	 LCD_write_char(*s);
	 s++;
      }
  }
/*-----------------------------------------------------------------------
LCD_write_chinese_string: 在LCD上显示汉字

输入参数：X、Y    ：显示汉字的起始X、Y坐标；
          ch_with ：汉字点阵的宽度
          num     ：显示汉字的个数；  
          line    ：汉字点阵数组中的起始行数
          row     ：汉字显示的行间距
编写日期          ：2004-8-11 
最后修改日期      ：2004-8-12 
测试：
	LCD_write_chi(0,0,12,7,0,0);
	LCD_write_chi(0,2,12,7,0,0);
	LCD_write_chi(0,4,12,7,0,0);	
-----------------------------------------------------------------------*/                        
void LCD_write_chinese_string(unsigned char X, unsigned char Y, 
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row)
  {
    unsigned char i,n;
    
    LCD_set_XY(X,Y);                             			//设置初始位置
    
    for (i=0;i<num;)
      {
      	for (n=0; n<ch_with*2; n++)              			//写一个汉字
      	  { 
      	    if (n==ch_with)                      			//写汉字的下半部分
      	      {
      	        if (i==0) LCD_set_XY(X,Y+1);
      	        else
      	           LCD_set_XY((X+(ch_with+row)*i),Y+1);
              }
      	    LCD_write_byte(write_chinese[line+i][n],1);
      	  }
      	i++;
      	LCD_set_XY((X+(ch_with+row)*i),Y);
      }
  }
  


/*-----------------------------------------------------------------------
LCD_draw_map      : 位图绘制函数

输入参数：X、Y    ：位图绘制的起始X、Y坐标；
          *map    ：位图点阵数据；
          Pix_x   ：位图像素（长）
          Pix_y   ：位图像素（宽）

编写日期          ：2004-8-13
最后修改日期      ：2004-8-13 
-----------------------------------------------------------------------*/
void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y)
  {
    unsigned int i,n;
    unsigned char row;
    
    if (Pix_y%8==0) row=Pix_y/8;      					//计算位图所占行数
      else
        row=Pix_y/8+1;
    
    for (n=0;n<row;n++)
      {
      	LCD_set_XY(X,Y);
        for(i=0; i<Pix_x; i++)
          {
            LCD_write_byte(map[i+n*Pix_x], 1);
          }
        Y++;                         					//换行
      }      
  }

/*-----------------------------------------------------------------------
LCD_write_byte    : 使用SPI接口写数据到LCD

输入参数：data    ：写入的数据；
          command ：写数据/命令选择；

编写日期          ：2004-8-10 
最后修改日期      ：2004-8-13 
-----------------------------------------------------------------------*/
void LCD_write_byte(unsigned char dat, unsigned char command)
  {
    unsigned char i;
    //PORTB &= ~LCD_CE ;		        	// 使能LCD
    LCD_CE = 0;
    
    if (command == 0)
     // PORTB &= ~LCD_DC ;	        		// 传送命令
     LCD_DC = 0;
    else
     // PORTB |= LCD_DC ;		        	// 传送数据
     LCD_DC = 1;
		for(i=0;i<8;i++)
		{
			if(dat&0x80)
				SDIN = 1;
			else
				SDIN = 0;
			SCLK = 0;
			dat = dat << 1;
			SCLK = 1;
		}
   // SPDR = data;							// 传送数据到SPI寄存器

    //while ((SPSR & 0x80) == 0);         	// 等待数据传送完毕
	
    //PORTB |= LCD_CE ;						// 关闭LCD
     LCD_CE = 1;
  }
  
 
  
  
  
  
  /*=====================整屏画图函数====================
输    入：map  图像向量地址
作    者：张盛平
修改时间：2013-3-12
======================================================*/  
  
void LCD_draw_whole(unsigned char * map)
  {
	  int i;
	  
	  LCD_clear();
	  
	  
	  for(i=0;i<504;i++)
	  {
		  LCD_write_byte(*map++,1);
	  }
  }
  
  
  
  
  
  
  
  /*=========长时间延时函数=============
  作    者：张盛平
  ====================================*/
  void delay_long_time(void)
 {
 	unsigned int time=2576;
 	while(time--);
 }





/*==============图像显示函数（智能车不常用，数组的一字节写nokia5110的8个点）========
LCD_draw_picture    : 将一个二维图像矩阵在nokia5110中显示

输入参数：start_x     ：显示图像的开始的行号；
          start_y    ：显示图像的开始的列号；
          map       : 图像数组；
          line     : 行数；
          row      ：列数（0-5）；

编写日期          ：2013-6-29 
最后修改日期      ：2013-6-29 
加入日期          ：2013-07-04
================================================================================*/
void LCD_draw_picture(unsigned char start_x, unsigned char start_y, 
                      unsigned char *map, unsigned char line, unsigned row)
  {
        unsigned char *p;
        unsigned i,j;
        p= map;
        for(i=0;i<line;i++)
        {
              LCD_set_XY(start_x,start_y+i);
              for(j=0;j<row;j++)
              {
                    LCD_write_byte(*p++,1);
              }
        }
  }
  
  
  
  
  
  
  
/*=========================================================================
** 函数名：
          LCD_draw_pixel
          
** 函数功能简介：
          将一个二维图像矩阵在nokia5110中显示

** 输入参数：
          image    ：要显示图像矩阵的首地址(指针)（可以是数组名）；
          line     ：图像行数（像素点）；
          row      : 图像列数（像素点）；
          threshold: 二值化阀值（如果是二值化以后的图像，阀值为0）；
          X        ：开始显示的X坐标；
          Y        ：开始显示的Y坐标（0-5）；

** 返回参数：
           无

** 作   者：
           张盛平

** 编写日期：
            2013-6-29 

** 修改历史：
            2013-6-29 

** 添加日期：
            2013-07-04
===========================================================================*/
  void LCD_draw_pixel(void *image, unsigned char line, unsigned char row,
                    unsigned char threshold,unsigned char X, unsigned char Y)
   {
      unsigned char *p_image, i, j, k, temp,n;
      p_image = image;
//      if(line > 0)
        n=line/8;
      for(i=0;i<n;i++)
      {
            LCD_set_XY(0+X,i+Y);
            for(j=0;j<row;j++)
            {
                  for(k=0;k<8;k++)
                  {
                       ((*(p_image+(i*8+k)*row+j))>threshold) ? 
                                     (temp &= ~(1<<k)):(temp |= 1<<k) ;
                  }
                  LCD_write_byte(temp,1);
            }
      }
      if(line%8)
            {
                  for(j=0;j<row;j++)
                        {
                              for(k=0;k<line%8;k++)
                              {
                                    ((*(p_image+(i*8+k)*row+j))>threshold) ? 
                                    (temp &= ~(1<<k)) : (temp |= 1<<k);
                              }
                              LCD_write_byte(temp,1);
                        }
            }
    }


/*=========================================================================
** 函数名：
          LCD_write_num
          
** 函数功能简介：
          显示一个十进制数

** 输入参数：
            X 开始书写的行号
            Y 开始书写的列好
            num 要显示的数据
          

** 返回参数：
           无

** 作   者：
           张盛平

** 编写日期：
            2013-9-17

** 修改历史：
            2013-9-17

** 添加日期：
            2013-9-17
===========================================================================*/

void LCD_write_num(u8 X, u8 Y, int num)
{
  u8 b[6], i;
  LCD_set_XY(X,Y);
  
  for(i = 0; i < 6; i++)
  {
    b[5-i] = (num % 10) + '0';
    num = num / 10;
  }
  
  for(i = 0; i < 6; i++)
  {
    LCD_write_char(b[i]);
  } 
}
