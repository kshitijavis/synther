//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_MUSIC_NOTE_H
#define SYNTHER_MUSIC_NOTE_H

#include <map>

namespace synther {

namespace music {

enum class Accidental { Sharp, Flat, Natural };

/**
 * Represents a musical note, defined by the main parameters: octave, letter,
 *   and accidental. These three parameters are used to define where the note
 *   is on the standard Western musical scale.
 *
 * Alternatively, a Note can also be defined by its semitone-index with respect
 *   to some base note. In this implementation, the base note, C0, has the
 *   semitone-index of 0. All other notes on the scale can be defined by their
 *   semitone distance from C0
 *
 * Regardless of the method of construction, a Note will keep track of its
 *   octave, letter, accidental, and semitone-index, each of which can be
 *   accessed but not changed
 */
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
   * Constructs a note using its semitone-index, which is the Note's semitone
   *   distance from C0
   * @param semitone_index the semitone-index of the note with respect to C0
   * @param priority the Accidental that will be given priority, if the note's
   *   semitone requires an accidental. Must be Sharp or Flat
   *   Since any note can have multiple names, (B-flat is the same as A-sharp),
   *   this constructor will prioritize the Accidental specified (If
   *   Accidental::Sharp is passed, the constructor will choose A-sharp instead
   *   of B-flat) If a note does not require an accidental, none will be
   *   assigned.
   */
  Note(int semitone_index, Accidental priority);

  /**
   * Checks if two notes are equal. Two notes are equal if all of their
   *   parameters (octave, letter, accidental, semitone-index) are equal
   * @param rhs the note to compare to
   * @return true if the two notes are equal
   */
  bool operator==(const Note& rhs) const;

  /**
   * Compares two notes, enabling Note object to be used as key in std::map
   * @param rhs the Note to compare to
   * @return true if the semitone of the current object is less than the
   *   semitone of rhs
   */
  bool operator<(const Note& rhs) const;

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
   *   such that the index of C0 = 0
   * @return a size_t representing the note's semitone index
   */
  int GetSemitoneIndex() const;

 private:
  int octave_;
  char letter_;
  Accidental accidental_;

  // A numerical 'code' that represents note's semitone.
  // 0-index starts from the note C0.
  // Every increase in a semitone increases the note's index by 1
  int semitone_index_;

  // Static fields
  static const std::map<char, int> kWholetoneIndices;
  static constexpr size_t kNotesPerOctave = 12;
};

}  // namespace music

}  // namespace synther

#endif  // SYNTHER_MUSIC_NOTE_H
