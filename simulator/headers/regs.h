#ifndef REGS_H
#define REGS_H

#include <stdbool.h>

//all uint16_t are representing 13 bits actually

typedef struct{
    int8_t rxa;
    int8_t rxb;
    int8_t rxc; 
    uint8_t ist_count;
    uint8_t stack;
    int8_t ist_code; // 5 bits
    int8_t ist_arg;
}Registers;


typedef struct{
    uint16_t adress;
    uint16_t data;
}Buss;



typedef struct{
    bool overflow;
    bool zero;
}Flags;


typedef struct{
    uint8_t size;
    int16_t data;
    uint8_t adress;
    uint16_t* memory;
}Ram;

extern Ram ram;
extern Registers registers;
extern Flags flags;
extern Buss bus;

#endif