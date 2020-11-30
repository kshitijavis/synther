//
// Created by Kshitij Sinha on 11/19/20.
//
#include "core/music_note.h"

#include <catch2/catch.hpp>

using synther::music::Note;
using synther::music::Accidental;

TEST_CASE("Octave/Letter constructor correctly sets fields", "[constructor]") {
  SECTION("Base note (C) in first octave without accidental") {
    Note note(0, 'C', Accidental::Natural);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 0);
  }

  SECTION("Base note (C) in higher octave without accidental") {
    Note note(5, 'C', Accidental::Natural);

    REQUIRE(note.GetOctave() == 5);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 60);
  }

  SECTION("Higher-level in first octave without accidental") {
    Note note(0, 'G', Accidental::Natural);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'G');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 7);
  }

  SECTION("Higher-level in higher octave without accidental") {
    Note note(3, 'B', Accidental::Natural);

    REQUIRE(note.GetOctave() == 3);
    REQUIRE(note.GetLetter() == 'B');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 47);
  }

  SECTION("Base note (C) in first octave with sharp accidental") {
    Note note(0, 'C', Accidental::Sharp);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Sharp);
    REQUIRE(note.GetSemitoneIndex() == 1);
  }

  SECTION("Higher-level note in higher octave with sharp accidental") {
    Note note(4, 'A', Accidental::Sharp);

    REQUIRE(note.GetOctave() == 4);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Sharp);
    REQUIRE(note.GetSemitoneIndex() == 58);
  }

  SECTION("Higher-level note in higher octave with flat accidental") {
    Note note(4, 'A', Accidental::Flat);

    REQUIRE(note.GetOctave() == 4);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Flat);
    REQUIRE(note.GetSemitoneIndex() == 56);
  }

  SECTION("Constructor handles inputs with lower-case character input") {
    Note note(4, 'a', Accidental::Flat);

    REQUIRE(note.GetOctave() == 4);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Flat);
    REQUIRE(note.GetSemitoneIndex() == 56);
  }
}

TEST_CASE("Semitone constructor correctly sets fields", "[constructor]") {
  SECTION("Base note (C) in first octave that doesn't require accidental") {
    // Use arbitrary accidental that should not be used
    Note note(0, Accidental::Sharp);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 0);
  }

  SECTION("Base note (A) in higher octave that doesn't require accidental") {
    // Use arbitrary accidental that should not be used
    Note note(60, Accidental::Sharp);

    REQUIRE(note.GetOctave() == 5);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 60);
  }

  SECTION("Higher-level note in first octave without accidental") {
    // Use arbitrary accidental that should not be used
    Note note(9, Accidental::Sharp);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 9);
  }

  SECTION("Higher-level in higher octave without accidental") {
    // Use arbitrary accidental that should not be used
    Note note(38, Accidental::Sharp);

    REQUIRE(note.GetOctave() == 3);
    REQUIRE(note.GetLetter() == 'D');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 38);
  }

  SECTION("Note in first octave that requires an accidental with Sharp"
      "priority") {
    Note note(1,Accidental::Sharp);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'C');
    REQUIRE(note.GetAccidental() == Accidental::Sharp);
    REQUIRE(note.GetSemitoneIndex() == 1);
  }

  SECTION("Note in first octave that requires an accidental with Flat"
      "priority") {
    Note note(1,Accidental::Flat);

    REQUIRE(note.GetOctave() == 0);
    REQUIRE(note.GetLetter() == 'D');
    REQUIRE(note.GetAccidental() == Accidental::Flat);
    REQUIRE(note.GetSemitoneIndex() == 1);
  }

  SECTION("Note in higher octave that requires an accidental with Sharp"
          "priority") {
    Note note(22,Accidental::Sharp);

    REQUIRE(note.GetOctave() == 1);
    REQUIRE(note.GetLetter() == 'A');
    REQUIRE(note.GetAccidental() == Accidental::Sharp);
    REQUIRE(note.GetSemitoneIndex() == 22);
  }

  SECTION("Note in higher octave that requires an accidental with Flat"
          "priority") {
    Note note(22,Accidental::Flat);

    REQUIRE(note.GetOctave() == 1);
    REQUIRE(note.GetLetter() == 'B');
    REQUIRE(note.GetAccidental() == Accidental::Flat);
    REQUIRE(note.GetSemitoneIndex() == 22);
  }

  SECTION("Boundary case: E with sharp priority should default to E-natural") {
    Note note(16,Accidental::Sharp);

    REQUIRE(note.GetOctave() == 1);
    REQUIRE(note.GetLetter() == 'E');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 16);
  }

  SECTION("Boundary case: E-flat with flat priority should default to E-flat") {
    Note note(15,Accidental::Flat);

    REQUIRE(note.GetOctave() == 1);
    REQUIRE(note.GetLetter() == 'E');
    REQUIRE(note.GetAccidental() == Accidental::Flat);
    REQUIRE(note.GetSemitoneIndex() == 15);
  }

  SECTION("Boundary case, F with flat priority should default to F natural") {
    Note note(17,Accidental::Flat);

    REQUIRE(note.GetOctave() == 1);
    REQUIRE(note.GetLetter() == 'F');
    REQUIRE(note.GetAccidental() == Accidental::Natural);
    REQUIRE(note.GetSemitoneIndex() == 17);
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
    Note second(3, 'B', Accidental::Sharp);

    REQUIRE(first.SemitoneEquals(second));
  }

  SECTION("Two notes that are an 'octave' apart but share a semitone"
      "are equal") {
    Note first(1, 'A', Accidental::Flat);
    Note second(1, 'G', Accidental::Sharp);

    REQUIRE(first.SemitoneEquals(second));
  }

  SECTION("Two notes with different semitones are not equal") {
    Note first(3, 'E', Accidental::Natural);
    Note second(0, 'G', Accidental::Sharp);

    REQUIRE(!first.SemitoneEquals(second));
  }
}

TEST_CASE("Equals operator accurately compares two notes", "[operator==]") {
  SECTION("Two identical notes are equal") {
    Note first(4, 'C', Accidental::Flat);
    Note second(4, 'C', Accidental::Flat);

    REQUIRE(first == second);
  }

  SECTION("Two identical notes with mismatched char case are still equal") {
    Note first(4, 'c', Accidental::Flat);
    Note second(4, 'C', Accidental::Flat);

    REQUIRE(first == second);
  }

  SECTION("Two non-identical notes are not equal") {
    Note first(4, 'D', Accidental::Sharp);
    Note second(4, 'E', Accidental::Flat);

    REQUIRE(!(first == second));
  }
}