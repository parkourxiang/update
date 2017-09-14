#include "esp_common.h"
#include "user_config.h"
#include "task_uart_parse_cmd.h"
#include "transmission.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "uart.h"
#include "callback_uart_recv.h"

struct transmission transmission_uart ;

extern xQueueHandle xQueueUart_recv_parse_cmd; //´«Êä¶ÓÁÐ



static void process_cmd(unsigned char * buff , unsigned char len)
{

    unsigned char cmd = buff[0];
    switch (cmd)
    {
    /**********************************/
    case cmd_up_system_restart:

        printf("\n-------system_restart--------\n");

        system_restart();

        break;


    /**********************************/
    case cmd_up_system_restore:

        printf("\n-------system_restore--------\n");

        system_restore();

        break;


    /**********************************/
    case cmd_up_smart_link_init:

        printf("\n-------smart_init--------\n");

        smartlink_init();

        break;




    /**********************************/
    case cmd_up_smart_link_start:


        printf("\n-------smart_start--------\n");
        smartlink_start();




        break;
    /**********************************/
    case cmd_up_smart_link_stop:


        printf("\n-------smart_stop--------\n");
        smartlink_stop();




        break;

    /**********************************/
    case cmd_up_udp_server:

        printf("\n-------udp server--------\n");

        //udp_server_softap_init("zigbee2017", "zigbee2017");

        break;




    case cmd_up_wendu_1:
    	if(len>1)
    	{

    	}

    	//printf("recv wendu :%d C\n",save_value_wendu_1);

       break;

    case cmd_up_shidu_1:

    	if(len>1)
    	{

    	}

    	//printf("recv wendu :%d C\n",save_value_shidu_1);

    	break;


    case cmd_up_end_1:

                  //  printf("\n-------udp server--------\n");

                    //udp_server_softap_init("zigbee2017", "zigbee2017");

                    break;



//            case cmd_up_udp_server_change:
//
//              if(len>12 && len <28)
//              {
//                  unsigned char ssid[15];
//                  unsigned char passwd[15];
//                  unsigned char * idx = buff+1;
//
//                  unsigned char * start = idx ;
//
//
//                  memset(ssid,'\0',15);
//                  memset(passwd,'\0',15);
//
//                  while(*idx != '\0')
//                  {
//                      idx++;
//                  }
//
//                  strcpy(ssid,start);
//
//                  while(*idx=='\0')
//                  {
//                      idx++;
//                  }
//
//                  start = idx ;
//
//                  while(*idx != '\0')
//                  {
//                      idx++;
//                      passwd_len++;
//                  }
//
//                  strcpy(passwd,start);
//
//
//                  udp_server_softap_init(ssid,passwd);
//
//
//              }
//
//              break ;






    }

}


static void init_transmission_uart(void)
{

   transmission_uart.device_send_buff = Uart_User_send_buff ;
   transmission_uart.user_recv_buff = process_cmd ;

}





void
Tasck_Uart_recv_parse_cmd(void *pvParameters)
{
    Recv_Data recv_data ;

	init_transmission_uart();


    for (;;) {
        if (xQueueReceive(
                    xQueueUart_recv_parse_cmd,
                    (void *)&recv_data,
                    (portTickType)portMAX_DELAY )
           )
        {

			transmit_recv_unpack_buff(&transmission_uart,recv_data.data,recv_data.len);

        }
    }
    vTaskDelete(NULL);
}


