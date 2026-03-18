#ifndef CNTRLUNIT_H
#define CNTRLUNIT_H

#include <stdint.h>
#include <stdio.h>
#include "regs.h"

void flag_checks(int16_t solution);
int8_t adder(int8_t a, int8_t b);
int8_t multiplier(int8_t a, int8_t b);
int8_t divider(int8_t a, int8_t b);
void code_mux(bool* running);
void read();


#endif
