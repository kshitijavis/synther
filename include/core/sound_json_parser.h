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
  /**
   * Construct a parser using a stream of instrument JSON data
   * @param json a stream of JSON data with information about a set of
   *   instrument sound files. The JSON must contain keys for "instrument",
   *   "organization", "performer", and "soundFiles"
   */
  explicit SoundJsonParser(std::istream& json);

  /**
   * Return the name of the instrument, as specified in the JSON file
   * @return the name of the instrument
   */
  std::string GetInstrumentName() const;

  /**
   * Return the name of the organization who produced the sound files, as
   *   specified in the JSON file
   * @return the name of the organization
   */
  std::string GetOrganizationName() const;

  /**
   * Return the name of the performer who produced the sound files, as
   *   specified in the JSON file
   * @return the name of the performer
   */
  std::string GetPerformerName() const;

  /**
   * Returns a map containing information about notes and filenames
   * @return A map from music::Notes to strings representing filenames. Every
   *   note in the map will corresponding to a filename, as instructed by
   *   the JSON used at construction
   */
  std::map<music::Note, std::string> GetNoteFiles() const;

  /**
   * Parses all note names in the JSON and returns a vector of the corresponding
   *   music::Notes
   * @return a vector of notes that appear in the JSON
   */
  std::vector<music::Note> GetNotes() const;

  /**
   * Converts a string representing a music note into a music::Note object
   * @param note_string. A String representing a music note.
   *   Expected that the note_string is a string of at least 2 characters, where
   *   the first character is the note letter, the second character (optional)
   *   is the accidental (b = Flat, s = Sharp, empty = Natural) and the last
   *   characters are the octave number
   *   Throws exception if note_string does not match the requirements
   * @return a music::Note object identical to the input note_string
   */
  music::Note ParseNoteString(const std::string& note_string) const;

 private:
  json sound_details_;

  static const std::string kInstrumentKey;
  static const std::string kOrganizationKey;
  static const std::string kPerformerKey;
  static const std::string kSoundFilesKey;

  std::string GetName(const std::string& key) const;
};

}  // namespace audio

}  // namespace synther

#endif  // SYNTHER_SOUND_JSON_PARSER_H
