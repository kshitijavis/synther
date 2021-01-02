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

const std::string Piano::kBackgroundColor = "gray";
const std::string Piano::kOutlineColor = "gold";
const std::string Piano::kOctaveMarkerColor = "white";
const std::string Piano::kFontName = "ToppanBunkyuGothicPr6N-DB";

Piano::Piano(const glm::dvec2& top_left_corner, double width, double height)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      first_semitone_(0) {
}

Piano::Piano(const glm::dvec2& top_left_corner, double width, double height,
             int first_semitone, size_t key_count, size_t view_whitekey_count)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      first_semitone_(first_semitone) {
  SetKeys(first_semitone, key_count, view_whitekey_count);
}

void Piano::SetKeys(int first_semitone, size_t key_count,
                    size_t view_whitekey_count) {
  if (key_count == 0) {
    return;
  }

  first_semitone_ = first_semitone;
  view_whitekey_count_ = view_whitekey_count;

  // Empty list of keys and set new keys given parameters
  keys_.clear();
  keys_.reserve(key_count);
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
  const music::Note& first_note = keys_.at(0).GetNote();
  if (first_note.GetAccidental() == music::Accidental::Natural) {
    view_first_index_ = 0;
  } else {
    // The key is not a natural, so shift view up to the next natural semitone
    view_first_index_ = 1;
  }
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

      // Shift again if view_first is on black key
      const PianoKey& first_key = keys_.at(view_first_index_);
      if (first_key.GetType() == PianoKeyType::Black) {
        if (view_first_index_ == 0) {
          view_first_index_++; // Can't move farther down, so move back up
        } else {
          view_first_index_--; // Move farther down to next white key
        }
      }
    } else if (displacement > 0) {
      view_first_index_++;

      // Shift again if view_first is on black key
      const PianoKey& first_key = keys_.at(view_first_index_);
      if (first_key.GetType() == PianoKeyType::Black) {
        if (view_first_index_ == keys_.size() - 1) {
          view_first_index_--; // Can't move farther up, so move back down
        } else {
          view_first_index_++; // Move farther up to next white key
        }
      }
    }
  }
}

void Piano::SetKeyLabels(
    const std::map<music::Note, std::string>& note_labels) {
  // First empty all key labels
  for (PianoKey& key : keys_) {
    key.SetLabel(" ");
  }

  // Set new key labels
  for (const auto& note_label : note_labels) {
    PianoKey& key = GetPianoKey(note_label.first);
    std::string label = note_label.second;
    key.SetLabel(label);
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
    std::string label = std::string(1, note_label.second);
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

  // Trim black keys at end because they cannot be drawn
  if (!keys_in_view.empty() &&
      keys_in_view.back().GetType() == PianoKeyType::Black) {
    keys_in_view.pop_back();
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

  const std::vector<PianoKey> keys_in_view = GetPianoKeysInView();
  for (size_t key_index = 0; key_index < keys_in_view.size(); key_index++) {
    const PianoKey& key = keys_in_view.at(key_index);

    if (key.GetType() == PianoKeyType::White) {
      glm::vec2 top_left(left_edge, top_edge);
      key.DrawWithLabel(top_left, white_key_width, white_key_height, kFontName);
    } else if (key.GetType() == PianoKeyType::Black) {
      // Draw next white key
      const PianoKey next_white = keys_in_view.at(key_index + 1);
      glm::vec2 white_top_left(left_edge, top_edge);
      next_white.DrawWithLabel(white_top_left, white_key_width,
                               white_key_height, kFontName);
      // Draw current black key
      glm::vec2 black_top_left(left_edge - (black_key_width / 2), top_edge);
      key.DrawWithLabel(black_top_left, black_key_width, black_key_height,
                        kFontName);
      key_index++;  // Extra increment because we drew a white and black key
    }
    left_edge += white_key_width;
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