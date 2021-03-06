//
// Created by Kshitij Sinha on 11/19/20.
//

#include "visualizer/piano_key.h"

#include <cinder/gl/gl.h>

#include "cinder/Color.h"
#include "core/music_note.h"

namespace synther {

namespace visualizer {

const ci::Color PianoKey::kPressedColor = ci::Color("green");

PianoKey::PianoKey(const synther::music::Note& note, const PianoKeyType& type,
                   const std::string& label)
    : note_(note), type_(type), label_(label) {
  if (type == PianoKeyType::White) {
    released_color_ = ci::Color("white");
    text_color_ = ci::Color("black");
  } else if (type == PianoKeyType::Black) {
    released_color_ = ci::Color("black");
    text_color_ = ci::Color("white");
  }
  fill_color_ = released_color_;
}

void PianoKey::Draw(const glm::dvec2& top_left_corner, double width,
                    double height) const {
  glm::dvec2 bottom_right_corner = top_left_corner + glm::dvec2(width, height);
  ci::Rectf bar_bounds(top_left_corner, bottom_right_corner);

  ci::gl::color(fill_color_);
  ci::gl::drawSolidRect(bar_bounds);
  ci::gl::color(outline_color_);
  ci::gl::drawStrokedRect(bar_bounds);
}

void PianoKey::DrawWithLabel(const glm::dvec2& top_left_corner, double width,
                             double height,
                             const std::string& font_name) const {
  Draw(top_left_corner, width, height);

  // Ensure that the text is resized to fit both the width and the height of
  // the piano key
  double font_size = std::min(width / 2, height);
  glm::dvec2 label_top_center =
      top_left_corner + glm::dvec2(0.5 * width, 0.9 * (height - font_size));
  ci::gl::drawStringCentered(label_, label_top_center, text_color_,
                             ci::Font(font_name, font_size));
}

void PianoKey::PressKey() {
  fill_color_ = kPressedColor;
}

void PianoKey::ReleaseKey() {
  fill_color_ = released_color_;
}

void PianoKey::SetLabel(const std::string& label) {
  label_ = label;
}

const synther::music::Note& PianoKey::GetNote() const {
  return note_;
}

const synther::visualizer::PianoKeyType& PianoKey::GetType() const {
  return type_;
}

std::string PianoKey::GetLabel() const {
  return label_;
}

}  // namespace visualizer

}  // namespace synther
