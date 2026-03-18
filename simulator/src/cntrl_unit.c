#include "../headers/cntrl_unit.h"

void flag_checks(int16_t solution){
    if (solution < 127 && solution > -127)
        flags.overflow = false;
    else
        flags.overflow = true;
    if ( (int8_t) solution == 0)
        flags.zero = true;
    else
        flags.zero = false;
}


int8_t adder(int8_t a, int8_t b){
    int16_t solution;
    solution = (int16_t) a + (int16_t) b;
    flag_checks(solution);
    return (int8_t) solution;
}

int8_t multiplier(int8_t a, int8_t b){
    int16_t solution;
    solution = (int16_t) a * (int16_t) b;
    flag_checks(solution);
    return (int8_t) solution;
}

int8_t divider(int8_t a, int8_t b){
    int16_t solution;
    solution = (int16_t) a / (int16_t) b;
    registers.rxb = (int16_t) a % (int16_t) b;
    flag_checks(solution);
    return (int8_t) solution;
}


void code_mux(bool* running){
    switch(registers.ist_code){
    
    case 0: //lda
        ram.adress = registers . ist_arg;
        registers.rxa = ram.memory[ram.adress];
        flag_checks(registers.rxa);
    break;
    case 1: //sta
        ram.adress = registers.ist_arg;
        ram.memory[ram.adress] = registers.rxa;
    break;    
    case 2: //add
        registers.rxa = adder(registers.rxa,  registers.rxb);

    break;
    case 3: //sub
        registers.rxa = adder(registers.rxa,  -registers.rxb);
    break;
    case 4: //and
        registers.rxa = registers.rxa & registers.rxb;
        flag_checks(registers.rxa);
    break;
    case 5: //or
        registers.rxa = registers.rxa | registers.rxb;
        flag_checks(registers.rxa);
    break;    
    case 6: //xor
        registers.rxa = registers.rxa ^ registers.rxb;
        flag_checks(registers.rxa);
        break;
    case 7: //not
        registers.rxa = ~registers.rxa;
        flag_checks(registers.rxa);
    break;
    case 8: //lla
       registers.rxa = registers.ist_arg;
       flag_checks(registers.rxa); 
    break;
    case 9: //NOP, just nothing
        ':' + ')' ;
    break;    
    case 10://jmp
        registers.ist_count = registers.ist_arg;            
    break;
    case 11://jz, jump if flag.zero
        if (!flags.zero) return;
        registers.ist_count = registers.ist_arg;            
    break;
    case 12://in
        registers.rxa = getchar();
        flag_checks(registers.rxa);
    break;
    case 13://out
        printf("%c", (char) registers.rxa);
        fflush(stdout);
    break;
    case 14://NOP, i dont even remember why

    break;    
    case 15://stp 
        *running = false;
    break;
    case 16: //ldb
        ram.adress = registers . ist_arg;
        registers.rxb = ram.memory[ram.adress];
        flag_checks(registers.rxb);
    break;
    case 17://stb
        ram.adress = registers.ist_arg;
        ram.memory[ram.adress] = registers.rxb;
    break;
    case 18://ldc
        ram.adress = registers.ist_arg;
        registers.rxc = ram.memory[ram.adress];
        flag_checks(registers.rxc);
    break;    
    case 19://stc
        ram.adress = registers.ist_arg;
        ram.memory[ram.adress] = registers.rxc;
    break;
    case 20://mul
        registers.rxa = multiplier(registers.rxa, registers.rxb);
    break;
    case 21://div  
         registers.rxa = divider(registers.rxa, registers.rxb);
    break;
    case 22://llb
       registers.rxb = registers.ist_arg;
       flag_checks(registers.rxb); 
    break;    
    case 23://llc
       registers.rxb = registers.ist_arg;
       flag_checks(registers.rxb); 
        
    break;
    case 24://NOP, again
    break;

    default:
    break;
    }
}
 
void read(){
    bool running = true;
    while (running){
        registers.ist_arg  =  (int8_t)  ram.memory[ram.adress];
        registers.ist_code =  (int8_t) (ram.memory[ram.adress] >> 8);
        code_mux(&running);
        registers.ist_count++;

        ram.adress = registers.ist_count;
    }
}
