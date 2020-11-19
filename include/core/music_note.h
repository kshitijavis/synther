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
 public:
  /**
   * Constructs a note using standard musical notation: octave, letter,
   *   accidental
   * @param octave and int representing the octave of the note. Indexes the
   * octave, given that the first octave in a keyboard is 0-indexed
   * @param letter a char representing the letter of the note. Options include
   *   A, B, C, D, E, F, G
   * @param accidental an enum representing the note's accidental
   *   (Sharp, Flat, Natural)
   */
  Note(int octave, char letter, Accidental accidental);

  /**
   * Compares two notes by their semitone index. The semitone index acts as a
   *   unique ID for any note. Bear in mind that this comparison allows two
   *   seemingly-different notes to be equal (e.g. C-sharp and D-flat)
   * @param rhs
   * @return
   */
  bool SemitoneEquals(const Note& other) const;

  /**
   * Get the octave in which the note lies
   * @return the octave of the note
   */
  int GetOctave() const;

  /**
   * Get the note's letter name (A, B, C, etc.) in upper-case
   * @return a char representing the note's letter name
   */
  char GetLetter() const;

  /**
   * Get the note's accidental
   * @return an enum representing the note's accidental
   */
  Accidental GetAccidental() const;

  /**
   * Get the note's semitone index, which defines the semitone ID of the note,
   *   such that the index of A0 = 0
   * @return a size_t representing the note's semitone index
   */
  int GetSemitoneIndex() const;
 private:
  int octave_;
  char letter_;
  Accidental accidental_;

  // A numerical 'code' that represents a note such that the index of A0 = 0.
  // Every increase in a semitone increases the note's index by 1
  int semitone_index_;

  static const std::map<char, int> kWholetoneIndices;
  static constexpr size_t kOctaveSize = 12;

};

} // namespace music

} // namespace synther

#endif  // SYNTHER_MUSIC_NOTE_H
