#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <time.h>

#include "led_strip/led_strip.h"


#define LED_STRIP_LENGTH 1344U
#define LED_STRIP_RMT_INTR_NUM 19U

static struct led_color_t led_strip1_buf_1[LED_STRIP_LENGTH];
static struct led_color_t led_strip1_buf_2[LED_STRIP_LENGTH];

// short ledsPosition[56][24];


struct led_strip_t led_strip1 = {
		.rgb_led_type = RGB_LED_TYPE_WS2812,
		.rmt_channel = RMT_CHANNEL_1,
		.rmt_interrupt_num = LED_STRIP_RMT_INTR_NUM,
		.gpio = GPIO_NUM_16,
		.led_strip_buf_1 = led_strip1_buf_1,
		.led_strip_buf_2 = led_strip1_buf_2,
		.led_strip_length = LED_STRIP_LENGTH
	};
	

static const char *TAG = "LED";

short ledmapalgo(int x, int y) {
	uint8_t row = y/8;
	short led = row*448;
	if (row!=1) {
		led += x*8;
		if ((x & 1) == 0) {
			led += y-row*8;
		} else {
			led += 8*(row+1)-y-1;
		}
	} else {
		led += (55-x)*8;
		if ((x & 1) == 0) {
			led += y-row*8;
		} else {
			led += 8*(row+1)-y-1;
		}
	}
	return led;
}

short ledMatrixMap(int px, int py) {
	short mat = py*7;
	if (py!=1) {
		mat += px;
	} else {
		mat += 6-px;
		
	}
	return mat;
}

bool led_set_pixel_color(uint8_t x, uint8_t y, struct led_color_t *color) {
	return led_strip_set_pixel_color(&led_strip1, ledmapalgo(x, y), color);
}

bool led_set_pixel_rgb(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue) {
	return led_strip_set_pixel_rgb(&led_strip1, ledmapalgo(x, y), red, green, blue);
}

bool led_get_pixel_color(uint8_t x, uint8_t y, struct led_color_t *color) {
	return led_strip_get_pixel_color(&led_strip1, ledmapalgo(x, y), color);
}

struct led_color_t* led_get_buf(uint8_t x, uint8_t y) {
	if (led_strip1.showing_buf_1) {
		return led_strip1_buf_2 + (ledMatrixMap(x, y) * 64);
	} else {
		return led_strip1_buf_1 + (ledMatrixMap(x, y) * 64);
	}
}

void led_show() {
	led_strip_show(&led_strip1);
}

void led_clear() {
	led_strip_clear(&led_strip1);
}




void init_led() {

	printf("LED MAP:\n");
	for (int y = 0 ; y<24 ; y++) {
		for (int x = 0 ; x<56 ; x++) {
			printf("%d ", ledmapalgo(x, y));
		}
		printf("\n");
	}
	printf("MAT MAP:\n");
	for (int y = 0 ; y<3 ; y++) {
		for (int x = 0 ; x<7 ; x++) {
			printf("%d ", ledMatrixMap(x, y));
		}
		printf("\n");
	}
	
	
	led_strip1.access_semaphore = xSemaphoreCreateBinary();
	ESP_LOGI(TAG,"Init led strip LEN:%d GPIO:%d RMT:%d", led_strip1.led_strip_length, led_strip1.gpio, led_strip1.rmt_channel);
	bool led_init_ok = led_strip_init(&led_strip1);
	if(!led_init_ok) {
		ESP_LOGE(TAG,"ERROR init led strip");
	}
	
	// led_strip2.access_semaphore = xSemaphoreCreateBinary();
	// ESP_LOGI(TAG,"Init led strip GPIO: %d", led_strip2.gpio);
	// led_init_ok = led_strip_init(&led_strip2);
	// if(!led_init_ok) {
		// ESP_LOGE(TAG,"ERROR init led strip");
	// }
	
	// led_strip3.access_semaphore = xSemaphoreCreateBinary();
	// ESP_LOGI(TAG,"Init led strip GPIO: %d", led_strip3.gpio);
	// led_init_ok = led_strip_init(&led_strip3);
	// if(!led_init_ok) {
		// ESP_LOGE(TAG,"ERROR init led strip");
	// }

	return;
}