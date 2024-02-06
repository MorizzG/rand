#include <Random123/philox.h>

#include <cassert>
#include <cstdint>
#include <iostream>

#include "philox.hh"

void CounterInc(r123::Philox2x32::ctr_type& counter) {
    counter[0]++;

    if (counter[0] == 0) {
        counter[1]++;
    }
}

void CounterInc(r123::Philox4x32::ctr_type& counter) {
    counter[0]++;

    if (counter[0] == 0) {
        counter[1]++;

        if (counter[1] == 0) {
            counter[2]++;

            if (counter[2] == 0) {
                counter[3]++;
            }
        }
    }
}

void CounterInc(r123::Philox2x64::ctr_type& counter) {
    counter[0]++;

    if (counter[0] == 0) {
        counter[1]++;
    }
}

void CounterInc(r123::Philox4x64::ctr_type& counter) {
    counter[0]++;

    if (counter[0] == 0) {
        counter[1]++;

        if (counter[1] == 0) {
            counter[2]++;

            if (counter[2] == 0) {
                counter[3]++;
            }
        }
    }
}

bool test_philox2x32() {
    r123::Philox2x32::ctr_type counter{0, 0};
    r123::Philox2x32::key_type key{0};

    Philox2x32 philox_2x32{};
    r123::Philox2x32 r123_philox_2x32{};

    auto run_test = [&philox_2x32, &r123_philox_2x32, &key, &counter]() -> bool {
        for (uint32_t i = 0; i < 1'0000; i++) {
            assert(key[0] == philox_2x32.key()[0]);

            auto x0 = philox_2x32.GenU32();
            auto x1 = philox_2x32.GenU32();

            auto y = r123_philox_2x32(counter, key);

            // test counter equality after generating since rand philox will only bump counter after
            // generating
            assert(counter[0] == philox_2x32.counter()[0]);
            assert(counter[1] == philox_2x32.counter()[1]);

            if (y[0] != x0 || y[1] != x1) {
                std::cout << "Philox2x32 test failed for i=" << i << std::endl;
                std::cout << "Key: key=[" << key[0] << "]" << std::endl;
                std::cout << "Counter: [" << counter[1] << " " << counter[0] << "]" << std::endl;

                std::cout << "Random123: " << y[0] << " " << y[1] << std::endl;
                std::cout << "Rand:    : " << x0 << " " << x1 << std::endl;

                return false;
            }

            CounterInc(counter);
        }

        return true;
    };

    // key = [0]
    if (!run_test()) {
        std::cout << "Test failed for key [" << key[0] << "]" << std::endl;

        return false;
    }

    for (uint32_t j = 0; j < 100; j++) {
        uint32_t key0 = philox_2x32.GenU32();

        key[0] = key0;
        counter = {0, 0};

        philox_2x32 = Philox2x32{{key0}};

        if (!run_test()) {
            std::cout << "Test failed for key [" << key[0] << "]" << std::endl;

            return false;
        }
    }

    return true;
}

bool test_philox4x32() {
    r123::Philox4x32::ctr_type counter{0, 0, 0, 0};
    r123::Philox4x32::key_type key{0, 0};

    Philox4x32 philox_4x32{};
    r123::Philox4x32 r123_philox_4x32{};

    auto run_test = [&philox_4x32, &r123_philox_4x32, &key, &counter]() -> bool {
        for (uint32_t i = 0; i < 1'0000; i++) {
            assert(key[0] == philox_4x32.key()[0]);
            assert(key[1] == philox_4x32.key()[1]);

            auto x0 = philox_4x32.GenU32();
            auto x1 = philox_4x32.GenU32();
            auto x2 = philox_4x32.GenU32();
            auto x3 = philox_4x32.GenU32();

            auto y = r123_philox_4x32(counter, key);

            // test counter equality after generating since rand philox will only bump counter after
            // generating
            assert(counter[0] == philox_4x32.counter()[0]);
            assert(counter[1] == philox_4x32.counter()[1]);
            assert(counter[2] == philox_4x32.counter()[2]);
            assert(counter[3] == philox_4x32.counter()[3]);

            if (y[0] != x0 || y[1] != x1 || y[2] != x2 || y[3] != x3) {
                std::cout << "Philox4x32 test failed for i=" << i << std::endl;
                std::cout << "Key: key=[" << key[1] << " " << key[0] << "]" << std::endl;
                std::cout << "Counter: [" << counter[3] << " " << counter[2] << counter[1] << " "
                          << counter[0] << "]" << std::endl;

                std::cout << "Random123: " << y[0] << " " << y[1] << y[2] << " " << y[3]
                          << std::endl;
                std::cout << "Rand:    : " << x0 << " " << x1 << " " << x2 << " " << x3
                          << std::endl;

                return false;
            }

            CounterInc(counter);
        }

        return true;
    };

    // key = [0]
    if (!run_test()) {
        std::cout << "Test failed for key [" << key[1] << key[0] << "]" << std::endl;

        return false;
    }

    for (uint32_t j = 0; j < 100; j++) {
        uint32_t key0 = philox_4x32.GenU32();
        uint32_t key1 = philox_4x32.GenU32();

        key[0] = key0;
        key[1] = key1;
        counter = {0, 0, 0, 0};

        philox_4x32 = Philox4x32{{key0, key1}};

        if (!run_test()) {
            std::cout << "Test failed for key [" << key[1] << key[0] << "]" << std::endl;

            return false;
        }
    }

    return true;
}

bool test_philox2x64() {
    r123::Philox2x64::ctr_type counter{0, 0};
    r123::Philox2x64::key_type key{0};

    Philox2x64 philox_2x64{};
    r123::Philox2x64 r123_philox_2x64{};

    auto run_test = [&philox_2x64, &r123_philox_2x64, &key, &counter]() -> bool {
        for (uint32_t i = 0; i < 1'0000; i++) {
            assert(key[0] == philox_2x64.key()[0]);

            auto x0 = philox_2x64.Gen();
            auto x1 = philox_2x64.Gen();

            auto y = r123_philox_2x64(counter, key);

            // test counter equality after generating since rand philox will only bump counter after
            // generating
            assert(counter[0] == philox_2x64.counter()[0]);
            assert(counter[1] == philox_2x64.counter()[1]);

            if (y[0] != x0 || y[1] != x1) {
                std::cout << "Philox2x32 test failed for i=" << i << std::endl;
                std::cout << "Key: key=[" << key[0] << "]" << std::endl;
                std::cout << "Counter: [" << counter[1] << " " << counter[0] << "]" << std::endl;

                std::cout << "Random123: " << y[0] << " " << y[1] << std::endl;
                std::cout << "Rand:    : " << x0 << " " << x1 << std::endl;

                return false;
            }

            CounterInc(counter);
        }

        return true;
    };

    // key = [0]
    if (!run_test()) {
        std::cout << "Test failed for key [" << key[0] << "]" << std::endl;

        return false;
    }

    for (uint32_t j = 0; j < 100; j++) {
        uint64_t key0 = philox_2x64.Gen();

        key[0] = key0;
        counter = {0, 0};

        philox_2x64 = Philox2x64{{key0}};

        if (!run_test()) {
            std::cout << "Test failed for key [" << key[0] << "]" << std::endl;

            return false;
        }
    }

    return true;
}

bool test_philox4x64() {
    r123::Philox4x64::ctr_type counter{0, 0, 0, 0};
    r123::Philox4x64::key_type key{0, 0};

    Philox4x64 philox_4x64{};
    r123::Philox4x64 r123_philox_4x64{};

    auto run_test = [&philox_4x64, &r123_philox_4x64, &key, &counter]() -> bool {
        for (uint32_t i = 0; i < 1'0000; i++) {
            assert(key[0] == philox_4x64.key()[0]);

            auto x0 = philox_4x64.Gen();
            auto x1 = philox_4x64.Gen();
            auto x2 = philox_4x64.Gen();
            auto x3 = philox_4x64.Gen();

            auto y = r123_philox_4x64(counter, key);

            // test counter equality after generating since rand philox will only bump counter after
            // generating
            assert(counter[0] == philox_4x64.counter()[0]);
            assert(counter[1] == philox_4x64.counter()[1]);
            assert(counter[2] == philox_4x64.counter()[2]);
            assert(counter[3] == philox_4x64.counter()[3]);

            if (y[0] != x0 || y[1] != x1 || y[2] != x2 || y[3] != x3) {
                std::cout << "Philox2x64 test failed for i=" << i << std::endl;
                std::cout << "Key: key=[" << key[1] << key[0] << "]" << std::endl;
                std::cout << "Counter: [" << counter[3] << " " << counter[2] << counter[1] << " "
                          << counter[0] << "]" << std::endl;

                std::cout << "Random123: " << y[0] << " " << y[1] << y[2] << " " << y[3]
                          << std::endl;
                std::cout << "Rand:    : " << x0 << " " << x1 << x2 << " " << x3 << std::endl;

                return false;
            }

            CounterInc(counter);
        }

        return true;
    };

    // key = [0]
    if (!run_test()) {
        std::cout << "Test failed for key [" << key[0] << "]" << std::endl;

        return false;
    }

    for (uint32_t j = 0; j < 100; j++) {
        uint32_t key0 = philox_4x64.Gen();
        uint32_t key1 = philox_4x64.Gen();

        key[0] = key0;
        key[1] = key1;
        counter = {0, 0, 0, 0};

        philox_4x64 = Philox4x64{{key0, key1}};

        if (!run_test()) {
            std::cout << "Test failed for key [" << key[1] << key[0] << "]" << std::endl;

            return false;
        }
    }

    return true;
}

int main() {
    bool all_passed = true;

    if (!test_philox2x32()) {
        all_passed = false;
    }

    return all_passed ? 0 : 1;
}
