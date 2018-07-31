#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <time.h>

#include "led_tasks.h"

static const char *TAG = "CONTROL";

int scene = -1;
int new_scene = 0;
	
void switchScene(int scene) {
	new_scene = scene;
}

void control_task() {
	
	/* scenes:
	0: test
	1: artnet
	2: light
	*/
	

	while (true) {
		if (scene != new_scene) {
			ESP_LOGI(TAG, "Switch to scene %d", new_scene);
			switch (scene) {
				case 0: effect_test_end();
					break;
				case 1: artnet_end();
					break;
			}
			scene = new_scene;
			switch (scene) {
				case 0: effect_test_start();
					break;
				case 1: artnet_start();
					break;
			}
		}
		switch (scene) {
			case 0: effect_test_process();
				break;
			case 1: artnet_process();
				break;
		}
	}
}