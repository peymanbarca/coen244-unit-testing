/*
 * CaesarCipherEncryption.h
 *
 * COEN 244 -- Programming Methodology II
 * Unit testing example: the code under test.
 *
 * SPECIFICATION
 * -------------
 * A Caesar cipher shifts each alphabetic character forward through the
 * alphabet by a fixed amount, wrapping around from 'z' back to 'a'.
 *
 * Contract for both functions:
 *   - Lowercase letters ('a'..'z') are shifted and stay lowercase.
 *   - Uppercase letters ('A'..'Z') are shifted and stay uppercase.
 *   - Every other character (digits, spaces, punctuation) is returned
 *     unchanged.
 *   - The shift is taken modulo 26, so a shift of 26 is the identity and a
 *     shift of 27 behaves like a shift of 1.
 *   - Negative shifts are permitted and rotate backwards.
 *   - The empty string maps to the empty string.
 *
 * decrypt(encrypt(s, k), k) == s  for every string s and every int k.
 *
 * This header is the oracle. The expected values in the tests are derived
 * from the rules above, not from running the implementation.
 */

#ifndef CAESAR_CIPHER_ENCRYPTION_H
#define CAESAR_CIPHER_ENCRYPTION_H

#include <string>

/* Shift every letter in plaintext forward by 'shift' positions. */
std::string encrypt(const std::string& plaintext, int shift);

/* Inverse of encrypt for the same shift. */
std::string decrypt(const std::string& ciphertext, int shift);

#endif /* CAESAR_CIPHER_ENCRYPTION_H */
