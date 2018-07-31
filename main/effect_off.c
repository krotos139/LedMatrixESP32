#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <time.h>

#include "led_tasks.h"

void effect_off_start() {
	vTaskDelay(200/portTICK_PERIOD_MS);
	led_clear();
	led_show();
}

void effect_off_process() {
	vTaskDelay(100/portTICK_PERIOD_MS);
}

void effect_off_end() {
	led_clear();
	led_show();
}
