//
// Created by Kshitij Sinha on 11/29/20.
//

#ifndef SYNTHER_SOUND_JSON_PARSER_H
#define SYNTHER_SOUND_JSON_PARSER_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "core/music_note.h"

namespace synther {

namespace audio {

using json = nlohmann::json;

class SoundJsonParser {
 public:
  explicit SoundJsonParser(std::istream& json);

  /**
   * Retruns the name of the instrument, as specified in the JSON file
   * @return the name of the instrument
   */
  std::string GetInstrumentName() const;

  /**
   * Retruns the name of the organization who produced the sound files, as
   * specified in the JSON file
   * @return the name of the organization
   */
  std::string GetOrganizationName() const;

  /**
   * Retruns the name of the performer who produced the sound files, as
   * specified in the JSON file
   * @return the name of the performer
   */
  std::string GetPerformerName() const;

  std::map<music::Note, std::string> GetSoundFiles() const;

 private:
  json sound_details_;
  std::string directory_path_;

  static const std::string kInstrumentKey;
  static const std::string kOrganizationKey;
  static const std::string kPerformerKey;
  static const std::string kSoundFilesKey;

  std::string GetName(const std::string& key) const;
};

}  // namespace audio

}  // namespace synther

#endif  // SYNTHER_SOUND_JSON_PARSER_H
