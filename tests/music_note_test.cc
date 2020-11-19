//
// Created by Kshitij Sinha on 11/19/20.
//
#include "core/music_note.h"

#include <catch2/catch.hpp>

using synther::music::Note;
using synther::music::Accidental;

TEST_CASE("Default constructor correctly sets fields", "[constructor]") {
  SECTION("Base note (A) in first octave without accidental") {
    Note note(0, 'A', Accidental::Natural);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 0);
  }

  SECTION("Base note (A) in higher octave without accidental") {
    Note note(5, 'A', Accidental::Natural);

    REQUIRE(note.GetOctave() == 5);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 60);
  }

  SECTION("Higher-level in first octave without accidental") {
    Note note(0, 'G', Accidental::Natural);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'G');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 10);
  }

  SECTION("Higher-level in higher octave without accidental") {
    Note note(3, 'B', Accidental::Natural);

    REQUIRE(note.GetOctave() == 3);
    REQUIRE(note.GetLetter() == 'B');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 38);
  }

  SECTION("Base note (A) in first octave with sharp accidental") {
    Note note(0, 'A', Accidental::Sharp);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Sharp);
    REQUIRE(note.GetSemitoneIndex() == 1);
  }

  SECTION("Higher-level note in higher octave with sharp accidental") {
    Note note(4, 'C', Accidental::Sharp);

    REQUIRE(note.GetOctave() == 4);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Sharp);
    REQUIRE(note.GetSemitoneIndex() == 52);
  }

  SECTION("Higher-level note in higher octave with flat accidental") {
    Note note(4, 'C', Accidental::Flat);

    REQUIRE(note.GetOctave() == 4);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Flat);
    REQUIRE(note.GetSemitoneIndex() == 50);
  }
}

TEST_CASE("Semitone equals accurately compares two notes", "[semitoneequals]") {
  SECTION("Two identical notes are equal") {
    Note first(4, 'C', Accidental::Flat);
    Note second(4, 'C', Accidental::Flat);

    REQUIRE(first.SemitoneEquals(second));
  }

  SECTION("Two non-identical notes with the same semitone "
      "(using sharp, flat accidentals), are equal") {
    Note first(4, 'D', Accidental::Sharp);
    Note second(4, 'E', Accidental::Flat);

    REQUIRE(first.SemitoneEquals(second));
  }

  SECTION("Two non-identical notes with the same semitone "
      "(using sharp, natural accidentals), are equal") {
    Note first(4, 'C', Accidental::Natural);
    Note second(4, 'B', Accidental::Sharp);

    REQUIRE(first.SemitoneEquals(second));
  }

  SECTION("Two notes that are an 'octave' apart but share a semitone"
      "are equal") {
    Note first(1, 'A', Accidental::Flat);
    Note second(0, 'G', Accidental::Sharp);

    REQUIRE(first.SemitoneEquals(second));
  }

  SECTION("Two notes with different semitones are not equal") {
    Note first(3, 'E', Accidental::Natural);
    Note second(0, 'G', Accidental::Sharp);

    REQUIRE(!first.SemitoneEquals(second));
  }
}