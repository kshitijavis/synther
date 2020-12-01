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

    PlayerGraph components{gain, buffer_player};
    players_[semitone] = components;
  }

  ctx->enable();
}

void Player::PlayNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();

  if (players_.find(semitone) != players_.end()) {
    ci::audio::BufferPlayerNodeRef player = players_.at(semitone).buffer_player_;
    if (!player->isEnabled()) {
      player->start();
    }
  }
}

void Player::StopNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();
  if (players_.find(semitone) != players_.end()) {
    players_.at(semitone).buffer_player_->stop();
  }
}

}  // namespace audio

}  // namespace synther
