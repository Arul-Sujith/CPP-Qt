#pragma once

#include <vector>
#include <string>
#include <cstdint>

class Disassembler {
public:
    std::vector<std::string> disassemble(const uint8_t* code, size_t size, uint64_t address = 0x1000);
};
