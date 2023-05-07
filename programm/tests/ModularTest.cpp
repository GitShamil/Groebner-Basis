#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"

using Monom = gb::Monom;
using Rational = gb::fields::Rational;

class MonomFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a_3 = Modular3(0);
        b_3 = Modular3(1);
        c_3 = Modular3(2);
        a_7 = Modular7(0);
        b_7 = Modular7(1);
        c_7 = Modular7(2);
    }

    Modular3 a_3;
    Modular3 b_3;
    Modular3 c_3;
    Modular7 a_7;
    Modular7 b_7;
    Modular7 c_7;
};

TEST_F(MonomFixture, LessTest) {
    ASSERT_TRUE(a_3 < b_3);
    ASSERT_TRUE(b_3 < c_3);
    ASSERT_TRUE(a_3 < c_3);
    ASSERT_TRUE(a_7 < b_7);
    ASSERT_TRUE(b_7 < c_7);
    ASSERT_TRUE(a_7 < c_7);
}

TEST_F(MonomFixture, EqualTest) {
    ASSERT_EQ(a_3, Modular3(-3));
    ASSERT_EQ(b_7, Modular7(8));
}

TEST_F(MonomFixture, SumTest) {
    ASSERT_EQ(b_3 + c_3, a_3);
    ASSERT_EQ(a_3, a_3 + a_3);
    ASSERT_EQ(a_7, c_7 + c_7 + c_7 + b_7);
}

TEST_F(MonomFixture, MinusTest) {
    ASSERT_EQ(a_3, -a_3);
    ASSERT_EQ(b_3, -c_3);
    ASSERT_EQ(b_7, c_7 - b_7);
}

TEST_F(MonomFixture, MultipleTest) {
    ASSERT_EQ(b_3, c_3 * c_3);
    ASSERT_EQ(b_7, c_7 * c_7 * c_7);
    ASSERT_EQ(a_7, c_7 * a_7);
}

TEST_F(MonomFixture, DivideTest) {
    ASSERT_EQ(a_7, a_7 / c_7);
    ASSERT_EQ(Modular7(4), 1 / c_7);
    ASSERT_EQ(b_7, 1 / b_7);
}


