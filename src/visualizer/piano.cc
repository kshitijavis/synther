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

const std::vector<int> Piano::kBlackKeyEvents{
    ci::app::KeyEvent::KEY_q, ci::app::KeyEvent::KEY_w,
    ci::app::KeyEvent::KEY_e, ci::app::KeyEvent::KEY_r,
    ci::app::KeyEvent::KEY_t, ci::app::KeyEvent::KEY_y,
    ci::app::KeyEvent::KEY_u, ci::app::KeyEvent::KEY_i,
    ci::app::KeyEvent::KEY_o, ci::app::KeyEvent::KEY_p};

const std::vector<int> Piano::kWhiteKeyEvents{
    ci::app::KeyEvent::KEY_a, ci::app::KeyEvent::KEY_s,
    ci::app::KeyEvent::KEY_d, ci::app::KeyEvent::KEY_f,
    ci::app::KeyEvent::KEY_g, ci::app::KeyEvent::KEY_h,
    ci::app::KeyEvent::KEY_j, ci::app::KeyEvent::KEY_k,
    ci::app::KeyEvent::KEY_l, ci::app::KeyEvent::KEY_SEMICOLON};

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
  view_whitekey_count_ =
      std::min(CountNaturals(), view_whitekey_count);

  SetKeyBinds();
}

void Piano::Draw() const {
  double white_key_height = height_;
  double black_key_height = white_key_height * kBlackKeyHeightFactor;
  double white_key_width = width_ / view_whitekey_count_;
  double black_key_width = white_key_width * kBlackKeyWidthFactor;

  double top_edge = top_left_corner_.y;
  double left_edge = top_left_corner_.x;

  size_t key_index = view_first_;
  size_t white_keys_drawn = 0;
  while (white_keys_drawn < view_whitekey_count_ && key_index < keys_.size()) {
    const PianoKey key = keys_.at(key_index);
    const music::Note& note = key.GetNote();

    if (note.GetAccidental() == music::Accidental::Natural) {
      glm::vec2 top_left(left_edge, top_edge);
      key.Draw(top_left, white_key_width, white_key_height);
      key_index++;
    } else {
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

void Piano::ShiftView(int displacement) {
  size_t distance = abs(displacement);
  for (size_t keys_shifted = 0; keys_shifted < distance; keys_shifted++) {
    if (displacement < 0) {
      view_first_--;
      // shift down again if view_first is on black key
      if (view_first_ >= 0 &&
          keys_.at(view_first_).GetType() == PianoKeyType::Black) {
        view_first_--;
      }
    } else if (displacement > 0) {
      view_first_++;
      // shift up again if view_first is on black key
      if (view_first_ < keys_.size() &&
          keys_.at(view_first_).GetType() == PianoKeyType::Black) {
        view_first_++;
      }
    }
  }

  SetKeyBinds();
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

const void Piano::SetKeyBinds() {
  std::map<int, PianoKey> keybinds;

  size_t white_ind = 0;
  size_t black_ind = 0;
  size_t key_ind = view_first_;

  // Add the keybinds
  while (white_ind < kWhiteKeyEvents.size() &&
         black_ind < kBlackKeyEvents.size() &&
         key_ind < view_whitekey_count_ + view_first_ &&
         key_ind < keys_.size()) {
    const PianoKey& key = keys_.at(key_ind);
    if (key.GetType() == PianoKeyType::White) {
      int white_key_event = kWhiteKeyEvents.at(white_ind);
      keybinds.emplace(white_key_event, key);

      // Increment both key indices only if we add a white-key mapping
      // This ensures that black_ind still increments between white keys that
      // have no black keys between them
      white_ind++;
      black_ind++;
    } else if (key.GetType() == PianoKeyType::Black) {
      int black_key_event = kBlackKeyEvents.at(black_ind);
      keybinds.emplace(black_key_event, key);
    }
    key_ind++;
  }

  keybinds_ = keybinds;
}

const music::Note& Piano::PlayKey(int key_event) {
  auto it = keybinds_.find(key_event);
  if (it == keybinds_.end()) {
    throw std::invalid_argument("No piano key bound to the given key_event");
  }

  // Todo: Update corresponding PianoKey to temporarily change color
  const PianoKey& key = it->second;
  return key.GetNote();
}

}  // namespace visualizer

}  // namespace synther