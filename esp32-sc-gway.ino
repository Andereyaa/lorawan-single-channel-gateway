#include<HardwareSerial.h>

#include "esp32-sc-gway.h"      // This file contains configuration of GWay

int debug = 1;									// Debug level! 0 is no msgs, 1 normal, 2 is extensive
HardwareSerial LoRaRadio(2);

// ----------------------------------------------------------------------------
// Function to join the Wifi Network
// ----------------------------------------------------------------------------
int initialiseLoraRadio(){
  LoRaRadio.begin(baudRate, SERIAL_8N1, DEFAULT_RX_PIN, DEFAULT_TX_PIN);
  delay(delay);
  LoRaRadio.print((String)"AT+ADDRESS=" + AT_ADDRESS + "\r\n");
  delay(delay);
  LoRaRadio.print((String)"AT+NETWORKID=" + AT_NETWORK_ID + "\r\n");
  delay(delay);
  LoRaRadio.print((String)"AT+MODE=" + AT_MODE + "\r\n");
  delay(delay);
  LoRaRadio.print((String)"AT+IPR=" + AT_IPR + "\r\n");
  delay(delay);
  LoRaRadio.print((String)"AT+CRFOP=" + AT_CRFOP + "\r\n");
  delay(delay);
  LoRaRadio.print((String)"AT+BAND=" + AT_BAND + "\r\n");
  delay(delay);
  LoRaRadio.print((String)"AT+PARAMETER=" + AT_PARAMETER + "\r\n");
  delay(delay);
  LoRaRadio.print("AT+CPIN=" + AT_PASSWORD + "\r\n");
  delay(delay);
  LoRaRadio.print("AT+CPIN?\r\n"); // confirm password is set

  return 0;
}
// ----------------------------------------------------------------------------
// Function to join the Wifi Network
// ----------------------------------------------------------------------------
int connectWifi(char* wifi_ssid, char* wifi_pass){

}

// ========================================================================
// MAIN PROGRAM (SETUP AND LOOP)

// ----------------------------------------------------------------------------
// Setup code (one time)
// ----------------------------------------------------------------------------
void setup() {

  Serial.print(F("\r\nBooting "));
}


// ----------------------------------------------------------------------------
// LOOP
// This is the main program that is executed time and time again.
// We need to give way to the backend WiFi processing that
// takes place somewhere in the ESP32 firmware and therefore
// we include yield() statements at important points.
//
// Note: If we spend too much time in user processing functions
//	and the backend system cannot do its housekeeping, the watchdog
// function will be executed which means effectively that the
// program crashes.
// ----------------------------------------------------------------------------
void loop() {}