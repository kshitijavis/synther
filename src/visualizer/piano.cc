//
// Created by Kshitij Sinha on 11/18/20.
//

#include "visualizer/piano.h"

#include <vector>

#include "cinder/Color.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "core/music_note.h"

namespace synther {

namespace visualizer {

const std::vector<Piano::KeyEvent> Piano::kBlackKeyCodes{
    {ci::app::KeyEvent::KEY_q, 'q'}, {ci::app::KeyEvent::KEY_w, 'w'},
    {ci::app::KeyEvent::KEY_e, 'e'}, {ci::app::KeyEvent::KEY_r, 'r'},
    {ci::app::KeyEvent::KEY_t, 't'}, {ci::app::KeyEvent::KEY_y, 'y'},
    {ci::app::KeyEvent::KEY_u, 'u'}, {ci::app::KeyEvent::KEY_i, 'i'},
    {ci::app::KeyEvent::KEY_o, 'o'}, {ci::app::KeyEvent::KEY_p, 'p'}
};

const std::vector<Piano::KeyEvent> Piano::kWhiteKeyCodes{
    {ci::app::KeyEvent::KEY_a, 'a'}, {ci::app::KeyEvent::KEY_s, 's'},
    {ci::app::KeyEvent::KEY_d, 'd'}, {ci::app::KeyEvent::KEY_f, 'f'},
    {ci::app::KeyEvent::KEY_g, 'g'}, {ci::app::KeyEvent::KEY_h, 'h'},
    {ci::app::KeyEvent::KEY_j, 'j'}, {ci::app::KeyEvent::KEY_k, 'k'},
    {ci::app::KeyEvent::KEY_l, 'l'}, {ci::app::KeyEvent::KEY_SEMICOLON, ';'}
};

Piano::Piano(const glm::dvec2& top_left_corner, double width, double height,
             int first_semitone, size_t key_count, size_t view_whitekey_count)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      first_semitone_(first_semitone) {
  // Set view_first_wholetone_ and ensure that it represents a white key,
  // i.e. a natural-note
  music::Note first_note(first_semitone, kPriority);
  if (first_note.GetAccidental() == music::Accidental::Natural) {
    view_first_ = 0;
  } else {
    // The key is not a natural, so shift view up to the next natural semitone
    view_first_ = 1;
  }

  // Initialize keys_
  for (int semitone = first_semitone_; semitone < first_semitone_ + key_count;
       semitone++) {
    music::Note to_add(semitone, kPriority);
    PianoKeyType type = to_add.GetAccidental() == music::Accidental::Natural
                            ? PianoKeyType::White
                            : PianoKeyType::Black;
    keys_.emplace_back(music::Note(semitone, kPriority), type);
  }

  // Set view_whitekey_count_ to default, unless the white keys on the board are
  // less than the default
  view_whitekey_count_ = std::min(CountNaturals(), view_whitekey_count);

  SetKeyBinds();
  SetKeyLabels();
}

void Piano::Draw() const {
  glm::vec2 bottom_right_corner =
      top_left_corner_ + glm::dvec2(width_, height_);
  ci::Rectf keyboard_bounds(top_left_corner_, bottom_right_corner);

  // Draw background
  ci::gl::color(kBackgroundColor);
  ci::gl::drawSolidRect(keyboard_bounds);
  ci::gl::color(kOutlineColor);
  ci::gl::drawStrokedRect(keyboard_bounds);

  glm::dvec2 keys_top_left = top_left_corner_ +
                             glm::dvec2(0, height_ * kTopPaddingFactor);
  double keys_height = height_ * (1-kTopPaddingFactor);

  DrawKeys(keys_top_left, width_, keys_height);
  DrawOctaveMarkers(top_left_corner_, width_, height_ * kTopPaddingFactor);
}

void Piano::ShiftView(int displacement) {
  size_t distance = abs(displacement);

  for (size_t keys_shifted = 0; keys_shifted < distance; keys_shifted++) {
    if ((view_first_ <= 0 && displacement < 0) ||
        (view_first_ >= keys_.size() - 1 && displacement > 0)) {
      break;
    }

    if (displacement < 0) {
      view_first_--;
      // shift down again if view_first is on black key
      if (keys_.at(view_first_).GetType() == PianoKeyType::Black) {
        view_first_--;
      }
    } else if (displacement > 0) {
      view_first_++;
      // shift up again if view_first is on black key
      if (keys_.at(view_first_).GetType() == PianoKeyType::Black) {
        view_first_++;
      }
    }
  }

  SetKeyBinds();
  SetKeyLabels();
}

const PianoKey& Piano::GetPianoKey(int index) const {
  return keys_.at(index);
}

const size_t Piano::GetKeyCount() const {
  return keys_.size();
}

const size_t Piano::CountNaturals() const {
  size_t natural_count = 0;
  for (const PianoKey& key : keys_) {
    if (key.GetNote().GetAccidental() == music::Accidental::Natural) {
      natural_count++;
    }
  }
  return natural_count;
}

void Piano::SetKeyBinds() {
  std::map<int, PianoKey*> keybinds;

  size_t white_index = 0;
  size_t black_index = 0;
  size_t key_index = std::max(view_first_,0);
  size_t white_keys_accessed = 0;

  // Add the keybinds
  while (white_index < kWhiteKeyCodes.size() &&
         black_index < kBlackKeyCodes.size() &&
         white_keys_accessed < view_whitekey_count_ &&
         key_index < keys_.size()) {
    PianoKey& key = keys_.at(key_index);
    if (key.GetType() == PianoKeyType::White) {
      int white_key_code = kWhiteKeyCodes.at(white_index).key_code_;
      keybinds[white_key_code] = &key;

      // Increment both key indices only if we add a white-key mapping
      // Ensures that black_ind still increments between white keys that
      // have no black keys between them (e.g. E and F)
      white_index++;
      black_index++;
      white_keys_accessed++;
    } else if (key.GetType() == PianoKeyType::Black) {
      int black_key_code = kBlackKeyCodes.at(black_index).key_code_;
      keybinds[black_key_code] = &key;
    }
    key_index++;
  }

  keybinds_ = keybinds;
}

const music::Note& Piano::GetNote(int key_code) {
  return GetKey(key_code).GetNote();
}

void Piano::PressKey(int key_code) {
  GetKey(key_code).PressKey();
}

void Piano::ReleaseKey(int key_code) {
  GetKey(key_code).ReleaseKey();
}

bool Piano::IsKeybind(int key_code) const {
  return keybinds_.find(key_code) != keybinds_.end();
}

PianoKey& Piano::GetKey(int key_code) {
  auto it = keybinds_.find(key_code);
  if (it == keybinds_.end()) {
    throw std::invalid_argument("No piano key bound to the given key_event");
  }

  PianoKey* key = it->second;
  return *key;
}

void Piano::SetKeyLabels() {
  // First empty all key labels
  for (PianoKey& key : keys_) {
    key.SetLabel(' ');
  }

  // Create map of KeyEvents to chars for efficient lookup
  std::map<int, char> key_events;
  for (KeyEvent key_event : kWhiteKeyCodes) {
    key_events[key_event.key_code_] = key_event.key_char_;
  }
  for (KeyEvent key_event : kBlackKeyCodes) {
    key_events[key_event.key_code_] = key_event.key_char_;
  }

  // Set new key labels
  for (auto keybind : keybinds_) {
    int key_code = keybind.first;
    PianoKey* key = keybind.second;
    char key_char = key_events.at(key_code);
    key->SetLabel(key_char);
  }
}

void Piano::DrawKeys(const glm::dvec2& top_left_corner, double width,
                     double height) const {
  double white_key_height = height;
  double black_key_height = white_key_height * kBlackKeyHeightFactor;
  double white_key_width = width / view_whitekey_count_;
  double black_key_width = white_key_width * kBlackKeyWidthFactor;

  double top_edge = top_left_corner.y;
  double left_edge = top_left_corner.x;

  size_t key_index = std::max(0,view_first_);
  size_t white_keys_drawn = 0;
  while (white_keys_drawn < view_whitekey_count_ && key_index < keys_.size()) {
    const PianoKey key = keys_.at(key_index);

    if (key.GetType() == PianoKeyType::White) {
      glm::vec2 top_left(left_edge, top_edge);
      key.Draw(top_left, white_key_width, white_key_height);
      key_index++;
    } else if (key.GetType() == PianoKeyType::Black) {
      // Draw next white key
      const PianoKey next_white = keys_.at(key_index + 1);
      glm::vec2 white_top_left(left_edge, top_edge);
      next_white.Draw(white_top_left, white_key_width, white_key_height);
      // Draw current black key
      glm::vec2 black_top_left(left_edge - (black_key_width / 2), top_edge);
      key.Draw(black_top_left, black_key_width, black_key_height);
      key_index += 2;
    }
    left_edge += white_key_width;
    white_keys_drawn++;
  }
}

void Piano::DrawOctaveMarkers(const glm::dvec2& top_left_corner, double width,
                              double height) const {
  double white_key_width = width / view_whitekey_count_;
  double top_edge = top_left_corner.y;
  double left_edge = top_left_corner.x;

  size_t key_index = std::max(0,view_first_);
  size_t white_keys_accessed = 0;

  while (white_keys_accessed < view_whitekey_count_ && key_index < keys_.size()) {
    const PianoKey key = keys_.at(key_index);
    const music::Note& note = key.GetNote();

    if (toupper(note.GetLetter()) == kOctaveMarkerLetter &&
        note.GetAccidental() == music::Accidental::Natural) {
      int octave = note.GetOctave();
      std::string octave_marker = kOctaveMarkerLetter + std::to_string(octave);

      glm::dvec2 marker_center(left_edge + white_key_width / 2, top_edge);
      ci::gl::drawStringCentered(octave_marker, marker_center,
                                 ci::Color("white"),
                                 ci::Font(kFontName, height));
    }

    if (key.GetType() == PianoKeyType::White) {
      left_edge += white_key_width;
      white_keys_accessed++;
    }
    key_index++;
  }
}

}  // namespace visualizer

}  // namespace synther