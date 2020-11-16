//
// Created by Kshitij Sinha on 10/31/20.
//

#ifndef IDEAL_GAS_SIMULATION_H
#define IDEAL_GAS_SIMULATION_H

#include "particle.h"

#include "cinder/gl/gl.h"
#include <vector>

namespace idealgas {

/**
 * An ideal gas simulation that simulates elastic particle collisions inside
 *   a container with fixed volume, pressure, and temperature.
 */
class Simulation {
 public:
  /**
   * Constructs a Simulation object
   * @param time_step the step speed of the simulation (in seconds)
   * @param bottom_left the position of the bottom-left corner of the container
   * @param top_right the position of the top-right corner ot the container
   */
  Simulation(double container_width, double container_height, double time_step);

  /**
   * Adds random particles to the simulation given the following parameters
   * @param num_particles the number of particles initialized in the container
   * @param min_speed the minimum speed of the particles, where speed represents
   *   the magnitude of a particle's velocity
   * @param max_speed the maximum speed of the particles, where speed represents
    *   the magnitude of a particle's velocity
   * @param min_radius the minimum radius of the particles
   * @param max_radius the maximum radius of the particles
   * @param min_mass the minimum mass of the particles
   * @param max_mass the maximum mass of the particles
   * @param color the color of the the particle
 */
  void AddRandomParticles(size_t num_particles, float min_speed,
                          float max_speed, float min_radius, float max_radius,
                          float min_mass, float max_mass,
                          const std::string& color = "black");

  /**
   * Updates the simulation by a single frame, based on the current simulation
   *   step speed
   */
  void StepForward();

  /**
   * Adds a Particle to the simulation
   * @param to_add the Particle to add to the simulation
   */
  void AddParticle(const Particle& to_add);

  /**
   * Adds a vector of Particles to the simulation
   * @param to_add a vector of Particles to add to the simulation
   */
  void AddParticles(const std::vector<Particle>& to_add);

  void GetTimeStep(double time_step);
  double SetTimeStep() const;
  const std::vector<Particle>& GetParticles() const;
 private:
  std::vector<Particle> particles_;
  double container_width_;
  double container_height_;
  double time_step_;

  /**
   * Takes a reference to a particle and updates its velocity if it is
   *   currently colliding with a container wall
   * @param particle a reference to a particle objects who's velocity will
   *   be changed if the particle is colliding with a wall
   */
  void UpdateWallCollision(Particle& particle);

  /**
   * Takes two references to a particle and updates their velocities if it is
   *   they are colliding with each other and moving towards each other
   * @param particle_1 the first particle involved in the collision
   * @param particle_2 the second particle involved in the collision
   */
  void UpdateParticleCollision(Particle& particle_1, Particle& particle_2);
};

} // namespace idealgas

#endif  // IDEAL_GAS_SIMULATION_H
