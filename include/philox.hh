#pragma once

#include <immintrin.h>

#include <array>
#include <cstdint>
#include <utility>

#include "randomgen.hh"

class Philox2x32 : public RandomGen {
   public:
    static constexpr uint32_t kNumRounds = 10;

    using Counter = std::array<uint32_t, 2>;
    using Key = std::array<uint32_t, 1>;

    constexpr Philox2x32() : Philox2x32({0}) {}
    constexpr explicit Philox2x32(Key key) : key_{key} { buffer_ = PhiloxRounds(key_, counter_); }

    constexpr Counter& counter() { return counter_; }
    constexpr Counter counter() const { return counter_; }

    constexpr Key& key() { return key_; }
    constexpr Key key() const { return key_; }

    constexpr uint32_t GenU32() {
        if (buffer_pos_ < buffer_.size()) {
            uint32_t out = buffer_[buffer_pos_];
            buffer_pos_++;

            return out;
        }

        counter_[0]++;

        if (counter_[0] == 0) {
            counter_[1]++;
        }

        // advance buffer by kNumRounds rounds
        buffer_ = PhiloxRounds(key_, counter_);

        // return first element of buffer
        buffer_pos_ = 1;

        return buffer_[0];
    }

    constexpr uint64_t Gen() override {
        auto lo = static_cast<uint64_t>(GenU32());
        auto hi = static_cast<uint64_t>(GenU32());

        return (hi << 32) | lo;
    }

   private:
    static constexpr std::pair<uint32_t, uint32_t> MulHiLo32(uint32_t x, uint32_t y) {
        uint64_t z = static_cast<uint64_t>(x) * static_cast<uint64_t>(y);

        return std::make_pair(static_cast<uint32_t>(z >> 32), static_cast<uint32_t>(z));
    }

    static constexpr Key BumpKey(Key key) {
        key[0] += 0x9E3779B9UL;

        return key;
    }

    static constexpr Counter PhiloxRound(Key key, Counter counter) {
        auto [hi, lo] = MulHiLo32(0xD256D193, counter[0]);

        return {hi ^ key[0] ^ counter[1], lo};
    }

    static constexpr Counter PhiloxRounds(Key key, Counter counter) {
        counter = PhiloxRound(key, counter);

        for (uint32_t r = 1; r < kNumRounds; r++) {
            key = BumpKey(key);
            counter = PhiloxRound(key, counter);
        }

        // save updated counter into buffer
        return counter;
    }

    Counter counter_{0, 0};
    Key key_{0};

    Counter buffer_ = {0, 0};
    uint32_t buffer_pos_ = 0;
};

class Philox4x32 : public RandomGen {
   public:
    static constexpr uint32_t kNumRounds = 10;

    using Counter = std::array<uint32_t, 4>;
    using Key = std::array<uint32_t, 2>;

    constexpr Philox4x32() : Philox4x32({0, 0}) {}
    constexpr explicit Philox4x32(Key key) : key_{key} { buffer_ = PhiloxRounds(key_, counter_); }

    constexpr Counter& counter() { return counter_; }
    constexpr Counter counter() const { return counter_; }

    constexpr Key& key() { return key_; }
    constexpr Key key() const { return key_; }

    constexpr uint32_t GenU32() {
        if (buffer_pos_ < buffer_.size()) {
            uint32_t out = buffer_[buffer_pos_];
            buffer_pos_++;

            return out;
        }

        counter_[0]++;

        if (counter_[0] == 0) {
            counter_[1]++;

            if (counter_[1] == 0) {
                counter_[2]++;

                if (counter_[2] == 0) {
                    counter_[3]++;
                }
            }
        }

        // advance buffer by kNumRounds rounds
        buffer_ = PhiloxRounds(key_, counter_);

        // return first element of buffer
        buffer_pos_ = 1;

        return buffer_[0];
    }

    constexpr uint64_t Gen() override {
        auto lo = static_cast<uint64_t>(GenU32());
        auto hi = static_cast<uint64_t>(GenU32());

        return (hi << 32) | lo;
    }

   private:
    static constexpr std::pair<uint32_t, uint32_t> MulHiLo32(uint32_t x, uint32_t y) {
        uint64_t z = static_cast<uint64_t>(x) * static_cast<uint64_t>(y);

        return std::make_pair(static_cast<uint32_t>(z >> 32), static_cast<uint32_t>(z));
    }

    static constexpr Key BumpKey(Key key) {
        key[0] += 0x9E3779B9UL;
        key[1] += 0xBB67AE85UL;

        return key;
    }

    static constexpr Counter PhiloxRound(Key key, Counter counter) {
        auto [hi0, lo0] = MulHiLo32(0xD2511F53UL, counter[0]);
        auto [hi1, lo1] = MulHiLo32(0xCD9E8D57UL, counter[2]);

        return {hi1 ^ key[0] ^ counter[1], lo1, hi0 ^ key[1] ^ counter[3], lo0};
    }

    static constexpr Counter PhiloxRounds(Key key, Counter counter) {
        counter = PhiloxRound(key, counter);

        for (uint32_t r = 1; r < kNumRounds; r++) {
            key = BumpKey(key);
            counter = PhiloxRound(key, counter);
        }

        // save updated counter into buffer
        return counter;
    }

    Counter counter_{0, 0, 0, 0};
    Key key_{0, 0};

    Counter buffer_ = {0, 0, 0, 0};
    uint32_t buffer_pos_ = 0;
};

class Philox2x64 : public RandomGen {
   public:
    static constexpr uint32_t kNumRounds = 10;

    using Counter = std::array<uint64_t, 2>;
    using Key = std::array<uint64_t, 1>;

    constexpr Philox2x64() : Philox2x64({0}) {}
    constexpr explicit Philox2x64(Key key) : key_{key} { buffer_ = PhiloxRounds(key_, counter_); }

    constexpr Counter& counter() { return counter_; }
    constexpr Counter counter() const { return counter_; }

    constexpr Key& key() { return key_; }
    constexpr Key key() const { return key_; }

    constexpr uint64_t Gen() override {
        if (buffer_pos_ < buffer_.size()) {
            uint64_t out = buffer_[buffer_pos_];
            buffer_pos_++;

            return out;
        }

        counter_[0]++;

        if (counter_[0] == 0) {
            counter_[1]++;
        }

        // advance buffer by kNumRounds rounds
        buffer_ = PhiloxRounds(key_, counter_);

        // return first element of buffer
        buffer_pos_ = 1;

        return buffer_[0];
    }

   private:
    static constexpr std::pair<uint64_t, uint64_t> MulHiLo64(uint64_t x, uint64_t y) {
        __uint128_t z = static_cast<__uint128_t>(x) * static_cast<__uint128_t>(y);

        return std::make_pair(static_cast<uint64_t>(z >> 64), static_cast<uint64_t>(z));
    }

    static constexpr Key BumpKey(Key key) {
        key[0] += 0x9E3779B97F4A7C15ULL;

        return key;
    }

    static constexpr Counter PhiloxRound(Key key, Counter counter) {
        auto [hi, lo] = MulHiLo64(0xD2E7470EE14C6C93ULL, counter[0]);

        return {hi ^ key[0] ^ counter[1], lo};
    }

    static constexpr Counter PhiloxRounds(Key key, Counter counter) {
        counter = PhiloxRound(key, counter);

        for (uint32_t r = 1; r < kNumRounds; r++) {
            key = BumpKey(key);
            counter = PhiloxRound(key, counter);
        }

        // save updated counter into buffer
        return counter;
    }

    Counter counter_{0, 0};
    Key key_{0};

    Counter buffer_ = {0, 0};
    uint32_t buffer_pos_ = 0;
};

class Philox4x64 : public RandomGen {
   public:
    static constexpr uint32_t kNumRounds = 10;

    using Counter = std::array<uint64_t, 4>;
    using Key = std::array<uint64_t, 2>;

    constexpr Philox4x64() : Philox4x64({0, 0}) {}
    constexpr explicit Philox4x64(Key key) : key_{key} { buffer_ = PhiloxRounds(key_, counter_); }

    constexpr Counter& counter() { return counter_; }
    constexpr Counter counter() const { return counter_; }

    constexpr Key& key() { return key_; }
    constexpr Key key() const { return key_; }

    constexpr uint64_t Gen() override {
        if (buffer_pos_ < buffer_.size()) {
            uint64_t out = buffer_[buffer_pos_];
            buffer_pos_++;

            return out;
        }

        counter_[0]++;

        if (counter_[0] == 0) {
            counter_[1]++;

            if (counter_[1] == 0) {
                counter_[2]++;

                if (counter_[2] == 0) {
                    counter_[3]++;
                }
            }
        }

        // advance buffer by kNumRounds rounds
        buffer_ = PhiloxRounds(key_, counter_);

        // return first element of buffer
        buffer_pos_ = 1;

        return buffer_[0];
    }

   private:
    static constexpr std::pair<uint64_t, uint64_t> MulHiLo64(uint64_t x, uint64_t y) {
        __uint128_t z = static_cast<__uint128_t>(x) * static_cast<__uint128_t>(y);

        return std::make_pair(static_cast<uint64_t>(z >> 64), static_cast<uint64_t>(z));
    }

    static constexpr Key BumpKey(Key key) {
        key[0] += 0x9E3779B97F4A7C15ULL;
        key[1] += 0xBB67AE8584CAA73BULL;

        return key;
    }

    static constexpr Counter PhiloxRound(Key key, Counter counter) {
        auto [hi0, lo0] = MulHiLo64(0xD2E7470EE14C6C93ULL, counter[0]);
        auto [hi1, lo1] = MulHiLo64(0xCA5A826395121157ULL, counter[2]);

        return {hi1 ^ key[0] ^ counter[1], lo1, hi0 ^ key[1] ^ counter[3], lo0};
    }

    static constexpr Counter PhiloxRounds(Key key, Counter counter) {
        counter = PhiloxRound(key, counter);

        for (uint32_t r = 1; r < kNumRounds; r++) {
            key = BumpKey(key);
            counter = PhiloxRound(key, counter);
        }

        // save updated counter into buffer
        return counter;
    }

    Counter counter_{0, 0, 0, 0};
    Key key_{0, 0};

    Counter buffer_ = {0, 0, 0, 0};
    uint32_t buffer_pos_ = 0;
};

using Philox = Philox4x64;
