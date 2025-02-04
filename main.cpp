#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "assembler.h"
#include "core.h"

int main() {
    Intel4004 ex;
    
    std::ifstream inFile("main.txt"); // Put your file in this
    
    std::string line;
    std::string asm_code;

    while (std::getline(inFile, line)) {
            asm_code += line + "\n";
        }
    
    inFile.close();
    
    auto instructions = ex.assemble(asm_code);
    
    ex.load_program(instructions);
    ex.run();
    
    ex.get_acc();
    ex.get_carry();
    ex.get_memory();
    
    return 0;
    
}
