//
// Created by Kshitij Sinha on 11/18/20.
//

#include <map>
#include <chrono>

#include "music.h"

#ifndef SYNTHER_RECORDING_H
#define SYNTHER_RECORDING_H

namespace synther {

class Recording {
 public:
  /**
   * Constructs a default recording with default parameters
   */
  Recording() = default;

  /**
   * Begins recording a composition. The class will begin keeping track of time
   *   since the recording is started and will allow notes to be added to the
   *   recording
   */
  void StartRecording();
 private:
  bool is_recording_;
  std::chrono::time_point<std::chrono::system_clock> start_time_;
  std::map<music::Note, double> notes_;
};

} // namespace synther

#endif  // SYNTHER_RECORDING_H
