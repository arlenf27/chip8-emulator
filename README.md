# CHIP-8 Emulator
## Status
In progress: 
- Core State and Core Instruction Handling in Development
- Test Infrastructure and Unit Tests in Development

## Introduction
Chip-8 is an interpreted programming language originally designed for use on the RCA COSMAC VIP computer in the 1970's by Joseph Weisbecker. The thirty-one hexadecimal instructions on the original Chip-8 instruction set provide functionalities for video/sound output, user input, and data manipulation. 

Chip-8 remains popular for hobbyist programs and games. Some examples can be found [here](https://johnearnest.github.io/chip8Archive/). 

## Resources
This interpreter/emulator is being developed by following [this unofficial Chip-8 standard](https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP%E2%80%908). 
Additional resources include: 
- [Unofficial Chip-8 Technical Reference](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference)
- [Unofficial Chip-8 Instruction Set](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set)

## Interpreter Virtual Environment
The allocated memory for this program is set at 0x1000, or 4096 bytes. This includes program memory, as well as memory reserved for display, data, and variables. The stack has space for 16 2-byte addresses, allowing up to 16 subroutine calls. In accordance with Chip-8 standard, 16 general-purpose data registers (V0 - V16) have been provided, including the flag register VF. The index register is also provided for operations relating to reading/writing memory. 
