//
// Created by Kshitij Sinha on 10/31/20.
//

#include "core/simulation.h"

#include <cinder/Rand.h>

namespace idealgas {

Simulation::Simulation(double container_width, double container_height,
                       double time_step)
    : container_width_(container_width),
      container_height_(container_height),
      time_step_(time_step) {
}

void Simulation::AddRandomParticles(size_t num_particles, float min_speed,
                                    float max_speed, float min_radius,
                                    float max_radius, float min_mass,
                                    float max_mass, const std::string& color) {
  float min_velocity = min_speed / sqrt(2);
  float max_velocity = max_speed / sqrt(2);

  for (size_t particle = 0; particle < num_particles; particle++) {
    // Generate random numbers
    glm::vec2 rand_position(ci::randFloat(0, container_width_),
                            ci::randFloat(0, container_height_));
    glm::vec2 rand_velocity(ci::randFloat(min_velocity, max_velocity),
                            ci::randFloat(min_velocity, max_velocity));
    float rand_radius = ci::randFloat(min_radius, max_radius);
    float rand_mass = ci::randFloat(min_mass, max_mass);

    particles_.emplace_back(rand_position, rand_velocity, rand_radius,
                            rand_mass, color);
  }
}

void Simulation::StepForward() {
  for (size_t first = 0; first < particles_.size(); first++) {
    Particle& particle = particles_.at(first);

    for (size_t second = first + 1; second < particles_.size(); second++) {
      UpdateParticleCollision(particle, particles_.at(second));
    }
    UpdateWallCollision(particle);
    particle.Move(time_step_);
  }
}

void Simulation::AddParticle(const idealgas::Particle& to_add) {
  particles_.push_back(to_add);
}

void Simulation::AddParticles(const std::vector<Particle>& to_add) {
  particles_.insert(std::end(particles_), std::begin(to_add), std::end(to_add));
}

void Simulation::UpdateWallCollision(Particle& particle) {
  const glm::vec2& position = particle.GetPosition();
  const glm::vec2& velocity = particle.GetVelocity();
  double radius = particle.GetRadius();

  if ((position.x - radius <= 0 && velocity.x < 0) ||
      (position.x + radius >= container_width_ && velocity.x > 0)) {
    glm::vec2 negated_velocity(velocity.x * -1, velocity.y);
    particle.SetVelocity(negated_velocity);
  }
  if ((position.y - radius <= 0 && velocity.y < 0) ||
      (position.y + radius >= container_height_ && velocity.y > 0)) {
    glm::vec2 negated_velocity(velocity.x, velocity.y * -1);
    particle.SetVelocity(negated_velocity);
  }
}

void Simulation::UpdateParticleCollision(Particle& particle_1,
                                         Particle& particle_2) {
  // Get necessary variables
  const glm::vec2& v1 = particle_1.GetVelocity();
  const glm::vec2& v2 = particle_2.GetVelocity();
  const glm::vec2& x1 = particle_1.GetPosition();
  const glm::vec2& x2 = particle_2.GetPosition();
  float m1 = particle_1.GetMass();
  float m2 = particle_2.GetMass();

  // Check conditions for colliding
  bool touching = glm::distance(x1, x2) <=
                  (particle_1.GetRadius() + particle_2.GetRadius());
  bool getting_closer = glm::dot(v1 - v2, x1 - x2) < 0;
  if (!touching || !getting_closer) {
    return;
  }

  // Calculate new velocities
  float const_factor =
      glm::dot(v1 - v2, x1 - x2) / pow(glm::distance(x1, x2), 2);
  auto sm1 = (2 * m2 / (m1 + m2));
  auto sm2 = (2 * m1 / (m1 + m2));
  glm::vec2 new_v1 = v1 - sm1 * (const_factor * (x1 - x2));
  glm::vec2 new_v2 = v2 - sm2 * (const_factor * (x2 - x1));

  particle_1.SetVelocity(new_v1);
  particle_2.SetVelocity(new_v2);
}

void Simulation::GetTimeStep(double time_step) {
  time_step_ = time_step;
}

double Simulation::SetTimeStep() const {
  return time_step_;
}

const std::vector<Particle>& Simulation::GetParticles() const {
  return particles_;
}

}  // namespace idealgas
