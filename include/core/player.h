//
// Created by Kshitij Sinha on 11/29/20.
//

#ifndef SYNTHER_PLAYER_H
#define SYNTHER_PLAYER_H

#include <map>
#include <string>

#include "cinder/audio/audio.h"
#include "core/music_note.h"

namespace synther {

namespace audio {

/**
 * Handles audio playback using discrete notes, mapping music::Notes to
 *   sound files. Offers methods for playing notes and simple sound processing
 *   to mimic a real piano
 */
class Player {
 public:
  /**
   * Constructs an empty Player object. Does not initialize any voices, so a
   *   default constructed Player cannot immediately be used for audio playback
   */
  explicit Player(double resonate_duration);

  /**
   * Sets up a map from music::Notes to audio voices. Enables audio playback
   * @param note_files a std::map from music::Notes to strings of file names
   *   if a file cannot be read, does not initialize the voice at that note
   * @param instrument_directory the relative path from the assets directory
   *   to the directory containing the instrument sound files
   */
  void SetUpVoices(const std::map<music::Note, std::string>& note_files,
                   const std::string& instrument_directory);

  /**
   * Plays the note corresponding to the specified note from the default
   *   audio device. The note will continue to play the entire duration of the
   *   sound file, unless StopNote is called
   * @param note a music::Note representing the note to start playing
   */
  void PlayNote(const music::Note& note);

  /**
   * Stops playing the note corresponding to the specified note. The note
   *   will resonate for a small amount of time to mimic a classic piano.
   *   The duration of the resonation can be changed by calling SetResonation()
   * @param note a music::Note representing the note to stop playing
   */
  void StopNote(const music::Note& note);

 private:
  struct NoteVoice {
    ci::audio::GainNodeRef gain_;
    ci::audio::BufferPlayerNodeRef buffer_player_;
    bool is_playing_;
  };
  // Maps semitones to voices
  std::map<int, NoteVoice> players_;
  double resonate_duration_;
};

}  // namespace audio

}  // namespace synther

#endif  // SYNTHER_PLAYER_H