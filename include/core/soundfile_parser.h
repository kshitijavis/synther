//
// Created by Kshitij Sinha on 11/29/20.
//

#ifndef SYNTHER_SOUNDFILE_PARSER_H
#define SYNTHER_SOUNDFILE_PARSER_H

#include <nlohmann/json.hpp>
#include <string>

namespace synther {

namespace audio {

using json = nlohmann::json;

/**
 * Parses a details.json file that comes in every sounds directory
 * Can be used to retrieve information such as the instrument name, performer,
 * and filepaths to instrument soundfiles
 */
class SoundfileParser {
 public:
  explicit SoundfileParser(const std::string& json_filepath);
 private:
  json sound_details_;
};

} // namespace audio

} // namespace synther

#endif  // SYNTHER_SOUNDFILE_PARSER_H
