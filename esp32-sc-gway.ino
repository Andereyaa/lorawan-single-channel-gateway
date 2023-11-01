#include <HardwareSerial.h>
#include <WiFi.h>

#include "esp32-sc-gway.h"  // This file contains configuration of GWay

int debug = 1;  // Debug level! 0 is no msgs, 1 normal, 2 is extensive
HardwareSerial LoRaRadio(2);
WiFiClient wifiClient;

// ----------------------------------------------------------------------------
// Function to initialise LoRa Radio
// ----------------------------------------------------------------------------
int initialiseLoraRadio() {
  LoRaRadio.begin(baudRate, SERIAL_8N1, DEFAULT_RX_PIN, DEFAULT_TX_PIN);
  delay(delay);
  LoRaRadio.print((String) "AT+ADDRESS=" + AT_ADDRESS + "\r\n");
  delay(delay);
  LoRaRadio.print((String) "AT+NETWORKID=" + AT_NETWORK_ID + "\r\n");
  delay(delay);
  LoRaRadio.print((String) "AT+MODE=" + AT_MODE + "\r\n");
  delay(delay);
  LoRaRadio.print((String) "AT+IPR=" + AT_IPR + "\r\n");
  delay(delay);
  LoRaRadio.print((String) "AT+CRFOP=" + AT_CRFOP + "\r\n");
  delay(delay);
  LoRaRadio.print((String) "AT+BAND=" + AT_BAND + "\r\n");
  delay(delay);
  LoRaRadio.print((String) "AT+PARAMETER=" + AT_PARAMETER + "\r\n");
  delay(delay);
  LoRaRadio.print("AT+CPIN=" + AT_PASSWORD + "\r\n");
  delay(delay);
  LoRaRadio.print("AT+CPIN?\r\n");  // confirm password is set

  return 0;
}

// ----------------------------------------------------------------------------
// Function to join the Wifi Network
// ----------------------------------------------------------------------------
int connectWifi(char* wifiSSID, char* wifiPASS) {
  int status = WiFi.status();

  WiFi.mode(WIFI_MODE_STA);

  // None empty SSID, try connect
  if (*wifiSSID != '*' && *wifiPASS != '*') {
    Serial.printf("connecting to %s with password %s\r\n", wifiSSID, wifiPASS);
    // Loop until connected or 20 sec time out
    unsigned long this_start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - this_start < 20000) {
      status = Wifi.begin(wifiSSID, wifiPASS);
      delay(1000);
    }
  } else {
  }

  if (status == WL_CONNECTED) {
    Serial.printf("WiFi Connection OK \r\n");
    Serial.printf("SSID: ");
    Serial.printf(WiFi.SSID());
    Serial.printf("\r\n");
    Serial.printf("IP Address: ");
    Serial.printf(WiFi.localIP());
    Serial.printf("\r\n");
  } else {
    Serial.println("WiFi Connection FAIL");
  }

  Serial.println("Testing internet connection...");
  if(wifiClient.connect(URL_TEST_SERVER, 80)){
    Serial.println("Internet Connection OK");
  }else{
    Serial.println("Internet Connection FAIL");
  }

  return status;
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