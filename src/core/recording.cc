//
// Created by Kshitij Sinha on 11/18/20.
//

#include "core/recording.h"

#include <chrono>

namespace synther {

void Recording::StartRecording() {
  is_recording_ = true;
  start_time_ = std::chrono::system_clock::now();
}

}  // namespace synther
