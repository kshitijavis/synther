#include <climits>
//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_PIANO_H
#define SYNTHER_PIANO_H

#include <vector>

#include "visualizer/piano_key.h"

namespace synther {

namespace visualizer {

class Piano {
 public:
  Piano(int first_semitone, size_t key_count);
 private:
  // Data
  __unused int first_semitone_;
  __unused size_t key_count_;
};

} // namespace visualizer

} // namespace synther

#endif  // SYNTHER_PIANO_H
