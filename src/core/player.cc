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
    // Get map-key
    music::Note note = note_file.first;
    int semitone = note.GetSemitoneIndex();

    // Load file
    std::string filename = note_file.second;
    std::string sourcefile_path = asset_directory + filename;
    ci::audio::SourceFileRef source_file =
        ci::audio::load(ci::app::loadAsset(sourcefile_path));

    // Create buffer player from file
    ci::audio::BufferPlayerNodeRef buffer_player =
        ctx->makeNode(new ci::audio::BufferPlayerNode());
    buffer_player->loadBuffer(source_file);

    // Connect buffer player to audio graph
    buffer_player >> ctx->getOutput();

    buffer_players_[semitone] = buffer_player;
  }
  ctx->enable();
}

void Player::PlayNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();
  if (buffer_players_.find(semitone) != buffer_players_.end()) {
    buffer_players_.at(semitone)->start();
  }
}

void Player::StopNote(const music::Note& note) {
  int semitone = note.GetSemitoneIndex();
  if (buffer_players_.find(semitone) != buffer_players_.end()) {
    buffer_players_.at(semitone)->stop();
  }
}

}  // namespace audio

}  // namespace synther
