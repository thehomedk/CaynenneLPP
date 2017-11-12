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
  std::string test("016700E8");

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
  std::string test("01020001");
  Payload.addAnalogInput(1, 1);
  REQUIRE_THAT(test, Equals(Payload.getHexString()));

  Payload.reset();
  std::string test2("01020000");
  Payload.addAnalogInput(1, 0);
  REQUIRE_THAT(test2, Equals(Payload.getHexString()));
}

TEST_CASE("Encode analog output", "[CayenneLPP]") {
  CayenneLPP Payload(MAX_SIZE);
  std::string test("01030001");
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
