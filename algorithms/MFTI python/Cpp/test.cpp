#include "lecture_3 Horner circuit.h"
#include <gtest/gtest.h>

TEST(horner_circuit, convert2Decimal) {
    EXPECT_EQ(convert2Decimal("1000", 2), 8);
    EXPECT_EQ(convert2Decimal("FF", 16), 255);
}

TEST(horner_circuit, changeBase) {
    EXPECT_EQ(changeBase("1000", 2, 8), "10");
    EXPECT_EQ(changeBase("255", 10, 16), "FF");
}