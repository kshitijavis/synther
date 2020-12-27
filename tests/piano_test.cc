//
// Created by Kshitij Sinha on 11/19/20.
//
#include "visualizer/piano.h"
#include "core/piano_keybinder.h"

#include <catch2/catch.hpp>
#include <vector>

#include "cinder/Color.h"
#include "core/music_note.h"
#include "visualizer/piano_key.h"

using synther::music::Accidental;
using synther::music::Note;
using synther::visualizer::Piano;
using synther::visualizer::PianoKey;
using synther::PianoKeybinder;

TEST_CASE("Constructor correctly initializes single-octave piano",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 9, 12);

  SECTION("Sanity check: piano size properly initialized") {
    REQUIRE(piano.GetKeyCount() == 12);
  }

  SECTION("All notes properly initialized") {
    std::vector<Note> expected_notes{
        Note(0, 'A', Accidental::Natural), Note(0, 'A', Accidental::Sharp),
        Note(0, 'B', Accidental::Natural), Note(1, 'C', Accidental::Natural),
        Note(1, 'C', Accidental::Sharp),   Note(1, 'D', Accidental::Natural),
        Note(1, 'D', Accidental::Sharp),   Note(1, 'E', Accidental::Natural),
        Note(1, 'F', Accidental::Natural), Note(1, 'F', Accidental::Sharp),
        Note(1, 'G', Accidental::Natural), Note(1, 'G', Accidental::Sharp)};

    for (size_t index = 0; index < expected_notes.size(); index++) {
      REQUIRE(piano.GetPianoKey(index).GetNote() == expected_notes.at(index));
    }
  }
}

TEST_CASE("Constructor correctly initializes notes on multiple octaves",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 9, 24);

  SECTION("Sanity check: piano size properly initialized") {
    REQUIRE(piano.GetKeyCount() == 24);
  }

  SECTION("All notes properly initialized") {
    std::vector<Note> expected_notes{
        Note(1, 'A', Accidental::Natural), Note(1, 'A', Accidental::Sharp),
        Note(1, 'B', Accidental::Natural), Note(2, 'C', Accidental::Natural),
        Note(2, 'C', Accidental::Sharp),   Note(2, 'D', Accidental::Natural),
        Note(2, 'D', Accidental::Sharp),   Note(2, 'E', Accidental::Natural),
        Note(2, 'F', Accidental::Natural), Note(2, 'F', Accidental::Sharp),
        Note(2, 'G', Accidental::Natural), Note(2, 'G', Accidental::Sharp)};

    for (size_t index = 13; index < expected_notes.size(); index++) {
      REQUIRE(piano.GetPianoKey(index).GetNote() == expected_notes.at(index));
    }
  }
}

TEST_CASE("Constructor correctly initializes full-sized (88 keys) piano",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88);

  SECTION("First note is A0") {
    Note expected_note(0, 'A', Accidental::Natural);
    Note actual_note = piano.GetPianoKey(0).GetNote();
    REQUIRE(actual_note == expected_note);
  }

  SECTION("Last note is C7") {
    Note expected_note(8, 'C', Accidental::Natural);
    Note actual_note = piano.GetPianoKey(piano.GetKeyCount() - 1).GetNote();
    REQUIRE(actual_note == expected_note);
  }
}

TEST_CASE("Constructor correctly initializes piano with offset first_semitone",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88);

  SECTION("First note is C0") {
    Note expected_note(0, 'C', Accidental::Natural);
    Note actual_note = piano.GetPianoKey(0).GetNote();
    REQUIRE(actual_note == expected_note);
  }

  SECTION("Second note is C0#") {
    Note expected_note(0, 'C', Accidental::Sharp);
    Note actual_note = piano.GetPianoKey(1).GetNote();
    REQUIRE(actual_note == expected_note);
  }
}

TEST_CASE("Key labels are set correctly", "[constructor][keylabel]") {
  SECTION("Standard piano with single-octave view") {
    size_t piano_size = 88;
    size_t view_whitekey_count = 8;
    size_t view_first_key = 0;
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, piano_size, view_whitekey_count);

    // Get expected labels
    std::vector<std::string> expected_labels = {
        "A", "W", "S", "D", "R", "F", "T", "G", "H", "U", "J", "I", "K"};

    // Get actual labels automatically using keybinder
    PianoKeybinder keybinder;
    keybinder.SetKeyBinds(piano.GetPianoKeysInView());
    auto t = keybinder.GetNoteChars();
    piano.SetKeyLabels(t);

    size_t view_key_count = 13;
    size_t label_ind = 0;
    for (size_t key_ind = 0; key_ind < piano_size; key_ind++) {
      // All keys except those in view window have labels
      std::string expected_label = " ";

      if (key_ind >= view_first_key && key_ind < view_key_count) {
        // Key is in view window
        expected_label = expected_labels.at(label_ind);
        label_ind++;
      }

      REQUIRE(piano.GetPianoKey(key_ind).GetLabel() == expected_label);
    }
  }
}

TEST_CASE("Correctly collects and returns all PianoKeys in view",
          "[constructor][getpianokeysinview][shiftview]") {
  SECTION("Single-octave view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 8);

    std::vector<Note> expected_notes_in_view{
        Note(0, 'A', Accidental::Natural), Note(0, 'A', Accidental::Sharp),
        Note(0, 'B', Accidental::Natural), Note(1, 'C', Accidental::Natural),
        Note(1, 'C', Accidental::Sharp),   Note(1, 'D', Accidental::Natural),
        Note(1, 'D', Accidental::Sharp),   Note(1, 'E', Accidental::Natural),
        Note(1, 'F', Accidental::Natural), Note(1, 'F', Accidental::Sharp),
        Note(1, 'G', Accidental::Natural), Note(1, 'G', Accidental::Sharp),
        Note(1, 'A', Accidental::Natural)};

    std::vector<PianoKey> actual_keys_in_view = piano.GetPianoKeysInView();

    REQUIRE(expected_notes_in_view.size() == actual_keys_in_view.size());
    for (int ind = 0; ind < expected_notes_in_view.size(); ind++) {
      const Note& expected_note = expected_notes_in_view.at(ind);
      const Note& actual_note = actual_keys_in_view.at(ind).GetNote();
      REQUIRE(expected_note == actual_note);
    }
  }

  SECTION("Standard Piano with larger view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 16);

    REQUIRE(piano.GetPianoKeysInView().size() == 27);
  }

  SECTION("Standard piano after shifted view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 20);
    // Shift up to F7 natural
    piano.ShiftView(47);

    std::vector<Note> expected_notes_in_view{
        Note(7, 'F', Accidental::Natural),
        Note(7, 'F', Accidental::Sharp),
        Note(7, 'G', Accidental::Natural),
        Note(7, 'G', Accidental::Sharp),
        Note(7, 'A', Accidental::Natural),
        Note(7, 'A', Accidental::Sharp),
        Note(7, 'B', Accidental::Natural),
        Note(8, 'C', Accidental::Natural),
    };

    std::vector<PianoKey> actual_keys_in_view = piano.GetPianoKeysInView();

    REQUIRE(expected_notes_in_view.size() == actual_keys_in_view.size());
    for (int ind = 0; ind < expected_notes_in_view.size(); ind++) {
      const Note& expected_note = expected_notes_in_view.at(ind);
      const Note& actual_note = actual_keys_in_view.at(ind).GetNote();
      REQUIRE(expected_note == actual_note);
    }
  }
}

TEST_CASE("GetKey correctly retrieves key from note using semitones") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 20);

  SECTION("Base note (A0) in first octave without accidental") {
    Note note(0, 'A', Accidental::Natural);
    REQUIRE(piano.GetKey(note).GetNote() == note);
  }

  SECTION("Base note in higher octave without accidental") {
    Note note(5, 'A', Accidental::Natural);
    REQUIRE(piano.GetKey(note).GetNote() == note);
  }

  SECTION("Other note in higher octave without accidental") {
    Note note(5, 'F', Accidental::Natural);
    REQUIRE(piano.GetKey(note).GetNote() == note);
  }

  SECTION("Other note in higher octave with accidental") {
    Note note(5, 'G', Accidental::Sharp);
    REQUIRE(piano.GetKey(note).GetNote() == note);
  }
}

// Regression tests on Shiftview after finding numerous unhandled exceptions
TEST_CASE("Stress-test Shiftview for unexpected errors", "[shiftview]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88);
  SECTION("Shift view up and back down") {
    REQUIRE_NOTHROW(piano.ShiftView(80));
    REQUIRE_NOTHROW(piano.ShiftView(80));
    REQUIRE_NOTHROW(piano.ShiftView(-80));
    REQUIRE_NOTHROW(piano.ShiftView(-80));
  }

  SECTION("Shift down and back up") {
    REQUIRE_NOTHROW(piano.ShiftView(-80));
    REQUIRE_NOTHROW(piano.ShiftView(-80));
    REQUIRE_NOTHROW(piano.ShiftView(80));
    REQUIRE_NOTHROW(piano.ShiftView(80));
  }

  SECTION("Shiftview incrementally up and back down") {
    for (size_t count = 0; count < 100; count++) {
      REQUIRE_NOTHROW(piano.ShiftView(1));
    }
    for (size_t count = 0; count < 100; count++) {
      REQUIRE_NOTHROW(piano.ShiftView(-1));
    }
  }

  SECTION("Shiftview incrementally down and back up") {
    for (size_t count = 0; count < 100; count++) {
      REQUIRE_NOTHROW(piano.ShiftView(-1));
    }
    for (size_t count = 0; count < 100; count++) {
      REQUIRE_NOTHROW(piano.ShiftView(1));
    }
  }
}