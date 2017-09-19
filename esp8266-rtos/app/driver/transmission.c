#include "transmission.h"




static unsigned char check_sum(const unsigned char * buff, unsigned char len)
{
	unsigned int num = 0;
	while (len--)
	{
		num += *(buff++);
	}
	return (num % 256);
}

void transmit_send_pack_buff(struct transmission *trans ,const unsigned char * buff, unsigned char len)
{
	unsigned char cache[TRANSMISSION_CACHE_LEN] = { PACK_DATA_HEAD, PACK_DATA_HEAD };
	unsigned char idx = 2;
	unsigned char checkSum = check_sum(buff, len);

	while (len--)
	{
		cache[idx++] = *buff;

		if (*buff == PACK_DATA_HEAD || *buff == PACK_DATA_TAIL)
		{
			cache[idx++] = PACK_DATA_MASK;
		}

		buff++;
	}

	cache[idx++] = checkSum;
	cache[idx++] = PACK_DATA_TAIL;
	cache[idx++] = PACK_DATA_TAIL;

	if (trans->device_send_buff != 0)
	{
		trans->device_send_buff(cache, idx);
	}
	else
	{
		while (len < idx)
		{
			trans->device_send_byte(cache[len++]);
		}
	}

}


void transmit_send_pack_byte(struct transmission* trans ,const unsigned char byte)
{
	unsigned char buff[1] = { byte };
	transmit_send_pack_buff(trans ,buff, 1);
}


void transmit_recv_unpack_buff( struct transmission *trans ,const unsigned char * buff, unsigned char len)
{
	while (len--)
	{
		if (*buff == PACK_DATA_HEAD && trans->pack_recv_last_data == PACK_DATA_HEAD)
		{
			trans->flag_recv_star = 1;
			trans->pack_recv_pointer = 0;
			trans->flag_recv_end = 0;
		}
		else if (*buff == PACK_DATA_MASK && (trans->pack_recv_last_data == PACK_DATA_HEAD || trans->pack_recv_last_data == PACK_DATA_TAIL) && trans->pack_recv_pointer > 0)
		{
			//do nothing
		}
		else if (*buff == PACK_DATA_TAIL && trans->pack_recv_last_data == PACK_DATA_TAIL)
		{
			if (trans->flag_recv_star)
			{
				if (trans->pack_recv_pointer > 2)
				{
					if (trans->pack_recv_cache_buff[trans->pack_recv_pointer - 2] == check_sum(trans->pack_recv_cache_buff, trans->pack_recv_pointer - 2))
					{
						//receive success
						trans->user_recv_buff(trans->pack_recv_cache_buff, trans->pack_recv_pointer - 2);
					}
				}

			}
			trans->flag_recv_star = 0;
			trans->pack_recv_pointer = 0;
		}
		else
		{
			if (trans->flag_recv_star)
			{
				if(trans->pack_recv_pointer<TRANSMISSION_CACHE_LEN)
				trans->pack_recv_cache_buff[trans->pack_recv_pointer++] = *buff;
			}
		}

		trans->pack_recv_last_data = *buff;
		buff++;
	}
}



void transmit_recv_unpack_byte(struct transmission *trans ,const unsigned char byte)
{

	if (byte == PACK_DATA_HEAD && trans->pack_recv_last_data == PACK_DATA_HEAD)
	{
		trans->flag_recv_star = 1;
		trans->pack_recv_pointer = 0;
		trans->flag_recv_end = 0;
	}
	else if (byte == PACK_DATA_MASK && (trans->pack_recv_last_data == PACK_DATA_HEAD || trans->pack_recv_last_data == PACK_DATA_TAIL) && trans->pack_recv_pointer > 0)
	{
		//do nothing
	}
	else if (byte == PACK_DATA_TAIL && trans->pack_recv_last_data == PACK_DATA_TAIL)
	{
		if (trans->flag_recv_star)
		{
			if (trans->pack_recv_pointer > 2)
			{
				if (trans->pack_recv_cache_buff[trans->pack_recv_pointer - 2] == check_sum(trans->pack_recv_cache_buff, trans->pack_recv_pointer - 2))
				{
					//receive success
					trans->user_recv_buff(trans->pack_recv_cache_buff, trans->pack_recv_pointer - 2);
				}
			}
		}
		trans->flag_recv_star = 0;
		trans->pack_recv_pointer = 0;
	}
	else
	{
		if (trans->flag_recv_star)
		{
			trans->pack_recv_cache_buff[trans->pack_recv_pointer++] = byte;
		}
	}
	trans->pack_recv_last_data = byte;
}


