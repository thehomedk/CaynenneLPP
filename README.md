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

    uint8_t addDigitalInput(uint8_t channel, uint8_t value)
    uint8_t addDigitalOutput(uint8_t channel, uint8_t value)

    uint8_t addAnalogInput(uint8_t channel, float value)
    uint8_t addAnalogOutput(uint8_t channel, float value)

    uint8_t addTemperature(uint8_t channel, float celsius)
    uint8_t addRelativeHumidity(uint8_t channel, float rh)
    uint8_t addPresence(uint8_t channel, uint8_t value)

Example:

    CayenneLPP Payload(MAX_SIZE);
    Payload.addTemperature(1, 23.6);
    dot->send(Payload.getData());

## Rounding
Compared to the reference implementation this encoder rounds the values.

    Payload.addRelativeHumidity(1, 57.2);
    Payload.addRelativeHumidity(2, 57.3);
    Payload.addRelativeHumidity(3, 57.4);
    Payload.addRelativeHumidity(4, 57.5);
    Payload.addRelativeHumidity(5, 57.6);
    Payload.addRelativeHumidity(6, 57.7);
    Payload.addRelativeHumidity(7, 57.8);

will result in:

    {
      "relative_humidity_1": 57,
      "relative_humidity_2": 57.5,
      "relative_humidity_3": 57.5,
      "relative_humidity_4": 57.5,
      "relative_humidity_5": 57.5,
      "relative_humidity_6": 57.5,
      "relative_humidity_7": 58
    }

And:

    Payload.addTemperature(1, 27.1);
    Payload.addTemperature(2, 27.11);
    Payload.addTemperature(3, 27.12);
    Payload.addTemperature(4, 27.13);
    Payload.addTemperature(5, 27.14);
    Payload.addTemperature(6, 27.15);
    Payload.addTemperature(7, 27.16);

will result in:

    {
      "temperature_1": 27.1,
      "temperature_2": 27.1,
      "temperature_3": 27.1,
      "temperature_4": 27.1,
      "temperature_5": 27.1,
      "temperature_6": 27.2,
      "temperature_7": 27.2
    }

## Upcoming
I will add the remaining data types from the CayenneLPP.

## Compiling
The library is headeronly so all you have to do is include the CayenneLPP.h file in your project.

The library requires a C++11 compatible compiler like the gcc-arm-embedded toolchain. The online mbed.os compiler does not support C++11.

### Multitech libmdot:
https://os.mbed.com/teams/MultiTech/code/libmDot-mbed5/

### Reference implementation
https://mydevices.com/cayenne/docs/lora/#lora-cayenne-low-power-payload
