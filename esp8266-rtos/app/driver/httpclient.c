#include "httpclient.h"
#include "esp_common.h"
#include "uart.h"

/******************************************************************************
*������Ϊ�༭��,����Ҫ�����Ƶ��뵽������༭!
*******************************************************************************/
/******************************************************************************/
at_recvTask() {} //�˺��������й�����ֻ�ܴ���һ�Σ��ɲ�������ط�
//httpЭ��ͻ�����ʼ
LOCAL struct espconn urlclient;
static ip_addr_t host_ip;
char host[128];
char urldata[1000];
char httphead[] = "%s /%s HTTP/1.1\r\n%s\r\nHost: %s\r\n\r\n";
/***͸��ģ���������******/



/***͸��ģ���������******/
void ICACHE_FLASH_ATTR
urlclient_recv(void *arg, char *pdata, unsigned short len)//���պ���
{
  struct espconn *pespconn = (struct espconn *)arg;
  pdata = strstr(pdata, "\n\r"); pdata += 3; //pdataΪ�����������������

  uart0_sendStr(pdata);


}

static void ICACHE_FLASH_ATTR
urlclient_discon_cb(void *arg)//�Ͽ��ص�
{
  struct espconn *pespconn = (struct espconn *)arg;

  uart0_sendStr("Unlink\r\n");

}

static void ICACHE_FLASH_ATTR
urlclient_sent_cb(void *arg)//���ͻص�
{
  struct espconn *pespconn = (struct espconn *)arg;
}



static void ICACHE_FLASH_ATTR
urlclient_connect_cb(void *arg) //���ӻص�
{
  struct espconn *pespconn = (struct espconn *)arg;
  os_printf("tcp urlclient connect\r\n");

  espconn_regist_disconcb(pespconn, urlclient_discon_cb);
  espconn_regist_recvcb(pespconn, urlclient_recv);
  espconn_regist_sentcb(pespconn, urlclient_sent_cb);
  espconn_sent(pespconn, urldata, strlen(urldata));
}

static void ICACHE_FLASH_ATTR
urlclient_recon_cb(void *arg, sint8 errType)//�����ص�,������ʧ�ܻص�
{
  uart0_sendStr("Fail\r\n");
  // espconn_connect(pespconn);
}


LOCAL void ICACHE_FLASH_ATTR
urlclient_dns_found(const char *name, ip_addr_t *ipaddr, void *arg)//������ ��������
{
  struct espconn *pespconn = (struct espconn *) arg;


  if (ipaddr == NULL)
  {
    os_printf("DNS Fail/r/n");

//    device_status = DEVICE_CONNECT_SERVER_FAIL;
    return;
  }

  os_printf("DNS found: %d.%d.%d.%d\n",
            *((uint8 *) &ipaddr->addr),
            *((uint8 *) &ipaddr->addr + 1),
            *((uint8 *) &ipaddr->addr + 2),
            *((uint8 *) &ipaddr->addr + 3));

  if (host_ip.addr == 0 && ipaddr->addr != 0)
  {
    if (pespconn->type == ESPCONN_TCP)
    {
      os_memcpy(pespconn->proto.tcp->remote_ip, &ipaddr->addr, 4);
      espconn_connect(pespconn);
    }
    else
    {
      os_memcpy(pespconn->proto.udp->remote_ip, &ipaddr->addr, 4);
      espconn_connect(pespconn);

    }
  }
}


LOCAL void ICACHE_FLASH_ATTR
urlclient_init() {
  uint32_t ip = 0;
  char ipTemp[128];
  os_sprintf(ipTemp, "%s", host);
  ip = ipaddr_addr(ipTemp);
  urlclient.type = ESPCONN_TCP;
  urlclient.proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
  urlclient.proto.tcp->local_port = espconn_port();
  urlclient.proto.tcp->remote_port = 80;
  os_memcpy(urlclient.proto.tcp->remote_ip, &ip, 4);
  espconn_regist_connectcb(&urlclient, urlclient_connect_cb); //���ӻص�
  espconn_regist_reconcb(&urlclient, urlclient_recon_cb);//�����ص������ӽ���ص�
  if ((ip == 0xffffffff) && (os_memcmp(ipTemp, "255.255.255.255", 16) != 0))
  {
    espconn_gethostbyname(&urlclient , ipTemp, &host_ip, urlclient_dns_found);//ͨ����������
  }
  else
  {
    espconn_connect(&urlclient);

  }

}

urlget(char *url, char *head) { //�����ֱ�Ϊ url ����Э��ͷ
  espconn_disconnect(&urlclient);
  memset(urldata, 0, sizeof(urldata));
  memset(host, 0, sizeof(host));
  int i = 0; url = strstr(url, "://");
  if (url) {
    url += 3;
    while (*url != 0 && *url != '/')
    { host[i] = *url;
      i++; url++;
    }
    host[i] = 0;
  } else return;
  if (url) {
    url++;
    os_sprintf(urldata, httphead, "GET", url, head, host);
  }
  urlclient_init();
}

urlpost(char *url, char *head, char *postdata) { //�����ֱ�Ϊ url ����Э��ͷ �ύ������
  espconn_disconnect(&urlclient);
  memset(urldata, 0, sizeof(urldata));
  memset(host, 0, sizeof(host));
  int i = 0; url = strstr(url, "://");
  if (url) {
    url += 3;
    while (*url != 0 && *url != '/')
    { host[i] = *url;
      i++; url++;
    }
    host[i] = 0;
  } else return;
  if (url) {
    url++;
    os_sprintf(urldata, httphead, "POST", url, head, host);
  }
  os_sprintf(urldata, "%s%s", urldata, postdata);
  urlclient_init();
}

//httpЭ��ͻ��˽�β
/******************************************************************************/


/******************************************************************************/
os_timer_t  cyctimer;
void ICACHE_FLASH_ATTR
//ʱ�����ڴ�����
cyctimer_exe(void)
{


  urlget("http://iot.espressif.cn/v1/ping", NULL); //��get������վhttp://iot.espressif.cn,/vi/ping����ȡ����



}
//ʱ�����ڴ�������β
void ICACHE_FLASH_ATTR
cyctimer_stop(void) //ֹͣʱ��
{
  os_timer_disarm (&cyctimer) ;
}

void ICACHE_FLASH_ATTR
cyctimer_star(void) //����ʱ��
{
  os_timer_setfn(&cyctimer, (os_timer_func_t *)cyctimer_exe, NULL);
  os_timer_arm(&cyctimer, 3000, 1);
}
/******************************************************************************/




/************************/ //ģ������·������ʼ,�ڵ���wifiģʽ��ʱ�����ò�����һ��Ҫ������wifiģʽǰ
conntwifi(void) { //ģ������·������������
  struct station_config stationConf;
  strcpy(stationConf.ssid, "jzzd");
  strcpy(stationConf.password, "53243690");
  ETS_UART_INTR_DISABLE();
  wifi_station_set_config(&stationConf);
  ETS_UART_INTR_ENABLE();
  wifi_station_connect();
}

/*******************************/ //ģ������·��������
/******************************************************************************
*�༭����β,������Ψһ���ӳ���,Ҳ�нӿڳ���,�벻Ҫ����λ��!
*******************************************************************************/
void ICACHE_FLASH_ATTR
httpclient_init(void)
{

  conntwifi();//����·����

  cyctimer_star();//ʱ��������ÿ3�����һ����վ

}
