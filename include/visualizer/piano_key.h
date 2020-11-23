//
// Created by Kshitij Sinha on 11/19/20.
//

#ifndef SYNTHER_PIANO_KEY_H
#define SYNTHER_PIANO_KEY_H

#include "core/music_note.h"
#include "cinder/Color.h"

namespace synther {

namespace visualizer {

class PianoKey {
 public:
  explicit PianoKey(const music::Note& note);

  /**
   * Gets the Note mapped to this PianoKey
   * @return the Note represented by this PianoKey
   */
  const music::Note& GetNote() const;

  void Draw(const glm::dvec2& top_left_corner, double width, double height) const;
 private:
  music::Note note_;
  ci::Color fill_color_;
  ci::Color outline_color_;
};

} // namespace visualizer

} // namespace synther

#endif  // SYNTHER_PIANO_KEY_H
