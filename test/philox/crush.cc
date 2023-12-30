#include <cassert>
#include <cstdint>

extern "C" {
#include "bbattery.h"
#include "unif01.h"
}

#include "philox.hh"

/*
typedef struct {
    void* state;
    void* param;
    char* name;
    double (*GetU01)(void* param, void* state);
    unsigned long (*GetBits)(void* param, void* state);
    void (*Write)(void* state);
} unif01_Gen;
*/

double GetU01(void* /* param */, void* state) {
    auto* philox = static_cast<Philox*>(state);

    return philox->NextF64();
}

unsigned long GetBits(void* /* param */, void* state) {
    auto* philox = static_cast<Philox*>(state);

    unsigned long u = static_cast<uint32_t>(philox->Next());

    assert(0 <= u && u < (1ULL << 32));

    return u;
}

void Write(void* /*state*/) {}

int main() {
    Philox philox{};

    unif01_Gen gen;

    gen.state = &philox;
    gen.param = nullptr;
    gen.name = "Philox";
    gen.GetU01 = &GetU01;
    gen.GetBits = &GetBits;
    gen.Write = &Write;

    bbattery_Crush(&gen);

    return 0;
}
