//
// Created by Kshitij Sinha on 11/29/20.
//

#include "core/sound_json_parser.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace synther {

namespace audio {

const std::string SoundJsonParser::kInstrumentKey = "instrument";
const std::string SoundJsonParser::kOrganizationKey = "organization";
const std::string SoundJsonParser::kPerformerKey = "performer";
const std::string SoundJsonParser::kSoundFilesKey = "soundFiles";

SoundJsonParser::SoundJsonParser(std::istream& json) {
  json >> sound_details_;
}

std::string SoundJsonParser::GetInstrumentName() const {
  return GetName(kInstrumentKey);
}

std::string SoundJsonParser::GetOrganizationName() const {
  return sound_details_.at(kOrganizationKey);
}

std::string SoundJsonParser::GetPerformerName() const {
  return sound_details_.at(kPerformerKey);
}

std::string SoundJsonParser::GetName(const std::string& key) const {
  std::string name = "";
  if (sound_details_.contains(key)) {
    name = sound_details_.at(key);
  }
  return name;
}

std::map<music::Note, std::string> SoundJsonParser::GetNoteFiles() const {
  std::map<music::Note, std::string> note_files;
  // Get raw note string to filename map from JSON
  std::map<std::string, std::string> note_pairs =
      sound_details_.at(kSoundFilesKey)
          .get<std::map<std::string, std::string>>();

  // Convert every note string to a music::Note
  for (const auto& note_pair : note_pairs) {
    music::Note note = ParseNote(note_pair.first);
    std::string filename = note_pair.second;
    note_files.emplace(note, filename);
  }

  return note_files;
}

music::Note SoundJsonParser::ParseNote(const std::string& note_string) const {
  if (note_string.length() < 2) {
    throw std::invalid_argument("note_string does not represent a valid note");
  }

  char letter = note_string.at(0);
  music::Accidental accidental;

  switch (note_string.at(1)) {
    case 'b':
      accidental = music::Accidental::Flat;
      break;
    case 's':
      accidental = music::Accidental::Sharp;
      break;
    default:
      accidental = music::Accidental::Natural;
  }

  size_t last_index = note_string.find_last_not_of("0123456789");
  std::string octave_digits = note_string.substr(last_index + 1);
  int octave = std::stoi(octave_digits);

  return {octave, letter, accidental};
}

}  // namespace audio

}  // namespace synther
