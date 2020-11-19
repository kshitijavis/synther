//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_PIANO_H
#define SYNTHER_PIANO_H

#include <core/music_note.h>

#include <vector>

namespace synther {

namespace visualizer {

class Piano {
 private:
  const std::vector<music::Note> octave_notes_ {
      music::Note{0, 'C', music::Accidental::Natural},
      music::Note{0, 'C', music::Accidental::Sharp},
      music::Note{0, 'D', music::Accidental::Natural},
      music::Note{0, 'D', music::Accidental::Sharp},
      music::Note{0, 'E', music::Accidental::Natural},
      music::Note{0, 'F', music::Accidental::Natural},
      music::Note{0, 'F', music::Accidental::Sharp},
      music::Note{0, 'G', music::Accidental::Natural},
      music::Note{0, 'G', music::Accidental::Sharp},
      music::Note{0, 'A', music::Accidental::Natural},
      music::Note{0, 'A', music::Accidental::Sharp},
      music::Note{0, 'B', music::Accidental::Natural},
  };
};

} // namespace visualizer

} // namespace synther

#endif  // SYNTHER_PIANO_H
