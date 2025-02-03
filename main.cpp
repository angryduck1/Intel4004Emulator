#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "assembler.h"
#include "core.h"

int main() {
    Intel4004 ex;
    
    std::vector<uint8_t> instructions {
        LDM, 7, XCH, RR0,
        LDM, 8,
        ADD, RR0
    };
    
    ex.load_program(instructions);
    
    ex.run();
    
    ex.get_acc();
    ex.get_carry();
    ex.get_memory();
    
    return 0;
    
}

