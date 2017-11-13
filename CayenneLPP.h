#include <inttypes.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#ifndef _CAYENNE_LPP_H_
#define _CAYENNE_LPP_H_

// Data types
#define LPP_DIGITAL_INPUT 0         // 1 byte
#define LPP_DIGITAL_OUTPUT 1        // 1 byte
#define LPP_ANALOG_INPUT 2          // 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT 3         // 2 bytes, 0.01 signed
#define LPP_LUMINOSITY 101          // 2 bytes, 1 lux unsigned
#define LPP_PRESENCE 102            // 1 byte, 1
#define LPP_TEMPERATURE 103         // 2 bytes, 0.1°C signed
#define LPP_RELATIVE_HUMIDITY 104   // 1 byte, 0.5% unsigned
#define LPP_ACCELEROMETER 113       // 2 bytes per axis, 0.001G
#define LPP_BAROMETRIC_PRESSURE 115 // 2 bytes 0.1 hPa Unsigned
#define LPP_GYROMETER 134           // 2 bytes per axis, 0.01 °/s
#define LPP_GPS 136 // 3 byte lon/lat 0.0001 °, 3 bytes alt 0.01m

// Data sizes
#define LPP_DIGITAL_INPUT_SIZE 3
#define LPP_DIGITAL_OUTPUT_SIZE 3
#define LPP_ANALOG_INPUT_SIZE 4
#define LPP_ANALOG_OUTPUT_SIZE 4
#define LPP_LUMINOSITY_SIZE 4
#define LPP_PRESENCE_SIZE 3
#define LPP_TEMPERATURE_SIZE 4
#define LPP_RELATIVE_HUMIDITY_SIZE 3
#define LPP_ACCELEROMETER_SIZE 8
#define LPP_BAROMETRIC_PRESSURE_SIZE 4
#define LPP_GYROMETER_SIZE 8
#define LPP_GPS_SIZE 11

class CayenneLPP {
public:
  // Initialize the payload data and set given maximum size.
  CayenneLPP(uint8_t size) : maxsize(size) {}

  ~CayenneLPP(){};

  // Reset the payload
  void reset(void) { data.clear(); }

  uint8_t getSize() { return data.size(); }

  // Return the payload buffer as vector
  std::vector<uint8_t> getData(void) { return data; }

  // Output the payload as hex string eg. 016700E8
  std::string getHexString(void) {
    std::ostringstream oss;
    for (int n : data) {
      oss << std::setfill('0') << std::setw(2) << std::uppercase << std::hex
          << n;
    }
    return oss.str();
  }

  /**
   * adds digital input to the payload.
   * @param channel integer, the data channel.
   * @param value uint8_t, digital input.
   * @return 1 on success, 0 on failure
   */
  uint8_t addDigitalInput(uint8_t channel, uint8_t value) {
    if ((data.size() + LPP_DIGITAL_INPUT_SIZE) > maxsize) {
      return 0;
    }

    data.push_back(channel);
    data.push_back(LPP_DIGITAL_INPUT);
    data.push_back(value);

    return 1;
  }

  /**
   * adds digital output to the payload.
   * @param channel integer, the data channel.
   * @param value uint8_t, digital output.
   * @return 1 on success, 0 on failure
   */
  uint8_t addDigitalOutput(uint8_t channel, uint8_t value) {
    if ((data.size() + LPP_DIGITAL_OUTPUT_SIZE) > maxsize) {
      return 0;
    }

    data.push_back(channel);
    data.push_back(LPP_DIGITAL_OUTPUT);
    data.push_back(value);

    return 1;
  }

  /**
   * adds analog input to the payload.
   * @param channel integer, the data channel.
   * @param value float, analog input.
   * @return 1 on success, 0 on failure
   */
  uint8_t addAnalogInput(uint8_t channel, float value) {
    if ((data.size() + LPP_ANALOG_INPUT_SIZE) > maxsize) {
      return 0;
    }

    int16_t val = value * 100;
    data.push_back(channel);
    data.push_back(LPP_ANALOG_INPUT);
    data.push_back(val >> 8);
    data.push_back(val);

    return 1;
  }

  /**
   * adds analog output to the payload.
   * @param channel integer, the data channel.
   * @param value float, analog output.
   * @return 1 on success, 0 on failure
   */
  uint8_t addAnalogOutput(uint8_t channel, float value) {
    if ((data.size() + LPP_ANALOG_OUTPUT_SIZE) > maxsize) {
      return 0;
    }

    int16_t val = value * 100;
    data.push_back(channel);
    data.push_back(LPP_ANALOG_OUTPUT);
    data.push_back(val >> 8);
    data.push_back(val);

    return 1;
  }

  /**
   * adds temperature to the payload.
   * @param channel integer, the data channel.
   * @param celcius float, the temperature in celcius.
   * @return 1 on success, 0 on failure
   */
  uint8_t addTemperature(uint8_t channel, float celsius) {
    if ((data.size() + LPP_TEMPERATURE_SIZE) > maxsize) {
      return 0;
    }

    int16_t val = floor(celsius * 10 + 0.5);
    data.push_back(channel);
    data.push_back(LPP_TEMPERATURE);
    data.push_back(val >> 8);
    data.push_back(val);

    return 1;
  }

  /**
   * adds relative humidity to the payload.
   * @param channel integer, the data channel.
   * @param rh float, the relative humidity.
   * @return 1 on success, 0 on failure
   */
  uint8_t addRelativeHumidity(uint8_t channel, float rh) {
    if ((data.size() + LPP_RELATIVE_HUMIDITY_SIZE) > maxsize) {
      return 0;
    }

    data.push_back(channel);
    data.push_back(LPP_RELATIVE_HUMIDITY);
    data.push_back(rh * 2);

    return 1;
  }

  /**
   * adds presence data to the payload.
   * @param channel integer, the data channel.
   * @param value uint8_t, presence.
   * @return 1 on success, 0 on failure
   */
  uint8_t addPresence(uint8_t channel, uint8_t value) {
    if ((data.size() + LPP_PRESENCE_SIZE) > maxsize) {
      return 0;
    }

    data.push_back(channel);
    data.push_back(LPP_PRESENCE);
    data.push_back(value);

    return 1;
  }

private:
  std::vector<uint8_t> data;
  uint8_t maxsize;
};

#endif
