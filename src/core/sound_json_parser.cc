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

SoundJsonParser::SoundJsonParser(std::istream& json){
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

std::map<music::Note, std::string> SoundJsonParser::GetSoundFiles()
    const {
  std::map<music::Note, std::string> sound_files;
  return sound_files;
}

}  // namespace audio

}  // namespace synther
