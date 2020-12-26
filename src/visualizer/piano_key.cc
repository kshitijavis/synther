//
// Created by Kshitij Sinha on 11/19/20.
//

#include "visualizer/piano_key.h"

synther::visualizer::PianoKey::PianoKey(const synther::music::Note& note)
    : note_(note) {
}

const synther::music::Note& synther::visualizer::PianoKey::GetNote() const {
  return note_;
}
