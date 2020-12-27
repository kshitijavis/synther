//
// Created by Kshitij Sinha on 12/26/20.
//

#include "core/piano_keybinder.h"

#include "cinder/app/App.h"

namespace synther {

const std::vector<PianoKeybinder::KeyEvent> PianoKeybinder::kBlackKeyCodes{
    {ci::app::KeyEvent::KEY_q, 'q'}, {ci::app::KeyEvent::KEY_w, 'w'},
    {ci::app::KeyEvent::KEY_e, 'e'}, {ci::app::KeyEvent::KEY_r, 'r'},
    {ci::app::KeyEvent::KEY_t, 't'}, {ci::app::KeyEvent::KEY_y, 'y'},
    {ci::app::KeyEvent::KEY_u, 'u'}, {ci::app::KeyEvent::KEY_i, 'i'},
    {ci::app::KeyEvent::KEY_o, 'o'}, {ci::app::KeyEvent::KEY_p, 'p'}};

const std::vector<PianoKeybinder::KeyEvent> PianoKeybinder::kWhiteKeyCodes{
    {ci::app::KeyEvent::KEY_a, 'a'}, {ci::app::KeyEvent::KEY_s, 's'},
    {ci::app::KeyEvent::KEY_d, 'd'}, {ci::app::KeyEvent::KEY_f, 'f'},
    {ci::app::KeyEvent::KEY_g, 'g'}, {ci::app::KeyEvent::KEY_h, 'h'},
    {ci::app::KeyEvent::KEY_j, 'j'}, {ci::app::KeyEvent::KEY_k, 'k'},
    {ci::app::KeyEvent::KEY_l, 'l'}, {ci::app::KeyEvent::KEY_SEMICOLON, ';'}};

void PianoKeybinder::SetKeyBinds(
    const std::vector<visualizer::PianoKey>& keys) {
  std::map<int, music::Note> keybinds;

  // Four indices will be used to set keybinds. Each of these will be checked
  // in the for-loop
  size_t white_index = 0;
  size_t black_index = 0;
  size_t key_index = 0;

  // Add the keybinds
  while (white_index < kWhiteKeyCodes.size() &&
         black_index < kBlackKeyCodes.size() && key_index < keys.size()) {
    const visualizer::PianoKey& key = keys.at(key_index);

    if (key.GetType() == visualizer::PianoKeyType::White) {
      int white_key_code = kWhiteKeyCodes.at(white_index).key_code_;
      keybinds.emplace(white_key_code, key.GetNote());

      // Increment both key indices only if we add a white-key mapping
      // This ensures that black_ind still increments between white keys that
      // have no black keys between them (e.g. E and F)
      white_index++;
      black_index++;
    } else if (key.GetType() == visualizer::PianoKeyType::Black) {
      int black_key_code = kBlackKeyCodes.at(black_index).key_code_;
      keybinds.emplace(black_key_code, key.GetNote());
    }
    key_index++;
  }

  keybinds_ = keybinds;
}

bool PianoKeybinder::IsKeybind(int key_code) const {
  return keybinds_.find(key_code) != keybinds_.end();
}

const music::Note& PianoKeybinder::PressKey(int key_code) {
  auto it = keybinds_.find(key_code);
  if (it == keybinds_.end()) {
    throw std::invalid_argument("No piano key bound to the given key_event");
  }

  return it->second;
}

std::map<music::Note, char> PianoKeybinder::GetNoteChars() const {
  std::map<music::Note, char> note_chars;

  // Create map of KeyEvents to chars for efficient lookup
  std::map<int, char> key_chars;
  for (KeyEvent key_event : kWhiteKeyCodes) {
    key_chars[key_event.key_code_] = key_event.key_char_;
  }
  for (KeyEvent key_event : kBlackKeyCodes) {
    key_chars[key_event.key_code_] = key_event.key_char_;
  }

  // Add note->character pairs to map
  for (const auto& keybind : keybinds_) {
    int key_code = keybind.first;
    const music::Note& note = keybind.second;
    char key_char = std::toupper(key_chars.at(key_code));
    note_chars.emplace(note, key_char);
  }

  return note_chars;
}

}  // namespace synther
