#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#define PACK_DATA_HEAD   0xFF
#define PACK_DATA_TAIL   0xFE
#define PACK_DATA_MASK   0x55

#define TRANSMISSION_CACHE_LEN  50


struct transmission
{
	void(*device_send_buff)(unsigned char * buff, unsigned char len);
	void(*device_send_byte)(unsigned char byte);
	void(*user_recv_buff)(unsigned char * buff, unsigned char len);
	unsigned char pack_recv_cache_buff[TRANSMISSION_CACHE_LEN]; 
	int pack_recv_pointer;
	unsigned char pack_recv_last_data;
	unsigned char flag_recv_star;
	unsigned char flag_recv_end;
};


void transmit_send_pack_buff(struct transmission *trans,const unsigned char * buff, unsigned char len);
void transmit_send_pack_byte(struct transmission* trans,const unsigned char byte);
void transmit_recv_unpack_buff(struct transmission *trans,const unsigned char * buff, unsigned char len);
void transmit_recv_unpack_byte(struct transmission *trans,const unsigned char byte);



#endif






