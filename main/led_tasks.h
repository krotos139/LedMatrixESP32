#pragma once

#include "led_strip/led_strip.h"

#define LED_LENGTH 448U
#define LED_X 56
#define LED_Y 24

bool led_set_pixel_color(uint8_t x, uint8_t y, struct led_color_t *color);
bool led_set_pixel_rgb(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);
bool led_get_pixel_color(uint8_t x, uint8_t y, struct led_color_t *color);
void led_show();
void led_clear();
struct led_color_t* led_get_buf(uint8_t x, uint8_t y);

short ledMatrixMap(int px, int py);

void switchScene(int scene);
int getScene();

void effect_test_start();
void effect_test_process();
void effect_test_end();

void effect_maillight_start();
void effect_maillight_process();
void effect_maillight_end();

void effect_off_start();
void effect_off_process();
void effect_off_end();


void artnet_start();
void artnet_process();
void artnet_end();

void init_led();

void artnet_task();
void control_task();
void http_server(void *pvParameters);
