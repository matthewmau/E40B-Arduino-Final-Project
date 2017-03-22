/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Arduino.h>
#include <string.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BleExt.h"

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN ,
                       BLUEFRUIT_UART_CTS_PIN ,  BLUEFRUIT_UART_RTS_PIN );

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// Function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);

// Packet buffer
extern uint8_t packetbuffer[];

/**************************************************************************/
bool bleSetup(void) {
  Serial.println();
  Serial.println(F("Adafruit Bluefruit App Controller"));
  Serial.println(F("******************************"));

  /* Initialise the module */
  Serial.print(F("Initialising Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) ){
    error(F("Couldn't find device, set commanc mode & check wires"));
  }
  Serial.println( F("OK!") );

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Use Adafruit Bluefruit LE app to connect Controller mode"));
  Serial.println();
  ble.verbose(false);

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("******************************"));

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));
  Serial.println();

  return true;
}

/**************************************************************************
 @brief  Constantly poll for new command or response data
 **************************************************************************/
bool bleGetInput(void) {
  /* Wait for new data to arrive */
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) {
    return false;
  }

  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttonNumber = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    return true;
  }
  return false;
}
