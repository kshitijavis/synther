//
// Created by Kshitij Sinha on 10/31/20.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"

namespace idealgas {

/**
 * An ideal gas particle, with a fixed radius and mass. A gas particle has
 *   a position and velocity and has the ability to change its position based
 *   on its velocity
 */
class Particle {
 public:
  /**
   * Construct a Particle object given the following parameters
   * @param position the 2D position of the particle
   * @param velocity the 2D velocity of the particle
   * @param radius the distance from the center of the particle to its edge
   * @param mass the mass of the particle
   * @param color the color of the particle
   */
  Particle(const glm::vec2& position, const glm::vec2& velocity, float radius, float mass,
           const std::string& color = "black");

  /**
   * Updates the position of the particle based on the current velocity and
   *   a specified time interval. Uses the formula (ds = v * dt)
   * @param time_step the amount of time for which the particle will move
   */
  void Move(double time_step);

  /**
   * Checks if two Particles are equal
   *
   * Two Particles are equal if their positions, velocities, radii, and mass
   * are the same
   *
   * @param rhs the Particle to compare to
   */
  bool operator==(const Particle& rhs) const;

  /**
   * Computes and returns the speed of the particle, where speed is the
   *   magnitude of the particle's velocity
   * @return the speed of the particle
   */
  double GetSpeed() const;

  void SetVelocity(const glm::vec2& new_velocity);

  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  float GetRadius() const;
  float GetMass() const;
  std::string GetColor() const;
 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  float radius_;
  float mass_;
  std::string color_;
};

} // namespace idealgas


#endif //IDEAL_GAS_PARTICLE_H
