#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "pair.h"
#include "loader.h"
#include "parse.h"



int main(){

    const char file_name[] = "../demos/helloWorld.asm";
    char code[ram_size][line_len];
    Pair code_parsed[ram_size];
    get_code(file_name, code);
    
    parse(code, code_parsed);
    //printPair(code_parsed); //dziala
    decode(code_parsed);
    return 0;
}


