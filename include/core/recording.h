//
// Created by Kshitij Sinha on 11/18/20.
//

#include <map>

#include "music.h"

#ifndef SYNTHER_RECORDING_H
#define SYNTHER_RECORDING_H

namespace synther {

class Recording {
 private:
  double start_time_;
  std::map<music::Note, double> notes_;
  bool is_recording_;
};

} // namespace synther

#endif  // SYNTHER_RECORDING_H
