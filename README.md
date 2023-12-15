# Single Channel LoraWAN Gateway
============================================================


This repository contains a proof-of-concept implementation of a single channel LoRaWAN gateway. 
It has been tested on the ESP32-S3-DevKitC-1U, using a Semtech SX1276 transceiver (Reyax RYLR890).

The code is for testing and development purposes only, and is not meant for production usage.

Inspired by Andres Spies ESP-1ch-Gateway https://github.com/SensorsIot/ESP-1ch-Gateway

# Building from source
------------------------
## Requirements
- Arduino IDE 2.2.1 or later
- Reyax RYLR890 transceiver
- Espressif ESP32-S3-DevKitC-1U


# Features
------------------------
- listen on configurable frequency and spreading factor
- SF7 to SF12
- can forward to one server


# Dependencies
------------------------



# Configurations
------------------------
Defaults
- LoRa: 

Edit esp32-sc-gway.h to change configuration (look for: "Configure these values!").


# License
------------------------