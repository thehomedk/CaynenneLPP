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

// Data ID + Data Type + Data Size
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

private:
  std::vector<uint8_t> data;
  uint8_t maxsize;
};

#endif
