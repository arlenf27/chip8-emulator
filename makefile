CC := gcc
CFLAGS := -std=c11 -Wall -g -pedantic
CFLAGS_EXTRA_FANALYZER := -fanalyzer
LDFLAGS := -lm

MAIN_SRC := src/main.c
CORE_SRCS := src/core/core_state.c src/core/instructions.c
TEST_SRCS := test/main.c test/unit_tests/test_core_state.c test/test_core/test_core.c

INCLUDE_PATHS_SRC := -Isrc/core
INCLUDE_PATHS_TEST := -Itest/test_core -Itest/unit_tests

TARGET := build/chip8_emulator
TARGET_TEST := build_test/chip8_emulator_test
TARGET_FANALYZER := build_fanalyzer/chip8_emulator

compile:
	mkdir -p build
	$(CC) -o $(TARGET) $(MAIN_SRC) $(CORE_SRCS) $(INCLUDE_PATHS_SRC) $(CFLAGS) $(LDFLAGS)

compiler_version:
	$(CC) --version
   
clean: 
	rm -f $(TARGET)
	rm -rf build/*.dSYM
	rm -rf build

run:
	./$(TARGET)
	
macos_leaks_run:
	leaks --atExit -- ./$(TARGET)

compile_tests:
	mkdir -p build_test
	$(CC) -o $(TARGET_TEST) $(CORE_SRCS) $(TEST_SRCS) $(INCLUDE_PATHS_SRC) $(INCLUDE_PATHS_TEST) $(CFLAGS) $(LDFLAGS)
	
clean_tests:
	rm -f $(TARGET_TEST)
	rm -rf build_test/*.dSYM
	rm -rf build_test
	
run_tests:
	./$(TARGET_TEST)
	
macos_leaks_run_tests:
	leaks --atExit -- ./$(TARGET_TEST)
	
compile_fanalyzer:
	mkdir -p build_fanalyzer
	$(CC) -o $(TARGET_FANALYZER) $(MAIN_SRC) $(CORE_SRCS) $(INCLUDE_PATHS_SRC) $(CFLAGS) $(LDFLAGS) $(CFLAGS_EXTRA_FANALYZER)
	
clean_fanalyzer:
	rm -f $(TARGET_FANALYZER)
	rm -rf build_fanalyzer/*.dSYM
	rm -rf build_fanalyzer
	
run_fanalyzer:
	./$(TARGET_FANALYZER)
	
macos_leaks_run_fanalyzer:
	leaks --atExit -- ./$(TARGET_FANALYZER)
	
valgrind_run:
	valgrind --leak-check=yes  ./$(TARGET)
	
valgrind_run_tests:
	valgrind --leak-check=yes ./$(TARGET_TEST)
	
valgrind_run_fanalyzer:
	valgrind --leak-check=yes ./$(TARGET_FANALYZER)