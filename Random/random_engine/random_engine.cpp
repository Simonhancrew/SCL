
#include "random_engine.h"

#include <random>

namespace {

constexpr int kMersenTwisteSize = 624;
constexpr int kPeriodParameter = 397;

}  // namespace

namespace random_engine {

std::random_device &GetRandomDevice() {
  static std::random_device device;
  return device;
}

Generator19937::result_type Generator19937::operator()() {
  if (index_ == 0) {
    GenerateNumbers();
  }

  uint32_t y = mt_[index_];
  y          = y ^ (y >> 11);
  y          = y ^ ((y << 7) & 0x9d2c5680);
  y          = y ^ ((y << 15) & 0xefc60000);
  y          = y ^ (y >> 18);

  index_ = (index_ + 1) % kMersenTwisteSize;
  return y;
}

void Generator19937::GenerateNumbers() {
  if (!seed_initialized_) {
    this->Seed(GetRandomDevice()());
  }

  for (uint32_t i = 0; i < kMersenTwisteSize; i++) {
    uint32_t y = (mt_[i] & 0x80000000) + (mt_[(i + 1) % 624] & 0x7fffffff);
    mt_[i]     = mt_[(i + kPeriodParameter) % kMersenTwisteSize] ^ (y >> 1);
    if (y & 0x01) {
      mt_[i] = mt_[i] ^ 0x9908b0df;
    }
  }
}

void Generator19937::Seed(uint32_t seed) {
  seed_initialized_ = true;
  mt_[0]            = seed;
  for (uint32_t i = 1; i < kMersenTwisteSize; i++) {
    mt_[i] =
        ((0x6c078965 * (mt_[i - 1] ^ (mt_[i - 1] >> 30))) & 0xffffffff) + i;
  }
  index_ = 0;
}

}  // namespace random_engine
