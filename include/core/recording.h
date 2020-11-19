//
// Created by Kshitij Sinha on 11/18/20.
//

#include <vector>
#include <utility>
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

  /**
   * Adds a music note to the recording and pairs it with the time from the
   *   start of the recording to the method call
   */
  void AddNote(const music::Note& note);
 private:
  bool is_recording_;
  std::chrono::time_point<std::chrono::system_clock> start_time_;
  std::vector<std::pair<music::Note, std::chrono::duration<double>>> notes_;
};

} // namespace synther

#endif  // SYNTHER_RECORDING_H
