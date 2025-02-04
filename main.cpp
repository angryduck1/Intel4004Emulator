#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "assembler.h"
#include "core.h"

int main() {
    Intel4004 ex;
    
    std::vector<uint8_t> instructions{
            LDM, 9,         // Загружаем 9 в аккумулятор
            XCH, RR0,       // Обмениваем значение аккумулятора с RR0 (RR0 теперь 9)
            LDM, 5,         // Загружаем 8 в аккумулятор
            ADD, RR0,       // Сложение: аккумулятор = 8 + 9 (аккумулятор теперь равен 17)
            JCN, C1, 15,    // Если Carry установлен (переполнение), перейти к адресу 12
            LDM, 8,         // Эта инструкция не будет выполнена при переходе
            NOP,
            LDM, 10         // Загружаем значение 10 в аккумулятор после перехода
        };
    
    ex.load_program(instructions);
    
    ex.run();
    
    ex.get_acc();
    ex.get_carry();
    ex.get_memory();
    
    return 0;
    
}

