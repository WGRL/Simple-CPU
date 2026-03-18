#ifndef PAIR_H
#define PAIR_H

enum instruction_set{
    lda, sta, add, sub, and_, 
    or_, xor_, not_, lla, nop, 
    jmp, jz, in, out, ldb, 
    stb, ldc, stc, mul, div, 
    llb, llc, stp
};

typedef struct{
    uint8_t base;
    char* number;
}Number;

typedef struct{
    char instruction[4];
    enum instruction_set inst;
    char argument[15];
}Pair;

void printPair(int ram_size, Pair code_parsed[ram_size]){
    for(int i = 0; i < ram_size; i++){
        if ( !strcmp(code_parsed[i].instruction, "") )
            continue;
        printf("%s - %s\n", code_parsed[i].instruction, code_parsed[i].argument);
    }
}

typedef struct {
    const char *name;
    enum instruction_set value;
} InstMap;

static const InstMap inst_map[] = {
    {"lda", lda}, {"sta", sta}, {"add", add}, {"sub", sub}, {"and", and_},
    {"or", or_}, {"xor", xor_}, {"not", not_}, {"lla", lla}, {"nop", nop},
    {"jmp", jmp}, {"jz", jz}, {"in", in}, {"out", out}, {"ldb", ldb},
    {"stb", stb}, {"ldc", ldc}, {"stc", stc}, {"mul", mul}, {"div", div},
    {"llb", llb}, {"llc", llc}
};

int assign_instruction(Pair *p) {
    for (size_t i = 0; i < sizeof(inst_map)/sizeof(inst_map[0]); i++) {
        if (strcmp(p->instruction, inst_map[i].name) == 0) {
            p->inst = inst_map[i].value;
            return 0; // sukces
        }
    }
    return -1; // nie znaleziono instrukcji
}

#endif