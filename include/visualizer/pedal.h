//
// Created by Kshitij Sinha on 12/8/20.
//

#ifndef SYNTHER_PEDAL_H
#define SYNTHER_PEDAL_H

#include <string>

#include "cinder/Color.h"
#include "cinder/gl/gl.h"

namespace synther {

namespace visualizer {

/**
 * A piano pedal that can be displayed in a Cinder app. The pedal is drawn
 *   as a rectangle with a primary color and secondary color. While the pedal
 *   is "released", the background of the pedal is its primary color and the
 *   text/outline are the secondary color. When the pedal is "pressed", these
 *   colors switch, giving the appearance of a pressed button.
 */
class Pedal {
 public:
  /**
   * Create a pedal with state required for displaying
   * @param top_left_corner pixel coordinates of the top left corner of the
   *   pedal
   * @param width the width of the pedal in pixels
   * @param height the height of the pedal in pixels
   * @param primary_color the color normally used for the background of the
   *   pedal. When the pedal is pressed, primary_color will become the color
   *   of the text and outline
   * @param highlight_color the color normally used for the text and outline
   *   of the pedal. When the pedal is pressed, secondary_color will become the
   *   color of the background
   * @param label the label of the pedal that will be displayed when drawn
   * @param font_name the name of the font used to display the label
   */
  Pedal(const glm::dvec2& top_left_corner, double width, double height,
        const ci::Color& primary_color, const ci::Color& highlight_color,
        const std::string& label, const std::string& font_name);

  /**
   * Draws the pedal to a Cinder application
   */
  void Draw() const;

 private:
  // Positioning
  glm::dvec2 top_left_corner_;
  double width_;
  double height_;

  // Aesthetics
  ci::Color primary_color_;    // Background color of pedal
  ci::Color highlight_color_;  // Color of text and outline
  std::string label_;
  std::string font_name_;
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PEDAL_H
