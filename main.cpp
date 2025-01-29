#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "assembler.h"

class Intel4004 {
public:
    Intel4004(): pc(0), acc(0), rr0(0), rr1(0), flags(0) {
        memory.resize(256);
    }
    
    void load_program(std::vector<uint8_t> instructions) {
        for (size_t i = 0; i < memory.size(); i++) {
            memory[i] = instructions[i];
        }
        
        for (size_t i = instructions.size(); i < memory.size(); i++) {
            memory[i] = 0;
        }
    }
    
    // Auxiliary methods
    
    uint8_t get_acc() {
        return acc;
    }
    
    uint8_t get_rr0() {
        return rr0;
    }
    
    uint8_t get_rr1() {
        return rr1;
    }
    
    //
    
    void run() {
        while (true) {
            uint8_t opcode = memory[pc++];
            switch (opcode) {
                case NOP: // Остановка
                    return;
                case LDM: // Загружаем число в аккум
                    acc = memory[pc++];
                    break;
                case XCH_RR0: // Загружаем число в регистер 0 из аккума
                    std::swap(acc, rr0);
                    break;
                case XCH_RR1: // Загружаем число в регистер 1 из аккума
                    std::swap(acc, rr1);
                    break;
                case ADD: // Сложение
                    if (acc + rr0 > 15) {
                        acc = acc + rr0 & 0x0F;
                        flags |= 0x01; // Устанавливаем флаг переноса
                    } else {
                        acc += rr0;
                        flags &= ~0x01; // Сбрасываем флаг переноса
                    }
                    break;
                case SUB: // Вычитание
                    acc -= rr0;
                    acc &= 0x0F;
                    break;
                default:
                    std::cerr << "Unknown instruction!" << std::endl;
                    return;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(11));
        }
    }
    
private:
    uint8_t pc;
    uint8_t rr0, rr1;
    uint8_t acc;
    uint8_t flags;
    std::vector<uint8_t> memory;
};

int main() {
    Intel4004 ex;
    
    std::vector<uint8_t> instructions {
        LDM, 0x07,
        XCH_RR0,
        LDM, 0x09,
        SUB, NOP
    };
    
    ex.load_program(instructions);
    
    ex.run();
    
    std::cout << static_cast<int>(ex.get_acc()) << std::endl;
    
    return 0;
    
}
