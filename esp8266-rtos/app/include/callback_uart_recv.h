
#ifndef __CALLBACK_UART_RECV_H__
#define __CALLBACK_UART_RECV_H__


#ifdef __cplusplus
extern "C" {
#endif


#include "uart.h"

#define Uart_Recv_Cache_Buff_Len 200  //串口数据转发处理的缓存大小


//发送到异步处理的 数据类型
typedef struct {
	unsigned char len ; //数据长度
	unsigned char * data ; //数据地址
}Recv_Data;






void Callback_Uart_Recv(UART_Callback_Event_arg interrupt_arg);






#ifdef __cplusplus
}
#endif

#endif
