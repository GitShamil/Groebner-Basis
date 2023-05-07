#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"

using Modular7 = gb::fields::Modular<7>;
using Modular3 = gb::fields::Modular<3>;

class ModularFixture : public ::testing::Test {
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

TEST_F(ModularFixture, LessTest) {
    ASSERT_TRUE(a_3 < b_3);
    ASSERT_TRUE(b_3 < c_3);
    ASSERT_TRUE(a_3 < c_3);
    ASSERT_TRUE(a_7 < b_7);
    ASSERT_TRUE(b_7 < c_7);
    ASSERT_TRUE(a_7 < c_7);
}

TEST_F(ModularFixture, EqualTest) {
    ASSERT_EQ(a_3, Modular3(-3));
    ASSERT_EQ(b_7, Modular7(8));
}

TEST_F(ModularFixture, SumTest) {
    ASSERT_EQ(b_3 + c_3, a_3);
    ASSERT_EQ(a_3, a_3 + a_3);
    ASSERT_EQ(a_7, c_7 + c_7 + c_7 + b_7);
}

TEST_F(ModularFixture, MinusTest) {
    ASSERT_EQ(a_3, -a_3);
    ASSERT_EQ(b_3, -c_3);
    ASSERT_EQ(b_7, c_7 - b_7);
}

TEST_F(ModularFixture, MultipleTest) {
    ASSERT_EQ(b_3, c_3 * c_3);
    ASSERT_EQ(b_7, c_7 * c_7 * c_7);
    ASSERT_EQ(a_7, c_7 * a_7);
}

TEST_F(ModularFixture, DivideTest) {
    ASSERT_EQ(a_7, a_7 / c_7);
    ASSERT_EQ(Modular7(4), 1 / c_7);
    ASSERT_EQ(b_7, 1 / b_7);
}


