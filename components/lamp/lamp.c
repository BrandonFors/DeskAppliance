#include "board.h"
#include "lamp.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"
#include <inttypes.h>



//these values represent the min and max duty cycle when the lamp is in a usable state
#define MAX_LAMP_DUTY 255
#define MIN_LAMP_DUTY 0

static ledc_timer_config_t timer_config;
static ledc_channel_config_t channel_config;
static const char *TAG = "Lamp";

static uint32_t current_duty;

#define TIMER_FREQ 1000 

void lamp_init(){
  // create a configuration for the timer of the ledc
  timer_config = (ledc_timer_config_t){
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_8_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = TIMER_FREQ,
    .clk_cfg = LEDC_AUTO_CLK,
  };
  
  ESP_LOGI(TAG, "Configuring LEDC Timer");
  ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

  //create a configuration for the channel of the ledc
  channel_config = (ledc_channel_config_t){
    .gpio_num = LAMP_PIN, 
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_0,
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0,

  };
  
  ESP_LOGI(TAG, "Configuring LEDC Channel");
  ESP_ERROR_CHECK(ledc_channel_config(&channel_config));

  current_duty = 0;

  // be sure to run ledc_fade_func_install(0); in main
  //this allows the ledc to transition between duty cycle values smoothly

}

//set brightness using a int from 0-100 (%)
void lamp_set_brightness(uint8_t percent){
  if(percent > 100){
    percent = 100;
  }else if(percent < 0){
    percent = 0;
  }
  current_duty = MIN_LAMP_DUTY + (MAX_LAMP_DUTY - MIN_LAMP_DUTY)*(percent/100.0);
  
  ESP_LOGI(TAG, "Lamp set to %" PRIu32 " duty.", current_duty);
  ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, current_duty, 0));
}

//turn lamp on from the stored duty cycle
void lamp_on(){
  ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, current_duty, 0));
  ESP_LOGI(TAG, "Lamp set to %" PRIu32 " duty.", current_duty);
  
}

//turn lamp off by setting duty to 0
void lamp_off(){
  ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0, 0));
  ESP_LOGI(TAG, "Lamp set to 0 duty.");
}
