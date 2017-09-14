#include "esp_common.h"

#include "udp_server.h"

struct espconn udp_server_connection;
esp_udp udp_server_connection_udp;

static int  remote_port ;


void udp_server_softap_init(char * ssid, char * passwd) {
    struct softap_config config;

    wifi_set_opmode(SOFTAP_MODE);

    memset(config.ssid, 0, 32);
    memset(config.password, 0, 64);
    memcpy(config.ssid, ssid, strlen(ssid));
    memcpy(config.password, passwd, strlen(passwd));
    config.ssid_len = 0;
    config.max_connection = 10;
    config.authmode = AUTH_WPA_WPA2_PSK;

    wifi_softap_set_config( & config);



}


void udp_server_connection_init(int port , espconn_recv_callback recv_cb) {


    remote_port = port;

    udp_server_connection.type = ESPCONN_UDP;
    udp_server_connection.proto.udp = & udp_server_connection_udp;

    udp_server_connection.proto.udp->local_port = port;
    udp_server_connection.proto.udp->remote_port = port;

    udp_server_connection.proto.udp->local_ip[0] = 192;
    udp_server_connection.proto.udp->local_ip[1] = 168;
    udp_server_connection.proto.udp->local_ip[3] = 4;
    udp_server_connection.proto.udp->local_ip[4] = 1;

    udp_server_connection.proto.udp->remote_ip[0] = 255;
    udp_server_connection.proto.udp->remote_ip[1] = 255;
    udp_server_connection.proto.udp->remote_ip[2] = 255;
    udp_server_connection.proto.udp->remote_ip[3] = 255;

    espconn_regist_recvcb( & udp_server_connection, recv_cb);
    espconn_create( & udp_server_connection);

}


void udp_server_send_data(uint8 *psent, uint16 length)
{

//  do{
//          udp_server_connection.proto.udp->remote_port = remote_port;
//          udp_server_connection.proto.udp->remote_ip[0] = 192;
//          udp_server_connection.proto.udp->remote_ip[1] = 168;
//          udp_server_connection.proto.udp->remote_ip[2] = 4;
//          udp_server_connection.proto.udp->remote_ip[3] = 2;
//
//  }
//  while(espconn_sendto(&udp_server_connection, psent, length));



    udp_server_connection.proto.udp->remote_port = remote_port;
    udp_server_connection.proto.udp->remote_ip[0] = 192;
    udp_server_connection.proto.udp->remote_ip[1] = 168;
    udp_server_connection.proto.udp->remote_ip[2] = 4;
    udp_server_connection.proto.udp->remote_ip[3] = 2;
    espconn_sendto(&udp_server_connection, psent, length);



    udp_server_connection.proto.udp->remote_port = remote_port;
    udp_server_connection.proto.udp->remote_ip[0] = 192;
    udp_server_connection.proto.udp->remote_ip[1] = 168;
    udp_server_connection.proto.udp->remote_ip[2] = 4;
    udp_server_connection.proto.udp->remote_ip[3] = 3;


    espconn_sendto(&udp_server_connection, psent, length);


    udp_server_connection.proto.udp->remote_port = remote_port;
        udp_server_connection.proto.udp->remote_ip[0] = 192;
        udp_server_connection.proto.udp->remote_ip[1] = 168;
        udp_server_connection.proto.udp->remote_ip[2] = 4;
        udp_server_connection.proto.udp->remote_ip[3] = 4;


        espconn_sendto(&udp_server_connection, psent, length);
}


