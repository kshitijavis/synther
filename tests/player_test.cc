//
// Created by Kshitij Sinha on 12/6/20.
//

#include "core/player.h"

#include <catch2/catch.hpp>
#include <string>

#include "core/music_note.h"

using synther::audio::Player;
using synther::music::Accidental;
using synther::music::Note;

TEST_CASE("SetUpVoices stores all notes mapped to valid filename",
          "[setupvoices][getnotes]") {
  SECTION("All valid filenames") {
    Player player(.5);
    std::string instrument_directory = "sounds/piano/";
    std::map<Note, std::string> note_files{
        {Note(0, 'A', Accidental::Natural), "Piano.ff.A0.mp3"},
        {Note(1, 'A', Accidental::Natural), "Piano.ff.A1.mp3"},
        {Note(2, 'A', Accidental::Natural), "Piano.ff.A2.mp3"},
        {Note(3, 'A', Accidental::Natural), "Piano.ff.A3.mp3"},
        {Note(4, 'A', Accidental::Natural), "Piano.ff.A4.mp3"},
        {Note(5, 'A', Accidental::Natural), "Piano.ff.A5.mp3"},
        {Note(6, 'A', Accidental::Natural), "Piano.ff.A6.mp3"},
    };

    player.SetUpVoices(note_files, instrument_directory);

    std::vector<Note> expected_notes{
        {Note(0, 'A', Accidental::Natural)},
        {Note(1, 'A', Accidental::Natural)},
        {Note(2, 'A', Accidental::Natural)},
        {Note(3, 'A', Accidental::Natural)},
        {Note(4, 'A', Accidental::Natural)},
        {Note(5, 'A', Accidental::Natural)},
        {Note(6, 'A', Accidental::Natural)},
    };

    REQUIRE(player.GetPlayableNotes() == expected_notes);
  }

  SECTION("Skips any invalid filenames") {
    Player player(.5);
    std::string instrument_directory = "sounds/piano/";
    std::map<Note, std::string> note_files{
        {Note(0, 'A', Accidental::Natural), "invalid"},
        {Note(1, 'A', Accidental::Natural), "invalid"},
        {Note(2, 'A', Accidental::Natural), "invalid"},
        {Note(3, 'A', Accidental::Natural), "invalid"},
        {Note(4, 'A', Accidental::Natural), "invalid"},
        {Note(5, 'A', Accidental::Natural), "invalid"},
        {Note(6, 'A', Accidental::Natural), "invalid"},
    };

    player.SetUpVoices(note_files, instrument_directory);

    std::vector<Note> expected_notes;

    REQUIRE(player.GetPlayableNotes() == expected_notes);
  }
}