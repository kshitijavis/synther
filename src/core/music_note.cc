//
// Created by Kshitij Sinha on 11/19/20.
//

#include <core/music_note.h>

#include <map>

namespace synther {

namespace music {

const std::map<char, int> Note::kWholetoneIndices{
    {'A', 0},
    {'B', 2},
    {'C', 3},
    {'D', 5},
    {'E', 7},
    {'F', 8},
    {'G', 10}
};

Note::Note(int octave, char letter, Accidental accidental)
    : octave_(octave), letter_(toupper(letter)), accidental_(accidental) {
  semitone_index_ = octave_ * kOctaveSize + kWholetoneIndices.at(letter);

  // Adjust semitone based on accidental
  switch (accidental_) {
    case Accidental::Sharp:
      semitone_index_++;
      break;
    case Accidental::Flat:
      semitone_index_--;
      break;
    case Accidental::Natural:
      break;
  }
}

bool Note::SemitoneEquals(const Note& other) const {
  return semitone_index_ == other.semitone_index_;
}

int Note::GetOctave() const {
  return octave_;
}

char Note::GetLetter() const {
  return letter_;
}

Accidental Note::GetAccidental() const {
  return accidental_;
}

int Note::GetSemitoneIndex() const {
  return semitone_index_;
}

}  // namespace music

}  // namespace synther
