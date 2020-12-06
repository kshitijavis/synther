//
// Created by Kshitij Sinha on 11/29/20.
//

#include "core/player.h"

#include "cinder/app/App.h"

namespace synther {

namespace audio {

Player::Player(double resonate_duration)
    : resonate_duration_(resonate_duration) {
}

void Player::SetUpVoices(const std::map<music::Note, std::string>& note_files,
                         const std::string& instrument_directory) {
  auto ctx = ci::audio::Context::master();

  for (const auto& note_file : note_files) {
    // Load file
    std::string filename = note_file.second;
    std::string sourcefile_path = instrument_directory + filename;
    ci::audio::SourceFileRef source_file =
        ci::audio::load(ci::app::loadAsset(sourcefile_path));

    // Create buffer player from file
    ci::audio::BufferPlayerNodeRef buffer_player =
        ctx->makeNode(new ci::audio::BufferPlayerNode());
    buffer_player->loadBuffer(source_file);

    // Create a gain node for volume control (init at max volume)
    ci::audio::GainNodeRef gain = ctx->makeNode(new ci::audio::GainNode(1));

    // Connect player components to audio graph
    buffer_player >> gain >> ctx->getOutput();

    // Map the player components to a note semitone
    music::Note note = note_file.first;
    int semitone = note.GetSemitoneIndex();

    NoteVoice components{gain, buffer_player, false};
    players_[semitone] = components;
  }

  ctx->enable();
}

void Player::PlayNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();

  if (players_.find(semitone) != players_.end()) {
    NoteVoice& voice = players_.at(semitone);
    ci::audio::BufferPlayerNodeRef buffer_player = voice.buffer_player_;

    if (!(voice.is_playing_)) {
      voice.is_playing_ = true;
      ci::audio::GainNodeRef gain = voice.gain_;
      gain->getParam()->setValue(1);
      buffer_player->start();
    }
  }
}

void Player::StopNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();

  if (players_.find(semitone) != players_.end()) {
    NoteVoice& voice = players_.at(semitone);
    ci::audio::BufferPlayerNodeRef buffer_player = voice.buffer_player_;

    if (voice.is_playing_) {
      voice.is_playing_ = false;

      ci::audio::GainNodeRef gain = voice.gain_;
      auto param = gain->getParam();
      if (param->getNumEvents() == 0) {
        gain->getParam()->applyRamp(0, resonate_duration_);
      }

      auto ctx = ci::audio::Context::master();
      buffer_player->stop(ctx->getNumProcessedSeconds() + resonate_duration_);
    }
  }
}

void Player::SetResonation(double resonate_duration) {
  resonate_duration_ = resonate_duration;
}

double Player::GetResonation() const {
  return resonate_duration_;
}

}  // namespace audio

}  // namespace synther
