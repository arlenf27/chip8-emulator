compile:
	mkdir -p build
	gcc -std=c11 -o build/chip8_emulator src/main.c src/core/core_state.c -lm -Wall -g -pedantic -Isrc/core

compiler_version:
	gcc --version
   
clean: 
	rm -f build/chip8_emulator
	rm -rf build/*.dSYM

run:
	./build/chip8_emulator
	
macos_leaks_run:
	leaks --atExit -- ./build/chip8_emulator
