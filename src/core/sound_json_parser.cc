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

std::map<music::Note, std::string> SoundJsonParser::GetNotesToFiles() const {
  std::map<music::Note, std::string> note_to_file;

  return note_to_file;
}

music::Note SoundJsonParser::ParseNote(const std::string& note_string) const {
  if (note_string.length() < 2 || note_string.length() > 3) {
    throw std::invalid_argument("note_string does not represent a valid note");
  }

  char letter = note_string.at(0);
  int octave = note_string.at(note_string.length() - 1) - '0';
  music::Accidental accidental = music::Accidental::Natural;

  // Parse optional accidental
  if (note_string.length() > 2) {
    switch (note_string.at(1)) {
      case 'b':
        accidental = music::Accidental::Flat;
        break;
      case 's':
        accidental = music::Accidental::Sharp;
        break;
    }
  }

  return {octave, letter, accidental};
}

}  // namespace audio

}  // namespace synther
