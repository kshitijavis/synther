//
// Created by Kshitij Sinha on 12/8/20.
//

#include "visualizer/pedal.h"

namespace synther {

namespace visualizer {

Pedal::Pedal(const glm::dvec2& top_left_corner, double width, double height,
             const ci::Color& primary_color, const ci::Color& highlight_color,
             const std::string& label, const std::string& font_name)
    : top_left_corner_(top_left_corner),
      width_(width),
      height_(height),
      primary_color_(primary_color),
      highlight_color_(highlight_color),
      label_(label),
      font_name_(font_name) {
}
}  // namespace visualizer

}  // namespace synther
