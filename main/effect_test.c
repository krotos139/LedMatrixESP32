#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <time.h>

#include "led_tasks.h"



void effect_test_start() {
	led_clear();
	led_show();
}

void effect_test_process() {
	struct led_color_t led_color = {
        .red = 0,
        .green = 0,
        .blue = 0,
    };
	
	struct led_color_t* ledbuf;
	
	led_color.red = 255;
	led_color.green = 0;
	led_color.blue = 0;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 255;
	led_color.green = 255;
	led_color.blue = 0;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 0;
	led_color.green = 255;
	led_color.blue = 0;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 0;
	led_color.green = 255;
	led_color.blue = 255;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 0;
	led_color.green = 0;
	led_color.blue = 255;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 255;
	led_color.green = 0;
	led_color.blue = 255;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 255;
	led_color.green = 255;
	led_color.blue = 255;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 128;
	led_color.green = 128;
	led_color.blue = 128;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 64;
	led_color.green = 64;
	led_color.blue = 64;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 32;
	led_color.green = 32;
	led_color.blue = 32;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 0;
	led_color.green = 0;
	led_color.blue = 0;
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	vTaskDelay(1000/portTICK_PERIOD_MS);
	
	led_color.red = 255;
	led_color.green = 0;
	led_color.blue = 0;
	for (int y = 0 ; y < LED_Y; y++) {
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, y, &led_color);
		}
		led_show();
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
	
	led_color.red = 0;
	led_color.green = 255;
	led_color.blue = 0;
	for (int x = 0 ; x < LED_X; x++) {
		for (int y = 0 ; y < LED_Y; y++) {
			led_set_pixel_color(x, y, &led_color);
		}
		led_show();
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
	
	
	// led_color.red = 0;
	// led_color.green = 0;
	// led_color.blue = 0;
	// for (int b = 0 ; b<256 ; b++) {
		// led_color.blue = b;
		// ledbuf = led_get_buf(0, 0);
		// for (int i=0; i<LED_LENGTH; i++)
			// ledbuf[i] = led_color;
		// ledbuf = led_get_buf(0, 1);
		// for (int i=0; i<LED_LENGTH; i++)
			// ledbuf[i] = led_color;
		// ledbuf = led_get_buf(0, 2);
		// for (int i=0; i<LED_LENGTH; i++)
			// ledbuf[i] = led_color;
		// led_show();
		// vTaskDelay(50/portTICK_PERIOD_MS);
	// }
	
}

void effect_test_end() {
	led_clear();
	led_show();
}
