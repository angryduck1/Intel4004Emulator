#include <iostream>
#include <chrono>
#include <thread>

class Intel4004 {
public:
    Intel4004(): pc(0), acc(0), rr0(0) {
        memory = new int[256];
    }
    
    ~Intel4004() {
        delete[] memory;
    }
    
    void load_program(uint8_t instructions[6]) {
        for (int i = 0; i < 256; i++) {
            memory[i] = instructions[i];
        }
    }
    
    uint8_t get_accum() {
        return acc;
    }
    
    void run() {
        while (true) {
            uint8_t opcode = memory[pc++];
            switch (opcode) {
                case 0x00: // Остановка
                    return;
                case 0xA2: // Загружаем число в аккум
                    acc = memory[pc++];
                    break;
                case 0xA4: // Загружаем число в регистер 0
                    rr0 = memory[pc++];
                    break;
                case 0x58: // Сложение
                    acc += rr0;
                    if (acc > 15) {
                        acc = 15;
                    }
                    break;
                case 0x29: // Вычитание
                    acc -= rr0;
                    if (acc < 0) {
                        acc = 0;
                    }
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
    uint8_t rr0;
    uint8_t acc;
    int* memory = nullptr;
};

int main() {
    Intel4004 ex;
    
    uint8_t instructions[6] = {
        0xA2, 0x05, // Помещаем в аккум значение 5
        0xA4, 0x03, // Помещаем в регистер 0 значение 3
        0x58, // Сложение
        0x00
    };
    
    ex.load_program(instructions);
    
    ex.run();
    
    std::cout << static_cast<int>(ex.get_accum()) << std::endl;
    
    return 0;
}
