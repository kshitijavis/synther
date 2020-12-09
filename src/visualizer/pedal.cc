//
// Created by Kshitij Sinha on 12/8/20.
//

#include "visualizer/pedal.h"

namespace synther {

namespace visualizer {

Pedal::Pedal(const ci::Color& primary_color, const ci::Color& highlight_color,
             const std::string& label, const std::string& font_name)
    : label_(label),
      primary_color_(primary_color),
      highlight_color_(highlight_color),
      font_name_(font_name) {
}
}  // namespace visualizer

}  // namespace synther
