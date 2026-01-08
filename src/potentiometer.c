#include "potentiometer.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"
#include "esp_log.h"
#include <sorting.h>
#include <stdint.h>
#include <inttypes.h>

//max adc reading
#define MAX_READ 4095
//max voltage that the potentiometer can read on wipper
#define MAX_VOLT 1.5f
//number of samples adc uses to calculate an average adc reading
#define NUM_SAMPLES 10

static adc_channel_t adc_channel;
static adc_oneshot_unit_handle_t adc_handle;
static adc_oneshot_unit_init_cfg_t init_config;
static adc_oneshot_chan_cfg_t channel_config;



static char *TAG = "Potentiometer";

void potentiometer_init(){
  adc_channel = ADC_CHANNEL_0;

  init_config = (adc_oneshot_unit_init_cfg_t){
    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
  };

  ESP_LOGI(TAG, "Creating ADC Oneshot Unit");
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));
  
  channel_config = (adc_oneshot_chan_cfg_t){
    .bitwidth = ADC_BITWIDTH_DEFAULT,
    .atten = ADC_ATTEN_DB_0,
  };
  ESP_LOGI(TAG, "Creating ADC Oneshot Channel");
  ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, adc_channel, &channel_config));


}

// In my setup, the potentiomter reads in a way that is counter intuitive
//I want the potentiometer to output higher values when turrned to the right so i use this fxn
int invert_reading(int raw){
  return MAX_READ-raw;
}

//returns the raw reading of the potentiometer
int read_pot_raw(){
  int samples[NUM_SAMPLES];
  int raw = 0;
  for(int i = 0; i<NUM_SAMPLES; i++){
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, adc_channel, &samples[i]));
  }
  //sort the samples and drop the outer four
  insertion_sort(samples, NUM_SAMPLES);
  for(int i = 2; i < NUM_SAMPLES - 2; i++){
    raw += samples[i];
  }
  raw /= (NUM_SAMPLES - 4);
  raw = invert_reading(raw);
  return raw;
}

//returns the adc reading as a percentage of the max
int read_pot_pct(){
  int pct = (read_pot_raw()*100)/MAX_READ;
  return pct;
}

//returns the adc reading as a voltage
float read_pot_volt(){
  float volt = (read_pot_raw()*MAX_VOLT)/MAX_READ;
  return volt;
}
