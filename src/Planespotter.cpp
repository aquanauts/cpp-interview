#include "Planespotter.hpp"
#include "types.hpp"

namespace aqtc {

Planespotter::Planespotter(uint16_t proximity_threshold,
                           uint8_t prediction_horizon)
    : proximity_threshold(proximity_threshold),
      prediction_horizon(prediction_horizon) {}

std::span<uint16_t>
Planespotter::handle([[maybe_unused]] const PositionMessage &message) {
  return {};
}

void Planespotter::handle([[maybe_unused]] const DepartureMessage &message) {}

} // namespace aqtc