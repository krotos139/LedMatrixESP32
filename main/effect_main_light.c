#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <time.h>

#include "led_tasks.h"

void effect_maillight_start() {
	struct led_color_t led_color = {
        .red = 0,
        .green = 0,
        .blue = 0,
    };
	
	led_clear();
	for (int l = 0 ; l < 256; l+=1) {
		led_color.red = l;
		led_color.green = l;
		led_color.blue = l;
		for (int y = 0 ; y < 8; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		led_show();
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
}

void effect_maillight_process() {
	vTaskDelay(100/portTICK_PERIOD_MS);
}

void effect_maillight_end() {
	struct led_color_t led_color = {
        .red = 255,
        .green = 255,
        .blue = 255,
    };
	
	for (int l = 255 ; l >=0; l-=2) {
		led_color.red = l;
		led_color.green = l;
		led_color.blue = l;
		for (int y = 0 ; y < 8; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, &led_color);
			}
		}
		led_show();
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
	vTaskDelay(200/portTICK_PERIOD_MS);
	led_clear();
	led_show();
}
