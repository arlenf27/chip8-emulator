compile:
	mkdir -p build
	gcc -std=c11 -o build/chip8_emulator src/main.c src/core/core_state.c -lm -Wall -g -pedantic -Isrc/core

compiler_version:
	gcc --version
   
clean: 
	rm -f build/chip8_emulator
	rm -rf build/*.dSYM
	rm -rf build

run:
	./build/chip8_emulator
	
macos_leaks_run:
	leaks --atExit -- ./build/chip8_emulator

compile_tests:
	mkdir -p build_test
	gcc -std=c11 -o build_test/chip8_emulator_test src/core/core_state.c test/test_core/test_core.c test/unit_tests/test_core_state.c test/main.c -lm -Wall -g -pedantic -Isrc/core -Itest/test_core -Itest/unit_tests
	
clean_tests:
	rm -f build_test/chip8_emlator_test
	rm -rf build_test/*.dSYM
	rm -rf build_test
	
run_tests:
	./build_test/chip8_emulator_test
	
macos_leaks_run_tests:
	leaks --atExit -- ./build_test/chip8_emulator_test