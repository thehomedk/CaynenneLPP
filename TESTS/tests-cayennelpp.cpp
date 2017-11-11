// tests-cayennelpp.cpp
#include "../CayenneLPP.h"
#include "catch.hpp"
#define MAX_SIZE 200

using Catch::Matchers::Equals;

TEST_CASE("Cayenne payload is empty to start", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  REQUIRE(Payload.getSize() == 0);
}

TEST_CASE("Cayenne payload is empty after reset", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  Payload.addTemperature(1, 10);
  Payload.reset();
  REQUIRE(Payload.getSize() == 0);
}

TEST_CASE("Encode temperature payload, rounding", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE); // 23.2 ºC
  std::string test ("016700E8");

  Payload.addTemperature(1, 23.2);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  Payload.addTemperature(1, 23.15);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  Payload.addTemperature(1, 23.24999);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  Payload.addTemperature(1, 23.25);
  REQUIRE_THAT(test, !Equals(Payload.getHexString()));

  Payload.reset();
  Payload.addTemperature(1, 23.14999);
  REQUIRE_THAT(test, !Equals(Payload.getHexString()));
}

TEST_CASE("Encode temperature payload, low temp", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test ("0167FFD7");  // -4.1 ºC

  Payload.addTemperature(1, -4.1);
  REQUIRE_THAT(test, Catch::Equals(Payload.getHexString()));
}


/*




TEST_CASE("Encode temperature payload, rounding", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  const char test[] = "01 67 00 E8"; char p[30];

  Payload.addTemperature(1, 23.2);
  uint8_t* payload = Payload.getBuffer();
  sprintf(p, "%02X %02X %02X %02X", payload[0], payload[1], payload[2], payload[3]);
  REQUIRE_THAT(test, Catch::Equals(p));

  Payload.reset();
  Payload.addTemperature(1, 23.15001);
  payload = Payload.getBuffer();
  sprintf(p, "%02X %02X %02X %02X", payload[0], payload[1], payload[2], payload[3]);

  REQUIRE_THAT(test, Catch::Equals(p));

  Payload.reset();
  Payload.addTemperature(1, 23.24999);
  payload = Payload.getBuffer();
  sprintf(p, "%02X %02X %02X %02X", payload[0], payload[1], payload[2], payload[3]);

  REQUIRE_THAT(test, Catch::Equals(p));

}

TEST_CASE("Encode temperature payload, low temp", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  const char test[] = "01 67 FF D7"; char p[30];

  Payload.addTemperature(1, -4.1);
  uint8_t* payload = Payload.getBuffer();
  sprintf(p, "%02X %02X %02X %02X", payload[0], payload[1], payload[2], payload[3]);
  REQUIRE_THAT(test, Catch::Equals(p));
}

TEST_CASE("Encode temperature payload, very low temp", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  const char test[] = "01 67 FE B2"; char p[30];

  Payload.addTemperature(1, -33.4);
  uint8_t* payload = Payload.getBuffer();
  sprintf(p, "%02X %02X %02X %02X", payload[0], payload[1], payload[2], payload[3]);
  REQUIRE_THAT(test, Catch::Equals(p));
}

TEST_CASE("Encode relative humidity payload", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  Payload.addRelativeHumidity(2, 47);
  uint8_t* payload = Payload.getBuffer();

  const char test[] = "02 68 5E";
  char p[30];
  sprintf(p, "%02X %02X %02X", payload[0], payload[1], payload[2]);

  REQUIRE_THAT(test, Catch::Equals(p));
}
*/
