#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#include "espconn.h"

//extern struct espconn udp_server_connection;
//extern esp_udp udp_server_connection_udp;


void udp_server_softap_init(char * ssid, char * passwd);


void udp_server_connection_init(int port , espconn_recv_callback recv_cb);


void udp_server_send_data(uint8 *psent, uint16 length);

#endif
