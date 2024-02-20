BUILD_DIR = build
TEST_EXE = ParallelsTests
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


all: ant

clean:
	rm -rf $(BUILD_DIR)
	rm -rf s21_lcov_report


ant: build
	cmake --build $(BUILD_DIR) --target ant
	./$(BUILD_DIR)/ant

winograd: build
	cmake --build $(BUILD_DIR) --target winograd
	./$(BUILD_DIR)/winograd

gauss: build
	cmake --build $(BUILD_DIR) --target gauss
	./$(BUILD_DIR)/gauss

build:
	CC=gcc CXX=g++ cmake -B $(BUILD_DIR) 

test: build
	cmake --build $(BUILD_DIR) --target $(TEST_EXE)
	./$(BUILD_DIR)/tests/$(TEST_EXE)

leaks: test
	$(MEMORY_TEST) $(BUILD_DIR)/tests/$(TEST_EXE) --gtest_filter=-*.*Throw* --gtest_filter=-*.*NoCheckLeaks*

report: build
	cmake --build $(BUILD_DIR) --target report
	./$(BUILD_DIR)/tests/report
	lcov --capture --directory $(BUILD_DIR)/tests/CMakeFiles/report.dir --output-file $(BUILD_DIR)/s21_coverage.info --exclude "/usr/*" --exclude "*build/*" $(REPORT_FLAG)
	genhtml $(BUILD_DIR)/s21_coverage.info --output-directory s21_lcov_report
	$(OPEN_FILE) ./s21_lcov_report/index.html

stylecheck: build
	cmake --build $(BUILD_DIR) --target stylecheck

cppcheck: build
	cmake --build $(BUILD_DIR) --target cppcheck

format: build
	cmake --build $(BUILD_DIR) --target format
