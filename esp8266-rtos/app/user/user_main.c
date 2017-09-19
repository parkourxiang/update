/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_common.h"
#include "callback_uart_recv.h"
#include "HttpRequst.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "task_uart_parse_cmd.h"
#include "callback_uart_recv.h"

#include "user_config.h"




xTaskHandle xHandle_http;

xQueueHandle xQueueUart_recv_transport; //传输队列

xQueueHandle xQueueUart_recv_parse_cmd; //传输队列


unsigned char save_value_wendu_1 = 25 ;
unsigned char save_value_shidu_1 = 25 ;

char * requst_url = "laomao.sc2yun.com/laomao/iot/server_mcu/0002/server_mcu.php";


/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
    case FLASH_SIZE_4M_MAP_256_256:
        rf_cal_sec = 128 - 5;
        break;

    case FLASH_SIZE_8M_MAP_512_512:
        rf_cal_sec = 256 - 5;
        break;

    case FLASH_SIZE_16M_MAP_512_512:
    case FLASH_SIZE_16M_MAP_1024_1024:
        rf_cal_sec = 512 - 5;
        break;

    case FLASH_SIZE_32M_MAP_512_512:


    case FLASH_SIZE_32M_MAP_1024_1024:
        rf_cal_sec = 1024 - 5;
        break;

    default:
        rf_cal_sec = 0;
        break;
    }

    return rf_cal_sec;
}




//http传输
void Tasck_HTTP_Requst(void *pvParameters)
{

    unsigned char request_recv_buff[100] ;
    unsigned char request_send_buff[100] ;


    uint16_t request_send_len = 0 ;
    unsigned int  request_recv_len = 0 ;

    unsigned char flag_request = 0 ;





    uint8 status;
    vTaskDelay( 1000 / portTICK_RATE_MS );

    do
    {
        status = wifi_station_get_connect_status( );

        vTaskDelay( 5000 / portTICK_RATE_MS );

        printf("\n not in got ip ,still scan ... \n");
    }
    while ( status != STATION_GOT_IP );


    while (1)
    {

    	request_send_len = sprintf(request_send_buff,"%s?wendu=%d&shidu=%d",requst_url,save_value_wendu_1,save_value_shidu_1);
    	request_send_buff[request_send_len] = '\0' ;
    	request_send_buff[request_send_len+1] = '\0' ;

    	//printf("\n%s\n",request_send_buff);

        flag_request = HttpRequst( 0 , request_send_buff , NULL , 0 , request_recv_buff , 100);

        if (flag_request)
        {
//        	printf("\n---------------------\n");
//            Uart_User_send_buff(request_recv_buff , 50);
//            printf("\n---------------------\n");

            if(strstr(request_recv_buff,"[control]")!=NULL && strstr(request_recv_buff,"[/control]")!=NULL)
            {
            	int led_value = atoi(strstr(request_recv_buff,"[control]")+strlen("[control]"));


            	if(led_value>0)
            	{
            		//send_data_to_mcu(cmd_down_light_led_1,1);
            	}
            	else
            	{
            		//send_data_to_mcu(cmd_down_light_led_1,0);
            	}
            }
        }
        else
        {
          //  printf("\nrequest fail .. \n");
        }

        memset(request_recv_buff,'\0',100);

        vTaskDelay( 1000 / portTICK_RATE_MS );

    }

}



/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/



void user_init(void)
{
   //初始化并开启串口
   Init_Uart_User(9600, Callback_Uart_Recv);

//    printf("SDK version:%s\n", system_get_sdk_version());

    printf("\n os start! ---||||--- start working\n");

    //创建数据解析队列
    xQueueUart_recv_parse_cmd = xQueueCreate(20, sizeof(Recv_Data));

    //开启串口数据解析任务
    //任务说明：（该任务将对串口接收到的数据 进行解析，得到控制指令）
    xTaskCreate(Tasck_Uart_recv_parse_cmd, (uint8 const *)"Task_pase_cmd", 512, NULL, tskIDLE_PRIORITY + 4, NULL);
    printf("\n uart parse_cmd task created! \n");

    //开启数据透传任务
    //任务说明：（该任务用于将串口接收到的数据 通过 UDP 以广播的形式发送出去）
    xTaskCreate(Tasck_HTTP_Requst, (uint8 const *)"Task_http_request", 512, NULL, tskIDLE_PRIORITY + 3, &xHandle_http);
    printf("\n http request task created! \n");




}

