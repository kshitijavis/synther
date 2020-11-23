//
// Created by Kshitij Sinha on 11/18/20.
//

#include "visualizer/piano.h"

#include "core/music_note.h"

namespace synther {

namespace visualizer {

Piano::Piano(const glm::dvec2& top_left_corner, double width, double height,
             const ci::Color& background_color, int first_semitone,
             size_t key_count)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      background_color_(background_color),
      first_semitone_(first_semitone) {
  // Initialize keys_
  for (int semitone = first_semitone_; semitone < first_semitone_ + key_count;
       semitone++) {
    keys_.emplace_back(music::Note(semitone, kPriority));
  }
}

const PianoKey& Piano::GetPianoKey(int index) const {
  return keys_.at(index);
}

const size_t Piano::GetKeyCount() const {
  return keys_.size();
}

}  // namespace visualizer

}  // namespace synther