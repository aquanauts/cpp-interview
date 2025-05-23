#pragma once

#include <chrono>
#include <cstdint>

// Feel free to modify this file in any way that makes sense to you,
// but please ensure that the tests in test.cpp continue to run.

namespace aqtc {

using AircraftId = uint16_t;

template <typename T> struct Vec3 {
  T x{};
  T y{};
  T z{};
};

struct PositionMessage {
  std::chrono::milliseconds timestamp{};
  AircraftId aircraft_id{};
  Vec3<int32_t> position;
  Vec3<float> direction;
  uint16_t ft_per_s{};
};

struct DepartureMessage {
  AircraftId aircraft_id{};
};

} // namespace aqtc