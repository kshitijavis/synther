//
// Created by Kshitij Sinha on 10/31/20.
//
#include <catch2/catch.hpp>

#include "core/particle.h"
#include "core/simulation.h"
#include <vector>

using std::vector;

bool ParticlesApproxEqual(const vector<idealgas::Particle>& first,
                          const vector<idealgas::Particle>& second) {
  for (size_t ind = 0; ind < first.size(); ind++) {
    const glm::vec2& first_pos = first.at(ind).GetPosition();
    const glm::vec2& first_vel = first.at(ind).GetVelocity();
    const glm::vec2& second_pos = second.at(ind).GetPosition();
    const glm::vec2& second_vel = second.at(ind).GetVelocity();
    if (!(Approx(first_pos.x).margin(0.02) == second_pos.x) ||
        !(Approx(first_pos.y).margin(0.02) == second_pos.y) ||
        !(Approx(first_vel.x).margin(0.02) == second_vel.x) ||
        !(Approx(first_vel.y).margin(0.02) == second_vel.y)
        ) {
      return false;
    }
  }
  return true;
}

TEST_CASE("AddParticles correctly appends vector of particles to existing "
    "vector of particles", "[addparticles]") {
  idealgas::Simulation simulation(10,10, 1);

  SECTION("Add single particle to empty simulation") {
    vector<idealgas::Particle> added_particles{
        idealgas::Particle(glm::vec2(3, 2), glm::vec2(2, 1), .5, 1)
    };
    simulation.AddParticles(added_particles);

    vector<idealgas::Particle> simulation_particles = simulation.GetParticles();
    REQUIRE(added_particles == simulation_particles);
  }

  SECTION("Add multiple particles to existing simulation") {
    idealgas::Particle initial_particle =
        idealgas::Particle(glm::vec2(1,1), glm::vec2(3,4), .8, 1);
    simulation.AddParticle(initial_particle);

    vector<idealgas::Particle> added_particles{
        idealgas::Particle(glm::vec2(3, 2), glm::vec2(2, 1), .5, 1),
        idealgas::Particle(glm::vec2(13, 32), glm::vec2(72, 1), 3, 2)
    };
    simulation.AddParticles(added_particles);

    vector<idealgas::Particle> expected_particles{
        idealgas::Particle(glm::vec2(1,1), glm::vec2(3,4), .8, 1),
        idealgas::Particle(glm::vec2(3, 2), glm::vec2(2, 1), .5, 1),
        idealgas::Particle(glm::vec2(13, 32), glm::vec2(72, 1), 3, 2)
    };

    vector<idealgas::Particle> actual_particles = simulation.GetParticles();
    REQUIRE(expected_particles == actual_particles);
  }
}

TEST_CASE("StepForward correctly moves non-colliding particles",
          "[stepforward]") {
  idealgas::Simulation simulation(10,10, 1);

  SECTION("Single particle") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(3, 2), glm::vec2(2, 1), .5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(5, 3), glm::vec2(2, 1), .5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Multiple particles") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(3, 2), glm::vec2(2, 1), .5, 1),
        idealgas::Particle(glm::vec2(5, 2), glm::vec2(1, 1), .5, 1),
        idealgas::Particle(glm::vec2(1, 1), glm::vec2(0, 5), .5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(5, 3), glm::vec2(2, 1), .5, 1),
        idealgas::Particle(glm::vec2(6, 3), glm::vec2(1, 1), .5, 1),
        idealgas::Particle(glm::vec2(1, 6), glm::vec2(0, 5), .5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Boundary: No particles") {
    vector<idealgas::Particle> inputs;
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected;
    REQUIRE(simulation.GetParticles() == expected);
  }
}

TEST_CASE("Step forward correctly 'bounces' particles colliding with the wall",
          "[stepforward][wallcollision]") {
  idealgas::Simulation simulation(10,20, 1);

  SECTION("Single particle whose radius touches bottom wall") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 1), glm::vec2(1, -1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(6, 2), glm::vec2(1, 1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Single particle whose radius touches left wall") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(1, 5), glm::vec2(-1, -1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(2, 4), glm::vec2(1, -1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Single particle whose radius touches top wall") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 19), glm::vec2(-1, 1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(4, 18), glm::vec2(-1, -1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Single particle whose radius touches right wall") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(9, 5), glm::vec2(1, 1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(8, 6), glm::vec2(-1, 1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Particle not touching a wall will NOT be bounced") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 5), glm::vec2(1, 1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(6, 6), glm::vec2(1, 1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Particle touching wall but moving towards the center of the"
          "container will NOT be 'bounced'") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 1), glm::vec2(1, 1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(6, 2), glm::vec2(1, 1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Particle touching a corner should be 'bounced' in both dimensions") {
    vector<idealgas::Particle> inputs{
        // Radius = 1 makes particle touch the wall tangentially
        idealgas::Particle(glm::vec2(2, 2), glm::vec2(-1, -1), 2.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(3, 3), glm::vec2(1, 1), 2.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Boundary case: Radius tangentially touches wall") {
    vector<idealgas::Particle> inputs{
        // Radius = 1 makes particle touch the wall tangentially
        idealgas::Particle(glm::vec2(5, 1), glm::vec2(1, -1), 1, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(6, 2), glm::vec2(1, 1), 1, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Boundary case: Particle outside the container but still touching "
      "a wall") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 21), glm::vec2(1, 1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(6, 20), glm::vec2(1, -1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }

  SECTION("Boundary case: Particle completely outside container should get "
      "'bounced'") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(-5, 5), glm::vec2(-2, 1), 1.5, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(-3, 6), glm::vec2(2, 1), 1.5, 1)
    };
    REQUIRE(simulation.GetParticles() == expected);
  }
}

TEST_CASE("Step forward correctly 'bounces' identical-mass particles colliding "
    "with each other", "[stepforward][particlecollision]") {
  idealgas::Simulation simulation(50,50, 1);

  SECTION("Two particles that are touching and moving towards each other") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(20, 20), glm::vec2(0.1, 0), 1, 1),
        idealgas::Particle(glm::vec2(21.4, 21.4), glm::vec2(-0.1, 0), 1, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(20, 19.9), glm::vec2(0, -0.1), 1, 1),
        idealgas::Particle(glm::vec2(21.4, 21.5), glm::vec2(0, 0.1), 1, 1)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }

  SECTION("Two particles tangentially touching and moving towards each other") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 5), glm::vec2(2, 3), 2.82, 1),
        idealgas::Particle(glm::vec2(7, 7), glm::vec2(-2, -5), 2.82, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(1, 2), glm::vec2(-4, -3), 1, 1),
        idealgas::Particle(glm::vec2(11, 8), glm::vec2(4, 1), 1, 1)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }

  SECTION("Two particles that not touching are NOT bounced") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(19.9, 20), glm::vec2(0.1, 0), 1, 1),
        idealgas::Particle(glm::vec2(21.5, 21.4), glm::vec2(-0.1, 0), 1, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(20, 20), glm::vec2(0.1, 0), 1, 1),
        idealgas::Particle(glm::vec2(21.4, 21.4), glm::vec2(-0.1, 0), 1, 1)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }

  SECTION("Two particles touching but moving away from each other are not "
      "bounced") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(6.5, 6.5), glm::vec2(-1, -1), 1, 1),
        idealgas::Particle(glm::vec2(7, 7), glm::vec2(1, 1), 1, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(5.5, 5.5), glm::vec2(-1, -1), 1, 1),
        idealgas::Particle(glm::vec2(8, 8), glm::vec2(1, 1), 1, 1)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }

  SECTION("Multiple particles in container, with two that should bounce") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(20, 20), glm::vec2(0.1, 0), 1, 1),
        idealgas::Particle(glm::vec2(21.4, 21.4), glm::vec2(-0.1, 0), 1, 1),
        idealgas::Particle(glm::vec2(30,30), glm::vec2(1,2), 1, 1),
        idealgas::Particle(glm::vec2(21,40), glm::vec2(0,0), 1, 1),
        idealgas::Particle(glm::vec2(30,40), glm::vec2(5,5), 1, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(20, 19.9), glm::vec2(0, -0.1), 1, 1),
        idealgas::Particle(glm::vec2(21.4, 21.5), glm::vec2(0, 0.1), 1, 1),
        idealgas::Particle(glm::vec2(31,32), glm::vec2(1,2), 1, 1),
        idealgas::Particle(glm::vec2(21,40), glm::vec2(0,0), 1, 1),
        idealgas::Particle(glm::vec2(35,45), glm::vec2(5,5), 1, 1)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }

  SECTION("Three particles colliding at once") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 5), glm::vec2(2, 3), 3, 1),
        idealgas::Particle(glm::vec2(7, 7), glm::vec2(-2, -5), 3, 1),
        idealgas::Particle(glm::vec2(9, 9), glm::vec2(-2, 0), 3, 1)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2(1, 2), glm::vec2(-4, -3), 3, 1),
        idealgas::Particle(glm::vec2(7.5, 4.5), glm::vec2(0.5, -2.5), 3, 1),
        idealgas::Particle(glm::vec2(10.5, 12.5), glm::vec2(1.5, 3.5), 3, 1)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }
}

TEST_CASE("Step forward correctly 'bounces' different-mass particles colliding "
          "with each other", "[stepforward][particlecollision]") {
  idealgas::Simulation simulation(50,50, 1);

  SECTION("Two particles touching and moving towards each other") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 5), glm::vec2(2, 3), 3, 15),
        idealgas::Particle(glm::vec2(7, 7), glm::vec2(-2, -5), 3, 7)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2((float)35/11, (float)46/11),
                           glm::vec2(-(float)20/11, -(float)9/11),
                           3, 15),
        idealgas::Particle(glm::vec2((float)145/11, (float)112/11),
                           glm::vec2((float)68/11, (float)35/11),
                           3, 7)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }

  SECTION("Three particles colliding at once") {
    vector<idealgas::Particle> inputs{
        idealgas::Particle(glm::vec2(5, 5), glm::vec2(2, 3), 3, 15),
        idealgas::Particle(glm::vec2(7, 7), glm::vec2(-2, -5), 3, 7),
        idealgas::Particle(glm::vec2(9, 9), glm::vec2(-2, 0), 3, 10)
    };
    simulation.AddParticles(inputs);
    simulation.StepForward();

    vector<idealgas::Particle> actual = simulation.GetParticles();
    vector<idealgas::Particle> expected{
        idealgas::Particle(glm::vec2((float)35/11, (float)46/11),
                           glm::vec2(-(float)20/11, -(float)9/11),
                           3, 15),
        idealgas::Particle(glm::vec2((float)1215/187, (float)654/187),
                           glm::vec2(-(float)94/187, -(float)655/187),
                           3, 7),
        idealgas::Particle(glm::vec2((float)2184/187, (float)2558/187),
                           glm::vec2((float)501/187, (float)875/187),
                           3, 10)
    };

    REQUIRE(ParticlesApproxEqual(actual, expected));
  }
}

TEST_CASE("Random Initialization", "[initrandom]") {
  float container_height = 10;
  float container_width = 10;
  size_t num_particles = 25;
  float min_speed = 5;
  float max_speed = 30;
  float min_radius = 2;
  float max_radius = 4;
  float min_mass = 10;
  float max_mass = 50;

  idealgas::Simulation simulation(container_width, container_height, 1);

  simulation.AddRandomParticles(num_particles, min_speed, max_speed, min_radius,
                                max_radius, min_mass, max_mass);

  SECTION("Simulation contains correct number of particles") {
    REQUIRE(simulation.GetParticles().size() == num_particles);
  }

  SECTION("Speeds of all particles are within given range") {
    const vector<idealgas::Particle>& particles = simulation.GetParticles();
    for (const idealgas::Particle& particle : particles) {
      float speed = glm::length(particle.GetVelocity());
      REQUIRE(min_speed <= speed);
      REQUIRE(speed <= max_speed);
    }
  }

  SECTION("Positions of all particles are within container bounds") {
    const vector<idealgas::Particle>& particles = simulation.GetParticles();
    for (const idealgas::Particle& particle : particles) {
      const glm::vec2& position = particle.GetPosition();
      REQUIRE(0 <= position.x);
      REQUIRE(position.x <= container_width);
      REQUIRE(0 <= position.y);
      REQUIRE(position.y <= container_height);
    }
  }

  SECTION("Scalar fields of all particles are within given ranges") {
    const vector<idealgas::Particle>& particles = simulation.GetParticles();
    for (const idealgas::Particle& particle : particles) {
      float radius = particle.GetRadius();
      float mass = particle.GetMass();
      REQUIRE(min_radius <= radius);
      REQUIRE(radius <= max_radius);
      REQUIRE(min_mass <= mass);
      REQUIRE(mass <= max_mass);
    }
  }
}
