//
// Created by Kshitij Sinha on 11/19/20.
//

#ifndef SYNTHER_PIANO_KEY_H
#define SYNTHER_PIANO_KEY_H

#include "cinder/Color.h"
#include "core/music_note.h"
#include "cinder/gl/TextureFont.h"

namespace synther {

namespace visualizer {

enum class PianoKeyType { Black, White };

/**
 * Represents a single PianoKey, which acts as a Cinder GUI component. Every
 * key stores its corresponding note, PianoKeyType, and label (used during
 * drawing).
 */
class PianoKey {
 public:
  PianoKey(const music::Note& note, const PianoKeyType& type, const std::string& label = " ");

  /**
   * Draws a plain Key in the Cinder application.
   * @param top_left_corner screen pixels of the top-left-corner of the key
   * @param width the width of the key, in pixels
   * @param height the height of the key, in pixels
   */
  void Draw(const glm::dvec2& top_left_corner, double width,
            double height) const;

  /**
   * Draws a Key with its label in the Cinder application.
   * @param top_left_corner screen pixels of the top-left-corner of the key
   * @param width the width of the key, in pixels
   * @param height the height of the key, in pixels
   * @param font_name the name of the font used to draw the label. Must be
   *   a cinder::Font
   */
  void DrawWithLabel(const glm::dvec2& top_left_corner, double width,
            double height, const std::string& font_name) const;

  /**
   * Press the key, which will temporarily change the color of the key. The
   *   color will remain changed until ReleaseKey() is called
   */
  void PressKey();

  /**
   * Press the key, which will temporarily change the color of the key. The
   *   color will remain changed until ReleaseKey() is called
   */
  void ReleaseKey();

  /**
   * Gets the Note mapped to this PianoKey
   * @return the Note represented by this PianoKey
   */
  const music::Note& GetNote() const;

  /**
   * Gets the PianoKeyType mapped to this PianoKey
   * @return the PianoKeyType represented by this PianoKey
   */
  const PianoKeyType& GetType() const;

  /**
   * Set the label of the key, which will be displayed when drawing the key
   * @param label a character to set the label to
   */
  void SetLabel(const std::string& label);

  /**
   * Gets the current label of this PianoKey
   * @return a char representing this PianoKey's label
   */
  std::string GetLabel() const;

 private:
  music::Note note_;
  PianoKeyType type_;
  std::string label_;

  // Colors
  ci::Color fill_color_;                 // Current color used for displaying
  ci::Color outline_color_;
  ci::Color text_color_;

  ci::Color released_color_;             // Standard, non-pressed Color
  static const ci::Color kPressedColor;  // Color after PressKey() is called
};

}  // namespace visualizer

}  // namespace synther

#endif  // SYNTHER_PIANO_KEY_H
