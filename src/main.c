#include "board.h"
#include "rtos_setup.h"
#include "esp_err.h"
#include "esp_log.h"

//outputs
#include "level_indicator.h"
#include "user_interface.h"
#include "fan_motor.h"
#include "lamp.h"
#include "vent.h"

//inputs
#include "potentiometer.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


static const BaseType_t app_cpu = 0;

static char* TAG = "RTOS";

void start_up(){
  //set led pin to output mode
  gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);

  //initialize peripherals
  indicator_init();
  display_init();
  fan_init();
  lamp_init();
  vent_init();
  potentiometer_init();


}

void actuators(void *parameters){
  while(1){

    // for(int i = 1; i <= 5; i++){
    //   set_level(i);
    //   vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
  vent_set_angle(0);     // min position
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  vent_set_angle(90);    // center
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  vent_set_angle(180);   // max position
  vTaskDelay(1000 / portTICK_PERIOD_MS);


  }

}

void read_potentiometer(void *parameters){
  while(1){
    int pct = read_pot_pct();
    ESP_LOGI(TAG, "Recieved pot reading of %d%%", pct);
    //send to actuator task 
    //actuator task will apply this value whereever it is relevant according to UI
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
  
}

void user_interface(void *parameters){
  while(1){
    drawTest();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
  }
}


void blink_led(void *parameters) {
  while(1){
    gpio_set_level(LED_BUILTIN, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(LED_BUILTIN, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  
}

void app_main() {
  start_up();
  
  ESP_LOGI(TAG, "Creating Tasks.");
  
  xTaskCreatePinnedToCore(
    blink_led,
    "Blink LED",
    1024,
    NULL,
    1,
    NULL,
    app_cpu
  );

  xTaskCreatePinnedToCore(
    actuators,
    "Actuator Task",
    2048,
    NULL,
    1,
    NULL,
    app_cpu
  );

  xTaskCreatePinnedToCore(
    user_interface,
    "User Interface",
    2048,
    NULL,
    1,
    NULL,
    app_cpu
  );

  xTaskCreatePinnedToCore(
    read_potentiometer,
    "Pot Test",
    2048,
    NULL,
    1,
    NULL,
    app_cpu
  );

  vTaskDelete(NULL);
}