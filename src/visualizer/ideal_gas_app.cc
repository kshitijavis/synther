#include <cinder/Rand.h>
#include <visualizer/ideal_gas_app.h>

#include <fstream>
#include <vector>

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : simulation_(kContainerWidth, kWindowHeight - 2 * kTopBottomMargin,
                  kDefaultTimeStep) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void IdealGasApp::setup() {
  // Set up simulations
  for (const auto& particle_class : kParticleClasses) {
    size_t num_particles = std::get<0>(particle_class);
    float mass = std::get<1>(particle_class);
    float radius = std::get<2>(particle_class);
    const std::string& color = std::get<3>(particle_class);

    simulation_.AddRandomParticles(num_particles, kMinSpeed, kMaxSpeed, radius,
                                   radius, mass, mass, color);
  }

  // Create histograms
  double hist_group_height = (kWindowHeight - 2 * kTopBottomMargin);
  size_t hist_count = kParticleClasses.size();
  double hist_height =
      (hist_group_height - kHistogramPadding * (hist_count - 1)) / hist_count;
  double hist_left_edge =
      kLeftMargin + kContainerWidth + kContainerRightPadding;
  double hist_top_edge = kTopBottomMargin;

  for (const auto& particle_class : kParticleClasses) {
    float mass = std::get<1>(particle_class);
    std::string title = kTitleTemplate + std::to_string(mass);
    mass_to_histogram_.emplace(
        mass, Histogram(glm::vec2(hist_left_edge, hist_top_edge), hist_height,
                        kHistogramWidth, kDefaultBinCount,
                        kDefaultRangeWidening, title, kXLabel, kYLabel));
    hist_top_edge += hist_height + kHistogramPadding;
  }
}

void IdealGasApp::update() {
  simulation_.StepForward();
}

void IdealGasApp::draw() {
  ci::Color8u background_color(ci::Color("darkgreen"));
  ci::gl::clear(background_color);

  ci::gl::drawStringCentered(
      "Seconds passed per frame: " + std::to_string(simulation_.SetTimeStep()),
      glm::vec2(kWindowWidth / 2, kTopBottomMargin / 2), ci::Color("white"),
      ci::Font("Arial", 18.0f));

  DrawContainer();
  DrawHistograms();
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
  glm::vec2 velocity(kAddVelocity, kAddVelocity);
  glm::vec2 position =
      event.getPos() - glm::ivec2(kLeftMargin, kTopBottomMargin);
  idealgas::Particle particle(position, velocity, 10, 10);
  simulation_.AddParticle(particle);
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      simulation_.GetTimeStep(simulation_.SetTimeStep() * kSpeedChangeFactor);
      break;

    case ci::app::KeyEvent::KEY_DOWN:
      simulation_.GetTimeStep(simulation_.SetTimeStep() / kSpeedChangeFactor);
      break;
  }
}

void IdealGasApp::DrawContainer() {
  glm::vec2 container_top_left(kLeftMargin, kTopBottomMargin);
  glm::vec2 container_bottom_right(kLeftMargin + kContainerWidth,
                                   kWindowHeight - kTopBottomMargin);
  ci::Rectf container_bounds(container_top_left, container_bottom_right);

  ci::gl::color(ci::Color("silver"));
  ci::gl::drawSolidRect(container_bounds);
  ci::gl::color(ci::Color("darkslategray"));
  ci::gl::drawStrokedRect(container_bounds);

  const std::vector<idealgas::Particle>& particles = simulation_.GetParticles();
  for (const idealgas::Particle& particle : particles) {
    ci::gl::color(
        ci::Color(particle.GetColor().c_str()));  // Get particle color

    glm::vec2 center = particle.GetPosition() + container_top_left;
    ci::gl::drawSolidCircle(center, particle.GetRadius());
  }
}

void IdealGasApp::DrawHistograms() {
  const std::vector<idealgas::Particle>& particles = simulation_.GetParticles();
  for (const auto& hist_pair : mass_to_histogram_) {
    float mass = hist_pair.first;

    std::vector<double> speeds;
    for (const Particle& particle : particles) {
      if (particle.GetMass() == mass) {
        speeds.push_back(particle.GetSpeed());
      }
    }

    hist_pair.second.Draw(speeds);
  }
}

}  // namespace visualizer

}  // namespace idealgas
