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
  explicit PianoKey(const music::Note& note, const PianoKeyType& type);

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
  ci::Color fill_color_;
  ci::Color outline_color_;
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PIANO_KEY_H
