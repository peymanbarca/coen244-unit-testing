/*
 * CaesarCipherEncryption.cpp
 *
 * COEN 244 -- Programming Methodology II
 * Correct implementation of the contract in CaesarCipherEncryption.h.
 */

#include "CaesarCipherEncryption.h"

namespace {

/*
 * Reduce any integer to the range [0, 25].
 *
 * C++'s % operator can return a negative result: (-13) % 26 is -13, not 13.
 * Adding 26 before the second reduction guarantees a non-negative answer.
 * This one helper is why encrypt and decrypt handle negative shifts, shifts
 * larger than 26, and the wrap-around at 'z' without any special cases.
 */
int wrap(int value) {
    return ((value % 26) + 26) % 26;
}

/* Shift a single character. Non-letters are returned unchanged. */
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
    /* Decrypting by k is the same as encrypting by -k. */
    return encrypt(ciphertext, -shift);
}
