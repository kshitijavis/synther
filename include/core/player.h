//
// Created by Kshitij Sinha on 11/29/20.
//

#ifndef SYNTHER_PLAYER_H
#define SYNTHER_PLAYER_H

#include <map>
#include <string>

#include "cinder/audio/audio.h"
#include "core/music_note.h"

namespace synther {

namespace audio {

class Player {
 public:
  Player() = default;

  void SetUpVoices(const std::map<music::Note, std::string>& note_files,
                   const std::string& asset_directory);

  void PlayNote(const music::Note& note);

 private:
  // Maps semitones to voices
  std::map<int, ci::audio::VoiceRef> voices_;
};

}  // namespace audio

}  // namespace synther

#endif  // SYNTHER_PLAYER_H
