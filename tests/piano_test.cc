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
  Piano piano(glm::dvec2(0, 0), 5, 5, 0, 12);

  SECTION("Sanity check: piano size properly initialized") {
    REQUIRE(piano.GetKeyCount() == 12);
  }

  SECTION("All notes properly initialized") {
    std::vector<Note> expected_notes{
        Note(0, 'A', Accidental::Natural), Note(0, 'A', Accidental::Sharp),
        Note(0, 'B', Accidental::Natural), Note(0, 'C', Accidental::Natural),
        Note(0, 'C', Accidental::Sharp),   Note(0, 'D', Accidental::Natural),
        Note(0, 'D', Accidental::Sharp),   Note(0, 'E', Accidental::Natural),
        Note(0, 'F', Accidental::Natural), Note(0, 'F', Accidental::Sharp),
        Note(0, 'G', Accidental::Natural), Note(0, 'G', Accidental::Sharp)};

    for (size_t index = 0; index < expected_notes.size(); index++) {
      REQUIRE(piano.GetPianoKey(index).GetNote() == expected_notes.at(index));
    }
  }
}

TEST_CASE("Constructor correctly initializes notes on multiple octaves",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 0, 24);

  SECTION("Sanity check: piano size properly initialized") {
    REQUIRE(piano.GetKeyCount() == 24);
  }

  SECTION("All notes properly initialized") {
    std::vector<Note> expected_notes{
        Note(1, 'A', Accidental::Natural), Note(1, 'A', Accidental::Sharp),
        Note(1, 'B', Accidental::Natural), Note(1, 'C', Accidental::Natural),
        Note(1, 'C', Accidental::Sharp),   Note(1, 'D', Accidental::Natural),
        Note(1, 'D', Accidental::Sharp),   Note(1, 'E', Accidental::Natural),
        Note(1, 'F', Accidental::Natural), Note(1, 'F', Accidental::Sharp),
        Note(1, 'G', Accidental::Natural), Note(1, 'G', Accidental::Sharp)};

    for (size_t index = 13; index < expected_notes.size(); index++) {
      REQUIRE(piano.GetPianoKey(index).GetNote() == expected_notes.at(index));
    }
  }
}

TEST_CASE("Constructor correctly initializes full-sized (88 keys) piano",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88);

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

TEST_CASE("Constructor correctly initializes piano with offset first_semitone",
          "[constructor]") {
  Piano piano(glm::dvec2(0, 0), 5, 5, 10, 88);

  SECTION("First note is G0") {
    Note expected_note(0, 'G', Accidental::Natural);
    Note actual_note = piano.GetPianoKey(0).GetNote();
    REQUIRE(actual_note == expected_note);
  }

  SECTION("Second note is G0#") {
    Note expected_note(0, 'G', Accidental::Sharp);
    Note actual_note = piano.GetPianoKey(1).GetNote();
    REQUIRE(actual_note == expected_note);
  }
}

TEST_CASE("Key Binds are set correctly",
          "[constructor][keybind][shiftview][playkey]") {
  SECTION("Constructor correctly initializes key binds for standard piano,"
      "with single-octave view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88, 8);

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_a, Note(0, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_w, Note(0, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_s, Note(0, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_d, Note(0, 'C', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_r, Note(0, 'C', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_f, Note(0, 'D', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_t, Note(0, 'D', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_g, Note(0, 'E', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_h, Note(0, 'F', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_u, Note(0, 'F', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_j, Note(0, 'G', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_i, Note(0, 'G', Accidental::Sharp)}
    };

    for (auto key_bind : key_binds) {
      REQUIRE(piano.PlayKey(key_bind.first) == key_bind.second);
    }
  }

  SECTION("Constructor correctly initializes key binds for standard piano,"
          "with larger view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88, 20);

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_k, Note(1, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_o, Note(1, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_l, Note(1, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_SEMICOLON, Note(1, 'C', Accidental::Natural)}
    };

    for (auto key_bind : key_binds) {
      REQUIRE(piano.PlayKey(key_bind.first) == key_bind.second);
    }
  }

  SECTION("Standard piano after shifted view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88, 20);
    // Shift up to F8 natural
    piano.ShiftView(47);

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_a, Note(6, 'F', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_w, Note(6, 'F', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_s, Note(6, 'G', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_e, Note(6, 'G', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_d, Note(7, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_r, Note(7, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_f, Note(7, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_g, Note(7, 'C', Accidental::Natural)},
    };

    for (auto key_bind : key_binds) {
      REQUIRE(piano.PlayKey(key_bind.first) == key_bind.second);
    }
  }
}

// The following test cases test the Draw() method. These cases are selected
// to ensure that no actual Cinder drawing is done. In all the following
// tests, the method will quit before drawing any object using Cinder.
// Otherwise, an exception would be thrown, causing the test suite to fail
TEST_CASE("Draw does not cause unexpected errors after ShiftView",
          "[shiftview][draw][constructor]") {
  SECTION("Standard piano, upward shift") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88);
    REQUIRE_NOTHROW(piano.ShiftView(150));
    REQUIRE_NOTHROW(piano.Draw());
  }

  SECTION("Standard piano, downward shift") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88);
    REQUIRE_NOTHROW(piano.ShiftView(-150));
    REQUIRE_NOTHROW(piano.Draw());
  }

  SECTION("Standard piano with view size of 0, downward shift") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88, 0);
    REQUIRE_NOTHROW(piano.ShiftView(150));
    REQUIRE_NOTHROW(piano.Draw());
  }

  SECTION("Standard piano with view size of 0, downward shift") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 0, 88, 0);
    REQUIRE_NOTHROW(piano.ShiftView(-150));
    REQUIRE_NOTHROW(piano.Draw());
  }
}