#pragma once

#include <visualizer/histogram.h>

#include <string>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/simulation.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to to visualize and interact with an ideal gas simulation.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

 private:
  // Window & Element positioning
  const double kWindowHeight = 700;
  const double kWindowWidth = 1100;
  const double kLeftMargin = 50;
  const double kTopBottomMargin = 50;

  const double kContainerWidth = 600;
  const double kContainerRightPadding = 25;
  const double kHistogramWidth = 375;
  const double kHistogramPadding = 25;

  // Initialization configurations
  /*
   * Every particle class represented by tuple
   * Tuple structure: number of particles, mass, radius, color
   */
  const std::vector<std::tuple<size_t, float, float, std::string>>
      kParticleClasses{{75, 25, 5, "mediumblue"},
                       {75, 50, 10, "darkgreen"},
                       {75, 75, 15, "firebrick"}};
  const float kMinSpeed = 2;
  const float kMaxSpeed = 3;

  // Simulation setup
  const double kDefaultTimeStep = 1;
  Simulation simulation_;

  // Histogram setup
  std::map<float, Histogram> mass_to_histogram_;
  const size_t kDefaultBinCount = 12;
  const double kDefaultRangeWidening = 1.2;
  const std::string kTitleTemplate = "Mass = ";
  const std::string kXLabel = "Particle Speed";
  const std::string kYLabel = "Number of Particles";

  // User input configurations
  const float kAddVelocity = 25;
  const double kSpeedChangeFactor = 1.5;

  /**
   * Draws the a box containing representing the simulation container.
   *   Draws the walls and particles of the simulation
   */
  void DrawContainer();

  /**
   * Draws a histogram for every stored particle class
   */
  void DrawHistograms();
};

}  // namespace visualizer

}  // namespace idealgas
