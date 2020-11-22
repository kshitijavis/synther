//
// Created by Kshitij Sinha on 11/19/20.
//
#include "visualizer/piano.h"
#include "cinder/Color.h"

#include <catch2/catch.hpp>
#include <iostream>

using synther::visualizer::Piano;

TEST_CASE("Constructor correctly initialize piano keys", "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, ci::Color("white"), 0, 88);
  SECTION("First note is A0") {
  }
}