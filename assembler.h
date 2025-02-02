#ifndef assembler_h
#define assembler_h

enum : uint8_t {
    NOP = 0x00, // Ничего
    LDM = 0xD,  // Загрузить в аккумулятор
    ADD = 0x08, // Сложить значение из аккумулятора с регистром
    SUB = 0x09, // Вычесть значение с аккумулятора из регистра
    INC = 0x06, // Увеличить значение в аккумуляторе на 1
    CMC = 0xF3, // Инвертировать флаг переноса
    RAL = 0xF5, // Сдвиг влево с переносом
    RAR = 0xF6, // Сдвиг вправо с переносом
    JCN = 0x01, // Условный переход
    XCH = 0xB,  // Обменять содержимое регистра RR с ACCUMULATOR
    
    RR0,  // Регистер 0
    RR1,  // Регистер 1
    RR2,  // Регистер 2
    RR3,  // Регистер 3
    RR4,  // Регистер 4
    RR5,  // Регистер 5
    RR6,  // Регистер 6
    RR7,  // Регистер 7
    RR8,  // Регистер 8
    RR9,  // Регистер 9
    RR10, // Регистер 10
    RR11, // Регистер 11
    RR12, // Регистер 12
    RR13, // Регистер 13
    RR14, // Регистер 14
    RR15, // Регистер 15
    
};

#endif // ASSEMBLER_H
