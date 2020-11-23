//
// Created by Kshitij Sinha on 11/19/20.
//

#include <cinder/gl/gl.h>

#include "visualizer/piano_key.h"
#include "core/music_note.h"

synther::visualizer::PianoKey::PianoKey(const synther::music::Note& note)
    : note_(note) {
  if (note.GetAccidental() == music::Accidental::Natural) {
    fill_color_ = ci::Color("white");
  } else {
    fill_color_ = ci::Color("black");
  }
}

const synther::music::Note& synther::visualizer::PianoKey::GetNote() const {
  return note_;
}

void synther::visualizer::PianoKey::Draw(const glm::dvec2& top_left_corner,
                                         double width, double height) const {
  glm::dvec2 bottom_right_corner = top_left_corner + glm::dvec2(width, height);
  ci::Rectf bar_bounds(top_left_corner, bottom_right_corner);

  ci::gl::color(fill_color_);
  ci::gl::drawSolidRect(bar_bounds);
  ci::gl::color(outline_color_);
  ci::gl::drawStrokedRect(bar_bounds);
}
