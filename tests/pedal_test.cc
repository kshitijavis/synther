//
// Created by Kshitij Sinha on 12/6/20.
//

#include "visualizer/pedal.h"

#include <catch2/catch.hpp>

#include "cinder/Color.h"

using synther::visualizer::Pedal;

TEST_CASE("Press and release correctly toggle pedal state",
          "[press][release][ispressed]") {
  Pedal pedal(glm::dvec2(0, 0), 5, 5, ci::Color("black"), ci::Color("white"),
              "TEST", "arial");

  SECTION("On construction, pedal is not pressed") {
    REQUIRE(!pedal.IsPressed());
  }

  SECTION("After press, pedal is not pressed") {
    pedal.Press();
    REQUIRE(pedal.IsPressed());
  }

  SECTION("After release, pedal is not pressed") {
    pedal.Release();
    REQUIRE(!pedal.IsPressed());
  }

  SECTION("Pressing twice keeps the pedal pressed") {
    pedal.Press();
    pedal.Press();
    REQUIRE(pedal.IsPressed());
  }

  SECTION("Releasing a pressed pedal makes it not pressed") {
    pedal.Press();
    pedal.Release();
    REQUIRE(!pedal.IsPressed());
  }
}

TEST_CASE("IsInBounds correctly validates position vectors", "[isinbounds]") {
  glm::dvec2 top_left_corner(0, 0);
  double width = 10;
  double height = 5;
  Pedal pedal(top_left_corner, width, height, ci::Color("black"),
              ci::Color("white"), "TEST", "arial");

  SECTION("Position vector completely inside the pedal") {
    glm::dvec2 position(3, 3);
    REQUIRE(pedal.IsInBounds(position));
  }

  SECTION("Position vector on bottom border is in bounds") {
    glm::dvec2 position(3, 0);
    REQUIRE(pedal.IsInBounds(position));
  }

  SECTION("Position vector on top border is in bounds") {
    glm::dvec2 position(3, height);
    REQUIRE(pedal.IsInBounds(position));
  }

  SECTION("Position vector on bottom border is in bounds") {
    glm::dvec2 position(0, 3);
    REQUIRE(pedal.IsInBounds(position));
  }

  SECTION("Position vector on bottom border is in bounds") {
    glm::dvec2 position(width, 3);
    REQUIRE(pedal.IsInBounds(position));
  }

  SECTION("Position vector on corner is in bounds") {
    glm::dvec2 position(0, 0);
    REQUIRE(pedal.IsInBounds(position));
  }

  SECTION("Position vector below bottom border is out of bounds") {
    glm::dvec2 position(3, -1);
    REQUIRE(!pedal.IsInBounds(position));
  }

  SECTION("Position vector above top border out of bounds") {
    glm::dvec2 position(3, height + 1);
    REQUIRE(!pedal.IsInBounds(position));
  }

  SECTION("Position vector to the left of left border out of bounds") {
    glm::dvec2 position(-1, 3);
    REQUIRE(!pedal.IsInBounds(position));
  }

  SECTION("Position vector to the left of left border out of bounds") {
    glm::dvec2 position(width + 1, 3);
    REQUIRE(!pedal.IsInBounds(position));
  }
}