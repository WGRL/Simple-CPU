#ifndef PARSE_H
#define PARSE_H
#include <string.h>
#include "pair.h"
#include "loader.h"

void parse(char code[ram_size][line_len], Pair code_parsed[ram_size]){
    Pair parsed;
    char* start;
    char* part;
    int part_len;
    for (int i = 0; i < ram_size; i++){
        //instruction
        start = code[i];
        instruction_parse(&start, &part);

        part_len = part - start;
        if (part_len <= 1) //no instruction is that short
            continue;
        strncpy(parsed.instruction, start, part_len);
        parsed.instruction[part_len] = '\0';

        //argument
        start = part;
        argument_parse(&start, &part);
        part_len = part - start;
        if (part_len < 1) // no argument = skip
            continue;
        strncpy(parsed.argument, start, part_len);
        parsed.argument[part_len] = '\0';

        code_parsed[i] = parsed;
    }
}


//sets starting and ending point of instruction
void instruction_parse(char** start, char** part){
    while(**start == ' ' && **start != '\0' && **start != ';' && **start != '\n'){
        (*start)++;
    }
    *part = *start;
    while(**part != ' ' && **part != '\0' && **part != ';' && **part != '\n'){
        (*part)++;   
    }
}

//sets starting and ending point of argument
void argument_parse(char** start, char** part){
    while(**start == ' ' && **start != '\0' && **start != ';' && **start != '\n'){
        (*start)++;
    }
    *part = *start;
    while(**part != ' ' && **part != ';'&& **part != '\0' && **part != ';' && **part != '\n'){
        (*part)++;
    }
}


#endif