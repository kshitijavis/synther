//
// Created by Kshitij Sinha on 11/29/20.
//

#include "core/player.h"

#include "cinder/app/App.h"

namespace synther {

namespace audio {

void Player::SetUpVoices(const std::map<music::Note, std::string>& note_files,
                         const std::string& asset_directory) {
  for (const auto& note_file : note_files) {
    music::Note note = note_file.first;
    int semitone = note.GetSemitoneIndex();

    std::string filename = note_file.second;
    std::string sourcefile_path = asset_directory + filename;
    ci::audio::SourceFileRef source_file =
        ci::audio::load(ci::app::loadAsset(sourcefile_path));
    ci::audio::VoiceRef voice = ci::audio::Voice::create(source_file);

    voices_[semitone] = voice;
  }
}

void Player::PlayNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();
  if (voices_.find(semitone) != voices_.end()) {
    voices_.at(semitone)->start();
  }
}

void Player::StopNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();
  if (voices_.find(semitone) != voices_.end()) {
    voices_.at(semitone)->stop();
  }
}

}  // namespace audio

}  // namespace synther
