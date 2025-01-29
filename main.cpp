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
        for (int i = 0; i < memory.size(); i++) {
            memory[i] = instructions[i];
        }
    }
    
    uint8_t get_accum() {
        return acc;
    }
    
    uint8_t get_register0() {
        return rr0;
    }
    
    uint8_t get_register1() {
        return rr1;
    }
    
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
                    pc++;
                    break;
                case XCH_RR1: // Загружаем число в регистер 1 из аккума
                    std::swap(acc, rr1);
                    pc++;
                    break;
                case ADD: // Сложение
                    result = acc + rr0;
                    if (result > 15) {
                        acc = 15;
                        flags |= 0x01; // Устанавливаем флаг переноса
                    } else {
                        acc = result;
                        flags &= ~0x01; // Сбрасываем флаг переноса
                    }
                    pc++;
                    break;
                case SUB: // Вычитание
                    acc -= rr0;
                    if (acc < 0) {
                        acc = 0;
                        flags |= 0x02;
                    } else {
                        flags &= ~0x02; // Сбрасываем флаг переноса
                    }
                    pc++;
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
    uint8_t result;
    std::vector<int> memory;
};

int main() {
    Intel4004 ex;
    
    std::vector<uint8_t> instructions {
        LDM, 0x05,
        XCH_RR0
    };
    
    ex.load_program(instructions);
    
    ex.run();
    
    std::cout << static_cast<int>(ex.get_register0()) << std::endl;
    
    return 0;
    
}
