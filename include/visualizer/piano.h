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
   * @param first_semitone the starting note of the piano, specified by its
   *   semitone distance from A0, where A0 has a semitone of 0. It is
   *   recommended that first_semitone represents a whole tone
   * @param key_count the number of keys on the piano
   * @param view_whitekey_count the number of white keys to display on the
   *   piano when Draw() is called
   */
  Piano(const glm::dvec2& top_left_corner, double width, double height,
        int first_semitone, size_t key_count,
        size_t view_whitekey_count = 20);

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
   * Get the music::Note mapped to a key_code on the piano
   * @param key_code a ci::app::KeyEvent code that is bound to a Piano Key on
   *   the keyboard. Throws an exception if key_event does not have a keybind
   *   or if key_event is not a valid ci::app::KeyEvent code
   * @return a const reference to a music::Note mapped to the given key
   */
  const music::Note& GetNote(int key_code);

  /**
   * "Plays a key" on the keyboard. Handles a ci::app::KeyEvent and "plays"
   *   the Piano Key corresponding to the KeyEvent. Calling this method will
   *   temporarily change the color of the key that was played and returns the
   *   note corresponding the to played key. The color of the key will remain
   *   changed until release_key is called
   * @param key_code a ci::app::KeyEvent code that is bound to a Piano Key on
   *   the keyboard. Throws an exception if key_event does not have a keybind
   *   or if key_event is not a valid ci::app::KeyEvent code
   */
  void PressKey(int key_code);

  /**
   * Releases a pressed key on the keyboard. This will reset the color of the
   *   key to the standard color (black or white)
   * @param key_code a ci::ap::KeyEvent code that is bound to a Piano Key on
   *   the keyboard. Throws and exception if key_event does not have a keybind
   *   or if key_bind is not a valid ci::app::KeyEvent code
   */
  void ReleaseKey(int key_code);

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
  static constexpr double kTopPaddingFactor = 0.1;
  static constexpr double kBlackKeyHeightFactor = 0.6;
  static constexpr double kBlackKeyWidthFactor = 0.4;

  const ci::Color kBackgroundColor = ci::Color("gray");
  const ci::Color kOutlineColor = ci::Color("white");
  const std::string kFontName = "ToppanBunkyuGothicPr6N-DB";

  // PianoKeys
  int first_semitone_;
  std::vector<PianoKey> keys_;
  const music::Accidental kPriority = music::Accidental::Sharp;
  char kOctaveMarkerLetter = 'C';

  // View window
  int view_first_;
  size_t view_whitekey_count_;

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
   * Get the music::Note mapped to a key_code on the piano
   * @param key_code a ci::app::KeyEvent code that is bound to a Piano Key on
   *   the keyboard. Throws an exception if key_event does not have a keybind
   *   or if key_event is not a valid ci::app::KeyEvent code
   * @return a const reference to a music::Note mapped to the given key
   */
  PianoKey& GetKey(int key_code);

  /**
   * For every key on the keyboard, sets the label of the key to its
   *   corresponding KeyEvent, which is stored in keybinds_. If the key does
   *   not have a keybind, sets the label to an empty char
   */
  void SetKeyLabels();

  /**
   * Draws all the PianoKeys in the current view
   * @param top_left_corner a vector representing the top left corner of the
   *   leftmost key
   * @param width the width of the keyboard
   * @param height the height of the keyboard
   */
  void DrawKeys(const glm::dvec2& top_left_corner, double width,
                double height) const;

  /**
   * Draws all the PianoKeys in the current view
   * @param the top left corner of the keyboard
   * @param the width of the entire marker drawing location
   * @param the height of the entire marker drawing location
   */
  void DrawOctaveMarkers(const glm::dvec2& top_left_corner, double width,
                         double height) const;
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PIANO_H
