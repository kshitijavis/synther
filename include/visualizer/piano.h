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
 * to represent a keyboard of any size, using standard western musical notes.
 * Once constructed, a keyboard virtually stores all of its notes as PianoKeys,
 * which cannot be changed.
 *
 * The keyboard is visualized using "views". A view allows the user to see a
 * subset of the piano keys, which always starts and ends on a white key.
 * The view position can be altered using public methods.
 *
 * The keyboard can also be "played", which temporarily changes the visual
 * behavior of the PianoKey that was played, and allows the client to access the
 * note mapped to the key that was played.
 */
class Piano {
 public:
  /**
   * Constructs an empty piano for visualization. On construction, the
   *   piano does not have any keys. SetKeys() must be called to initialize
   *   the set of keys
   * @param top_left_corner the screen coordinates of the top left corner of
   *   the piano, in pixels
   * @param width the width of the piano in pixels
   * @param height the height of the piano in pixels
   */
  Piano(const glm::dvec2& top_left_corner, double width, double height);

  /**
   * Constructs a filled piano for visualization. This constructor sets up
   *   the piano keys on construction
   * @param top_left_corner the screen coordinates of the top left corner of
   *   the piano, in pixels
   * @param width the width of the piano in pixels
   * @param height the height of the piano in pixels
   * @param first_semitone the starting note of the piano, specified by its
   *   semitone distance from C0, where C0 has a semitone of 0.
   *   It is recommended that first_semitone represents a white key
   * @param key_count the number of keys on the piano
   * @param view_whitekey_count the number of white keys to display on the
   *   piano when Draw() is called
   */
  Piano(const glm::dvec2& top_left_corner, double width, double height,
        int first_semitone, size_t key_count, size_t view_whitekey_count = 20);

  /**
   * Draws the current view of the keyboard. By default, displays 12 white keys
   *   on the board and all black keys that lie within these bounds. The first
   *   and last keys on the display will always be white keys.
   */
  void Draw() const;

  /**
   * Sets the size and position of the entire virtual piano given the following
   *   parameters
   * @param first_semitone the starting note of the piano, specified by
   *   its semitone distance from C0, where C0 has a semitone of 0. It is
   *   recommended that first_semitone represents a white key
   * @param key_count the number of keys on the piano
   * @param view_whitekey_count the number of white keys to display on the
   *   piano when Draw() is called
   */
  void SetKeys(int first_semitone, size_t key_count,
               size_t view_whitekey_count = 20);

  /**
   * Shifts the view of the keyboard up/down depending on the input parameter
   * @param displacement an integer representing the distance to shift the
   *   keyboard view. The magnitude of the input represents the number of white
   *   keys by which the view will shift.
   *   A negative input will shift the view downwards and a positive input will
   *   shift the view upwards.
   */
  void ShiftView(int displacement);

  /**
   * Sets the labels of the keys on the keyboard. Given a map of music notes to
   *   strings
   * @param note_labels a map of music notes to strings. Every Piano Key
   *   corresponding to a music note will be given a label (given by the map
   *   values)
   */
  void SetKeyLabels(const std::map<music::Note, std::string>& note_labels);

  /**
   * Sets the labels of the keys on the keyboard. Given a map of music notes to
   *   characters
   * @param note_labels a map of music notes to characters. Every Piano Key
   *   corresponding to a music note will be given a label (given by the map
   *   values)
   */
  void SetKeyLabels(const std::map<music::Note, char>& note_labels);

  /**
   * "Plays a key" on the keyboard. corresponding to a given music::Note.
   *   Calling this method will temporarily change the color of the key that
   *   was played. The color of the key will remain changed until release_key is
   *   called
   * @param note a music::Note whose corresponding piano key will be pressed.
   *   Throws an exception if there is no Key mapped to the note.
   */
  void PressKey(const music::Note& note);

  /**
   * Releases a pressed key on the keyboard. This will reset the color of the
   *   key to the standard color (black or white)
   * @param note a music::Note whose corresponding piano key will be released.
   *   Throws an exception if there is no Key mapped to the note.
   */
  void ReleaseKey(const music::Note& note);

  /**
   * Returns a Piano Key corresponding to a given music::Note. Uses the
   *   semitone index of the given note to search for the corresponding key in
   *   constant O(1) time.
   * @param note a music::Note whose corresponding piano key will be pressed.
   *   Throws an exception if there is no Key mapped to the note.
   */
  PianoKey& GetPianoKey(const music::Note& note);

  /**
   * Get the PianoKey at the specified index
   * @param index the index of the piano key, where the first key has an index
   *   of 0. Input must be between 0 (inclusive) and key_count (exclusive)
   * @return a PianoKey reference to the piano key at the index
   */
  const PianoKey& GetPianoKey(int index) const;

  /**
   * Gets a vector of all the PianoKeys that will be rendered when Draw() is
   *   called
   * @return a vector of all the PianoKeys in the current keyboard view
   */
  std::vector<PianoKey> GetPianoKeysInView() const;

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

  static const std::string kBackgroundColor;
  static const std::string kOutlineColor;
  static const std::string kOctaveMarkerColor;
  static const std::string kFontName;

  // PianoKeys
  int first_semitone_;
  std::vector<PianoKey> keys_;
  static const music::Accidental kPriority = music::Accidental::Sharp;
  char kOctaveMarkerLetter = 'C';
  static constexpr double kOctaveMakerSizeFactor = 0.7;

  // View window
  int view_first_index_;
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
  const size_t CountWhiteKeys() const;

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
