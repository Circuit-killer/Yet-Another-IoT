/****************************************************************************

                 Yet Another IoT Node

  NAME       : YAIoT Node - Base board only Si70xx
  AUTHOR     : Eng. Felipe Navarro
  LICENSE    : MIT
  
****************************************************************************/

// If you want to test the NODE with a serial connection, uncomment 
// the next line, so you will get serial data.
//#define DEBUG

//If your node has the TPL5111, uncomment the next line
#define DONE_PIN

#define DELAY_TIME 10000

//If we use DONE_PIN with TPL5111 do not use the delay
#ifdef DONE_PIN
#undef DELAY_TIME
#endif

//Includes for RFM59HCW
#include <RHReliableDatagram.h>
#include <RH_RF69.h>
#include <SPI.h>

// Node Adress, if you're not using the I2C EEPROM option,
// uncomment the line below
#define CLIENT_ADDRESS 13

// Server will be always number 1 in the network!
#define SERVER_ADDRESS 1

#ifdef DONE_PIN
#define DONE_PIN 8
#endif

// Singleton instance of the radio driver
RH_RF69 driver;

#include "si70xx.h"
//Singleton instance of Si7021
Si70xx_driver Si7021;

// Use the RadioHead Reliable Datagram 
RHReliableDatagram manager(driver, CLIENT_ADDRESS);

void setup()
{
  Wire.begin();
  
  #ifdef DEBUG
  Serial.begin(115200);
  Serial.print("DEBUG MODE ON");
  #endif
  
  #ifdef DONE_PIN
  pinMode(DONE_PIN, OUTPUT);
  #endif

  
  
  manager.init();
  driver.setModemConfig(12); //GFSK_Rb4_8Fd9_6 
                             /* We're using the GFSK mode, with 4.8kbps on a 9.6Khz channel
                              * the maximum distance of usage, the maximum amount of nodes 
                              * ( 254 is the absolute maximum allowed by RadioHead driver),
                              * the time between each node packet sent, all this is a tradeoff
                              * that you need to test! 
                              * The more data, you need bigger datarate and you will get LOWER
                              * maximum distance between nodes and server. 
                              * 
                              * It's a tradeoff. Higher bandwith, higher noise, lower distance.
                              * 
                              * Even the server location needs to be really well thought.
                              * For this, take a look into ARRL Antenna Book, Chapter 17
                              * about Repeater Antenna Systems, however the books cover about
                              * VHF and UHF, it's a good start for server positioning for long range.
                              */
                              
  driver.setFrequency(915.0); //If you're using 868Mhz radio, change here to 868.0
  driver.setTxPower(20);
}
  
uint8_t data[4];

//Message buffer
uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];

void loop()
{
  /***********************************************************

       Si7020 data acquisition

  **********************************************************/

  float temperature = Si7021.read_temperature_celsius();
  float humidity    = Si7021.read_humidity();

#ifdef DEBUG
  Serial.println("INFO - Sending data to server");
  Serial.print("Temperature: "); Serial.println(temperature,2);
  Serial.print("Humidity: "; Serial.println(humidity,2);
#endif

/****************************************************************************
*
* Protocol Design:
* ID (from EEPROM unique ID) / SensorType /t:temp / u:humidity
*  
****************************************************************************/



send:
  // Send a message to server
  if (manager.sendtoWait(data, sizeof(data), SERVER_ADDRESS))
  {
    uint8_t len = sizeof(buf);
    uint8_t from;
    /* 
     *  Wait for ACK, so we garantee that the packet was received
     */
    if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
    { 
      #ifdef DEBUG
      Serial.print("INFO - Replied: 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);
      #endif
    }
    else
    { 
      #ifdef DEBUG
      Serial.println("No reply - Server OK?");
      #endif
      goto send; // If no ACK, try to resend!
      /*
       *  For the one's who are afraid of the software get 
       *  stuck here, it's not possible, if the timer doesn't 
       *  receive a done signal, it will turn the circuit off 
       *  and on shortly.
       */
    }

  }// After this, the data was already sent!

/*  
 *  If using TPL5111 timer, pull DONE_PIN high so the system will sleep, 
 *  and hook into a while(1) before power goes down, else, use the delay. 
 *  We hook to while(1) so the node doesn't go into a undefined behavior
 *  like trying to reaqcuire data and resend.
 */
#ifdef DONE_PIN  
  digitalWrite(DONE_PIN, HIGH);
  while(1); // After DONE_PIN beeing pulled HIGH the node will turn off
          // But ensure it doesn't try to do anything before power goes down.
#else
  delay(DELAY_TIME);
#endif
  
}// End of Main 

