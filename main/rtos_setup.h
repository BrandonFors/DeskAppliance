#ifndef RTOS_SETUP_H
#define RTOS_SETUP_H

#include "freertos/FreeRTOS.h"

#define BUTTON_QUEUE_LEN 1
#define CONTROLLER_QUEUE_LEN 20

#define DEBOUNCE_TIME_MS 250

// enums correlate with menu items
typedef enum {
  FAN = 0,
  VENT = 1,
  LAMP = 2,
  ACTUATOR_NA = 3,
} Actuator_Id;

typedef enum {
  UI = 0,
  CONTROLLER = 1,
  POTENTIOMETER = 2,
} Sender_Id;


//struct used to 
typedef enum {
  MODE = 0,
  TOGGLE = 1,
  ADJUST = 2,
  ACTION_NA = 3,
} Action_Id;

typedef struct {
  Actuator_Id actuator_id; 
  Action_Id action_id; 
  uint8_t pct; //used by ADC tasks
  Sender_Id sender_id; 
} ControllerMsg;

typedef struct {
  bool is_auto;
  bool is_on;
} ActuatorState;



//queue handles

QueueHandle_t buttonQueue; //handles button interrupts to UI task

QueueHandle_t controllerQueue; //handles messages sent to controller


//Task Handles 

TaskHandle_t userInterfaceTask;


void gpio_isr_handler(void* arg);

#endif