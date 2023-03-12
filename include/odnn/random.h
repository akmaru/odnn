#pragma once

#include <cstdint>
#include <random>

#include "singleton.h"

namespace odnn {

namespace details {

class Rng;

}  // namespace details

void manual_seed(std::uint_fast32_t seed);

template <typename T>
T random_value(T lower = -127, T upper = 127);

}  // namespace odnn
