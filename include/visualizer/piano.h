#include <climits>
//
// Created by Kshitij Sinha on 11/18/20.
//

#ifndef SYNTHER_PIANO_H
#define SYNTHER_PIANO_H

#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/Color.h"

#include "visualizer/piano_key.h"
#include "core/music_note.h"

namespace synther {

namespace visualizer {

class Piano {
 public:
  /**
   * Constructs a piano for visualization
   * @param top_left_corner the screen coordinates of the top left corner of
   *   the piano
   * @param width the width of the piano in pixels
   * @param height the height of the piano in pixels
   * @param background_color the background color of the piano
   * @param first_semitone the starting note of the piano, specified by its
   *   semitone distance from A0, where A0 has a semitone of 0
   * @param key_count the number of keys on the piano
   */
  Piano(const glm::dvec2& top_left_corner, double width, double height,
        const ci::Color& background_color, int first_semitone,
        size_t key_count);

  /**
   * Get the PianoKey at the specified index
   * @param index the index of the piano key, where the first key has an index
   *   of 0. Input must be between 0 (inclusive) and key_count (exclusive)
   * @return a PianoKey reference to the piano key at the index
   */
  const PianoKey& GetPianoKey(int index) const;
 private:
  // Visuals
  glm::dvec2 top_left_corner_;
  double width_;
  double height_;
  ci::Color background_color_;

  // Data
  int first_semitone_;
  size_t key_count_;
  std::vector<PianoKey> keys_;

  const music::Accidental kPriority = music::Accidental::Sharp;
};

} // namespace visualizer

} // namespace synther

#endif  // SYNTHER_PIANO_H
