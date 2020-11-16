//
// Created by Kshitij Sinha on 10/31/20.
//

#include "core/particle.h"

#include "cinder/gl/gl.h"

namespace idealgas {
Particle::Particle(const glm::vec2& position, const glm::vec2& velocity,
                   float radius, float mass, const std::string& color)
    : position_(position),
      velocity_(velocity),
      radius_(radius),
      mass_(mass),
      color_(color) {
}

void Particle::Move(double time_step) {
  position_ += (velocity_ * static_cast<float>(time_step));
}

bool Particle::operator==(const Particle& rhs) const {
  return position_ == rhs.position_ && velocity_ == rhs.velocity_ &&
         radius_ == rhs.radius_ && mass_ == rhs.mass_;
}

double Particle::GetSpeed() const {
  return glm::length(velocity_);
}

void Particle::SetVelocity(const glm::vec2& new_velocity) {
  velocity_ = new_velocity;
}

const glm::vec2& Particle::GetPosition() const {
  return position_;
}

const glm::vec2& Particle::GetVelocity() const {
  return velocity_;
}

float Particle::GetRadius() const {
  return radius_;
}

float Particle::GetMass() const {
  return mass_;
}

std::string Particle::GetColor() const {
  return color_;
}

}  // namespace idealgas
