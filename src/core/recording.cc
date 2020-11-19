//
// Created by Kshitij Sinha on 11/18/20.
//

#include <chrono>

#include "core/recording.h"
#include "core/music.h"

namespace synther {

void Recording::StartRecording() {
  is_recording_ = true;
  start_time_ = std::chrono::system_clock::now();
}

void Recording::AddNote(const music::Note& note) {
  std::chrono::duration<double> time =
      std::chrono::system_clock::now() - start_time_;

  notes_.emplace_back(note, time);
}

}  // namespace synther
