#ifndef LOADER_H
#define LOADER_H

#define ram_size (255)
#define line_len (30)

#include <stdio.h>
#include <string.h>


void get_code(char file_name[],char code[ram_size][line_len]){
	FILE *file = fopen(file_name, "r");
    char buffer[line_len];

    if (file == NULL) {
		char err[45];
		snprintf(err, sizeof(err), "Can't open %s", file_name);
		perror(err);
        return;
    }
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)){
        strcpy(code[i], buffer);
        i++;
    }
}

void clear_file(char* fname){
    FILE *file = fopen(fname, "w");
    char error_msg[25];
    if (file == NULL) {
        sprintf(error_msg, "error loading a file %s", fname);
        perror(error_msg);
        return 1;
    }
    fclose(file);
}




#endif