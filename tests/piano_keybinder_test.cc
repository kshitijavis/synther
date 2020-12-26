//
// Created by Kshitij Sinha on 11/19/20.
//
#include "core/music_note.h"
#include "core/piano_keybinder.h"
#include "visualizer/piano.h"

#include <catch2/catch.hpp>
#include "cinder/app/App.h"

using synther::music::Note;
using synther::music::Accidental;
using synther::PianoKeybinder;
using synther::visualizer::Piano;

TEST_CASE("Key Binds are set correctlyj adsfoiajd gapioewj aewpfoijwe",
          "[constructor][setkeybinds][iskeybind][presskey]") {
  PianoKeybinder keybinder;

  SECTION(
      "Correctly initializes key binds for standard piano, with single-octave "
      "view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 8);
    keybinder.SetKeyBinds(piano.GetPianoKeysInView());

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
      REQUIRE(keybinder.IsKeybind(key_bind.first));
      REQUIRE(keybinder.PressKey(key_bind.first).GetNote() == key_bind.second);
    }
  }

  SECTION(
      "Constructor correctly initializes key binds for standard piano,"
      "with larger view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 20);
    keybinder.SetKeyBinds(piano.GetPianoKeysInView());

    std::map<int, Note> key_binds{
        {ci::app::KeyEvent::KEY_k, Note(1, 'A', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_o, Note(1, 'A', Accidental::Sharp)},
        {ci::app::KeyEvent::KEY_l, Note(1, 'B', Accidental::Natural)},
        {ci::app::KeyEvent::KEY_SEMICOLON, Note(2, 'C', Accidental::Natural)}};

    for (auto key_bind : key_binds) {
      REQUIRE(keybinder.IsKeybind(key_bind.first));
      REQUIRE(keybinder.PressKey(key_bind.first).GetNote() == key_bind.second);
    }
  }

  SECTION("Standard piano after shifted view") {
    Piano piano(glm::dvec2(0, 0), 5, 5, 9, 88, 20);
    // Shift up to F7 natural
    piano.ShiftView(47);
    keybinder.SetKeyBinds(piano.GetPianoKeysInView());

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
      REQUIRE(keybinder.IsKeybind(key_bind.first));
      REQUIRE(keybinder.PressKey(key_bind.first).GetNote() == key_bind.second);
    }
  }
}