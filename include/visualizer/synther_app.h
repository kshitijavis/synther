#pragma once

#include <string>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "visualizer/piano.h"
#include "core/player.h"

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
  const std::string kBackgroundColor = "black";
  const std::string kFontName = "Futura-Bold";

  // Instrument text
  const double kInstrumentTextHeight = 50;
  const double kInstrumentTextPadding = 30;
  const std::string kInstrumentTextColor = "white";

  // Piano
  Piano piano_;
  static constexpr double kPianoHeight = 400;
  static constexpr int kFirstSemitoneIndex = 0;
  static constexpr size_t kKeyCount = 88;
  static constexpr size_t kViewWhitekeyCount = 10;
  static constexpr int kWholetoneDistance = 1;
  static constexpr int kOctaveDistance = 7;

  // Audio
  const std::string kDefaultSoundPath = "sounds/piano/";
  const std::string kJsonFilename = "details.json";
  std::string instrument_;
  audio::Player player_;

  // Helper methods
  void SetupInstrument(const std::string& asset_directory);
};

}  // namespace visualizer

}  // namespace synther
