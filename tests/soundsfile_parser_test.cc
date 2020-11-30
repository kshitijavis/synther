//
// Created by Kshitij Sinha on 11/29/20.
//

#include <catch2/catch.hpp>
#include <fstream>
#include <string>

#include "core/sound_json_parser.h"

using synther::audio::SoundJsonParser;

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
    parser.GetSoundFiles();
  }
}