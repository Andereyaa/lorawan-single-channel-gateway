

#include <Arduino.h>

#define VERSION "V.0.0.0"

/*******************************************************************************

   Configure these values if necessary!

 *******************************************************************************/

//
#define delayInMillis 100

// WiFi definitions
// Setup your Wifi SSID and password
#define _SSID mySSID
#define _PASS myPASSWORD

// Gateway Ident definitions
#define _DESCRITPION ""
#define _PLATFORM "ESP32"
#define _LAT 0.0
#define _LONG 0.0
#define _ALT 0.0

// REYAX RYLR890
#define DEFAULT_TX_PIN 18
#define DEFAULT_RX_PIN 17
#define baudRate 115200
#define AT_ADDRESS 1
#define AT_NETWORK_ID 10
#define AT_MODE 0
#define AT_IPR 115200
#define AT_PARAMETER "12,4,1,7"
#define AT_BAND 868500000
#define AT_CRFOP 10
#define AT_PASSWORD "92A0ECEC9000DA0DCF0CAAB0ABA2E0EF"

// Web Server
#define URL_TEST_SERVER ""
#define URL_SERVER ""
#define URL_SECURE_SERVER ""
