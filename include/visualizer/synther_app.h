#pragma once

#include <string>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/piano_keybinder.h"
#include "core/player.h"
#include "visualizer/pedal.h"
#include "visualizer/piano.h"

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
  static constexpr double kWindowHeight = 700;
  static constexpr double kWindowWidth = 1100;
  static constexpr double kSidePadding = 30;
  static constexpr double kTopPadding = 50;
  static constexpr double kBottomPadding = 25;
  static constexpr double kInstrumentTextPadding = 0;
  static constexpr double kInstrumentTextHeight = 100;
  static constexpr double kPianoHeight = 450;
  static constexpr double kPedalHeight = 50;
  static constexpr double kPedalWidth = 200;

  // Appearance
  const std::string kBackgroundColor = "black";
  const std::string kMainFontName = "ToppanBunkyuGothicPr6N-DB";
  const std::string kInstrumentFontName = "SignPainter-HouseScript";

  // Metallic gold
  const ci::Color kInstrumentTextColor = ci::Color::hex(0xD4AF37);

  // Piano
  Piano piano_;
  PianoKeybinder keybinder_;
  static constexpr int kFirstSemitoneIndex = 9;
  static constexpr size_t kKeyCount = 88;
  static constexpr size_t kViewWhitekeyCount = 10;

  // Constants to specify how much to move the keyboard on ShiftView()
  static constexpr int kWholetoneDistance = 1;
  static constexpr int kOctaveDistance = 7;

  // Pedals
  Pedal sustain_pedal_;
  const std::string kSustainPedalLabel = "Sustain";
  const std::string kPedalPrimaryColor = "gold";
  const std::string kPedalSecondaryColor = "black";

  // Audio
  std::string instrument_;
  audio::Player player_;
  const std::string kDefaultSoundJson = "sounds/piano/";
  const std::string kJsonFilename = "details.json";
  static constexpr double kStandardResonation = 0.4;
  static constexpr double kSustainedResonation = 5.0;

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
   * Shifts the view window of the piano and updates keybinds accordingly
   * @param displacement an integer representing the distance to shift the
   *   keyboard view. The magnitude of the input represents the number of white
   *   keys by which the view will shift.
   *   A negative input will shift the view downwards and a positive input will
   *   shift the view upwards.
   */
  void HandleShiftView(int displacement);

  /**
   * Updates the state of the app to reflect a change in instrument
   * @param asset_directory the directory containing the instrument's sound
   *   files. The directory must contain a details.json file with information
   *   about the authors and note names of the sound files
   */
  void SetupInstrument(const std::string& asset_directory);

  /**
   * Toggles the resonate duration of the player. If duration is currently set
   *   to standard, switches to sustained, and vice versa.
   */
  void ToggleSustainPedal();

  /**
   * Sets keybinds based on the state of the piano's current view. Uses
   *   updated keybinds to set corresponding labels on the piano
   */
  void UpdateKeybindsAndLabels();
};

}  // namespace visualizer

}  // namespace synther
