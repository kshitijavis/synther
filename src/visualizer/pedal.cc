//
// Created by Kshitij Sinha on 12/8/20.
//

#include "visualizer/pedal.h"

#include "cinder/Text.h"

namespace synther {

namespace visualizer {

Pedal::Pedal(const glm::dvec2& top_left_corner, double width, double height,
             const ci::Color& primary_color, const ci::Color& secondary_color,
             const std::string& label, const std::string& font_name)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      primary_color_(primary_color),
      secondary_color_(secondary_color),
      label_(label),
      font_name_(font_name),
      is_pressed_(false) {
}

void Pedal::Draw() const {
  ci::Color background_color = is_pressed_ ? primary_color_ : secondary_color_;
  ci::Color highlight_color = is_pressed_ ? secondary_color_ : primary_color_;

  glm::dvec2 bottom_right_corner =
      top_left_corner_ + glm::dvec2(width_, height_);
  ci::Rectf bar_bounds(top_left_corner_, bottom_right_corner);

  ci::gl::color(background_color);
  ci::gl::drawSolidRect(bar_bounds);
  ci::gl::color(highlight_color);
  ci::gl::drawStrokedRect(bar_bounds);

  // Ensure that the label is resized to fit both the width and the height
  // of the rectangle
  double font_size = std::min(width_ / 2, height_) * kFontSizeFactor;
  glm::dvec2 label_top_center =
      top_left_corner_ + glm::dvec2(0.5 * width_, (height_ - font_size) / 2);
  ci::gl::drawStringCentered(label_, label_top_center, highlight_color,
                             ci::Font(font_name_, font_size));
}
}  // namespace visualizer

}  // namespace synther
