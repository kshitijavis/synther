#include <climits>
//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_PIANO_H
#define SYNTHER_PIANO_H

#include <vector>

#include "visualizer/piano_key.h"
#include "core/music_note.h"

namespace synther {

namespace visualizer {

class Piano {
 public:
  Piano(int first_semitone, size_t key_count);
 private:
  // Data
  int first_semitone_;
  size_t key_count_;
  std::vector<PianoKey> keys_;

  const music::Accidental kPriority = music::Accidental::Sharp;
};

} // namespace visualizer

} // namespace synther

#endif  // SYNTHER_PIANO_H
