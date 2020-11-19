//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_MUSIC_NOTE_H
#define SYNTHER_MUSIC_NOTE_H

#include <map>

namespace synther {

namespace music {

enum class Accidental { Sharp, Flat, Natural };

class Note {
  Note(size_t octave, char letter, Accidental accidental);

  /**
   * Get the octave in which the note lies
   * @return the octave of the note
   */
  size_t GetOctave() const;

  /**
   * Get the note's letter name (A, B, C, etc.)
   * @return a char representing the note's letter name
   */
  char GetLetter() const;

  /**
   * Get the note's accidental
   * @return an enum representing the note's accidental
   */
  Accidental GetAccidental() const;
 private:
  size_t octave_;
  char letter_;
  Accidental accidental_;

  // A numerical 'code' that represents a note such that the index of A0 = 0.
  // Every increase in a semitone increases the note's index by 1
  size_t semitone_index_;

  static const std::map<char, size_t> kWholetoneIndices;
  static constexpr size_t kOctaveSize = 12;

};

} // namespace music

} // namespace synther

#endif  // SYNTHER_MUSIC_NOTE_H
