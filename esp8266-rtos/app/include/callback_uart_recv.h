
#ifndef __CALLBACK_UART_RECV_H__
#define __CALLBACK_UART_RECV_H__


#ifdef __cplusplus
extern "C" {
#endif


#include "uart.h"

#define Uart_Recv_Cache_Buff_Len 200  //��������ת������Ļ����С


//���͵��첽����� ��������
typedef struct {
	unsigned char len ; //���ݳ���
	unsigned char * data ; //���ݵ�ַ
}Recv_Data;






void Callback_Uart_Recv(UART_Callback_Event_arg interrupt_arg);






#ifdef __cplusplus
}
#endif

#endif
