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

class PianoKey {
 public:
  PianoKey(const music::Note& note, const PianoKeyType& type, char label = ' ');

  /**
   * Set the label of the key, which will be displayed when drawing the key
   * @param label a character to set the label to
   */
  void SetLabel(char label);

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

  void Draw(const glm::dvec2& top_left_corner, double width,
            double height) const;

 private:
  music::Note note_;
  PianoKeyType type_;
  char label_;

  // Colors
  ci::Color fill_color_;
  ci::Color outline_color_;
  ci::Color text_color_;
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PIANO_KEY_H
