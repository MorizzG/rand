#pragma once

#include <array>
#include <cassert>
#include <cstdint>

#include "randomgen.hh"

constexpr std::array<uint32_t, 16> kThreefryR64x4 =
    std::to_array({14U, 16U, 52U, 57U, 23U, 40U, 5U, 37U, 25U, 33U, 46U, 12U, 58U, 22U, 32U, 32U});

constexpr std::array<uint32_t, 8> kThreefryR64x2 =
    std::to_array({16U, 42U, 12U, 31U, 16U, 32U, 24U, 21U});

constexpr std::array<uint32_t, 16> kThreefryR32x4 =
    std::to_array({10U, 26U, 11U, 21U, 13U, 27U, 23U, 5U, 6U, 20U, 17U, 11U, 25U, 10U, 18U, 20U});

constexpr std::array<uint32_t, 8> kThreefryR32x2 =
    std::to_array({13U, 15U, 26U, 6U, 17U, 29U, 16U, 24U});

constexpr uint64_t RotL64(uint64_t x, uint32_t n) {
    assert(n <= 64);
    return (x << n) | (x >> (64 - n));
}

constexpr uint32_t RotL32(uint32_t x, uint32_t n) {
    assert(n <= 32);
    return (x << n) | (x >> (32 - n));
}

constexpr uint64_t kSkeinParity64 = 0x1BD11BDAA9FC1A22;
constexpr uint32_t kSkeinParity32 = 0x1BD11BDA;

class Threefry2x32 : public RandomGen {
   public:
    using Counter = std::array<uint32_t, 2>;
    using Key = std::array<uint32_t, 2>;
    using UKey = std::array<uint32_t, 2>;

   private:
    Counter ThreefryRound(uint32_t R, Counter counter, Key key) {
        assert(R <= 32);

        uint32_t x0;
        uint32_t x1;

        uint32_t ks0;
        uint32_t ks1;
        uint32_t ks2;

        ks2 = kSkeinParity32;

        ks0 = key[0];
        x0 = counter[0] + ks0;
        ks2 ^= ks0;

        ks1 = key[1];
        x1 = counter[1] + ks1;
        ks2 ^= ks1;
    }
};

class Threefry4x32 : public RandomGen {
   public:
    using Counter = std::array<uint32_t, 4>;
    using Key = std::array<uint32_t, 4>;
    using UKey = std::array<uint32_t, 4>;

   private:
};

class Threefry2x64 : public RandomGen {
   public:
    using Counter = std::array<uint32_t, 2>;
    using Key = std::array<uint32_t, 2>;
    using UKey = std::array<uint32_t, 2>;

   private:
};

class Threefry4x64 : public RandomGen {
   public:
    using Counter = std::array<uint32_t, 4>;
    using Key = std::array<uint32_t, 4>;
    using UKey = std::array<uint32_t, 4>;

   private:
};
