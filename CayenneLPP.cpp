#include "CayenneLPP.h"

// Initialize the payload data and set given maximum size.
CayenneLPP::CayenneLPP(uint8_t size) : maxsize(size) {
}

/*
CayenneLPP::~CayenneLPP(void) { free(buffer); }

*/
// Reset the payload, to call before building a frame payload
void CayenneLPP::reset(void) { data.clear(); }

/*
// Returns the current size of the payload
uint8_t CayenneLPP::getSize(void) { return cursor; }
*/

// Return the payload buffer as vector
std::vector<uint8_t> *CayenneLPP::getData(void) { return &data; }

/*
uint8_t CayenneLPP::copy(uint8_t *dst) {
  memcpy(dst, buffer, cursor);
  return cursor;
}

uint8_t CayenneLPP::addDigitalInput(uint8_t channel, uint8_t value) {
  if ((cursor + LPP_DIGITAL_INPUT_SIZE) > maxsize) {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DIGITAL_INPUT;
  buffer[cursor++] = value;
  return cursor;
}

uint8_t CayenneLPP::addDigitalOutput(uint8_t channel, uint8_t value) {
  if ((cursor + LPP_DIGITAL_OUTPUT_SIZE) > maxsize) {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DIGITAL_OUTPUT;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addAnalogInput(uint8_t channel, float value) {
  if ((cursor + LPP_ANALOG_INPUT_SIZE) > maxsize) {
    return 0;
  }

  int16_t val = value * 100;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ANALOG_INPUT;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addAnalogOutput(uint8_t channel, float value) {
  if ((cursor + LPP_ANALOG_OUTPUT_SIZE) > maxsize) {
    return 0;
  }
  int16_t val = value * 100;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ANALOG_OUTPUT;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addLuminosity(uint8_t channel, uint16_t lux) {
  if ((cursor + LPP_LUMINOSITY_SIZE) > maxsize) {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_LUMINOSITY;
  buffer[cursor++] = lux >> 8;
  buffer[cursor++] = lux;

  return cursor;
}

uint8_t CayenneLPP::addPresence(uint8_t channel, uint8_t value) {
  if ((cursor + LPP_PRESENCE_SIZE) > maxsize) {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_PRESENCE;
  buffer[cursor++] = value;

  return cursor;
}
*/

uint8_t CayenneLPP::addTemperature(uint8_t channel, float celsius) {
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

/*
uint8_t CayenneLPP::addRelativeHumidity(uint8_t channel, float rh) {
  if ((cursor + LPP_RELATIVE_HUMIDITY_SIZE) > maxsize) {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_RELATIVE_HUMIDITY;
  buffer[cursor++] = rh * 2;

  return cursor;
}

uint8_t CayenneLPP::addAccelerometer(uint8_t channel, float x, float y,
                                     float z) {
  if ((cursor + LPP_ACCELEROMETER_SIZE) > maxsize) {
    return 0;
  }
  int16_t vx = x * 1000;
  int16_t vy = y * 1000;
  int16_t vz = z * 1000;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ACCELEROMETER;
  buffer[cursor++] = vx >> 8;
  buffer[cursor++] = vx;
  buffer[cursor++] = vy >> 8;
  buffer[cursor++] = vy;
  buffer[cursor++] = vz >> 8;
  buffer[cursor++] = vz;

  return cursor;
}

uint8_t CayenneLPP::addBarometricPressure(uint8_t channel, float hpa) {
  if ((cursor + LPP_BAROMETRIC_PRESSURE_SIZE) > maxsize) {
    return 0;
  }
  int16_t val = hpa * 10;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_BAROMETRIC_PRESSURE;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addGyrometer(uint8_t channel, float x, float y, float z) {
  if ((cursor + LPP_GYROMETER_SIZE) > maxsize) {
    return 0;
  }
  int16_t vx = x * 100;
  int16_t vy = y * 100;
  int16_t vz = z * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GYROMETER;
  buffer[cursor++] = vx >> 8;
  buffer[cursor++] = vx;
  buffer[cursor++] = vy >> 8;
  buffer[cursor++] = vy;
  buffer[cursor++] = vz >> 8;
  buffer[cursor++] = vz;

  return cursor;
}

uint8_t CayenneLPP::addGPS(uint8_t channel, float latitude, float longitude,
                           float meters) {
  if ((cursor + LPP_GPS_SIZE) > maxsize) {
    return 0;
  }
  int32_t lat = latitude * 10000;
  int32_t lon = longitude * 10000;
  int32_t alt = meters * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GPS;

  buffer[cursor++] = lat >> 16;
  buffer[cursor++] = lat >> 8;
  buffer[cursor++] = lat;
  buffer[cursor++] = lon >> 16;
  buffer[cursor++] = lon >> 8;
  buffer[cursor++] = lon;
  buffer[cursor++] = alt >> 16;
  buffer[cursor++] = alt >> 8;
  buffer[cursor++] = alt;

  return cursor;
}
*/
