#include <climits>
//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_PIANO_H
#define SYNTHER_PIANO_H

#include <vector>

#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "core/music_note.h"
#include "visualizer/piano_key.h"

namespace synther {

namespace visualizer {

/**
 * A Piano Keyboard that can be used as a Cinder GUI Component. Can be used
 * the represent a keyboard of any size, using standard western musical notes.
 * Once constructed, a keyboard virtually stores all of its notes as PianoKeys
 * which cannot be changed.
 *
 * The keyboard is visualized using "views". A "view"
 * allows the user to see a subset of the piano keys, which always starts and
 * ends on a white key. The piano position can be altered.
 *
 * The keyboard can also be "played", which temporarily changes the visual
 * behavior of the PianoKey that was played, and allows the client to access the
 * note mapped to the key that was played.
 */
class Piano {
 public:
  /**
   * Constructs a piano for visualization
   * @param top_left_corner the screen coordinates of the top left corner of
   *   the piano
   * @param width the width of the piano in pixels
   * @param height the height of the piano in pixels
   * @param background_color the background color of the piano
   * @param first_semitone the starting note of the piano, specified by its
   *   semitone distance from A0, where A0 has a semitone of 0. It is
   *   recommended that first_semitone represents a whole tone
   * @param key_count the number of keys on the piano
   */
  Piano(const glm::dvec2& top_left_corner, double width, double height,
        int first_semitone, size_t key_count,
        size_t view_whitekey_count = kDefaultViewWhitekeyCount);

  /**
   * Updates the current state of the keyboard and all keys on the keyboard.
   *   Signals the passage of time, allowing piano key colors to reset after
   *   a certain number of calls to Update()
   */
  void Update();

  /**
   * Draws the current view of the keyboard. By default, displays 12 white keys
   *   on the board and all black keys that lie within these bounds. The first
   *   and last keys on the display will always be white keys.
   */
  void Draw() const;

  /**
   * Shifts the view of the keyboard up/down depending on the input parameter
   * @param displacement an integer representing the distance to shift the
   *   keyboard view. The magnitude of the input represents the number of white
   *   keys by which the view will shift.
   *   A negative input will shift the view down and a positive input will
   *   shift the view up.
   */
  void ShiftView(int displacement);

  /**
   * "Plays a key" on the keyboard. Handles a ci::app::KeyEvent and "plays"
   *   the Piano Key corresponding to the KeyEvent. Calling this method will
   *   temporarily change the color of the key that was played and returns the
   *   note corresponding the to played key
   * @param key_code a ci::app::KeyEvent code that is bound to a Piano Key on
   *   the keyboard. Throws an exception if key_event does not have a keybind
   *   or if key_event is not a ci::app::KeyEvent
   * @return a const reference to a music::Note mapped to the key that
   *   was played
   */
  const music::Note& PlayKey(int key_code);

  /**
   * Checks if the input key_code represents a valid keybind on the piano. In
   *   other words, checks if the KeyEvent corresponding to the key_code is
   *   mapped to any PianoKey on the keyboard
   * @param key_code an int representing ci::app::KeyEvent code
   * @return true if the input key_code is a valid keybind
   */
  bool IsKeybind(int key_code) const;

  /**
   * Get the PianoKey at the specified index
   * @param index the index of the piano key, where the first key has an index
   *   of 0. Input must be between 0 (inclusive) and key_count (exclusive)
   * @return a PianoKey reference to the piano key at the index
   */
  const PianoKey& GetPianoKey(int index) const;

  /**
   * Get the number of keys on this piano
   * @return the key count of the piano
   */
  const size_t GetKeyCount() const;

 private:
  // Visualization
  glm::dvec2 top_left_corner_;
  double width_;
  double height_;
  __unused ci::Color background_color_;
  static constexpr double kBlackKeyHeightFactor = 0.6;
  static constexpr double kBlackKeyWidthFactor = 0.4;

  // PianoKeys
  int first_semitone_;
  std::vector<PianoKey> keys_;
  const music::Accidental kPriority = music::Accidental::Sharp;

  // View window
  int view_first_;
  size_t view_whitekey_count_;
  static constexpr int kDefaultViewWhitekeyCount = 20;

  // Keybinds
  struct KeyEvent {
    int key_code_;
    char key_char_;
  };
  std::map<int, PianoKey*> keybinds_;
  static const std::vector<KeyEvent> kBlackKeyCodes;
  static const std::vector<KeyEvent> kWhiteKeyCodes;

  // Helper methods
  /**
   * Counts the number of natural notes/white keys on the keyboard
   * @return a size_t representing the number of natural notes on the keyboard
   */
  const size_t CountNaturals() const;

  /**
   * Maps keys on the piano to cinder KeyEvents. Uses the first row of the
   *   keyboard (QWERTY..) for black keys and the second row (ASDF...) for
   *   white keys. Adds keybinds to the private field keybinds_. Maps keys
   *   using the natural staggered layout of te computer keyboard. This allows
   *   keybinds to lie between white keybinds, just as they would on a physical
   *   piano.
   */
  void SetKeyBinds();

  /**
   * For every key on the keyboard, sets the label of the key to its
   *   corresponding KeyEvent, which is stored in keybinds_. If the key does
   *   not have a keybind, sets the label to an empty char
   */
  void SetKeyLabels();
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PIANO_H
