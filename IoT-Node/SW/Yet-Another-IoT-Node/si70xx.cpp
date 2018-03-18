#include "si70xx.h"

 float Si70xx_driver::read_temperature_celsius(void)
 {
  //Start I2C TX
  Wire.beginTransmission(Si70xx_ADDR);
  //Temperature Measurement with NO HOLD MASTER
  Wire.write(Si70xx_R_Temperature_NoHold);
  Wire.endTransmission();
  
  //If the code uses FreeRTOS, use vTaskDelay instead of delay();
  #ifdef FreeRTOS
  vTaskDelay(pdMS_TO_TICKS(500)); //Delay 500ms
  #else
  delay(500);
  #endif

  Wire.requestFrom(Si70xx_ADDR, 2);
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  temp  = ((data[0] * 256.0) + data[1]);
  return (((175.72 * temp) / 65536.0) - 46.85);
 }

 float Si70xx_driver::read_humidity(void)
 {
  //Start I2C TX
  Wire.beginTransmission(Si70xx_ADDR);
  //Humidity Measurement with NO HOLD MASTER
  Wire.write(Si70xx_R_Humidity_NoHold);
  Wire.endTransmission();
  
  //If the code uses FreeRTOS, use vTaskDelay instead of delay();
  #ifdef FreeRTOS
  vTaskDelay(pdMS_TO_TICKS(500)); //Delay 500ms
  #else
  delay(500);
  #endif

  Wire.requestFrom(Si70xx_ADDR, 2);
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  temp = (data[0] * 256.0) + data[1];
  temp = ((125 * temp) / 65536.0) - 6;
  return temp;
 }
