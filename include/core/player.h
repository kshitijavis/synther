//
// Created by Kshitij Sinha on 11/29/20.
//

#ifndef SYNTHER_PLAYER_H
#define SYNTHER_PLAYER_H

#include <map>
#include <string>
#include <vector>

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
   *   constructed Player cannot immediately be used for audio playback
   */
  explicit Player(double resonate_duration);

  /**
   * Sets up a map from music::Notes to audio voices. Enables audio playback
   * @param note_files a std::map from music::Notes to strings of file names.
   *   If a file cannot be read, does not initialize the voice at that note
   * @param instrument_directory the relative path from the assets directory
   *   to the directory containing the instrument sound files
   */
  void SetUpVoices(const std::map<music::Note, std::string>& note_files,
                   const std::string& instrument_directory);

  /**
   * Plays the note corresponding to the specified note from the default
   *   audio device. The note will play for the entire duration of the
   *   sound file, unless StopNote is called
   * @param note a music::Note representing the note to start playing
   */
  void PlayNote(const music::Note& note);

  /**
   * Stops playing the note corresponding to the specified note. The note
   *   will resonate for a small amount of time to mimic a classic piano.
   *   During this time, the note will slowly fade away, completely stopping
   *   only after the resonate duration has passed.
   *   The resonate duration can be changed by calling SetResonateDuration()
   * @param note a music::Note representing the note to stop playing
   */
  void StopNote(const music::Note& note);

  /**
   * Set the resonate duration of the Player. The resonate duration determines
   *   how long the note will continue to sound after StopNote() is called.
   * @param resonate_duration the duration to set the resonation of the player.
   */
  void SetResonateDuration(double resonate_duration);

  /**
   * Get the current resonate duration of the player
   * @return the current resonate duration of the player
   */
  double GetResonateDuration() const;

  /**
   * Gets a vector of all the notes that are playable in the current state of
   *   the player. In other words, returns a vector of all of notes currently
   *   mapped to voices
   * @return a vector of all the playable notes in the player
   */
  std::vector<music::Note> GetPlayableNotes() const;

 private:
  struct NoteVoice {
    ci::audio::GainNodeRef gain_;
    ci::audio::BufferPlayerNodeRef buffer_player_;
    bool is_playing_;
  };
  // Maps semitones to voices
  std::map<int, NoteVoice> voices_;
  double resonate_duration_;
};

}  // namespace audio

}  // namespace synther

#endif  // SYNTHER_PLAYER_H