#pragma once

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <random>

namespace random_engine {

std::random_device &GetRandomDevice();

class Generator19937 {
 public:
  using result_type = uint32_t;
  result_type operator()();
  void Seed(uint32_t seed);

 private:
  uint32_t mt_[624]{};
  uint32_t index_{0};
  bool seed_initialized_{false};
  void GenerateNumbers();
};

class RandomEngine {};

}  // namespace random_engine