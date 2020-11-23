//
// Created by Kshitij Sinha on 11/19/20.
//

#include <cinder/gl/gl.h>

#include "visualizer/piano_key.h"
#include "core/music_note.h"

synther::visualizer::PianoKey::PianoKey(const synther::music::Note& note)
    : note_(note) {
  if (note.GetAccidental() == music::Accidental::Natural) {
    color_ = ci::Color("white");
  } else {
    color_ = ci::Color("black");
  }
}

const synther::music::Note& synther::visualizer::PianoKey::GetNote() const {
  return note_;
}

void synther::visualizer::PianoKey::Draw(glm::dvec2 top_left_corner,
                                         double width, double height) const {
  glm::dvec2 bottom_right_corner(top_left_corner + width,
                                 top_left_corner + height);
  ci::Rectf bar_bounds(top_left_corner, bottom_right_corner);

  ci::gl::color(color_);
  ci::gl::drawSolidRect(bar_bounds);
}
