BUILD_DIR = build
# TEST_EXE = SimpleNavigatorTests
REPORT_FLAG =

OS = $(shell uname -s)
MACOS = Darwin

ifeq ($(OS), $(MACOS))
MEMORY_TEST = leaks -atExit --
REPORT_FLAG = --ignore-errors mismatch
OPEN_FILE	= open
else 
MEMORY_TEST = valgrind --trace-children=yes --leak-check=yes --track-origins=yes
OPEN_FILE	= xdg-open
endif


all:

clean:
	rm -rf $(BUILD_DIR)

ant: build
	cmake --build $(BUILD_DIR) --target ant
	./$(BUILD_DIR)/ant

build:
	CC=gcc CXX=g++ cmake -B $(BUILD_DIR) 
