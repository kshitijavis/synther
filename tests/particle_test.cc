//
// Created by Kshitij Sinha on 10/31/20.
//

#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"

#include "core/particle.h"

TEST_CASE("Particle Move", "[move]") {
  glm::vec2 position(0,1);
  glm::vec2 velocity(2,3);
  idealgas::Particle particle(position, velocity, 1, 1);

  SECTION("Move default unit of time (1 second)") {
    particle.Move(1);
    REQUIRE(particle.GetPosition() == glm::vec2(2, 4));
  }

  SECTION("Move larger unit of time") {
    particle.Move(100);
    REQUIRE(particle.GetPosition() == glm::vec2(200, 301));
  }

  SECTION("Move fractional unit of time") {
    particle.Move(0.5);
    REQUIRE(particle.GetPosition() == glm::vec2(1, 2.5));
  }

  SECTION("Boundary: Move for no time") {
    particle.Move(0);
    REQUIRE(particle.GetPosition() == glm::vec2(0,1));
  }

  SECTION("Sanity check: Does not affect vectors used to create particle") {
    particle.Move(1);
    REQUIRE(position == glm::vec2(0,1));
    REQUIRE(velocity == glm::vec2(2,3));
  }
}

TEST_CASE("== Operator", "[operator==]") {
  SECTION("Particles with all equal fields are equal") {
    idealgas::Particle first(glm::vec2(0,1), glm::vec2(1, 2), 2, 3);
    idealgas::Particle second(glm::vec2(0,1), glm::vec2(1, 2), 2, 3);

    REQUIRE(first == second);
  }

  SECTION("Particles with some different fields are not equal") {
    idealgas::Particle first(glm::vec2(1,1), glm::vec2(3, 2), 2, 3);
    idealgas::Particle second(glm::vec2(0,1), glm::vec2(1, 2), 2, 3);

    REQUIRE(!(first == second));
  }

  SECTION("Particles with all different fields are not equal") {
    idealgas::Particle first(glm::vec2(4,2), glm::vec2(9, 0), 1, .5);
    idealgas::Particle second(glm::vec2(0,1), glm::vec2(1, 2), 2, 3);

    REQUIRE(!(first == second));
  }
}

TEST_CASE("GetSpeed", "[getspeed]") {
  SECTION("Particle with no speed") {
    idealgas::Particle particle(glm::vec2(1, 1), glm::vec2(0, 0), 1, 1);
    REQUIRE(particle.GetSpeed() == 0);
  }

  SECTION("Particle with positive speed, where velocity components are equal") {
    idealgas::Particle particle(glm::vec2(1, 1), glm::vec2(5, 5), 1, 1);
    REQUIRE(particle.GetSpeed() == Approx(sqrt(50)).epsilon(0.001));
  }

  SECTION("Particle with positive speed, where velocity components are not "
      "equal") {
    idealgas::Particle particle(glm::vec2(1, 1), glm::vec2(12, 5), 1, 1);
    REQUIRE(particle.GetSpeed() == Approx(13).epsilon(0.01));
  }
}
