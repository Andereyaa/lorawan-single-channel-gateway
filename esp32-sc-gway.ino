#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#include "esp32-sc-gway.h"  // This file contains configuration of GWay

int debug = 1;  // Debug level! 0 is no msgs, 1 normal, 2 is extensive
HardwareSerial LoRaRadio(2);
WiFiClient wifiClient;
HTTPClient httpClient;

// ----------------------------------------------------------------------------
// Function to initialise LoRa Radio
// ----------------------------------------------------------------------------
int initialiseLoraRadio() {
  LoRaRadio.begin(baudRate, SERIAL_8N1, DEFAULT_RX_PIN, DEFAULT_TX_PIN);
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+ADDRESS=" + AT_ADDRESS + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+NETWORKID=" + AT_NETWORK_ID + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+MODE=" + AT_MODE + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+IPR=" + AT_IPR + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+CRFOP=" + AT_CRFOP + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+BAND=" + AT_BAND + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+PARAMETER=" + AT_PARAMETER + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print((String) "AT+CPIN=" + AT_PASSWORD + "\r\n");
  delay(delayInMillis);
  LoRaRadio.print("AT+CPIN?\r\n");  // confirm password is set

  return 0;
}

// ----------------------------------------------------------------------------
// Function to join the Wifi Network
// ----------------------------------------------------------------------------
int connectWifi(String wifiSSID, String wifiPASS) {
  int status = WiFi.status();

  WiFi.mode(WIFI_MODE_STA);

  // None empty SSID, try connect
  if (!wifiSSID.isEmpty() && !wifiPASS.isEmpty()) {
    Serial.printf("connecting to %s with password %s\r\n", wifiSSID, wifiPASS);
    // Loop until connected or 20 sec time out
    unsigned long this_start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - this_start < 20000) {
      status = WiFi.begin(wifiSSID, wifiPASS);
      delay(1000);
    }
  } else {
    Serial.println(F("No SSID/PSK defined in sketch\r\nConnecting with SDK ones if any"));
  }

  if (status == WL_CONNECTED) {
    Serial.printf("WiFi Connection OK \r\n");
    Serial.printf("SSID: ");
    Serial.print(WiFi.SSID());
    Serial.printf("\r\n");
    Serial.printf("IP Address: ");
    Serial.print(WiFi.localIP());
    Serial.printf("\r\n");
  } else {
    Serial.println("WiFi Connection FAIL");
  }

  return status;
}

// ----------------------------------------------------------------------------
// Function to test internet connection
// ----------------------------------------------------------------------------
bool isConnectedToInternet(){

  bool isConnected = false;
  Serial.println("Testing internet connection...");
  if (wifiClient.connect(URL_TEST_SERVER, 80)) {
    Serial.println("Internet Connection OK");
    isConnected = true;
  } else {
    Serial.println("Internet Connection FAIL");
  }
  
  return isConnected;
}




// ========================================================================
// MAIN PROGRAM (SETUP AND LOOP)

// ----------------------------------------------------------------------------
// Setup code (one time)
// ----------------------------------------------------------------------------
void setup() {
  Serial.begin(baudRate);
  Serial.printf("Booting up \r\n");
  
  initialiseLoraRadio();

  if(connectWifi(WIFI_SSID, WIFI_PASS) == WL_CONNECTED){
    // If we are here we are connected to WLAN
    // So now test the Internet Connection
    if(isConnectedToInternet()){
      Serial.println("Error Internet connection failed");
    }
  }

  // TODO setup breathing LED 

  Serial.printf("Boot complete \r\n");
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
void loop() {
  
  // Receive Lora messages
  if(LoRaRadio.available()){
    yield();
    
    String incomingPacket = LoRaRadio.readString();

    httpClient.begin(wifiClient, URL_SERVER);
    JSONVar httpPostPayload;
    httpPostPayload["data"] = incomingPacket;
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.POST(JSON.stringify(httpPostPayload));


  }
}