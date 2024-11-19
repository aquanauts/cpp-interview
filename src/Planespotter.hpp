#pragma once

#include "types.hpp"
#include <span>

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace aqtc {

class Planespotter {
private:
  uint16_t proximity_threshold{};
  uint8_t prediction_horizon{};

public:
  // The proximity threshold determines how close two aircraft have to be for
  // them to represent a proximity violation.
  //
  // The prediction horizon specifies how far into the future to predict
  // aircraft positions: if the aircraft maintained their linear flight tracks
  // for this duration (in seconds), an alert should be raised if a
  // proximity violation is predicted to occur.
  Planespotter(uint16_t proximity_threshold, uint8_t prediction_horizon);

  // Given a message, return a span of aircraft IDs participating in any
  // predicted proximity violations. The lifetime of the span should be up to
  // the next time this method is called.
  std::span<AircraftId> handle(const PositionMessage &message);

  void handle(const DepartureMessage &message);
};

} // namespace aqtc