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
