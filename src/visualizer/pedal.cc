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
  ci::gl::drawSolidRoundedRect(bar_bounds, kCornerRadius);
  ci::gl::color(highlight_color);
  ci::gl::drawStrokedRoundedRect(bar_bounds, kCornerRadius);

  // Ensure that the label is resized to fit both the width and the height
  // of the rectangle
  double font_size = std::min(width_ / 2, height_) * kFontSizeFactor;
  glm::dvec2 label_top_center =
      top_left_corner_ + glm::dvec2(0.5 * width_, (height_ - font_size) / 2);
  ci::gl::drawStringCentered(label_, label_top_center, highlight_color,
                             ci::Font(font_name_, font_size));
}

void Pedal::Press() {
  is_pressed_ = true;
}

void Pedal::Release() {
  is_pressed_ = false;
}

bool Pedal::IsPressed() const {
  return is_pressed_;
}
bool Pedal::IsInBounds(const glm::dvec2& position) const {
  double left_edge = top_left_corner_.x;
  double right_edge = top_left_corner_.x + width_;
  double top_edge = top_left_corner_.y;
  double bottom_edge = top_left_corner_.y + height_;

  bool is_x_in_bounds = left_edge < position.x && position.x < right_edge;
  bool is_y_in_bounds = top_edge < position.y && position.y < bottom_edge;

  return is_x_in_bounds && is_y_in_bounds;
}
}  // namespace visualizer

}  // namespace synther
