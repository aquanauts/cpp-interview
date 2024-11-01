#pragma once

#include <cstdint>

namespace aqtc {

using AircraftId = uint16_t;

template <typename T> struct Vec3 {
  T x{};
  T y{};
  T z{};
};

struct PositionMessage {
  uint32_t timestamp{};
  AircraftId aircraft_id{};
  Vec3<int32_t> position;
  Vec3<float> direction;
  uint16_t speed{};
};

struct DepartureMessage {
  AircraftId aircraft_id{};
};

} // namespace aqtc