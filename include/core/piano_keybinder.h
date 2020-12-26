//
// Created by Kshitij Sinha on 12/26/20.
//

#ifndef SYNTHER_PIANO_CONTROLLER_H
#define SYNTHER_PIANO_CONTROLLER_H

#include <vector>

#include "cinder/gl/gl.h"
#include "visualizer/piano_key.h"

namespace synther {

class PianoKeybinder {
 public:
  /**
   * Constructs a default PianoKeybinder without any keybinds. To set up
   *   PianoKeybinder for use, SetKeyBinds must be called
   */
  PianoKeybinder() = default;

  /**
   * Maps keys on the piano to cinder KeyEvents. Uses the first row of the
   *   keyboard (QWERTY..) for black keys and the second row (ASDF...) for
   *   white keys. Adds keybinds to the private field keybinds_. Maps keys
   *   using the natural staggered layout of the computer keyboard. This allows
   *   keybinds to lie between white keybinds, just as they would on a physical
   *   piano.
   */
  void SetKeyBinds(const std::vector<visualizer::PianoKey>& keys);

  /**
   * Checks if the input key_code represents a valid keybind on the piano. In
   *   other words, checks if the KeyEvent corresponding to the key_code is
   *   mapped to any PianoKey on the keyboard
   * @param key_code an int representing ci::app::KeyEvent code
   * @return true if the input key_code is a valid keybind
   */
  bool IsKeybind(int key_code) const;

  /**
   * Get the visualizer::PianoKey mapped to a key_code on the piano.
   *   PianoKeybinder stores a list of all keys that are currently pressed.
   *   Calling PressKey() tells PianoKeybinder to remember they key that was
   *   pressed. This key will be remembered until ReleaseKey() is called
   * @param key_code a ci::app::KeyEvent code that is bound to a Piano Key.
   *   Throws an exception if key_event does not have a keybind or if key_event
   *   is not a valid ci::app::KeyEvent code
   * @return a const reference to a visualizer::PianoKey mapped to the
   *   given key code
   */
  const visualizer::PianoKey& PressKey(int key_code);

 private:
  struct KeyEvent {
    int key_code_;
    char key_char_;
  };
  std::map<int, visualizer::PianoKey> keybinds_;
  static const std::vector<KeyEvent> kBlackKeyCodes;
  static const std::vector<KeyEvent> kWhiteKeyCodes;
};

}  // namespace synther

#endif  // SYNTHER_PIANO_CONTROLLER_H
