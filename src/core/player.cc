//
// Created by Kshitij Sinha on 11/29/20.
//

#include "core/player.h"

#include "cinder/app/App.h"

namespace synther {

namespace audio {

void Player::SetUpVoices(const std::map<music::Note, std::string>& note_files,
                         const std::string& asset_directory) {
  auto ctx = ci::audio::Context::master();

  for (const auto& note_file : note_files) {
    // Load file
    std::string filename = note_file.second;
    std::string sourcefile_path = asset_directory + filename;
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

    PlayerComponent components{gain, buffer_player};
    players_[semitone] = components;
  }

  ctx->enable();
}

void Player::PlayNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();

  if (players_.find(semitone) != players_.end()) {
    PlayerComponent player = players_.at(semitone);
    ci::audio::BufferPlayerNodeRef buffer_player = player.buffer_player_;
    if (!(buffer_player->isEnabled())) {
      ci::audio::GainNodeRef gain = player.gain_;
      gain->getParam()->setValue(1);
      buffer_player->start();
    }
  }
}

void Player::StopNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();
  if (players_.find(semitone) != players_.end()) {
    PlayerComponent& player = players_.at(semitone);
    ci::audio::GainNodeRef gain = player.gain_;
    ci::audio::BufferPlayerNodeRef buffer_player = player.buffer_player_;

    if (buffer_player->isEnabled()) {
      auto param = gain->getParam();
      if (param->getNumEvents() == 0) {
        gain->getParam()->applyRamp(0, 1);
      }
      auto ctx = ci::audio::Context::master();
      buffer_player->stop(ctx->getNumProcessedSeconds() + 1);
    }
  }
}

}  // namespace audio

}  // namespace synther
