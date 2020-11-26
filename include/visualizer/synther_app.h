#pragma once

#include <string>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"

#include "visualizer/piano.h"

namespace synther {

namespace visualizer {

/**
 * Allows a user to to visualize and interact with an ideal gas simulation.
 */
class SyntherApp : public ci::app::App {
 public:
  SyntherApp();

  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
  void keyUp(ci::app::KeyEvent event) override;

 private:
  // Window & Element positioning
  const double kWindowHeight = 700;
  const double kWindowWidth = 1100;
  const double kSidePadding = 30;
  const double kTopPadding = 30;

  // Appearance
  const std::string kBackgroundColor = "brown";

  // Piano
  Piano piano_;
  static constexpr double kPianoHeight = 300;
  static constexpr int kFirstSemitoneIndex = 0;
  static constexpr size_t kKeyCount = 88;
  static constexpr size_t kViewWhitekeyCount = 15;

  // Voice handling
  ci::audio::VoiceRef v1;
  ci::audio::VoiceRef v2;

  // Voice processing

};

}  // namespace visualizer

}  // namespace synther
