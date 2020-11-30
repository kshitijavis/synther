//
// Created by Kshitij Sinha on 11/29/20.
//

#include "core/soundfile_parser.h"

#include <fstream>
#include <iostream>
#include <string>
synther::audio::SoundfileParser::SoundfileParser(
    const std::string& json_filepath) {
  std::ifstream json_file(json_filepath);
  if (json_file.is_open()) {
    json_file >> sound_details_;
  }
}
