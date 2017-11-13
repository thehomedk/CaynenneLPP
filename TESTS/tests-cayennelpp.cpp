// tests-cayennelpp.cpp
#include "../CayenneLPP.h"
#include "catch.hpp"
#define MAX_SIZE 242

using Catch::Matchers::Equals;

TEST_CASE("Payload is empty at start", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  REQUIRE(Payload.getSize() == 0);
}

TEST_CASE("Payload is empty after reset", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  Payload.addTemperature(1, 10);
  Payload.reset();
  REQUIRE(Payload.getSize() == 0);
}

TEST_CASE("Encode temperature payload, rounding", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("0167010F0267010F0367010F0467010F0567010F0667011007670110");
  Payload.addTemperature(1, 27.1);
  Payload.addTemperature(2, 27.11);
  Payload.addTemperature(3, 27.12);
  Payload.addTemperature(4, 27.13);
  Payload.addTemperature(5, 27.14);
  Payload.addTemperature(6, 27.15);
  Payload.addTemperature(7, 27.16);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));
}

TEST_CASE("Encode temperature payload, low temp", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string minus4point1("0167FFD7");
  std::string testminus100("0167FC18");

  Payload.addTemperature(1, -4.1);
  REQUIRE_THAT(minus4point1, Catch::Equals(Payload.getHexString()));

  Payload.reset();
  Payload.addTemperature(1, -100);
  REQUIRE_THAT(testminus100, Equals(Payload.getHexString()));
}

TEST_CASE("Encode relative humidity", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("026866");
  Payload.addRelativeHumidity(2, 51);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("026861");
  Payload.addRelativeHumidity(2, 48.5);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}

TEST_CASE("Encode relative humidity, rounding", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("016872026873036873046873056873066873076874");
  Payload.addRelativeHumidity(1, 57.2);
  Payload.addRelativeHumidity(2, 57.3);
  Payload.addRelativeHumidity(3, 57.4);
  Payload.addRelativeHumidity(4, 57.5);
  Payload.addRelativeHumidity(5, 57.6);
  Payload.addRelativeHumidity(6, 57.7);
  Payload.addRelativeHumidity(7, 57.8);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));
}

TEST_CASE("Encode presence", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("016601");
  Payload.addPresence(1, 1);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("016600");
  Payload.addPresence(1, 0);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}

TEST_CASE("Encode digital input", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("010001");
  Payload.addDigitalInput(1, 1);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("010000");
  Payload.addDigitalInput(1, 0);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}

TEST_CASE("Encode digital output", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("010101");
  Payload.addDigitalOutput(1, 1);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("010100");
  Payload.addDigitalOutput(1, 0);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}


TEST_CASE("Encode analog input", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("01020064");
  Payload.addAnalogInput(1, 1);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("01020000");
  Payload.addAnalogInput(1, 0);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}

TEST_CASE("Encode analog output", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("01030064");
  Payload.addAnalogOutput(1, 1);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("01030000");
  Payload.addAnalogOutput(1, 0);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}

TEST_CASE("Encode data on two channels", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("016700D3026866");
  Payload.addTemperature(1, 21.1);
  Payload.addRelativeHumidity(2, 51);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));
}
