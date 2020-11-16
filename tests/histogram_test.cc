//
// Created by Kshitij Sinha on 11/8/20.
//

#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"
#include <vector>

#include "visualizer/histogram.h"

using idealgas::visualizer::Histogram;

TEST_CASE("GetFrequencies", "[getfrequencies]") {
  SECTION("Single-element dataset with multiple bins") {
    Histogram histogram(glm::vec2(0,0), 10, 10, 5, 1.2, "", "", "");
    std::vector<double> data{15};
    std::vector<size_t> actual_frequencies = histogram.GetFrequencies(data);
    std::vector<size_t> expected_frequencies{0, 0, 0, 0, 1};

    REQUIRE(actual_frequencies == expected_frequencies);
  }

  SECTION("Multi-element dataset with multiple bins") {
    Histogram histogram(glm::vec2(0,0), 10, 10, 5, 1.2, "", "", "");
    std::vector<double> data{20, 30, 50, 75, 100};
    std::vector<size_t> actual_frequencies = histogram.GetFrequencies(data);
    std::vector<size_t> expected_frequencies{1, 1, 1, 1, 1};

    REQUIRE(actual_frequencies == expected_frequencies);
  }

  SECTION("Multi-element, skewed right data. Multiple bins") {
    Histogram histogram(glm::vec2(0,0), 10, 10, 5, 1.2, "", "", "");
    std::vector<double> data{10, 12, 13, 15, 40, 70, 100};
    std::vector<size_t> actual_frequencies = histogram.GetFrequencies(data);
    std::vector<size_t> expected_frequencies{4, 1, 1, 0, 1};

    REQUIRE(actual_frequencies == expected_frequencies);
  }

  SECTION("Multi-element dataset with single bin") {
    Histogram histogram(glm::vec2(0,0), 10, 10, 1, 1.2, "", "", "");
    std::vector<double> data{10, 20, 30};
    std::vector<size_t> actual_frequencies = histogram.GetFrequencies(data);
    std::vector<size_t> expected_frequencies{3};

    REQUIRE(actual_frequencies == expected_frequencies);
  }

  SECTION("Rejects any range_widening_factor < 1") {
    REQUIRE_THROWS_AS(Histogram(glm::vec2(0,0), 10, 10, 1, 0.9, "", "", ""),
                      std::invalid_argument);
  }
}