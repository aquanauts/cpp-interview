#pragma once

#include <chrono>
#include <cstdint>

// Feel free to modify this file in any way that makes sense to you,
// although it'd be nice if the tests in `test.cpp` don't require
// any changes to run, since we have a few other tests of that form
// that use these types that we'll paste in and hope to run when
// evaluating your submission. It's no big deal if we have to manually
// fix something up, though.

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