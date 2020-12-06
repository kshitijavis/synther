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

  /**
   * Sets up the application to its default state
   */
  void setup() override;

  /**
   * Updates the state of the application
   */
  void update() override;

  /**
   * Draws all the components of the app on a window on the computer screen
   */
  void draw() override;

  /**
   * Handle event when the mouse is pressed down
   * @param event a MouseEvent representing the state of the mouse
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /**
   * Handle event when a key on the keyboard is pressed down
   * @param event a KeyEvent representing the pressed Key
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Handle event when a key on the keyboard is released
   * @param event event a KeyEvent representing the released Key
   */
  void keyUp(ci::app::KeyEvent event) override;

 private:
  // Window & Element positioning
  const double kWindowHeight = 700;
  const double kWindowWidth = 1100;
  const double kSidePadding = 30;
  const double kTopPadding = 50;

  // Appearance
  const std::string kBackgroundColor = "black";
  const std::string kFontName = "SignPainter-HouseScript";

  // Instrument text
  const double kInstrumentTextHeight = 80;
  const double kInstrumentTextPadding = 30;
  // Metallic gold
  const ci::Color kInstrumentTextColor = ci::Color::hex(0xD4AF37);

  // Piano
  Piano piano_;
  static constexpr double kPianoHeight = 400;
  static constexpr int kFirstSemitoneIndex = 9;
  static constexpr size_t kKeyCount = 88;
  static constexpr size_t kViewWhitekeyCount = 10;

  // Constants to specify how much to move the keyboard on ShiftView()
  static constexpr int kWholetoneDistance = 1;
  static constexpr int kOctaveDistance = 7;

  // Audio
  const std::string kDefaultSoundJson = "sounds/piano/";
  const std::string kJsonFilename = "details.json";
  std::string instrument_;
  audio::Player player_;
  static constexpr double kStandardResonation = 0.4;

  // Helper methods
  /**
   * Prompts the user to select a directory and returns the relative path
   *   to that directory from the assets/ folder. Opens the file explorer in
   *   assets/sounds/
   * @return a relative path from the assets/ directory to the user's selected
   *   directory
   */
  std::string RequestInstrumentDirectory();

  /**
   * Updates the state of the app to reflect a change in instrument
   * @param asset_directory the directory containing the instrument's sound
   *   files. The directory must contain a details.json file with information
   *   about the authors and note names of the sound files
   */
  void SetupInstrument(const std::string& asset_directory);
};

}  // namespace visualizer

}  // namespace synther
