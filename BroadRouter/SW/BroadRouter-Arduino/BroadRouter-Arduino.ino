/****************************************************************************

                 Yet Another IoT Node

  NAME       : YAIoT Node - Broadrouter board 
               For use with only nodes with Si70xx
  AUTHOR     : Eng. Felipe Navarro
  LICENSE    : MIT
  
****************************************************************************/

#include <RHReliableDatagram.h>
#include <RH_RF69.h>
#include <SPI.h>

#define SERVER_ADDRESS 1

// Singleton instance of the radio driver
RH_RF69 driver;

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, SERVER_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  if (!manager.init())
    Serial.println("init failed");
  // If you are using a high power RF69, you *must* set a Tx power in the
  // range 14 to 20 like this:
  // driver.setTxPower(14);
    driver.setModemConfig(12); //GFSK_Rb4_8Fd9_6    
    driver.setFrequency(915.0);
    driver.setTxPower(20);

}

uint8_t data[] = "";
uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];

void loop()
{
  if (manager.available())
  {
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from))
    {
      float dhumidity  = ((buf[0] * 256.0) + buf[1]);
      dhumidity = ((125 * dhumidity) / 65536.0) - 6;  
      float dtemp  = ((buf[2] * 256.0) + buf[3]);
      dtemp = ((175.72 * dtemp) / 65536.0) - 46.85;
      Serial.print(from);              Serial.print(";");
      Serial.print(dhumidity,1);       Serial.print(";");
      Serial.print(dtemp,2);           Serial.print(";");
      Serial.println(driver.lastRssi());    
      // Send a reply back to the sender
      if (!manager.sendtoWait(data, sizeof(data), from))
        Serial.println("ERR - ACK");
    }
  }
}

