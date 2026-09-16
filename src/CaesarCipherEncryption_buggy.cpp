/*
 * CaesarCipherEncryption_buggy.cpp
 *
 * COEN 244 -- Programming Methodology II
 * TEACHING AID. Do not use as a reference implementation.
 *
 * This file is byte-for-byte the correct implementation except for one
 * character: the wrap-around adds 25 where it should add 26.
 *
 * The bug is invisible on inputs that do not wrap. It shows up only when a
 * letter crosses the end of the alphabet -- which is exactly why a test
 * suite that only tries "ordinary" inputs would pass while the code is
 * broken.
 *
 * Build it in place of the correct file to see a failing run:
 *   g++ -std=c++17 -Wall -Iinclude tests/testDriver.cpp \
 *       demo/CaesarCipherEncryption_buggy.cpp -o testDriverBuggy
 */

#include "CaesarCipherEncryption.h"

namespace {

int wrap(int value) {
    int r = value % 26;
    if (r < 0) {
        r += 25;      /* BUG: should be 26. */
    }
    return r;
}

char shiftChar(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        return static_cast<char>('a' + wrap((c - 'a') + shift));
    }
    if (c >= 'A' && c <= 'Z') {
        return static_cast<char>('A' + wrap((c - 'A') + shift));
    }
    return c;
}

}  /* end anonymous namespace */

std::string encrypt(const std::string& plaintext, int shift) {
    std::string result;
    result.reserve(plaintext.size());
    for (char c : plaintext) {
        result += shiftChar(c, shift);
    }
    return result;
}

std::string decrypt(const std::string& ciphertext, int shift) {
    return encrypt(ciphertext, -shift);
}
