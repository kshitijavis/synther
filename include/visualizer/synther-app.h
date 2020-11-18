#pragma once

#include <string>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to to visualize and interact with an ideal gas simulation.
 */
class SynterApp : public ci::app::App {
 public:
  SynterApp();

  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

 private:
  // Window & Element positioning
  const double kWindowHeight = 700;
  const double kWindowWidth = 1100;

  // Voice handling
  ci::audio::VoiceRef v1;
  ci::audio::VoiceRef v2;

  // Voice processing

};

}  // namespace visualizer

}  // namespace idealgas
