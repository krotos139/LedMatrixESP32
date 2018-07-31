#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "led_tasks.h"


#define ART_DMX_START 18
int udp_server;
char buf[600];
int artnetFramesCount = 0;

static const char *TAG = "ARTNET";

uint8_t ArtNetBegin(){
  //stop();
  uint16_t port = 6454;

  uint16_t server_port = port;
  

  if ((udp_server=socket(AF_INET, SOCK_DGRAM, 0)) == -1){
    ESP_LOGE(TAG, "could not create socket: %d", errno);
    return 0;
  }

  int yes = 1;
  if (setsockopt(udp_server,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
      ESP_LOGE(TAG, "could not set socket option: %d", errno);
      //stop();
      return 0;
  }

  struct sockaddr_in addr;
  memset((char *) &addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(server_port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(udp_server , (struct sockaddr*)&addr, sizeof(addr)) == -1){
    ESP_LOGE(TAG, "could not bind socket: %d", errno);
    return 0;
  }
  fcntl(udp_server, F_SETFL, O_NONBLOCK);
  return 1;
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
	artnetFramesCount++;
	if (universe == 0) {
		led_show();
	}
	int gx=universe & 0x0F;
	int gy=(universe >> 4) & 0x0F;
	int data_index = 0;
	gx = gx*8;
	gy = gy*8;
	for (int y=0 ; y<8 ; y++) {
		for (int x=0 ; x<8 ; x++) {
			led_set_pixel_rgb(x+gx, y+gy, data[data_index], data[data_index+1], data[data_index+2]);
			data_index += 3;
		}
	}
}

int ArtNetParsePacket(){
  struct sockaddr_in si_other;
  int slen = sizeof(si_other) , len;
  
  if ((len = recvfrom(udp_server, buf, 600, MSG_DONTWAIT, (struct sockaddr *) &si_other, (socklen_t *)&slen)) == -1){
    //delete[] buf;
    if(errno == EWOULDBLOCK){
      return 0;
    }
    ESP_LOGE(TAG,"could not receive data: %d", errno);
    return 0;
  }
  
  onDmxFrame(
    buf[14] | buf[15] << 8, 
    buf[17] | buf[16] << 8, 
    buf[12], 
    (uint8_t*)(buf + ART_DMX_START));

  //delete[] buf;
  return len;
}

static void artnet_receive(void *pvParameters) {
	ArtNetParsePacket();
}

void artnet_task() {
	
	ArtNetBegin();
	ArtNetParsePacket();
	
	uint32_t clock_millis = (uint32_t) (clock() * 1000 / CLOCKS_PER_SEC) + 1000;
    while (true) {
		while (true) {
			if (ArtNetParsePacket() == 0)  break;
		}
		if (clock_millis < (uint32_t) (clock() * 1000 / CLOCKS_PER_SEC)) {
			if (artnetFramesCount>0) {
				switchScene(1);
			}
			ESP_LOGI(TAG, "artnetFramesCount=%d", artnetFramesCount);
			// printf("ARTNET DATA:\n");
			// struct led_color_t color;
			// for (int y = 0 ; y<24 ; y++) {
				// for (int x = 0 ; x<16 ; x++) {
					// led_get_pixel_color(x, y, &color);
					// printf("%3d,%3d,%3d | ", color.red, color.green, color.blue);
				// }
				// printf("\n");
			// }
			artnetFramesCount = 0;
			clock_millis += 1000;
		}
		//printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1);
    }
}

void artnet_start() {
	
}
void artnet_process() {
	
}
void artnet_end() {
	
}