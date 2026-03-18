#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../headers/regs.h"
#include "../headers/cntrl_unit.h"
#include "../headers/utils.h"


void init();
void set_ram();

Ram ram;
Registers registers;
Flags flags;
Buss bus;

int main(){
	init();
	set_ram();
	read();
	free(ram.memory);
	return 0;
}

void init(){
	ram.size = 255; // 16 bits * 255
	ram.memory = (uint16_t*) malloc(ram.size * sizeof(uint16_t));
	memset(&flags, 0, sizeof(flags));
	memset(&registers, 0, sizeof(registers));
	memset(&flags, 0, sizeof(flags));
	for (int i = 0; i < ram.size; i++){
		ram.memory[i] = 0;
	}
	ram.data = 0;
	ram.adress = 0;
}

void set_ram(){
	char file_name[] = "../demos/helloWorld.bin";
	FILE *file = fopen(file_name, "r");
    if (file == NULL) {
		char err[45];
		snprintf(err, sizeof(err), "Can't open %s", file_name);
		perror(err);
        return;
    }

    char buffer[14];
	bool bits[16];
	int16_t line;
	int addr = 0;
	
    while (fgets(buffer, sizeof(buffer), file)) {
		line = 0;
		for(int i = 0; i < 13; i++){
			bits[i] = buffer[i] - '0';
			if (bits[i]){
				line |= (1 << (12 - i));
			}
		}
		ram.memory[addr] = line;
		addr++;
    }
    fclose(file);
}