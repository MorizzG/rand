#pragma once

#include <immintrin.h>

#include <array>
#include <cstdint>
#include <utility>

class Philox {
   public:
    static constexpr uint32_t kNumRounds = 10;

    using Ctr = std::array<uint64_t, 4>;
    using Key = std::array<uint64_t, 2>;

    constexpr Philox() : Philox({0, 0}) {}
    constexpr explicit Philox(Key key) : key_{key} {}

    constexpr Ctr ctr() const { return ctr_; }
    constexpr void ctr(Ctr ctr) { ctr_ = ctr; }

    constexpr Key key() const { return key_; }
    constexpr void key(Key key) { key_ = key; }

    constexpr uint64_t Next() {
        Ctr ct{};

        if (buffer_pos_ < 4) {
            uint64_t out = buffer_[buffer_pos_];
            buffer_pos_++;

            return out;
        }

        ctr_[0]++;

        if (ctr_[0] == 0) {
            ctr_[1]++;

            if (ctr_[1] == 0) {
                ctr_[2]++;

                if (ctr_[2] == 0) {
                    ctr_[3]++;
                }
            }
        }

        ct = PhiloxRounds(kNumRounds, ctr_, key_);

        buffer_ = ct;

        buffer_pos_ = 1;

        return buffer_[0];
    }

    // taken from Numpy
    // throw away 11 bits (need only 53) and divide by 2**53 (max representable integer)
    // only one I found that actually converts to [0.0, 1.0)
    // does not generate subnormals
    constexpr double NextF64() {
        double x = static_cast<double>(Next() >> 11) / 9007199254740992.0;

        return x;
    }

   private:
    static constexpr std::pair<uint64_t, uint64_t> MulHiLo64(uint64_t x, uint64_t y) {
        __uint128_t z = static_cast<__uint128_t>(x) * static_cast<__uint128_t>(y);

        return std::make_pair(static_cast<uint64_t>(z >> 64), static_cast<uint64_t>(z));
    }

    static constexpr Ctr PhiloxRounds(uint32_t R, Ctr ctr, Key key) {
        if (R > 0) {
            ctr = PhiloxRound(ctr, key);
        }

        for (uint32_t r = 1; r < R; r++) {
            key = BumpKey(key);
            ctr = PhiloxRound(ctr, key);
        }

        return ctr;
    }

    static constexpr Ctr PhiloxRound(Ctr ctr, Key key) {
        auto [hi0, lo0] = MulHiLo64(0xD2E7470EE14C6C93ULL, ctr[0]);
        auto [hi1, lo1] = MulHiLo64(0xCA5A826395121157ULL, ctr[2]);

        return {hi1 ^ ctr[1] ^ key[0], lo1, hi0 ^ ctr[3] ^ key[1], lo0};
    }

    static constexpr Key BumpKey(Key key) {
        key[0] += 0x9E3779B97F4A7C15ULL;
        key[1] += 0xBB67AE8584CAA73BULL;

        return key;
    }

    Ctr ctr_{0, 0, 0, 0};
    Key key_{0, 0};

    uint32_t buffer_pos_ = 4;
    std::array<uint64_t, 4> buffer_ = {0, 0, 0, 0};
};
