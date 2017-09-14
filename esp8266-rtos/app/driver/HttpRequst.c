/******************************************************************************
 * Copyright 2013-2014 
 *
 * FileName:HttpRequst.c
 *
 * Description: 
 *
 * Modification history:
 *     2014/12/1, v1.0 create this file.
*******************************************************************************/
#include "esp_common.h"

#include "espressif/esp8266/ets_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/lwip/Netdb.h"
#include <unistd.h>

#include "HttpRequst.h"

/**
  * @brief  http����
  * @param  method 0:GET,1:POST��Url:����http����:www.baidu.com/index.html��
	body:�������ݣ�ʡ��ʱΪNULL��bodylen:body���ֽ�����buff:���յ�ʵ�����ݣ�bufflen:buff��С��
  * @retval true:����ɹ���false:����ʧ�ܡ�
  * @note http�汾Ϊ1.0��ֻ�ܽ��յ���󳤶�Ϊ1024�ֽڡ�
  */
bool HttpRequst( uint8_t method , char * Url , char * body , uint16_t bodylen , uint8_t *buff , uint16_t bufflen )
{
	struct  hostent hostinfo,*phost;
	char buf[101];
	char hostname[100];
	char *ipaddr = NULL;
	char *ptr , *path;
	int ret;

	if( Url == NULL )
	{
		//printf("error:have no url!\r\n");
		return false;
	}
	ptr = strchr( Url , '/' );
	if( ptr == NULL )
	{
		//printf("error:url parse!\r\n");
		return false;
	}
	path = ptr + 1;
	
	memcpy( hostname , Url , ptr - Url );
	hostname[ ptr - Url ] = 0x00;

//	printf("Host:%s\r\n" , hostname );
	if( gethostbyname_r( hostname , &hostinfo , buf , 100 , &phost , &ret ) )
	{
		//printf( "error:gethostbyname\r\n" );
		return false;
	}
	else
	{
		int i;

		for( i = 0; hostinfo.h_addr_list[i]; i++ )
		{
			ipaddr = inet_ntoa( *(struct in_addr*)hostinfo.h_addr_list[i] );
			if( ipaddr != NULL )
			{
//				printf("host addr is:%s\n",  ipaddr );
				break;
			}
		}

		if( ipaddr == NULL )
		{
			//printf("error:get ip fail!\r\n");
			return false;
		}
	}

	int32 sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	int32 nNetTimeout = 800;                           										 //���ճ�ʱʱ��Ϊ800ms.
	char * data_buf;
	
	sockfd = socket( PF_INET, SOCK_STREAM, 0 );
	if( sockfd == -1 )
	{
		//printf("client socket fail!\r\n");
		return false;
	}
	else
	{
		//printf("---------CliSock:%d!\r\n------" , sockfd );
 	}

	memset( &address , 0 , sizeof( address ) );
	
	 address.sin_family = AF_INET;
	 address.sin_addr.s_addr = inet_addr( ipaddr );
	 address.sin_port = htons(80);
	 address.sin_len = sizeof(address);
	 len = sizeof(address);
	 
	 result = connect( sockfd, (struct sockaddr *)&address, len );

	 ret = false;
	 if (result != -1 )
	 {
		data_buf = (char *)malloc( 300 * sizeof(char) );
		
		if( data_buf == NULL )
		{
			close( sockfd );
			//printf("client buf get fail!\r\n");
			return false;
		}
		
		 setsockopt( sockfd ,SOL_SOCKET , SO_RCVTIMEO ,(char*)&nNetTimeout, sizeof(int) );

		 if( method == GET )
		 {
			sprintf( data_buf , "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n" , path , hostname );
			write( sockfd ,  data_buf , strlen( data_buf ) );
		 }
		 else if( method == POST )
		 {
			sprintf( data_buf , "POST /%s HTTP/1.0\r\nHost: %s\r\nConnction: keep-alive\r\nContent-Length: %d\r\n" , path , hostname , bodylen );
			if( bodylen > 0 )
			{ 
				strcat( data_buf, "Cache-Control: no-cache\r\n" );
				strcat( data_buf, "Content-type: text/html\r\n" );
				strcat( data_buf, "\r\n" );
				
				send( sockfd ,  data_buf , strlen( data_buf ) , MSG_WAITALL );
			}
			
			write( sockfd ,  body ,  bodylen );
		 }
		 int ReadLen;
		 int i = 0;
		 
		do
		{
			if( i > 0 )
			{
				//printf("try again!\r\n");
				vTaskDelay( 50 / portTICK_RATE_MS );
			}
			ReadLen = read( sockfd , data_buf , 299 );
		}while( ( ReadLen < 0 ) && ( errno == EAGAIN ) && ( ( ++i ) < 10 ) );
		 

		 if( ReadLen > 0 )
		 {
			uint16_t status = 0 ;
		
			ptr = strchr( data_buf , ' ' );
			if( ptr != NULL )
			{
				status = atoi( ptr + 1 );
		//		printf("http response status:%d\r\n" , status );

				if( status == 200 )
				{
					ret = true;
					ptr = strstr( data_buf , "\r\n\r\n" );

		//			printf("Body:%s\r\n" , ptr + 4 );
					if( buff != NULL )
					{
						unsigned int len;
						
						len = strlen( ptr + 4 );

						len = len > bufflen ? bufflen : len;

						memcpy( buff , ptr + 4 , len );
						buff[len] = 0x00;
					}
				}
				else
				{
					//printf("response status code error,data:%s!\r\n" , data_buf );
				}

			}
			else
			{    
				//printf("response data len:%d!\r\n" , ReadLen );
			}
		}
		else if( ReadLen < 0 )
		{
			//printf("errno:%d!\r\n" , errno );
		}
		else
		{
			//printf("socket already disconnect!\r\n");
		}

		close( sockfd );

		free( data_buf );
	 }
	 else
	 {
	 	close( sockfd );
		//printf("client cannot connect server!\r\n");
	 }
	
	return ret;

}


