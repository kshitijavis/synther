//
// Created by Kshitij Sinha on 11/19/20.
//

#ifndef SYNTHER_PIANO_KEY_H
#define SYNTHER_PIANO_KEY_H

#include "core/music_note.h"

namespace synther {

namespace visualizer {

class PianoKey {
 public:
  explicit PianoKey(const music::Note& note);

  const music::Note& GetNote() const;
 private:
  music::Note note_;
};

} // namespace visualizer

} // namespace synther

#endif  // SYNTHER_PIANO_KEY_H
