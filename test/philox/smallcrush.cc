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

    uint64_t u = philox->Next();

    return static_cast<unsigned long>(u);
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

    bbattery_SmallCrush(&gen);

    return 0;
}
