#pragma once

#include <cstdint>

class RandomGen {
   public:
    virtual ~RandomGen() = default;

    virtual uint64_t Gen() = 0;

    inline uint64_t operator()() { return Gen(); }

    // Lemire's almost divisionless algorithm
    uint64_t GenInRange(uint64_t s) {
        uint64_t x = Gen();

        __uint128_t m = static_cast<__uint128_t>(x) * static_cast<__uint128_t>(s);

        auto l = static_cast<uint64_t>(m);

        if (l < s) {
            uint64_t t = -s % s;

            while (l < t) {
                x = Gen();
                m = static_cast<__uint128_t>(x) * static_cast<__uint128_t>(s);
                l = static_cast<uint64_t>(m);
            }
        }

        return static_cast<uint64_t>(m >> 64);
    }

    // taken from Numpy
    // throw away 11 bits (need only 53 for 53 bits of significant in IEEE754 F64) and divide by
    // 2**53 (max representable integer)
    // only one I found that actually generates in [0.0, 1.0)
    // does not generate subnormals
    double GenF64() {
        double x = static_cast<double>(Gen() >> 11) / 9007199254740992.0;

        return x;
    }
};
