# Unit Testing in C++ — Caesar Cipher Example

Companion source for the COEN 244 unit testing lecture. No framework, no build
system required — one `g++` command builds and runs the whole suite.

## Layout


```
include/CaesarCipherEncryption.h        the specification (the oracle)
src/CaesarCipherEncryption.cpp          correct implementation
tests/testDriver.cpp                    the test harness and 17 tests
demo/CaesarCipherEncryption_buggy.cpp   one-character bug, for demonstration
Makefile                                optional convenience targets
```

## Build and run

**Any platform, one command:**

```
g++ -std=c++17 -Wall -Iinclude tests/testDriver.cpp src/CaesarCipherEncryption.cpp -o testDriver
./testDriver
```

**Windows (MSVC), from a Developer Command Prompt:**

```
cl /EHsc /std:c++17 /Iinclude tests\testDriver.cpp src\CaesarCipherEncryption.cpp /Fe:testDriver.exe
testDriver.exe
```

**With make:**

```
make test
```

Expected output ends with:

```
17 / 17 tests passed
```

## Check the exit code

This is the part students skip, and it is the part that matters.

```
./testDriver ; echo $?          # Linux / macOS  -> 0
testDriver.exe & echo %ERRORLEVEL%   # Windows    -> 0
```

## Demonstrating a failure

`demo/CaesarCipherEncryption_buggy.cpp` is identical to the correct file except
that the wrap-around adds 25 where it should add 26. Build the same tests
against it:

```
g++ -std=c++17 -Wall -Iinclude tests/testDriver.cpp src/CaesarCipherEncryption_buggy.cpp -o testDriverBuggy
./testDriverBuggy
```

or `make buggy`. Verified output:

```
[ FAIL ] decrypt: basic word
         expected: "coen244"
         actual:   "cnem244"
[ FAIL ] decrypt: wraps at a
         expected: "z"
         actual:   "y"
[ FAIL ] round trip with shift 5
         expected: "Attack at dawn! 244"
         actual:   "Attack at davn! 244"
[ FAIL ] round trip with shift 40
         expected: "Attack at dawn! 244"
         actual:   "Assabj as cavm! 244"

13 / 17 tests passed
```

Exit code 1.


## with GoogleTest

```
g++ -std=c++17 -Wall -Iinclude tests/testGoogle.cpp src/CaesarCipherEncryption.h src/CaesarCipherEncryption.cpp -lgtest -lgtest_main -pthread -o testDriverGoogle
./testDriverGoogle
```

## Teaching points this example is built around

**The bug is invisible to "ordinary" inputs.** `encrypt: basic word` passes
against the broken code. Every failure involves a letter that wrapped past the
start or end of the alphabet. This is the argument for testing boundaries
rather than typical values, made concrete.

**The failure output localises the bug.** `expected: "coen244"` against
`actual: "cnem244"` tells you two letters are wrong and that both of them
wrapped. That is enough to find the defect without a debugger.

**Shift 13 cannot detect a swap.** ROT13 is its own inverse, so a version where
the bodies of `encrypt` and `decrypt` had been exchanged would still pass every
shift-13 test. The round-trip tests use shifts 5 and 40 for this reason. Try
swapping the two function bodies in `src/` and confirm which tests catch it.

**The exit code is the interface to everything else.** `make test` fails the
build when a test fails, because `testDriver` returns 1. Change the last line
of `main()` to `return 0;` and watch `make test` report success on broken code.

## Exercises

1. Swap the bodies of `encrypt` and `decrypt` in `src/`. Which tests fail?
   Which would have passed if the suite only used shift 13?
2. Add a `checkInt` overload of `check` for integer comparison. Then add a
   `charShift(char, int)` accessor and test it directly.
3. `check` compares with `==`. Make it report the first differing position when
   two strings have the same length.
4. Delete `tests/testDriver.cpp`'s `testEdgeShifts()` and reintroduce the
   `+ 25` bug. Does the remaining suite still catch it?

## Note on `SimpleEncryption.h`

The original driver included `SimpleEncryption.h` alongside the Caesar cipher.
That file is not reproduced here — the lecture example is deliberately limited
to one unit under test. To bring it back, add its `.cpp` to the compile command
and write a `testSimpleEncryption()` function following the same shape as
`testEncrypt()`. The `check` harness needs no changes.
