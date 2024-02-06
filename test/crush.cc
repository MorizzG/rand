#include <cstdint>
#include <iostream>
#include <ostream>
#include <span>
#include <string>
#include <vector>

#include "philox.hh"
#include "randomgen.hh"

extern "C" {
#include "bbattery.h"
#include "unif01.h"
}

double GetU01(void* /* param */, void* state) {
    auto* gen = static_cast<RandomGen*>(state);

    return gen->GenF64();
}

unsigned long GetBits(void* /* param */, void* state) {
    auto* gen = static_cast<RandomGen*>(state);

    return static_cast<uint32_t>(gen->Gen());
}

void Write(void* /*state*/) {}

int main(int argc, char* argv[]) {
    std::vector<std::string> args;

    for (auto* arg : std::span<char*>(argv, argc)) {
        args.emplace_back(arg);
    }

    RandomGen* gen;
    char* name;

    if (args.size() != 2) {
        std::cout << "Usage: <exe> <randomgen>" << std::endl;

        return 1;
    }

    if (args[1] == "philox4x64") {
        gen = new Philox4x64{};
        name = "philox4x64";
    } else if (args[1] == "philox2x64") {
        gen = new Philox2x64;
        name = "philox2x64";
    } else if (args[1] == "philox4x32") {
        gen = new Philox4x32{};
        name = "philox4x32";
    } else if (args[1] == "philox2x32") {
        gen = new Philox2x32{};
        name = "philox2x32";
    } else {
        std::cout << "Unknown random gen " << args[1] << std::endl;

        return 1;
    }

    unif01_Gen unif01_gen;

    unif01_gen.state = gen;
    unif01_gen.param = nullptr;
    unif01_gen.name = static_cast<char*>(name);
    unif01_gen.GetU01 = &GetU01;
    unif01_gen.GetBits = &GetBits;
    unif01_gen.Write = &Write;

    if (args[0].ends_with("smallcrush")) {
        bbattery_SmallCrush(&unif01_gen);
    } else if (args[0].ends_with("bigcrush")) {
        bbattery_BigCrush(&unif01_gen);
    } else if (args[0].ends_with("crush")) {
        bbattery_Crush(&unif01_gen);
    } else {
        std::cout << "Program needs to be named smallcrush, crush, or bigcrush, not \"" << args[0]
                  << "\"" << std::endl;
    }

    delete gen;

    return 0;
}
