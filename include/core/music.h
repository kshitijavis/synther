//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_MUSIC_H
#define SYNTHER_MUSIC_H

#include <string>

namespace synther {

namespace music {

enum class Accidental { Sharp, Flat, Natural };

struct Note {
  size_t octave_;
  char letter_;
  Accidental accidental_;
};

} // namespace music

} // namespace synther

#endif  // SYNTHER_MUSIC_H
