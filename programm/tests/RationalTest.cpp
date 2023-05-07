#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"

using Rational = gb::fields::Rational;

class RationalFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a = Rational(2, 7);
        b = Rational(6, 4);
        c = Rational(-3, 7);
        d = Rational(15, -2);
    }

    Rational a;
    Rational b;
    Rational c;
    Rational d;
};

TEST_F(RationalFixture, LessTest) {
    ASSERT_TRUE(a < b);
    ASSERT_TRUE(c < a);
    ASSERT_FALSE(a < d);
}

TEST_F(RationalFixture, EquelTest) {
    ASSERT_EQ(a, Rational(-2, -7));
    ASSERT_EQ(b, Rational(24, 16));
    ASSERT_EQ(c, Rational(3, -7));
}

TEST_F(RationalFixture, NotEquelTest) {
    ASSERT_NE(a, -Rational(-2, -7));
    ASSERT_NE(b, Rational(2, 16));
    ASSERT_NE(c, Rational(3, -77));
}

TEST_F(RationalFixture, SumTest) {
    ASSERT_EQ(a + b, Rational(25, 14));
    ASSERT_EQ(b + c, Rational(15, 14));
    ASSERT_EQ(a + c, -Rational(1, 7));
    ASSERT_EQ(c + d, -Rational(111, 14));
}

TEST_F(RationalFixture, MinusTest) {
    ASSERT_EQ(a - b, Rational(-17, 14));
    ASSERT_EQ(b - c, Rational(27, 14));
    ASSERT_EQ(a - c, Rational(5, 7));
    ASSERT_EQ(c - d, Rational(99, 14));
}

TEST_F(RationalFixture, MultipleTest) {
    ASSERT_EQ(a * b, Rational(3, 7));
    ASSERT_EQ(b * c, Rational(-9, 14));
    ASSERT_EQ(a * c, Rational(-6, 49));
    ASSERT_EQ(c * d, Rational(45, 14));
}

TEST_F(RationalFixture,DivideTest) {
    ASSERT_EQ(a / b, Rational(4, 21));
    ASSERT_EQ(b / c, Rational(-7, 2));
    ASSERT_EQ(a / c, -Rational(2, 3));
    ASSERT_EQ(c / d, Rational(2, 35));
}