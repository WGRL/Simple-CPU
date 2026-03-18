# Simple-CPU
Simple CPU designed in verilog. High Level emulated in C. Assembler and fortran inspired 'high' level programming language compiled for it.

# Specification
- 3 general use registers (rxa, rxb, rxc)
- 4 strict use registers (program counter - pc, instruction register - ir, argument register - ar, stack)
- 2 flags (zero, overflow)
- ram stores 255 lines
- every line in ram is 13 bits: 5 bits of instruction code, 8 bits of instruction argument

# Instructions
- 00000 -> LDA : lda x => a=ram[x]
- 00001 -> STA : sta x => ram[x] = a
- 00010 -> ADD : add x => a = a + b    (ignores the argument)
- 00011 -> SUB : sub x => a = a - b    (ignores the argument)
- 00100 -> AND : and x => a = a & b    (ignores the argument)
- 00101 -> OR  : or  x => a = a or b   (ignores the argument)
- 00110 -> XOR : xor x => a = a xor b  (ignores the argument)
- 00111 -> NOT : not x => a = ~a       (ignores the argument)
- 01000 -> LLA : lla x => a = x
- 01001 -> NOP : does nothing
- 01010 -> JMP : jmp x => pc = x
- 01011 -> JZ  : jz  x => if ( flag.zero = 1 ) : px = x
- 01100 -> IN  : input -> a
- 01101 -> OUT : a -> output
- 01110 -> NOP : does nothing
- 01111 -> STP : stp x => program stops(ignores the argument)
- 10000 -> LDB : ldb x => b=ram[x]
- 10001 -> STB : stb x => ram[x] = b
- 10010 -> LDC : ldc x => c=ram[x]
- 10011 -> STC : stc x => ram[x] = c
- 10100 -> MUL : mul x => a = a * b    # note that it might easly overflow
  (ignores the argument)
- 10101 -> DIV : div x => a = a // b; b = a % b
  (ignores the argument)
- 10100 -> LLB : llb x => b = x
- 10101 -> LLC : llc x => c = x

# Demos
bla bla bla

# Fortran
bla bla bla

# Instalation
bla bla bla

# How to use
bla bla bla
