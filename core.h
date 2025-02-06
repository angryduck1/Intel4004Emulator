#ifndef core_h
#define core_h

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "assembler.h"
#include <unordered_map>
#include <sstream>

class Intel4004 {
private:
    size_t instructions_size;
    size_t memory_size;
    std::vector<uint8_t> memory;
    
    std::unordered_map<std::string, Opcode> opcode_map {
            {"NOP", NOP}, {"LDM", LDM}, {"XCH", XCH}, {"ADD", ADD},
            {"CMC", CMC}, {"RAL", RAL}, {"RAR", RAR},
            {"INC", INC}, {"JCN", JCN}, {"SUB", SUB}, {"RR0", RR0},
            {"RR1", RR1}, {"RR2", RR2}, {"RR3", RR3}, {"RR4", RR4},
            {"RR5", RR5}, {"RR6", RR6}, {"RR7", RR7}, {"RR8", RR8},
            {"RR9", RR9}, {"RR10", RR10}, {"RR11", RR11}, {"RR12", RR12},
            {"RR13", RR13}, {"RR14", RR14}, {"RR15", RR15}, {"C1", C1},
            {"C2", C2}, {"C3", C3}, {"C4", C4}
        
    };
public:
    std::unordered_map<std::string, uint16_t> labelMap;
    std::unordered_map<uint, uint> instruction_addresses;
    uint counter_r = 0;
    uint counter_u = 0;
    
    struct PointerCounter {
        uint pc : 12;
    };
    struct Registers {
        uint8_t rr0 : 4;
        uint8_t rr1 : 4;
        uint8_t rr2 : 4;
        uint8_t rr3 : 4;
        uint8_t rr4 : 4;
        uint8_t rr5 : 4;
        uint8_t rr6 : 4;
        uint8_t rr7 : 4;
        uint8_t rr8 : 4;
        uint8_t rr9 : 4;
        uint8_t rr10 : 4;
        uint8_t rr11 : 4;
        uint8_t rr12 : 4;
        uint8_t rr13 : 4;
        uint8_t rr14 : 4;
        uint8_t rr15 : 4;
    };
    struct Accumulator {
        uint8_t ac : 4;
    };
    struct Flag {
        bool carry = false; // Если во время операции произошло переполнение
    };
    
    struct Temporary { // Вспомогательная переменная не относящаяся к Intel 4004;
        uint8_t temp : 4;
        uint8_t tempac : 4;
    };
    
    struct Condition {
        bool c1;
        bool c2;
        bool c3;
        bool c4;
        
        bool shouldJump;
        
        uint8_t condition;
        uint address;
    };
    
    struct BitsControll {
        bool lsb; // Младший бит
        bool msb; // Старший бит
    };
    
    Registers r; Accumulator a; PointerCounter p; Flag f; Temporary t; Condition c; BitsControll b;
    
    Intel4004() {
        memory.resize(256);
        
        r.rr0 = 0;
        r.rr1 = 0;
        r.rr2 = 0;
        r.rr3 = 0;
        r.rr4 = 0;
        r.rr5 = 0;
        r.rr6 = 0;
        r.rr7 = 0;
        r.rr8 = 0;
        r.rr9 = 0;
        r.rr10 = 0;
        r.rr11 = 0;
        r.rr12 = 0;
        r.rr13 = 0;
        r.rr14 = 0;
        r.rr15 = 0;
        
        a.ac = 0;
        
        p.pc = 0;
    }
    
    void load_program(std::vector<uint8_t> instructions) {
        this->instructions_size = instructions.size();
        this->memory_size = memory.size();
        for (size_t i = 0; i < memory.size(); i++) {
            memory[i] = instructions[i];
        }
        
        for (size_t i = instructions.size(); i < memory.size(); i++) {
            memory[i] = 0;
        }
    }
    
    // Auxiliary methods
    
    uint8_t get_acc() {
        std::cout << static_cast<int>(a.ac) << std::endl;
        return a.ac;
    }
    
    bool get_carry() {
        std::cout << f.carry << std::endl;
        return f.carry;
    }
    
    uint8_t get_rr0() {
        std::cout << static_cast<int>(r.rr0) << std::endl;
        return r.rr0;
    }
    
    uint8_t get_rr1() {
        std::cout << static_cast<int>(r.rr1) << std::endl;
        return r.rr1;
    }
    
    uint8_t get_rr2() {
        std::cout << static_cast<int>(r.rr2) << std::endl;
        return r.rr2;
    }
    
    uint8_t get_rr3() {
        std::cout << static_cast<int>(r.rr3) << std::endl;
        return r.rr3;
    }
    
    uint8_t get_rr4() {
        std::cout << static_cast<int>(r.rr4) << std::endl;
        return r.rr4;
    }
    
    uint8_t get_rr5() {
        std::cout << static_cast<int>(r.rr5) << std::endl;
        return r.rr5;
    }
    
    uint8_t get_rr6() {
        std::cout << static_cast<int>(r.rr6) << std::endl;
        return r.rr6;
    }
    
    uint8_t get_rr7() {
        std::cout << static_cast<int>(r.rr7) << std::endl;
        return r.rr7;
    }
    
    uint8_t get_rr8() {
        std::cout << static_cast<int>(r.rr8) << std::endl;
        return r.rr8;
    }
    
    uint8_t get_rr9() {
        std::cout << static_cast<int>(r.rr9) << std::endl;
        return r.rr9;
    }
    
    uint8_t get_rr10() {
        std::cout << static_cast<int>(r.rr10) << std::endl;
        return r.rr10;
    }
    
    uint8_t get_rr11() {
        std::cout << static_cast<int>(r.rr11) << std::endl;
        return r.rr11;
    }
    
    uint8_t get_rr12() {
        std::cout << static_cast<int>(r.rr12) << std::endl;
        return r.rr12;
    }
    
    uint8_t get_rr13() {
        std::cout << static_cast<int>(r.rr13) << std::endl;
        return r.rr13;
    }
    
    uint8_t get_rr14() {
        std::cout << static_cast<int>(r.rr14) << std::endl;
        return r.rr14;
    }
    
    uint8_t get_rr15() {
        std::cout << static_cast<int>(r.rr15) << std::endl;
        return r.rr15;
    }
    
    std::vector<uint8_t> assemble(const std::string & asm_code) {
        std::vector<uint8_t> instructions;
        std::istringstream stream(asm_code);
        std::string token;
        
        while (stream >> token) {
            if (opcode_map.find(token) != opcode_map.end()) {
                instructions.push_back(opcode_map[token]);
            } else {
                instructions.push_back(static_cast<uint8_t>(std::stoi(token)));
            }
            
            if (token == "NOP" || token == "RAL" ||  token == "RAR" ||  token == "CMC" || token == "CMC") {
                ++counter_r;
                instruction_addresses[++counter_u] = counter_r;
            } else if (token == "JCN") {
                ++counter_r;
                instruction_addresses[++counter_u] = counter_r;
                ++counter_r;
                ++counter_r;
            } else {
                ++counter_r;
                instruction_addresses[++counter_u] = counter_r;
                ++counter_r;
            }
            
        }
        return instructions;
    }
    
    
    
    uint get_memory() {
        std::cout << "FREE_MEMORY - " << memory_size - instructions_size;
        std::cout << std::endl;
        std::cout << "USING_MEMORY - " << instructions_size;
        std::cout << std::endl;
        return 0;
    }
    
    // Pin command
    
    void reset() {
        p.pc = 0;
        
        a.ac = 0;
        
        r.rr0 = 0;
        r.rr1 = 0;
        r.rr2 = 0;
        r.rr3 = 0;
        r.rr4 = 0;
        r.rr5 = 0;
        r.rr6 = 0;
        r.rr7 = 0;
        r.rr8 = 0;
        r.rr9 = 0;
        r.rr10 = 0;
        r.rr11 = 0;
        r.rr12 = 0;
        r.rr13 = 0;
        r.rr14 = 0;
        r.rr15 = 0;
        
        f.carry = false;
        
        // Auxiliary
        
        t.temp = 0;
        t.tempac = 0;
    }
    
    void run() {
        while (true) {
            uint8_t opcode = memory[p.pc++];
            
            switch (opcode) {
                case NOP: // Остановка
                    return;
                case LDM: // Загружаем число в аккум
                    a.ac = memory[p.pc++];
                    break;
                case XCH: // Загружаем число в регистер 0 из аккума
                    if (memory[p.pc] == RR0) {
                        t.temp = r.rr0;
                        r.rr0 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR1) {
                        t.temp = r.rr1;
                        r.rr1 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR2) {
                        t.temp = r.rr2;
                        r.rr2 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR3) {
                        t.temp = r.rr3;
                        r.rr3 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR4) {
                        t.temp = r.rr4;
                        r.rr4 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR5) {
                        t.temp = r.rr5;
                        r.rr5 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR6) {
                        t.temp = r.rr6;
                        r.rr6 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR7) {
                        t.temp = r.rr7;
                        r.rr7 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR8) {
                        t.temp = r.rr8;
                        r.rr8 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR9) {
                        t.temp = r.rr9;
                        r.rr9 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR10) {
                        t.temp = r.rr10;
                        r.rr10 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR11) {
                        t.temp = r.rr11;
                        r.rr11 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR12) {
                        t.temp = r.rr12;
                        r.rr12 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR13) {
                        t.temp = r.rr13;
                        r.rr13 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR14) {
                        t.temp = r.rr14;
                        r.rr14 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    } else if (memory[p.pc] == RR15) {
                        t.temp = r.rr15;
                        r.rr15 = a.ac;
                        a.ac = t.temp;
                        
                        t.temp = 0;
                    }
                                                    
                    p.pc++;
                    break;
                case ADD: // Сложение
                    t.tempac = a.ac;
                    if (memory[p.pc] == RR0) {
                        a.ac += r.rr0;
                        t.temp = r.rr0;
                    } else if (memory[p.pc] == RR1) {
                        a.ac += r.rr1;
                        t.temp = r.rr1;
                    } else if (memory[p.pc] == RR2) {
                        a.ac += r.rr2;
                        t.temp = r.rr2;
                    } else if (memory[p.pc] == RR3) {
                        a.ac += r.rr3;
                        t.temp = r.rr3;
                    } else if (memory[p.pc] == RR4) {
                        a.ac += r.rr4;
                        t.temp = r.rr4;
                    } else if (memory[p.pc] == RR5) {
                        a.ac += r.rr5;
                        t.temp = r.rr5;
                    } else if (memory[p.pc] == RR6) {
                        a.ac += r.rr6;
                        t.temp = r.rr6;
                    } else if (memory[p.pc] == RR7) {
                        a.ac += r.rr7;
                        t.temp = r.rr7;
                    } else if (memory[p.pc] == RR8) {
                        a.ac += r.rr8;
                        t.temp = r.rr8;
                    } else if (memory[p.pc] == RR9) {
                        a.ac += r.rr9;
                        t.temp = r.rr9;
                    } else if (memory[p.pc] == RR10) {
                        a.ac += r.rr10;
                        t.temp = r.rr10;
                    } else if (memory[p.pc] == RR11) {
                        a.ac += r.rr11;
                        t.temp = r.rr11;
                    } else if (memory[p.pc] == RR12) {
                        a.ac += r.rr12;
                        t.temp = r.rr12;
                    } else if (memory[p.pc] == RR13) {
                        a.ac += r.rr13;
                        t.temp = r.rr13;
                    } else if (memory[p.pc] == RR14) {
                        a.ac += r.rr14;
                        t.temp = r.rr14;
                    } else if (memory[p.pc] == RR15) {
                        a.ac -= r.rr15;
                        t.temp = r.rr15;
                    }
                    
                    if (t.temp + t.tempac > 15) {
                        f.carry = true;
                    } else {
                        f.carry = false;
                    }
                    t.temp = 0;
                    t.tempac = 0;
                    
                    p.pc++;
                    break;
                case INC: // Добавляем 1 к выбранному регистру
                    if (memory[p.pc] == RR0) {
                        t.temp = r.rr0;
                        r.rr0 ++;
                    } else if (memory[p.pc] == RR1) {
                        t.temp = r.rr1;
                        r.rr1 ++;
                    } else if (memory[p.pc] == RR2) {
                        t.temp = r.rr2;
                        r.rr2 ++;
                    } else if (memory[p.pc] == RR3) {
                        t.temp = r.rr3;
                        r.rr3 ++;
                    } else if (memory[p.pc] == RR4) {
                        t.temp = r.rr4;
                        r.rr4 ++;
                    } else if (memory[p.pc] == RR5) {
                        t.temp = r.rr5;
                        r.rr5 ++;
                    } else if (memory[p.pc] == RR6) {
                        t.temp = r.rr6;
                        r.rr6 ++;
                    } else if (memory[p.pc] == RR7) {
                        t.temp = r.rr7;
                        r.rr7 ++;
                    } else if (memory[p.pc] == RR8) {
                        t.temp = r.rr8;
                        r.rr8 ++;
                    } else if (memory[p.pc] == RR9) {
                        t.temp = r.rr9;
                        r.rr9 ++;
                    } else if (memory[p.pc] == RR10) {
                        t.temp = r.rr10;
                        r.rr10 ++;
                    } else if (memory[p.pc] == RR11) {
                        t.temp = r.rr11;
                        r.rr11 ++;
                    } else if (memory[p.pc] == RR12) {
                        t.temp = r.rr12;
                        r.rr12 ++;
                    } else if (memory[p.pc] == RR13) {
                        t.temp = r.rr13;
                        r.rr13 ++;
                    } else if (memory[p.pc] == RR14) {
                        t.temp = r.rr14;
                        r.rr14 ++;
                    } else if (memory[p.pc] == RR15) {
                        t.temp = r.rr5;
                        r.rr15 ++;
                    }
                    
                    if (t.temp + 1 > 15) {
                        f.carry = true;
                    } else {
                        f.carry = false;
                    }
                    t.temp = 0;
           
                    p.pc++;
                    break;
                case JCN:
                    c.condition = memory[p.pc++];
                    c.address = instruction_addresses[memory[p.pc++]];
                    
                    c.shouldJump = false;
                    
                    if (c.condition == C1) {
                        if (f.carry == true) {
                            c.shouldJump = true;
                        }
                    } else if (c.condition == C2) {
                        if (a.ac == 0) {
                            c.shouldJump = true;
                        }
                    } else if (c.condition == C3) {
                        if ((a.ac & 0b1000) != 0) {
                            c.shouldJump = true;
                        }
                    } else if (c.condition == C4) {
                        c.shouldJump = !(f.carry || (a.ac == 0) || ((a.ac & 0b1000) != 0));
                    }
                    
                    if (c.shouldJump) {
                        p.pc = c.address - 1;
                    }
                    
                    break;
                case SUB: // Вычитание
                    t.tempac = a.ac;
                    if (memory[p.pc] == RR0) {
                        a.ac -= r.rr0;
                        t.temp = r.rr0;
                    } else if (memory[p.pc] == RR1) {
                        a.ac -= r.rr1;
                        t.temp = r.rr1;
                    } else if (memory[p.pc] == RR2) {
                        a.ac -= r.rr2;
                        t.temp = r.rr2;
                    } else if (memory[p.pc] == RR3) {
                        a.ac -= r.rr3;
                        t.temp = r.rr3;
                    } else if (memory[p.pc] == RR4) {
                        a.ac -= r.rr4;
                        t.temp = r.rr4;
                    } else if (memory[p.pc] == RR5) {
                        a.ac -= r.rr5;
                        t.temp = r.rr5;
                    } else if (memory[p.pc] == RR6) {
                        a.ac -= r.rr6;
                        t.temp = r.rr6;
                    } else if (memory[p.pc] == RR7) {
                        a.ac -= r.rr7;
                        t.temp = r.rr7;
                    } else if (memory[p.pc] == RR8) {
                        a.ac -= r.rr8;
                        t.temp = r.rr8;
                    } else if (memory[p.pc] == RR9) {
                        a.ac -= r.rr9;
                        t.temp = r.rr9;
                    } else if (memory[p.pc] == RR10) {
                        a.ac -= r.rr10;
                        t.temp = r.rr10;
                    } else if (memory[p.pc] == RR11) {
                        a.ac -= r.rr11;
                        t.temp = r.rr11;
                    } else if (memory[p.pc] == RR12) {
                        a.ac -= r.rr12;
                        t.temp = r.rr12;
                    } else if (memory[p.pc] == RR13) {
                        a.ac -= r.rr13;
                        t.temp = r.rr13;
                    } else if (memory[p.pc] == RR14) {
                        a.ac -= r.rr14;
                        t.temp = r.rr14;
                    } else if (memory[p.pc] == RR15) {
                        a.ac -= r.rr15;
                        t.temp = r.rr15;
                    }
                    
                    if (t.tempac < t.temp) {
                        f.carry = true;
                    } else {
                        f.carry = false;
                    }
                    t.temp = 0;
                    p.pc++;
                    
                    break;
                case CMC: // Инвертируем флаг переноса
                    if (f.carry == true) {
                        f.carry = false;
                    } else if (f.carry == false) {
                        f.carry = true;
                    }
                    
                    break;
                case RAL: // Сдвиг влево с переносом у аккумулятора
                    b.msb = (a.ac & 0b1000) != 0;
                    f.carry = b.msb;
                    a.ac <<= 1;
                    
                    b.lsb = (f.carry & 0b0001) != 0;
                    a.ac |= b.lsb;
                    
                    break; 
                case RAR: // Сдвиг вправо с переносом у аккумулятора
                    b.lsb = (a.ac & 0b0001) != 0;
                    f.carry = b.lsb;
                    a.ac >>= 1;
                    
                    if (f.carry) {
                        a.ac |= 0b1000;
                    } else {
                        a.ac &= 0b0111;
                    }
                    break;
                default:
                    std::cerr << "Unknown instruction!" << std::endl;
                    return;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(11));
        }
    }
    
};

#endif /* core_h */
