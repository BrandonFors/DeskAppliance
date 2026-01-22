#include "photoresistor.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"


#include "esp_err.h"
#include "esp_log.h"
#include <stdint.h>
#include <inttypes.h>

//max adc reading
#define MAX_READ 4095
//max voltage that the potentiometer can read on wipper in mv
#define MAX_VLTG_MV 3300
//number of samples adc uses to calculate an average adc reading
#define NUM_SAMPLES 10

//adc variables
static adc_channel_t adc_channel;

static char *TAG = "Potentiometer";

void photoresistor_init(){
  adc_channel = ADC_CHANNEL_6;

  
}