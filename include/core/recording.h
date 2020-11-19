//
// Created by Kshitij Sinha on 11/18/20.
//
#ifndef SYNTHER_RECORDING_H
#define SYNTHER_RECORDING_H

#include <chrono>
#include <utility>
#include <vector>

#include "music-note.h"

namespace synther {

/**
 * A Recording based on the idea that a piece of music is simply a list of
 *   notes played at some time after the beginning of the piece. This class
 *   stores a Recording of a musical composition as a list of notes paired with
 *   the time the note was played.
 */
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
