/*
 * Si70xx Driver Class
 */
 #include "Arduino.h"
 #include "Wire.h"

 #define Si70xx_ADDR 0x40
 #define Si70xx_R_Humidity_NoHold 0xF5
 #define Si70xx_R_Temperature_NoHold 0xF3
  
 class Si70xx_driver
 {
  public:
    float read_temperature_celsius(void);
    float read_humidity(void);
    
  private:
    uint8_t data[2];
    float temp;
 };


float Si70xx_driver::read_temperature_celsius(void);
float Si70xx_driver::read_humidity(void);

