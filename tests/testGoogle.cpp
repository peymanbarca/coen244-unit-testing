/*
 * testDriver.cpp (Google Test version)
 *
 * COEN 244 -- Programming Methodology II
 * Converted to use the Google Test framework.
 */

#include <gtest/gtest.h>
#include <string>

#include "../src/CaesarCipherEncryption.h"

/* ------------------------------------------------------------------
 * The tests using Google Test MACROs (TEST).
 * ------------------------------------------------------------------ */

TEST(CaesarCipherTest, EncryptBasicAndShifts) {
    // c->p  o->b  e->r  n->a, digits unchanged.
    EXPECT_EQ(encrypt("coen244", 13), "pbra244");

    // Shift 3 is the classic Caesar: a->d, b->e, c->f.
    EXPECT_EQ(encrypt("abc", 3), "def");

    // Wrap-around: z + 1 goes back to a.
    EXPECT_EQ(encrypt("z", 1), "a");

    // A full rotation changes nothing.
    EXPECT_EQ(encrypt("hello", 26), "hello");

    // A zero shift changes nothing.
    EXPECT_EQ(encrypt("hello", 0), "hello");
}

TEST(CaesarCipherTest, DecryptBasicAndShifts) {
    EXPECT_EQ(decrypt("pbra244", 13), "coen244");
    EXPECT_EQ(decrypt("def", 3), "abc");

    // Wrap-around in the other direction: a - 1 goes back to z.
    EXPECT_EQ(decrypt("a", 1), "z");
}

TEST(CaesarCipherTest, NonAlphabeticHandling) {
    EXPECT_EQ(encrypt("244", 13), "244");
    EXPECT_EQ(encrypt("a b!c", 0), "a b!c");
    EXPECT_EQ(encrypt("", 13), "");
}

TEST(CaesarCipherTest, CasePreservation) {
    // Uppercase must stay uppercase.
    EXPECT_EQ(encrypt("ABC", 3), "DEF");
    // Mixed case preserved.
    EXPECT_EQ(encrypt("AbC", 3), "DeF");
}

TEST(CaesarCipherTest, RoundTrip) {
    /*
     * The contract says decrypt(encrypt(s, k), k) == s for every s and k.
     * Shift 5 is used to avoid ROT13's inverse symmetry flaw.
     */
    const std::string original = "Attack at dawn! 244";

    EXPECT_EQ(decrypt(encrypt(original, 5), 5), original);
    EXPECT_EQ(decrypt(encrypt(original, 40), 40), original);
}

TEST(CaesarCipherTest, EdgeShifts) {
    // Shift 27 behaves like shift 1.
    EXPECT_EQ(encrypt("abc", 27), encrypt("abc", 1));

    // Negative shifts rotate backwards.
    EXPECT_EQ(encrypt("def", -3), "abc");
}

/* ------------------------------------------------------------------
 * Main function is no longer needed if linking with -lgtest_main,
 * but if you want to keep an explicit main, you can use this:
 * ------------------------------------------------------------------ */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}