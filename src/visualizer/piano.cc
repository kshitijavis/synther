//
// Created by Kshitij Sinha on 11/18/20.
//

#include "visualizer/piano.h"

#include "core/music_note.h"

namespace synther {

namespace visualizer {

Piano::Piano(int first_semitone, size_t key_count)
    : first_semitone_(first_semitone), key_count_(key_count) {
  // Initialize keys_
  for (int semitone = first_semitone_; semitone < first_semitone_ + key_count_;
       semitone++) {
    keys_.emplace_back(music::Note(semitone, kPriority));
  }
}
}  // namespace visualizer

}  // namespace synther