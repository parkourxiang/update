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

#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

//指令码解析


//zigbee指令

/*********************终端节点1 指令码*******************/
#define cmd_up_wendu_1			01
#define cmd_up_shidu_1 			02
#define cmd_up_guangmin_1 		03
#define cmd_up_turangshidu_1	04
#define cmd_up_ds18b20_1		05
#define cmd_up_renti_1			06
#define cmd_up_heart_1			07
#define cmd_up_do1_1			08
#define cmd_up_do2_1			09
#define cmd_up_flow_abs_1		10
#define cmd_up_flow_all_1		11
#define cmd_up_mq_1				12

#define cmd_up_end_1 			19

#define cmd_down_light_led_1 			20
#define cmd_down_fengmingqi_1  			21
#define cmd_down_jidianqi1_1 			22
#define cmd_down_jidianqi2_1 			23
#define cmd_down_light_color_red_1		24
#define cmd_down_light_color_blue_1		25
#define cmd_down_light_color_green_1	26
#define cmd_down_light_color_all_1		27


#define  cmd_down_zidongtiaojie_wendu_heigh_1 		30
#define  cmd_down_zidongtiaojie_wendu_low_1 		31
#define  cmd_down_zidongtiaojie_shidu_heigh_1 		32
#define  cmd_down_zidongtiaojie_shidu_low_1  		33
#define  cmd_down_zidongtiaojie_guangmin_heigh_1 	34
#define  cmd_down_zidongtiaojie_guangmin_low_1 		35
#define  cmd_down_zidongtiaojie_turang_heigh_1 		36
#define  cmd_down_zidongtiaojie_turang_low_1  		37
#define  cmd_down_zidongtiaojie_qiti_heigh_1  		38
#define  cmd_down_zidongtiaojie_qiti_low_1  		39
#define cmd_down_zidongtiaojie_all_open_1  			40
#define cmd_down_zidongtiaojie_all_close_1  		41





/*********************终端节点2 指令码*******************/
#define cmd_up_wendu_2			51
#define cmd_up_shidu_2 			52
#define cmd_up_guangmin_2 		53
#define cmd_up_turangshidu_2	54
#define cmd_up_ds18b20_2		55
#define cmd_up_renti_2			56
#define cmd_up_heart_2			57
#define cmd_up_do1_2			58
#define cmd_up_do2_2			59
#define cmd_up_flow_abs_2		60
#define cmd_up_flow_all_2		61
#define cmd_up_mq_2				62

#define cmd_up_end_2 			69

#define cmd_down_light_led_2 			70
#define cmd_down_fengmingqi_2  			71
#define cmd_down_jidianqi1_2 			72
#define cmd_down_jidianqi2_2 			73
#define cmd_down_light_color_red_2		74
#define cmd_down_light_color_blue_2		75
#define cmd_down_light_color_green_2	76
#define cmd_down_light_color_all_2		77


#define  cmd_down_zidongtiaojie_wendu_heigh_2 		80
#define  cmd_down_zidongtiaojie_wendu_low_2 		81
#define  cmd_down_zidongtiaojie_shidu_heigh_2 		82
#define  cmd_down_zidongtiaojie_shidu_low_2  		83
#define  cmd_down_zidongtiaojie_guangmin_heigh_2 	84
#define  cmd_down_zidongtiaojie_guangmin_low_2 		85
#define  cmd_down_zidongtiaojie_turang_heigh_2 		86
#define  cmd_down_zidongtiaojie_turang_low_2  		87
#define  cmd_down_zidongtiaojie_qiti_heigh_2  		88
#define  cmd_down_zidongtiaojie_qiti_low_2  		89
#define cmd_down_zidongtiaojie_all_open_2  			90
#define cmd_down_zidongtiaojie_all_close_2  		91




/*********************终端节点3 指令码*******************/
#define cmd_up_wendu_3			101
#define cmd_up_shidu_3 			102
#define cmd_up_guangmin_3 		103
#define cmd_up_turangshidu_3	104
#define cmd_up_ds18b20_3		105
#define cmd_up_renti_3			106
#define cmd_up_heart_3			107
#define cmd_up_do1_3			108
#define cmd_up_do2_3			109
#define cmd_up_flow_abs_3		110
#define cmd_up_flow_all_3		111
#define cmd_up_mq_3				112

#define cmd_up_end_3 			119

#define cmd_down_light_led_3 			120
#define cmd_down_fengmingqi_3  			121
#define cmd_down_jidianqi1_3 			122
#define cmd_down_jidianqi2_3 			123
#define cmd_down_light_color_red_3		124
#define cmd_down_light_color_blue_3		125
#define cmd_down_light_color_green_3	126
#define cmd_down_light_color_all_3		127


#define  cmd_down_zidongtiaojie_wendu_heigh_3 		130
#define  cmd_down_zidongtiaojie_wendu_low_3 		131
#define  cmd_down_zidongtiaojie_shidu_heigh_3 		132
#define  cmd_down_zidongtiaojie_shidu_low_3  		133
#define  cmd_down_zidongtiaojie_guangmin_heigh_3 	134
#define  cmd_down_zidongtiaojie_guangmin_low_3 		135
#define  cmd_down_zidongtiaojie_turang_heigh_3 		136
#define  cmd_down_zidongtiaojie_turang_low_3  		137
#define  cmd_down_zidongtiaojie_qiti_heigh_3  		138
#define  cmd_down_zidongtiaojie_qiti_low_3  		139
#define cmd_down_zidongtiaojie_all_open_3  			140
#define cmd_down_zidongtiaojie_all_close_3  		141





//系统指令
#define cmd_up_system_restore 241
#define cmd_up_system_restart 242
#define cmd_up_smart_link_init 243
#define cmd_up_smart_link_start 244
#define cmd_up_smart_link_stop 245
#define cmd_up_udp_server 246
#define cmd_up_udp_server_change 247




#endif

