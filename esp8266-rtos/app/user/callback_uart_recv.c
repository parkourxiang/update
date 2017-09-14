#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "uart.h"

#include "callback_uart_recv.h"



/*************parce buff*******************/


// //����ת�����첽����Ļ���
static unsigned char Uart_Recv_Cache_Buff[Uart_Recv_Cache_Buff_Len];  //������

//��ǰ���Ͷ���ָ������
static unsigned char  process_loop_point = 0;

extern xQueueHandle xQueueUart_recv_parse_cmd; //�������


//Ӳ�����ڽ��ջص�����
void Callback_Uart_Recv(UART_Callback_Event_arg interrupt_arg)
{
    unsigned char fifo_len = Uart_User_read_len();
    Recv_Data send_data ;

    portBASE_TYPE xHigherPriorityTaskWoken;


    /****************�û�������********************/

    if (fifo_len > Uart_Recv_Cache_Buff_Len)
    {
        fifo_len = Uart_Recv_Cache_Buff_Len ;
        //os_printf("warning : too small uart_recv buffer\n");
    }

    if (process_loop_point + fifo_len >= Uart_Recv_Cache_Buff_Len)
    {
        process_loop_point = 0;
    }

    Uart_User_read_buff(&Uart_Recv_Cache_Buff[process_loop_point], fifo_len);

    send_data.len = fifo_len;
    send_data.data = &Uart_Recv_Cache_Buff[process_loop_point];

    process_loop_point += fifo_len ;



//    //ת�����ݵĴ������
//    xQueueSendFromISR(xQueueUart_recv_transport,
//                      (void *)&send_data,
//                      &xHigherPriorityTaskWoken);
//    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);


    //�������ݵĴ������
    xQueueSendFromISR(xQueueUart_recv_parse_cmd,
                      (void *)&send_data,
                      &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);


}




