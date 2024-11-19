#include "src/Planespotter.hpp"

#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>

using namespace aqtc;

namespace {

void check_id_in(AircraftId aircraft_id, std::span<AircraftId> aircraft_ids) {
  for (const auto id : aircraft_ids) {
    if (id == aircraft_id)
      return;
  }
  FAIL(fmt::format("Couldn't find {} in: {}", aircraft_id,
                   fmt::join(aircraft_ids, ",")));
}

Vec3<float> unit(Vec3<float> v) {
  const float magnitude =
      std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z, 2));
  return {v.x / magnitude, v.y / magnitude, v.z / magnitude};
}

} // namespace

// Feel free to modify this file in any way that makes sense to you.

TEST_CASE("A Planespotter") {
  // Configured to alert if any planes are expected to come within 500 meters of
  // each other in the next 30 seconds
  Planespotter spotter{500, 30};

  SECTION("Should allow one aircraft to appear and depart") {
    // A few position updates
    CHECK(spotter.handle(PositionMessage{0, 1, {-1, 0, 0}, {1, 0, 0}, 0})
              .empty());
    CHECK(
        spotter.handle(PositionMessage{1000000000, 1, {0, 0, 0}, {1, 0, 0}, 0})
            .empty());
    CHECK(
        spotter.handle(PositionMessage{2000000000, 1, {1, 0, 0}, {1, 0, 0}, 0})
            .empty());

    // Exiting airspace
    spotter.handle(DepartureMessage{1});
  }

  SECTION("Should not complain if two static aircraft are reported to be 501 "
          "meters of "
          "each other at the same time") {
    CHECK(
        spotter.handle(PositionMessage{0, 1, {0, 0, 0}, {1, 0, 0}, 0}).empty());

    CHECK(spotter.handle(PositionMessage{0, 2, {501, 0, 0}, {1, 0, 0}, 0})
              .empty());
  }

  SECTION("Should not complain if two moving aircraft move in the same "
          "direction, separated by 501 meters") {
    CHECK(spotter.handle(PositionMessage{0, 1, {0, 0, 0}, unit({1, 1, 1}), 500})
              .empty());

    CHECK(
        spotter.handle(PositionMessage{0, 2, {501, 0, 0}, unit({1, 1, 1}), 500})
            .empty());
  }

  SECTION("Should complain if two moving aircraft are moving directly toward "
          "each other") {
    CHECK(spotter.handle(PositionMessage{0, 1, {0, 0, 0}, {1, 0, 0}, 500})
              .empty());

    CHECK(spotter.handle(PositionMessage{0, 2, {100000, 0, 0}, {-1, 0, 0}, 500})
              .empty());
  }

  SECTION(
      "Should complain if two static aircraft are reported to be 500 meters of "
      "each other at the same time") {
    CHECK(
        spotter.handle(PositionMessage{0, 1, {0, 0, 0}, {1, 0, 0}, 0}).empty());

    const auto proximity_violations =
        spotter.handle(PositionMessage{0, 2, {500, 0, 0}, {1, 0, 0}, 0});
    check_id_in(1, proximity_violations);
    check_id_in(2, proximity_violations);
  }

  SECTION("Should complain if a moving aircraft is projected to be within 500 "
          "meters of a static aircraft") {
    // Plane 1 moving at 250m/s along the x-axis will be 7500m away in 30s
    CHECK(spotter.handle(PositionMessage{0, 1, {0, 0, 0}, {1, 0, 0}, 250})
              .empty());

    // Plane 2 for simplicity has a speed of 0, hovering at x=7900
    const auto proximity_violations =
        spotter.handle(PositionMessage{0, 2, {7900, 0, 0}, {1, 0, 0}, 0});
    check_id_in(1, proximity_violations);
    check_id_in(2, proximity_violations);
  }

  SECTION("Should complain if a moving aircraft is projected to be within 500 "
          "meters of another moving aircraft") {
    // Plane 1 moving at 250m/s along the x-axis will be 7500m away in 30s
    CHECK(spotter.handle(PositionMessage{0, 1, {0, 0, 0}, {1, 0, 0}, 250})
              .empty());

    // Plane 2 moving at 100m/s, but starting farther up the x-axis
    const auto proximity_violations =
        spotter.handle(PositionMessage{0, 2, {4500, 0, 0}, {1, 0, 0}, 100});
    check_id_in(1, proximity_violations);
    check_id_in(2, proximity_violations);
  }
}
