#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

#include <vector>

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

class Histogram {
 public:
  /**
   * Creates a histogram
   * @param top_left_corner  the screen coordinates of the top left corner of
   *   the histogram
   * @param height the height of the sketchpad in screen pixels
   * @param width the width of the sketchpad in screen pixels
   * @param bin_count the number of bins in the histogram. The histogram will
   *   make sure all data falls within a bin
   * @param range_widening_factor the factor by which to "stretch" the x-axis of
   *   the histogram. This makes sure that the maximum element in a dataset
   *   falls into the last (rightmost) bin of the histogram. Requires that
   *   range_widening_factor > 1
   * @param title the title of the histogram, displayed on the top of the graph
   * @param x_title the label for the x-axis of the graph, displayed under the
   *   x-axis
   * @param y_title the label for the y-axis of the graph, displayed next to the
   *   y-axis
   */
  Histogram(const glm::vec2& top_left_corner, double height, double width,
            size_t bin_count, double range_widening_factor,
            const std::string& title, const std::string& x_title,
            const std::string& y_title);

  /**
   * Displays the current state of the histogram in the Cinder application
   * @param data a vector of data to plot on the histogram
   */
  void Draw(const std::vector<double>& data) const;

  /**
   * Computes the frequency distribution of the given data, based on the current
   *   bin count
   * @param data a vector of doubles whose frequency distribution will be
   *   calculated
   * @return a frequency distribution of the data
   */
  std::vector<size_t> GetFrequencies(const std::vector<double>& data) const;

 private:
  // Formatting
  glm::vec2 top_left_corner_;
  double height_;
  double width_;
  double graph_height_;
  double graph_width_;
  glm::vec2 graph_top_left_corner_;
  const std::string font_color_ = "white";
  const std::string background_color = "maroon";
  const std::string bar_color = "silver";

  // Size of left, top, bottom margins with respect to histogram dimensions
  // Makes room for labels
  static constexpr double kTextMargin = 0.15;

  // Contents
  size_t bin_count_;
  double range_widening_factor_;
  std::string title_;
  std::string x_title_;
  std::string y_title_;
  static constexpr size_t kYLabelCount = 5;  // Excluding 0.0 label

  // Helper methods
  /**
   * Calculates the x-axis range of bins based on the number of bins and the
   *   range widening factor
   * @param data the data whose optimal bin range will be calculated
   * @return the range of the bins
   */
  double ComputeBinRange(const std::vector<double>& data) const;

  void DrawBars(const std::vector<size_t>& frequencies) const;
  void DrawTitles() const;
  void DrawXLabels(const std::vector<size_t>& frequencies,
                   double bin_range) const;
  void DrawYLabels(const std::vector<size_t>& frequencies) const;

  /**
   * Converts a floating-point number to a string based on the specified
   *   precision
   * @param to_convert the floating-point number to convert
   * @param the precision of the output string
   * @return a string representing the floating-point number, truncated to
   *   the given precision
   */
  std::string DoubleToString(double to_convert, int precision) const;
};

}  // namespace visualizer

}  // namespace idealgas

#endif  // IDEAL_GAS_HISTOGRAM_H
