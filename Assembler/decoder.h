#ifndef DECODER_H
#define DECODER_H
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "pair.h"
#include "loader.h"

uint8_t get_base(char* arg){
    char* start = arg;
    char* base_str; 
    int len;
    uint8_t number;
    uint8_t base_modifier, base;

    while (*start != 'x'){
        start++;
    }
    len = start - arg;
    strncpy(base_str, arg, len);
    base_str[len - 2] = 0;
    base = strtol(arg, &start, 10);
    return base;
    
}

//retruns base and argument value
Number get_base_arg(char* arg){
    Number num;
    char* start = arg;
    char* end;
    uint8_t base_modifier;
    size_t len;
    num.base = get_base(arg); //tu moze optymalizacja
    base_modifier = num.base - 10;
    while (*start != 'x'){
        start++;
    }
    end = start;
    start++; //ignore the 'x'
    //while *end is a number we go further
    while ( (*end >= '0' && *end <= '9') || 
    (base_modifier > 0 && *end >= 'A' 
    && *end <= 'A' + base_modifier)){
        end++;
    }
    len = end - start;
    strncpy(num.number, start, len);
    return num;
}

char* arg_to_bin(char* arg, char bin[9]){
    //bool solution[8] = {0, 0, 0, 0, 0};
    Number num;
    num = get_base_arg(arg);
    num.number = base_change(num, 2);
    bin = num.number;
}

int char_to_val(char c) {
    if (isdigit(c)) return c - '0';
    if (isalpha(c)) return toupper(c) - 'A' + 10;
    return -1;
}

char* base_change(Number num, uint8_t dest_base){
    size_t len = strlen(num.number);
    int8_t digit;
    int decimal = 0;
    char decimal_str[15];
    for(int i = len - 1 ; i >= 0 ; i--){
        digit =  char_to_val(num.number[i]);
        if (digit < 0 || digit >= num.base) {
            fprintf(stderr, "Niepoprawny znak: %c\n", num[i]);
            return NULL;
        }
        decimal = decimal * num.base + digit;
    }
    sprintf(decimal_str, "%d", decimal);
    return decimal_str;
}

bool bin_to_bool(uint8_t size, char bin[], bool out[]){
    if (size > 8)
        return 1;
    else if (size < 8){
        for(int i = 7; i >= size  ; i++){
            out[i] = false;
        }
    }
    for(int i = 0 ; i < size ; i++){
        out[i] = bin[i] - '0';
    }
    return 0;
}

void zeroing(int size, bool binary[]){
    for (int i = 0; i < size; i++){
        binary[i] = false;
    }
}

void decode(Pair code[ram_size]){
    const int size = ram_size * 13;
    bool binary[size];//13 -> 5bits code + 8 bits argument
    uint16_t line_start = 0;
    bool instruction[5];
    bool argument[8];
    char bin[9];
    char exe_file[25] = "out.ex";
    uint8_t j;
    zeroing(size, binary);

    clear_file(exe_file);
    for(int i = 0; i < ram_size ; i++){
        assign_instruction(&(code[i]));
        
        switch(code[i].inst){
        case lda: //lda
            memset(instruction, 0, sizeof(instruction));
            arg_to_bin(code[i].argument, bin);
            if (bin_to_bool(sizeof(bin), bin, argument)){
                fprintf(stderr, "invalid number (decode)\n");
            }
        break;
        case sta: //sta

        break;    
        case add: //add


        break;
        case sub: //sub

        break;
        case and_: //and

        break;
        case or_: //or

        break;    
        case xor_: //xor

            break;
        case not_: //not

        break;
        case lla: //lla

        break;
        case nop: //NOP, just nothing
            ':' + ')' ;
        break;    
        case jmp://jmp
           
        break;
        case jz://jz, jump if flag.zero
         
        break;
        case in://in

        break;
        case out://out

        break;   
        case stp ://stp 
            
        break;
        case ldb: //ldb

        break;
        case stb://stb

        break;
        case ldc://ldc

        break;    
        case stc://stc

        break;
        case mul://mul
            
        break;
        case div  ://div  
            
        break;
        case llb://llb
       
        
        break;    
        case llc://llc
            
        break;
        
        default:
        break;
        }

        for (j = line_start; j < line_start + 5; j++){
            binary[j] = instruction[j];
        }for (j = j; j < line_start + 13; j++){
            binary[j] = argument[j - 5];
        }j++;
    }


}

#endif
