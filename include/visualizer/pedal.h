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
  Pedal() = default;

  /**
   * Create a pedal with state required for displaying
   * @param top_left_corner pixel coordinates of the top left corner of the
   *   pedal
   * @param width the width of the pedal in pixels
   * @param height the height of the pedal in pixels
   * @param primary_color the color normally used for the background of the
   *   pedal. When the pedal is pressed, primary_color will become the color
   *   of the text and outline
   * @param secondary_color the color normally used for the text and outline
   *   of the pedal. When the pedal is pressed, secondary_color will become the
   *   color of the background
   * @param label the label of the pedal that will be displayed when drawn
   * @param font_name the name of the font used to display the label
   */
  Pedal(const glm::dvec2& top_left_corner, double width, double height,
        const ci::Color& primary_color, const ci::Color& secondary_color,
        const std::string& label, const std::string& font_name);

  /**
   * Draws the pedal to a Cinder application
   */
  void Draw() const;

  /**
   * Checks if a specified position vector (in pixels) is within the bounds
   *   of the pedal rectangle
   * @param position a vector representing a position (in pixels)
   * @return true if the position vector inside the pedal rectangle, false
   *   otherwise
   */
  bool IsInBounds(const glm::dvec2& position) const;

  /**
   * Updates state of pedal to pressed. The pedal colors will invert to
   *   signify the pressed state
   */
  void Press();

  /**
   * Updates state of pedal to released. The pedal colors will now revert to
   *   the standard colors used at construction
   */
  void Release();

  /**
   * Checks if the pedal is pressed
   * @return true if the pedal is pressed, false otherwise
   */
  bool IsPressed() const;

 private:
  // Positioning
  glm::dvec2 top_left_corner_;
  double width_;
  double height_;

  // Aesthetics
  ci::Color primary_color_;
  ci::Color secondary_color_;
  std::string label_;
  std::string font_name_;

  double kFontSizeFactor = 0.6;
  double kCornerRadius = 10;

  // Functionality
  bool is_pressed_;
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PEDAL_H
