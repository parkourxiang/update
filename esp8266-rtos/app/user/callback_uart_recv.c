#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "uart.h"

#include "callback_uart_recv.h"



/*************parce buff*******************/


// //数据转发到异步处理的缓存
static unsigned char Uart_Recv_Cache_Buff[Uart_Recv_Cache_Buff_Len];  //缓冲区

//当前发送队列指针序列
static unsigned char  process_loop_point = 0;

extern xQueueHandle xQueueUart_recv_parse_cmd; //传输队列


//硬件串口接收回掉函数
void Callback_Uart_Recv(UART_Callback_Event_arg interrupt_arg)
{
    unsigned char fifo_len = Uart_User_read_len();
    Recv_Data send_data ;

    portBASE_TYPE xHigherPriorityTaskWoken;


    /****************用户处理区********************/

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



//    //转发数据的传输队列
//    xQueueSendFromISR(xQueueUart_recv_transport,
//                      (void *)&send_data,
//                      &xHigherPriorityTaskWoken);
//    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);


    //解析数据的传输队列
    xQueueSendFromISR(xQueueUart_recv_parse_cmd,
                      (void *)&send_data,
                      &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);


}




