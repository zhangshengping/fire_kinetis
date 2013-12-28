/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：isr.h
 * 描述         ：重新宏定义中断号，重映射中断向量表里的中断函数地址，
 *                使其指向我们所定义的中断服务函数。声明中断服务函数
 *                警告：只能在"vectors.c"包含，而且必须在"vectors.h"包含的后面！！！
 *          
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室 
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008   
**********************************************************************************/

/*
#define VECTOR_103      default_isr     // 0x0000_019C 103   87     Port control module Pin Detect (Port A)
#define VECTOR_104      default_isr     // 0x0000_01A0 104   88     Port control module Pin Detect (Port B)
#define VECTOR_105      default_isr     // 0x0000_01A4 105   89     Port control module Pin Detect (Port C)
#define VECTOR_106      default_isr     // 0x0000_01A8 106   90     Port control module Pin Detect (Port D)
#define VECTOR_107      default_isr     // 0x0000_01AC 107   91     Port control module Pin Detect (Port E)
*/



#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"  

/*                          重新定义中断向量表
 *  先取消默认的中断向量元素宏定义       #undef  VECTOR_xxx
 *  在重新定义到自己编写的中断函数       #define VECTOR_xxx    xxx_IRQHandler
 *  例如：
 *       #undef  VECTOR_003
 *       #define VECTOR_003    HardFault_Handler    重新定义硬件上访中断服务函数
 */

#undef  VECTOR_103                        //取消中断号的定义
#define VECTOR_103    PORTA_IRQHandler    //PORTA中断
extern void PORTA_IRQHandler();           //PORTA中断服务函数


#undef  VECTOR_106
#define VECTOR_106    PORTD_IRQHandler
extern  void PORTD_IRQHandler();

#undef  VECTOR_107
#define VECTOR_107    PORTE_IRQHandler
extern  void PORTE_IRQHandler();


#endif  //__ISR_H

/* End of "isr.h" */
