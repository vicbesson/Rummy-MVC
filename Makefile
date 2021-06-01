# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++11
CXXFLAGS= $(CXXVERSION) -g -fprofile-arcs -ftest-coverage
LINKFLAGS= -lgtest -lpthread -lgmock

# Directories
SRC_DIR = src
SRCS = $(SRC_DIR)/Card.cpp $(SRC_DIR)/Deck.cpp \
		$(SRC_DIR)/Game.cpp $(SRC_DIR)/GameUI.cpp $(SRC_DIR)/GoFish.cpp \
		$(SRC_DIR)/GoFishUI.cpp $(SRC_DIR)/Player.cpp \
		$(SRC_DIR)/Rummy.cpp $(SRC_DIR)/RummyUI.cpp
GTEST_DIR = test
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Tool varialbes
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

MEMCHECK_RESULTS = ValgrindOut.xml

STATIC_RESULTS = CppCheckResults.xml

PROGRAM = cardGame
PROGRAM_TEST = testGame

# default rule for compiling .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean up all files that should NOT be submitted
.PHONY: clean
clean:
	rm -rf *~ $(SRC_DIR)/*.o $(GTEST_DIR)/*.o *.gcov *.gcda *.gcno \
	$(PROGRAM) \
	$(PROGRAM_TEST) \
	$(COVERAGE_RESULTS) \
	$(MEMCHECK_RESULTS) \
	$(COVERAGE_DIR) \
	$(STATIC_RESULTS) \
	docs

# compilation using the files in include, src, and test, but not src/project
$(PROGRAM_TEST): $(GTEST_DIR)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) \
	$(GTEST_DIR)/*.cpp $(SRCS) $(LINKFLAGS)

# compilation using the files in include, src, and src/project
$(PROGRAM): $(SRC_DIR)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(INCLUDE) \
	$(SRC_DIR)/*.cpp

# Perform only unit tests - use locally if gtest/gmock installed
.PHONY: tests
tests: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)

.PHONY: memcheck
memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

.PHONY: fullmemcheck
fullmemcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=full $(PROGRAM_TEST)

.PHONY: memcheck-test
memcheck-test: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

.PHONY: memcheck-game
memcheck-game: $(PROGRAM)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM)

.PHONY: coverage
coverage: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)
	# Determine code coverage
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	$(LCOV) --extract $(COVERAGE_RESULTS) */$(SRC_DIR)/* -o $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	genhtml $(COVERAGE_RESULTS)  --output-directory $(COVERAGE_DIR) --rc lcov_branch_coverage=1
	#Remove all of the generated files from gcov
	rm -f *.gc*

.PHONY: static
static: ${SRC_DIR} ${GTEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${GTEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

.PHONY: style
style: ${SRC_DIR} ${GTEST_DIR} ${SRC_INCLUDE}
	${STYLE_CHECK} ${SRC_INCLUDE}/* ${SRC_DIR}/* ${GTEST_DIR}/*

.PHONY: docs
docs: ${SRC_INCLUDE} ${SRC_DIR}
	doxygen Doxyfile