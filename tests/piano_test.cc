//
// Created by Kshitij Sinha on 11/19/20.
//
#include "visualizer/piano.h"

#include <catch2/catch.hpp>
#include <vector>

#include "cinder/Color.h"
#include "cinder/app/App.h"
#include "core/music_note.h"

using synther::music::Accidental;
using synther::music::Note;
using synther::visualizer::Piano;

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

TEST_CASE("Key Binds are set correctly",
          "[constructor][keybind][iskeybind][shiftview][playkey]") {
  SECTION(
      "Constructor correctly initializes key binds for standard piano,"
      "with single-octave view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 8);

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_a, Note(0, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_w, Note(0, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_s, Note(0, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_d, Note(1, 'C', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_r, Note(1, 'C', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_f, Note(1, 'D', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_t, Note(1, 'D', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_g, Note(1, 'E', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_h, Note(1, 'F', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_u, Note(1, 'F', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_j, Note(1, 'G', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_i, Note(1, 'G', Accidental::Sharp)}};

    for (auto key_bind : key_binds) {
      REQUIRE(piano.IsKeybind(key_bind.first));
      REQUIRE(piano.GetNote(key_bind.first) == key_bind.second);
    }
  }

  SECTION(
      "Constructor correctly initializes key binds for standard piano,"
      "with larger view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 20);

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_k, Note(1, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_o, Note(1, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_l, Note(1, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_SEMICOLON, Note(2, 'C', Accidental::Natural)}};

    for (auto key_bind : key_binds) {
      REQUIRE(piano.IsKeybind(key_bind.first));
      REQUIRE(piano.GetNote(key_bind.first) == key_bind.second);
    }
  }

  SECTION("Standard piano after shifted view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 20);
    // Shift up to F7 natural
    piano.ShiftView(47);

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_a, Note(7, 'F', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_w, Note(7, 'F', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_s, Note(7, 'G', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_e, Note(7, 'G', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_d, Note(7, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_r, Note(7, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_f, Note(7, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_g, Note(8, 'C', Accidental::Natural)},
    };

    for (auto key_bind : key_binds) {
      REQUIRE(piano.IsKeybind(key_bind.first));
      REQUIRE(piano.GetNote(key_bind.first) == key_bind.second);
    }
  }
}

TEST_CASE("Key labels are set correctly", "[constructor][keylabel]") {
  SECTION("Constructor on standard piano with single-octave view") {
    size_t piano_size = 88;
    size_t view_whitekey_count = 8;
    size_t view_first_key = 0;
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, piano_size, view_whitekey_count);

    std::vector<std::string> expected_labels = {
        "A", "W", "S", "D", "R", "F", "T", "G", "H", "U", "J", "I", "K"};

    size_t view_key_count = 13;
    size_t label_ind = 0;
    for (size_t key_ind = 0; key_ind < piano_size; key_ind++) {
      std::string expected_label = " ";
      if (key_ind >= view_first_key && key_ind < view_key_count) {
        expected_label = expected_labels.at(label_ind);
        label_ind++;
      }

      REQUIRE(piano.GetPianoKey(key_ind).GetLabel() == expected_label);
    }
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