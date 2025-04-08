#include "Disassembler.h"
#include "Disassembler.h"
#include <capstone/capstone.h>
#include <sstream>
#include <iomanip>

std::vector<std::string> Disassembler::disassemble(const uint8_t* code, size_t size, uint64_t address) {
    std::vector<std::string> result;
    csh handle;
    cs_insn* insn;
    size_t count;

    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
        return {};

    count = cs_disasm(handle, code, size, address, 0, &insn);
    if (count > 0) {
        for (size_t i = 0; i < count; i++) {
            std::ostringstream oss;
            oss << "0x" << std::hex << insn[i].address << ": "
                << insn[i].mnemonic << "\t" << insn[i].op_str;
            result.push_back(oss.str());
        }
        cs_free(insn, count);
    }
    cs_close(&handle);
    return result;
}
