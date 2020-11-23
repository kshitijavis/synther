//
// Created by Kshitij Sinha on 11/19/20.
//
#include "visualizer/piano.h"
#include "core/music_note.h"
#include "cinder/Color.h"

#include <catch2/catch.hpp>
#include <vector>

using synther::visualizer::Piano;
using synther::music::Note;
using synther::music::Accidental;

TEST_CASE("Constructor correctly initializes single-octave piano",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, ci::Color("white"), 0, 12);

  SECTION("Sanity check: piano size properly initialized") {
    REQUIRE(piano.GetKeyCount() == 12);
  }

  SECTION("All notes properly initialized") {
    std::vector<Note> expected_notes{
        Note(0, 'A', Accidental::Natural),
        Note(0, 'A', Accidental::Sharp),
        Note(0, 'B', Accidental::Natural),
        Note(0, 'C', Accidental::Natural),
        Note(0, 'C', Accidental::Sharp),
        Note(0, 'D', Accidental::Natural),
        Note(0, 'D', Accidental::Sharp),
        Note(0, 'E', Accidental::Natural),
        Note(0, 'F', Accidental::Natural),
        Note(0, 'F', Accidental::Sharp),
        Note(0, 'G', Accidental::Natural),
        Note(0, 'G', Accidental::Sharp)
    };

    for (size_t index = 0; index < expected_notes.size(); index++) {
      REQUIRE(piano.GetPianoKey(index).GetNote() == expected_notes.at(index));
    }
  }
}

TEST_CASE("Constructor correctly initializes notes on multiple octaves",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, ci::Color("white"), 0, 24);

  SECTION("Sanity check: piano size properly initialized") {
    REQUIRE(piano.GetKeyCount() == 24);
  }

  SECTION("All notes properly initialized") {
    std::vector<Note> expected_notes{
        Note(1, 'A', Accidental::Natural),
        Note(1, 'A', Accidental::Sharp),
        Note(1, 'B', Accidental::Natural),
        Note(1, 'C', Accidental::Natural),
        Note(1, 'C', Accidental::Sharp),
        Note(1, 'D', Accidental::Natural),
        Note(1, 'D', Accidental::Sharp),
        Note(1, 'E', Accidental::Natural),
        Note(1, 'F', Accidental::Natural),
        Note(1, 'F', Accidental::Sharp),
        Note(1, 'G', Accidental::Natural),
        Note(1, 'G', Accidental::Sharp)
    };

    for (size_t index = 13; index < expected_notes.size(); index++) {
      REQUIRE(piano.GetPianoKey(index).GetNote() == expected_notes.at(index));
    }
  }
}

TEST_CASE("Constructor correctly initializes full-sized (88 keys) piano",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, ci::Color("white"), 0, 88);

  SECTION("First note is A0") {
    Note expected_note(0, 'A', Accidental::Natural);
    Note actual_note = piano.GetPianoKey(0).GetNote();
    REQUIRE(actual_note == expected_note);
  }

  SECTION("Last note is C7") {
    Note expected_note(7, 'C', Accidental::Natural);
    Note actual_note = piano.GetPianoKey(piano.GetKeyCount() - 1).GetNote();
    REQUIRE(actual_note == expected_note);
  }
}