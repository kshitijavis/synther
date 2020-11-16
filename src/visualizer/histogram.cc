//
// Created by Kshitij Sinha on 11/8/20.
//

#include "visualizer/histogram.h"

namespace idealgas {

namespace visualizer {

Histogram::Histogram(const glm::vec2& top_left_corner, double height,
                     double width, size_t bin_count,
                     double range_widening_factor, const std::string& title,
                     const std::string& x_title, const std::string& y_title)
    : top_left_corner_(top_left_corner),
      height_(height),
      width_(width),
      graph_height_(height - 2 * (kTextMargin * height)),
      graph_width_(width - (kTextMargin * width_)),
      graph_top_left_corner_(
          top_left_corner +
          glm::vec2((width_ - graph_width_), (height_ - graph_height_) / 2)),
      bin_count_(bin_count),
      title_(title),
      x_title_(x_title),
      y_title_(y_title) {
  if (range_widening_factor < 1) {
    throw std::invalid_argument(
        "range_widening_factor must be greater than 1 "
        "to ensure that all data falls into a histogram bin");
  }
  range_widening_factor_ = range_widening_factor;
}

std::vector<size_t> Histogram::GetFrequencies(
    const std::vector<double>& data) const {
  double bin_range = ComputeBinRange(data);

  std::vector<size_t> frequencies(bin_count_, 0);
  for (double value : data) {
    size_t bin = value / bin_range;
    frequencies.at(bin)++;
  }

  return frequencies;
}

double Histogram::ComputeBinRange(const std::vector<double>& data) const {
  double max = *std::max_element(data.begin(), data.end());
  return (max / bin_count_) * range_widening_factor_;
}

void Histogram::Draw(const std::vector<double>& data) const {
  glm::vec2 graph_bottom_right_corner =
      graph_top_left_corner_ + glm::vec2(graph_width_, graph_height_);
  ci::Rectf histogram_bounds(graph_top_left_corner_, graph_bottom_right_corner);

  // Draw histogram graphing area
  ci::gl::color(ci::Color(background_color.c_str()));
  ci::gl::drawSolidRect(histogram_bounds);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(histogram_bounds);

  double bin_range = ComputeBinRange(data);
  std::vector<size_t> frequencies = GetFrequencies(data);

  DrawBars(frequencies);
  DrawTitles();
  DrawXLabels(frequencies, bin_range);
  DrawYLabels(frequencies);
}

void Histogram::DrawBars(const std::vector<size_t>& frequencies) const {
  size_t max_freq = *std::max_element(frequencies.begin(), frequencies.end());
  double bar_height_factor = graph_height_ / max_freq;  // Scale to graph height
  double bar_width = graph_width_ / bin_count_;
  double bar_left_edge = graph_top_left_corner_.x;
  double bar_bottom_edge = graph_top_left_corner_.y + graph_height_;

  // Draw a bar for every frequency
  for (size_t frequency : frequencies) {
    double bar_height = frequency * bar_height_factor;

    glm::vec2 bar_top_left(bar_left_edge, bar_bottom_edge - bar_height);
    glm::vec2 bar_bottom_right(bar_left_edge + bar_width, bar_bottom_edge);
    ci::Rectf bar_bounds(bar_top_left, bar_bottom_right);

    ci::gl::color(ci::Color(bar_color.c_str()));
    ci::gl::drawSolidRect(bar_bounds);

    bar_left_edge += bar_width;  // Shift next bar right by bar width
  }
}

void Histogram::DrawTitles() const {
  // Translate coordinate system to top left of the histogram
  ci::gl::pushModelMatrix();
  ci::gl::translate(top_left_corner_);

  double top_bottom_margin = graph_top_left_corner_.y - top_left_corner_.y;

  // Draw graph title
  glm::vec2 title_center = glm::vec2(width_ / 2, 0);
  ci::gl::drawStringCentered(title_, title_center, ci::Color(font_color_.c_str()),
                             ci::Font("Arial", 15.0f));

  // Draw x-axis title
  glm::vec2 x_title_center =
      glm::vec2(width_ / 2, top_bottom_margin + 1.2 * graph_height_);
  ci::gl::drawStringCentered(x_title_, x_title_center, ci::Color(font_color_.c_str()),
                             ci::Font("Arial", 13.0f));

  // Rotate coordinate system to draw y-label
  ci::gl::translate(glm::vec2(0, height_));
  ci::gl::rotate(glm::radians(270.0));

  // Draw y-axis title
  glm::vec2 y_title_center = glm::vec2(height_ / 2, 0);
  ci::gl::drawStringCentered(y_title_, y_title_center, ci::Color(font_color_.c_str()),
                             ci::Font("Arial", 13.0f));

  ci::gl::popModelMatrix();
}
void Histogram::DrawXLabels(const std::vector<size_t>& frequencies,
                            double bin_range) const {
  // Translate coordinate system to top left of the graph
  ci::gl::pushModelMatrix();
  ci::gl::translate(graph_top_left_corner_);

  double x_pos = 0;
  double y_pos = 1.05 * graph_height_;  // Slightly offset underneath y-axis
  double label = 0;
  double label_dist = graph_width_ / bin_count_;

  // Draw labels, starting at left and moving right on every iteration
  for (int bin = 0; bin < frequencies.size(); bin++) {
    std::string label_str = DoubleToString(label, 2);

    glm::vec2 label_center = glm::vec2(x_pos, y_pos);
    ci::gl::drawStringCentered(label_str, label_center, ci::Color(font_color_.c_str()),
                               ci::Font("Arial", 11.0f));

    x_pos += label_dist;
    label += bin_range;
  }
  ci::gl::popModelMatrix();
}
void Histogram::DrawYLabels(const std::vector<size_t>& frequencies) const {
  // Translate coordinate system to top left of the histogram
  ci::gl::pushModelMatrix();
  ci::gl::translate(graph_top_left_corner_);

  double side_margin = graph_top_left_corner_.x - top_left_corner_.x;
  size_t max_freq = *std::max_element(frequencies.begin(), frequencies.end());

  double x_pos = -1 * (side_margin / 2);  // Offset labels slightly left
  double y_pos = graph_height_;           // Begin the labels at top of y-axis
  double label = 0;
  double label_dist = graph_height_ / kYLabelCount;
  double label_diff = (float)max_freq / kYLabelCount;

  // Draw labels starting at top and moving down on every iteration
  for (int label_count = 0; label_count <= kYLabelCount; label_count++) {
    std::string label_str = DoubleToString(label, 1);

    glm::vec2 label_center = glm::vec2(x_pos, y_pos);
    ci::gl::drawStringCentered(label_str, label_center, ci::Color(font_color_.c_str()),
                               ci::Font("Arial", 11.0f));

    y_pos -= label_dist;
    label += label_diff;
  }
  ci::gl::popModelMatrix();
}

std::string Histogram::DoubleToString(double to_convert, int precision) const {
  // Conversion method  derived from...
  // https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
  std::stringstream conversion_stream;
  conversion_stream << std::fixed << std::setprecision(precision) << to_convert;
  return conversion_stream.str();
}

}  // namespace visualizer

}  // namespace idealgas
