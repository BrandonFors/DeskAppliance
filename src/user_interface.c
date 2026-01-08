#include "board.h"
#include "user_interface.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include <string.h>


#include "u8g2.h"
#include "u8g2_esp32_hal.h"


// u8g2: https://github.com/olikraus/u8g2/wiki/u8g2setupc
// u8g2 HAL: https://github.com/mkfrey/u8g2-hal-esp-idf

//Useful functions
// Draw Line: https://github.com/olikraus/u8g2/wiki/u8g2reference#drawhline
// Draw String: https://github.com/olikraus/u8g2/wiki/u8g2reference#drawstr
// Draw Triangle: https://github.com/olikraus/u8g2/wiki/u8g2reference
static u8g2_esp32_hal_t u8g2_esp32_hal;
static u8g2_t u8g2; // contains all data for the display

void display_init(){

  //initialize HAL for 2 wire i2c use
  u8g2_esp32_hal = (u8g2_esp32_hal_t)U8G2_ESP32_HAL_DEFAULT;
  u8g2_esp32_hal.bus.i2c.sda = SDA;
  u8g2_esp32_hal.bus.i2c.scl = SCL;
  u8g2_esp32_hal_init(u8g2_esp32_hal);
  
  //initialize u8g2 

  //the last two arguments come from the HAL
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0,
    u8g2_esp32_i2c_byte_cb,
    u8g2_esp32_gpio_and_delay_cb); // i2c callback function for mapping

  // note that the address here is shifted to the left to include a R/W flag
  u8x8_SetI2CAddress(&u8g2.u8x8,0x78); 
  
  u8g2_InitDisplay(&u8g2); 
  u8g2_SetPowerSave(&u8g2, 0); // wake up display as it is initialized in sleep mode
  u8g2_ClearBuffer(&u8g2);


}


void drawHome(){
  //inputs need to be the temp and time
  //displays time and room temperature
  
}

void drawToggleMenu(){
  //selection menu for toggling periferals on or off
}

void drawTest(){
  u8g2_ClearBuffer(&u8g2);
  u8g2_DrawRFrame(&u8g2, 0, 0, 128, 64, 7);
  u8g2_SendBuffer(&u8g2);
}