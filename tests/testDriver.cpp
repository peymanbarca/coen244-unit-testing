/*
 * testDriver.cpp
 *
 * COEN 244 -- Programming Methodology II
 * A hand-written unit test driver. No framework, no build system.
 *
 * Build:
 *   g++ -std=c++17 -Wall -Iinclude tests/testDriver.cpp \
 *       src/CaesarCipherEncryption.cpp -o testDriver
 *
 * Run:
 *   ./testDriver ; echo $?
 */

#include <iostream>
#include <string>

#include "../src/CaesarCipherEncryption.h"

/* ------------------------------------------------------------------
 * The test harness: two counters and one function.
 * ------------------------------------------------------------------ */

int testsRun = 0;
int testsFailed = 0;

/*
 * Compare one actual value against one expected value and report.
 *
 * Three things this does that a bare cout does not:
 *   1. names the test, so a failure identifies itself;
 *   2. prints both values, so you can see HOW it is wrong;
 *   3. records the failure, so main can return a non-zero exit code.
 */
void check(const std::string& testName,
           const std::string& actual,
           const std::string& expected) {
    ++testsRun;
    if (actual == expected) {
        std::cout << "[ PASS ] " << testName << "\n";
    } else {
        ++testsFailed;
        std::cout << "[ FAIL ] " << testName << "\n"
                  << "         expected: \"" << expected << "\"\n"
                  << "         actual:   \"" << actual << "\"\n";
    }
}

/* ------------------------------------------------------------------
 * The tests.
 *
 * Every expected value below was worked out by hand from the
 * specification in CaesarCipherEncryption.h. None of them was obtained
 * by running the code. That is what makes them tests rather than
 * snapshots.
 * ------------------------------------------------------------------ */

void testEncrypt() {
    /* c->p  o->b  e->r  n->a, digits unchanged. */
    check("encrypt: basic word",
          encrypt("coen244", 13), "pbra244");

    /* Shift 3 is the classic Caesar: a->d, b->e, c->f. */
    check("encrypt: shift 3",
          encrypt("abc", 3), "def");

    /* Wrap-around: z + 1 goes back to a. */
    check("encrypt: wraps at z",
          encrypt("z", 1), "a");

    /* A full rotation changes nothing. */
    check("encrypt: full cycle is identity",
          encrypt("hello", 26), "hello");

    /* A zero shift changes nothing. */
    check("encrypt: zero shift is identity",
          encrypt("hello", 0), "hello");

      check("encrypt: wraps at zyz",
          encrypt("zyz", 1), "aza");
}

void testDecrypt() {
    check("decrypt: basic word",
          decrypt("pbra244", 13), "coen244");

    check("decrypt: shift 3",
          decrypt("def", 3), "abc");

    /* Wrap-around in the other direction: a - 1 goes back to z. */
    check("decrypt: wraps at a",
          decrypt("a", 1), "z");

     std::string encrypted = encrypt("zyz", -1); 
     std::string decrypted = decrypt("zyz", 1);
     check("decrypt: wraps at zyz",
          decrypted, encrypted);
}

void testNonAlphabetic() {
    check("digits are unchanged",
          encrypt("244", 13), "244");


      check("digits are unchanged",
          encrypt("2448472", 26), "2448472");

    check("punctuation and spaces are unchanged",
          encrypt("a b!c", 0), "a b!c");

    check("empty string stays empty",
          encrypt("", 13), "");
}

void testCase() {
    /* Uppercase must stay uppercase. */
    check("uppercase preserved",
          encrypt("ABC", 3), "DEF");

    check("mixed case preserved",
          encrypt("AbC", 3), "DeF");
}

void testRoundTrip() {
    /*
     * The contract says decrypt(encrypt(s, k), k) == s for every s and k.
     *
     * Note that shift 13 is a poor choice for this test on its own:
     * ROT13 is its own inverse, so encrypt and decrypt would both pass
     * even if their bodies had been swapped by mistake. Shift 5 does not
     * have that property, so it catches the swap.
     */
    const std::string original = "Attack at dawn! 244";

    check("round trip with shift 5",
          decrypt(encrypt(original, 5), 5), original);

    check("round trip with shift 40",
          decrypt(encrypt(original, 40), 40), original);
}

void testEdgeShifts() {
    /* Shift 27 behaves like shift 1. */
    check("shift 27 equals shift 1",
          encrypt("abc", 27), encrypt("abc", 1));

      check("shift 53 equals shift 1",
          encrypt("abc", 53), encrypt("abc", 1));


    check("shift -2 equals shift 24",
          encrypt("abc", -2), encrypt("abc", 24));          

     check("shift -2 equals shift -28",
          encrypt("abc", -2), encrypt("abc", -28));

    /* Negative shifts rotate backwards. */
    check("negative shift rotates backwards",
          encrypt("def", -3), "abc");

      check("negative shift rotates backwards",
          encrypt("def123def.", -3), "abc123abc.");
}

/* ------------------------------------------------------------------
 * The runner.
 * ------------------------------------------------------------------ */

int main() {
    testEncrypt();
    testDecrypt();
    testNonAlphabetic();
//     testCase();
//     testRoundTrip();
    testEdgeShifts();

    std::cout << "\n"
              << (testsRun - testsFailed) << " / " << testsRun
              << " tests passed\n";

    /*
     * The exit code is what build scripts and automated marking read.
     * Returning 0 unconditionally would make every failure invisible.
     */
    return (testsFailed == 0) ? 0 : 1;
}
