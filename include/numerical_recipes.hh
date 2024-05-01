#pragma once

#include <cstdint>

#include "randomgen.hh"

class NumericalRecipesGen : public RandomGen {
   public:
    constexpr explicit NumericalRecipesGen(uint64_t j) {
        u_ = j ^ v_;
        Gen();
        v_ = u_;
        Gen();
        w_ = v_;
        Gen();
    }

    uint64_t Gen() override {
        u_ = u_ * 2862933555777941757ULL + 7046029254386353087ULL;

        v_ ^= v_ >> 17;
        v_ ^= v_ << 31;
        v_ ^= v_ >> 8;

        w_ = 4294957665ULL * (w_ & 0xffffffff) + (w_ >> 32);

        uint64_t x = u_ ^ (u_ << 21);
        x ^= x >> 35;
        x ^= x << 4;

        return (x + v_) ^ w_;
    }

   private:
    uint64_t u_;
    uint64_t v_{4101842887655102017ULL};
    uint64_t w_{1ULL};
};

class NumericalRecipesGen1 : public RandomGen {
   public:
    constexpr explicit NumericalRecipesGen1(uint64_t j) {
        v_ ^= j;
        v_ = Gen();
    }

    uint64_t Gen() override {
        v_ ^= v_ >> 21;
        v_ ^= v_ << 35;
        v_ ^= v_ >> 4;

        return v_ * 2685821657736338717ULL;
    }

   private:
    uint64_t v_{4101842887655102017ULL};
};

class NumericalRecipesGen2 : public RandomGen {
   public:
    constexpr explicit NumericalRecipesGen2(uint64_t j) {
        v_ ^= j;

        w_ = Gen();
        v_ = Gen();
    }

    uint64_t Gen() override {
        v_ ^= v_ >> 17;
        v_ ^= v_ << 31;
        v_ ^= v_ >> 8;

        w_ = 4294957665ULL * (w_ & 0xffffffff) + (w_ >> 32);

        return v_ ^ w_;
    }

   private:
    uint64_t v_{4101842887655102017ULL};
    uint64_t w_{1ULL};
};
