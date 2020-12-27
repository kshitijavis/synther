//
// Created by Kshitij Sinha on 11/18/20.
//

#include "visualizer/piano.h"

#include <vector>

#include "cinder/Color.h"
#include "cinder/app/App.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/gl/gl.h"
#include "core/music_note.h"

namespace synther {

namespace visualizer {

const std::vector<Piano::KeyEvent> Piano::kBlackKeyCodes{
    {ci::app::KeyEvent::KEY_q, 'q'}, {ci::app::KeyEvent::KEY_w, 'w'},
    {ci::app::KeyEvent::KEY_e, 'e'}, {ci::app::KeyEvent::KEY_r, 'r'},
    {ci::app::KeyEvent::KEY_t, 't'}, {ci::app::KeyEvent::KEY_y, 'y'},
    {ci::app::KeyEvent::KEY_u, 'u'}, {ci::app::KeyEvent::KEY_i, 'i'},
    {ci::app::KeyEvent::KEY_o, 'o'}, {ci::app::KeyEvent::KEY_p, 'p'}};

const std::vector<Piano::KeyEvent> Piano::kWhiteKeyCodes{
    {ci::app::KeyEvent::KEY_a, 'a'}, {ci::app::KeyEvent::KEY_s, 's'},
    {ci::app::KeyEvent::KEY_d, 'd'}, {ci::app::KeyEvent::KEY_f, 'f'},
    {ci::app::KeyEvent::KEY_g, 'g'}, {ci::app::KeyEvent::KEY_h, 'h'},
    {ci::app::KeyEvent::KEY_j, 'j'}, {ci::app::KeyEvent::KEY_k, 'k'},
    {ci::app::KeyEvent::KEY_l, 'l'}, {ci::app::KeyEvent::KEY_SEMICOLON, ';'}};

const std::string Piano::kBackgroundColor = "gray";
const std::string Piano::kOutlineColor = "gold";
const std::string Piano::kOctaveMarkerColor = "white";
const std::string Piano::kFontName = "ToppanBunkyuGothicPr6N-DB";

Piano::Piano(const glm::dvec2& top_left_corner, double width, double height,
             int first_semitone, size_t key_count, size_t view_whitekey_count)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      first_semitone_(first_semitone) {
  // Initialize keys_
  for (int semitone = first_semitone_; semitone < first_semitone_ + key_count;
       semitone++) {
    music::Note to_add(semitone, kPriority);
    PianoKeyType type = to_add.GetAccidental() == music::Accidental::Natural
                            ? PianoKeyType::White
                            : PianoKeyType::Black;
    keys_.emplace_back(music::Note(semitone, kPriority), type);
  }

  // Set view_first_index_ and ensure that it represents a white key,
  // i.e. a natural-note
  music::Note first_note(first_semitone, kPriority);
  if (first_note.GetAccidental() == music::Accidental::Natural) {
    view_first_index_ = 0;
  } else {
    // The key is not a natural, so shift view up to the next natural semitone
    view_first_index_ = 1;
  }

  // Set view_whitekey_count_ to the input parameters, unless there are fewer
  // white keys on the keyboard than specified by the input
  view_whitekey_count_ = std::min(CountWhiteKeys(), view_whitekey_count);
}

void Piano::Draw() const {
  // Draw background
  glm::vec2 bottom_right_corner =
      top_left_corner_ + glm::dvec2(width_, height_);
  ci::Rectf keyboard_bounds(top_left_corner_, bottom_right_corner);

  ci::gl::color(ci::Color(kBackgroundColor.c_str()));
  ci::gl::drawSolidRect(keyboard_bounds);

  // Draw keys
  glm::dvec2 keys_top_left =
      top_left_corner_ + glm::dvec2(0, height_ * kTopPaddingFactor);
  double keys_height = height_ * (1 - kTopPaddingFactor);
  DrawKeys(keys_top_left, width_, keys_height);

  // Draw octave markers
  DrawOctaveMarkers(top_left_corner_, width_, height_ * kTopPaddingFactor);
}

void Piano::ShiftView(int displacement) {
  size_t distance = abs(displacement);

  for (size_t keys_shifted = 0; keys_shifted < distance; keys_shifted++) {
    // Prevent first index from shifting off the keyboard
    if ((view_first_index_ <= 0 && displacement < 0) ||
        (view_first_index_ >= keys_.size() - 1 && displacement > 0)) {
      break;
    }

    if (displacement < 0) {
      view_first_index_--;
      // shift down again if view_first is on black key
      if (keys_.at(view_first_index_).GetType() == PianoKeyType::Black) {
        view_first_index_--;
      }
    } else if (displacement > 0) {
      view_first_index_++;
      // shift up again if view_first is on black key
      if (keys_.at(view_first_index_).GetType() == PianoKeyType::Black) {
        view_first_index_++;
      }
    }
  }
}

void Piano::SetKeyLabels(const std::map<music::Note, char>& note_labels) {
  // First empty all key labels
  for (PianoKey& key : keys_) {
    key.SetLabel(" ");
  }

  // Set new key labels
  for (const auto& note_label : note_labels) {
    PianoKey& key = GetPianoKey(note_label.first);
    std::string label(1, note_label.second);
    key.SetLabel(label);
  }
}

const PianoKey& Piano::GetPianoKey(int index) const {
  return keys_.at(index);
}

std::vector<PianoKey> Piano::GetPianoKeysInView() const {
  // Unoptimized solution: loop through keys by the number of white keys in view
  std::vector<PianoKey> keys_in_view;

  size_t key_index = std::max(0, view_first_index_);
  size_t white_keys_drawn = 0;
  while (white_keys_drawn < view_whitekey_count_ && key_index < keys_.size()) {
    const PianoKey& key = keys_.at(key_index);
    keys_in_view.push_back(key);

    if (key.GetType() == PianoKeyType::White) {
      white_keys_drawn++;
    }
    key_index++;
  }

  return keys_in_view;
}

const size_t Piano::GetKeyCount() const {
  return keys_.size();
}

const size_t Piano::CountWhiteKeys() const {
  size_t white_key_count = 0;
  for (const PianoKey& key : keys_) {
    if (key.GetType() == PianoKeyType::White) {
      white_key_count++;
    }
  }
  return white_key_count;
}

void Piano::PressKey(const music::Note& note) {
  GetPianoKey(note).PressKey();
}

void Piano::ReleaseKey(const music::Note& note) {
  GetPianoKey(note).ReleaseKey();
}

PianoKey& Piano::GetPianoKey(const music::Note& note) {
  size_t semitone_index = note.GetSemitoneIndex();
  size_t key_index = semitone_index - first_semitone_;
  if (key_index < 0 || key_index >= keys_.size()) {
    throw std::invalid_argument("Note does not exist on the piano");
  }
  return keys_.at(key_index);
}

void Piano::DrawKeys(const glm::dvec2& top_left_corner, double width,
                     double height) const {
  // Set key sizes
  double white_key_height = height;
  double black_key_height = white_key_height * kBlackKeyHeightFactor;
  double white_key_width = width / view_whitekey_count_;
  double black_key_width = white_key_width * kBlackKeyWidthFactor;

  // Loop through every key, drawing black keys after adjacent white keys
  // so the black key appears on top
  double top_edge = top_left_corner.y;
  double left_edge = top_left_corner.x;

  size_t key_index = std::max(0, view_first_index_);
  size_t white_keys_drawn = 0;
  while (white_keys_drawn < view_whitekey_count_ && key_index < keys_.size()) {
    const PianoKey key = keys_.at(key_index);

    if (key.GetType() == PianoKeyType::White) {
      glm::vec2 top_left(left_edge, top_edge);
      key.DrawWithLabel(top_left, white_key_width, white_key_height, kFontName);
      key_index++;
    } else if (key.GetType() == PianoKeyType::Black) {
      // Draw next white key
      const PianoKey next_white = keys_.at(key_index + 1);
      glm::vec2 white_top_left(left_edge, top_edge);
      next_white.DrawWithLabel(white_top_left, white_key_width,
                               white_key_height, kFontName);
      // Draw current black key
      glm::vec2 black_top_left(left_edge - (black_key_width / 2), top_edge);
      key.DrawWithLabel(black_top_left, black_key_width, black_key_height,
                        kFontName);
      key_index += 2; // Increment by two because we drew a white and black key
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

  size_t key_index = std::max(0, view_first_index_);
  size_t white_keys_accessed = 0;

  while (white_keys_accessed < view_whitekey_count_ &&
         key_index < keys_.size()) {
    const PianoKey key = keys_.at(key_index);
    const music::Note& note = key.GetNote();

    if (toupper(note.GetLetter()) == kOctaveMarkerLetter &&
        note.GetAccidental() == music::Accidental::Natural) {
      int octave = note.GetOctave();
      std::string octave_marker = kOctaveMarkerLetter + std::to_string(octave);
      double font_size = height * kOctaveMakerSizeFactor;
      glm::dvec2 marker_center(left_edge + white_key_width / 2,
                               top_edge + (height - font_size) / 2);
      ci::gl::drawStringCentered(octave_marker, marker_center,
                                 ci::Color(kOctaveMarkerColor.c_str()),
                                 ci::Font(kFontName, font_size));
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