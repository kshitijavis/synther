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
      first_semitone_(first_semitone){
  // Set view_first_wholetone_ and ensure that it represents a whitekey,
  // i.e. a natural-note
  music::Note first_note(first_semitone, kPriority);
  if (first_note.GetAccidental() == music::Accidental::Natural) {
    view_first_wholetone_ = first_semitone;
  } else {
    // The key is not a natural, so shift view up to the next natural semitone
    view_first_wholetone_ = first_semitone + 1;
  }

  // Initialize keys_ and view_white_key_count_
  size_t natural_count = 0;
  for (int semitone = first_semitone_; semitone < first_semitone_ + key_count;
       semitone++) {
    music::Note to_add(semitone, kPriority);
    keys_.emplace_back(music::Note(semitone, kPriority));
    // All natural notes are whitekeys
    if (to_add.GetAccidental() == music::Accidental::Natural) {
      natural_count++;
    }
  }

  // Set window size to default, unless there are fewer total white keys on the
  // keyboard than the default
  view_whitekey_count_ = std::min(natural_count, kDefaultViewWhitekeyCount);
}

const PianoKey& Piano::GetPianoKey(int index) const {
  return keys_.at(index);
}

const size_t Piano::GetKeyCount() const {
  return keys_.size();
}

}  // namespace visualizer

}  // namespace synther