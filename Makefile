# COEN 244 -- Unit testing example
#
#   make          build the test driver
#   make test     build and run it (fails the build if any test fails)
#   make buggy    run the same tests against a deliberately broken version
#   make clean    remove binaries

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

all: testDriver

testDriver: tests/testDriver.cpp src/CaesarCipherEncryption.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

testDriverBuggy: tests/testDriver.cpp demo/CaesarCipherEncryption_buggy.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# make stops here with an error if testDriver returns non-zero.
# That is the whole point of the exit code.
test: testDriver
	./testDriver

# The '-' lets make continue past the expected failure so you can read it.
buggy: testDriverBuggy
	-./testDriverBuggy
	@echo "exit code above was non-zero -- that is correct behaviour"

clean:
	rm -f testDriver testDriverBuggy

.PHONY: all test buggy clean
