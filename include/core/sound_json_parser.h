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

  std::map<music::Note, std::string> GetNotesToFiles() const;

  /**
   * Converts a string representing a music note into a music::Note object
   * @param note_string. A String representing a music note.
   *   Expected that the note_string is a string of 2-3 characters, where the
   *   first character is the note letter, the second character (optional) is
   *   the accidental (b = Flat, s = Sharp, empty = Natural) and the last
   *   character is the octave number
   *   Throws exception if note_string does not match the requirements
   * @return a music::Note object identical to the input note_string
   */
  music::Note ParseNote(const std::string& note_string) const;

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
