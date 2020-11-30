//
// Created by Kshitij Sinha on 11/29/20.
//

#include <catch2/catch.hpp>
#include <fstream>
#include <string>

#include "core/sound_json_parser.h"
#include "core/music_note.h"

using synther::audio::SoundJsonParser;
using synther::music::Note;
using synther::music::Accidental;

TEST_CASE("Correctly parses simple key-value pairs",
          "[getinstrumentname][getorganizationname][getperformername]") {
  SECTION("JSON containing all pairs") {
    std::fstream json("../assets/sounds/piano/details.json");
    SoundJsonParser parser(json);
    REQUIRE(parser.GetInstrumentName() == "Acoustic Piano");
    REQUIRE(parser.GetOrganizationName() ==
            "University of Iowa Electronic Music Studios");
    REQUIRE(parser.GetPerformerName() == "Evan Mazunik");
  }
}

TEST_CASE("Correctly parses filenames", "[getfilenames]") {
  SECTION("JSON containing notes for standard piano (88 files)") {
    std::fstream json("../assets/sounds/piano/details.json");
    SoundJsonParser parser(json);
    parser.GetNotesToFiles();
  }
}

TEST_CASE("Correctly parses note string", "[parsenote]") {
  std::fstream json("../assets/sounds/piano/details.json");
  SoundJsonParser parser(json);

  SECTION("A on first octave without accidental") {
    std::string note_string = "A0";
    Note note(0, 'A', Accidental::Natural);
    REQUIRE(parser.ParseNote(note_string) == note);
  }

  SECTION("A on higher octave without accidental") {
    std::string note_string = "A5";
    Note note(5, 'A', Accidental::Natural);
    REQUIRE(parser.ParseNote(note_string) == note);
  }

  SECTION("Any note on any octave without accidental") {
    std::string note_string = "G3";
    Note note(3, 'G', Accidental::Natural);
    REQUIRE(parser.ParseNote(note_string) == note);
  }

  SECTION("Note on any octave with sharp accidental") {
    std::string note_string = "Ds8";
    Note note(8, 'D', Accidental::Sharp);
    REQUIRE(parser.ParseNote(note_string) == note);
  }

  SECTION("Note on any octave with flat accidental") {
    std::string note_string = "Cb3";
    Note note(3, 'C', Accidental::Flat);
    REQUIRE(parser.ParseNote(note_string) == note);
  }

  SECTION("Note on multi-digit octave with accidental") {
    std::string note_string = "Cb33";
    Note note(33, 'C', Accidental::Flat);
    REQUIRE(parser.ParseNote(note_string) == note);
  }

  SECTION("Invalid note: length too small") {
    std::string note_string = "C";
    REQUIRE_THROWS_AS(parser.ParseNote(note_string), std::invalid_argument);
  }
}