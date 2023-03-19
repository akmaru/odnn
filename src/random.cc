#include <odnn/random.h>

#include <atomic>
#include <random>
#include <type_traits>

#include "logging.h"
#include "singleton.h"

namespace odnn {
namespace details {

class Rng final {
  friend Singleton<Rng>;

private:
  Rng() = default;

public:
  Rng(const Rng&) = delete;
  Rng& operator=(const Rng&) = delete;
  Rng(Rng&&) = delete;
  Rng& operator=(Rng&&) = delete;

  auto seed() const noexcept { return seed_; }

  auto& engine() noexcept { return engine_; }

  const auto& engine() const noexcept { return engine_; }

  void set_seed_and_engine(std::uint_fast32_t seed) {
    seed_ = seed;
    engine_ = std::mt19937(seed);
  }

private:
  std::uint_fast32_t seed_ = 0;
  std::mt19937 engine_ = std::mt19937(seed_);
};

}  // namespace details

void manual_seed(std::uint_fast32_t seed) {
  auto& rng = Singleton<details::Rng>::get();
  rng.set_seed_and_engine(seed);
}

template <typename T>
T random_value(T lower, T upper) {
  auto& rng = Singleton<details::Rng>::get();

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dist(lower, upper);
    return dist(rng.engine());
  } else if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist(lower, upper);
    return dist(rng.engine());

    UNREACHABLE();
  }
}

template float random_value(float, float);

}  // namespace odnn
