# CaynenneLPP

## Overview
The Cayenne Low Power Payload (LPP) provides a convenient and easy way to send data over LPWAN networks such as LoRaWAN. The Cayenne LPP is compliant with the payload size restriction, which can be lowered down to 11 bytes, and allows the device to send multiple sensor data at one time.

This implementation differs from the reference implementation as the internal datastructures are `std::vector<uint8_t>` instead of a `uint8_t *buffer`. The encoder returns a `std::vector<uint8_t>` and is well suited for the Multitech libraries for sending LoraWAN data.

## Interface
     
    CayenneLPP(uint8_t size)
    void reset(void)
    uint8_t getSize()
    std::vector<uint8_t> getData(void)
    std::string getHexString(void)
    uint8_t addTemperature(uint8_t channel, float celsius)
    uint8_t addRelativeHumidity(uint8_t channel, float rh)
    uint8_t addPresence(uint8_t channel, uint8_t value)

Example:

    CayenneLPP Payload(MAX_SIZE);
    Payload.addTemperature(1, 23.6);
    dot->send(Payload.getData());

## Upcoming
I will add the remaining data types from the CayenneLPP.

## Compiling
The library is headeronly so all you have to do is include the CayenneCPP.h file in your project.

The library requires a C++11 compatible compiler like the gcc-arm-embedded toolchain. The online mbed.os compiler does not support C++11.

### Multitech libmdot:
https://os.mbed.com/teams/MultiTech/code/libmDot-mbed5/

### Reference implementation
https://mydevices.com/cayenne/docs/lora/#lora-cayenne-low-power-payload
