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
  std::map<int, visualizer::PianoKey> keybinds;

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
      keybinds.emplace(white_key_code, key);

      // Increment both key indices only if we add a white-key mapping
      // This ensures that black_ind still increments between white keys that
      // have no black keys between them (e.g. E and F)
      white_index++;
      black_index++;
    } else if (key.GetType() == visualizer::PianoKeyType::Black) {
      int black_key_code = kBlackKeyCodes.at(black_index).key_code_;
      keybinds.emplace(black_key_code, key);
    }
    key_index++;
  }

  keybinds_ = keybinds;
}

bool PianoKeybinder::IsKeybind(int key_code) const {
  return keybinds_.find(key_code) != keybinds_.end();
}

const visualizer::PianoKey& PianoKeybinder::PressKey(int key_code) {
  auto it = keybinds_.find(key_code);
  if (it == keybinds_.end()) {
    throw std::invalid_argument("No piano key bound to the given key_event");
  }

  return it->second;
}

}  // namespace synther
