//
// Created by Kshitij Sinha on 11/19/20.
//

#ifndef SYNTHER_PIANO_KEY_H
#define SYNTHER_PIANO_KEY_H

#include "cinder/Color.h"
#include "core/music_note.h"

namespace synther {

namespace visualizer {

enum class PianoKeyType { Black, White };

/**
 * Represents a single PianoKey, which acts as a Cinder GUI component. Every
 * key stores its corresponding note, PianoKeyType, and label (used during
 * drawing).
 */
class PianoKey {
 public:
  PianoKey(const music::Note& note, const PianoKeyType& type, char label = ' ');

  /**
   * Draws a Key in the Cinder application.
   * @param top_left_corner screen pixels of the top-left-corner of the key
   * @param width the width of the key, in pixels
   * @param height the height of the key, in pixels
   */
  void Draw(const glm::dvec2& top_left_corner, double width,
            double height) const;

  /**
   * Updates the state of the PianoKey. If the PianoKey is in a changed-color
   *   calling update will advance the internal clock of PianoKey. Once a
   *   certain amount of time (calls to Update()) has passed, the PianoKey
   *   color will reset to normal
   */
  void Update();

  /**
   * Updates state of the piano key to temporarily change its color. While
   *   the key is in this state, the PianoKey color will be different when
   *   calling Draw()
   */
  void ChangeColor();

  /**
   * Gets the Note mapped to this PianoKey
   * @return the Note represented by this PianoKey
   */
  const music::Note& GetNote() const;

  /**
   * Gets the PianoKeyType mapped to this PianoKey
   * @return the PianoKeyType represented by this PianoKey
   */
  const PianoKeyType& GetType() const;

  /**
   * Set the label of the key, which will be displayed when drawing the key
   * @param label a character to set the label to
   */
  void SetLabel(char label);

  /**
   * Gets the current label of this PianoKey
   * @return a char representing this PianoKey's label
   */
  char GetLabel() const;

 private:
  music::Note note_;
  PianoKeyType type_;
  char label_;

  // Colors
  ci::Color standard_color_; // Standard, non-pressed color
  ci::Color fill_color_; // Current display color
  ci::Color outline_color_;
  ci::Color text_color_;

  // Temporarily changing color on play
  int time_to_reset_ = 0;
  static const ci::Color kChangedColor; // Color after ChangeColor() is called
  static constexpr int kColorChangeDuration = 5;
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PIANO_KEY_H
