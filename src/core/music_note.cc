//
// Created by Kshitij Sinha on 11/19/20.
//

#include <core/music_note.h>

#include <map>

namespace synther {

namespace music {

const std::map<char, int> Note::kWholetoneIndices{
    {'C', 0}, {'D', 2}, {'E', 4}, {'F', 5}, {'G', 7}, {'A', 9}, {'B', 11}};

Note::Note(int octave, char letter, Accidental accidental)
    : octave_(octave), accidental_(accidental) {
  letter_ = toupper(letter);
  semitone_index_ = octave_ * kNotesPerOctave + kWholetoneIndices.at(letter_);

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

Note::Note(int semitone_index, Accidental priority)
    : semitone_index_(semitone_index) {
  octave_ = semitone_index / kNotesPerOctave;
  int octave_index = semitone_index % kNotesPerOctave;

  // Reverse kWholeToneIndices because we will have to make a multiple searches
  std::map<int, char> reverse_wholetones;
  for (auto kWholetoneIndex : kWholetoneIndices) {
    reverse_wholetones[kWholetoneIndex.second] = kWholetoneIndex.first;
  }

  auto possible_note = reverse_wholetones.find(octave_index);
  if (possible_note != reverse_wholetones.end()) {
    // If there is already a wholetone at the index, set letter to the wholetone
    // and accidental to natural
    accidental_ = Accidental::Natural;
    letter_ = reverse_wholetones.at(octave_index);
  } else if (priority == Accidental::Flat) {
    // Take next wholetone and set accidental to flat
    accidental_ = Accidental::Flat;
    letter_ = reverse_wholetones.at(octave_index + 1);
  } else if (priority == Accidental::Sharp) {
    // Take previous wholetone and set accidental to sharp
    accidental_ = Accidental::Sharp;
    letter_ = reverse_wholetones.at(octave_index - 1);
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

bool Note::operator==(const Note& rhs) const {
  return octave_ == rhs.octave_ && letter_ == rhs.letter_ &&
         accidental_ == rhs.accidental_ &&
         semitone_index_ == rhs.semitone_index_;
}

bool Note::operator<(const Note& rhs) const {
  return GetSemitoneIndex() < rhs.GetSemitoneIndex();
}

}  // namespace music

}  // namespace synther
