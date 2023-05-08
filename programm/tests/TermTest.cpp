#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Term = gb::Term<Rational>;

class TermFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a = {{4, 3},
             {4, 2, 1}};
        b = {{4},
             {2}};
        c = {{-2},
             {0, 0, 3, 1}};
    }

    Term a;
    Term b;
    Term c;
};

TEST_F(TermFixture, EqualTest) {
    Term a_copy = {{-8, -6},
                   {4,  2, 1, 0}};
    ASSERT_EQ(a, a_copy);
    Term b_copy = b = {{8, 2},
                       {2}};
    ASSERT_EQ(b, b_copy);
    Term c_copy = b = {{-2},
                       {0, 0, 1}};
    ASSERT_NE(c, c_copy);
}

TEST_F(TermFixture, OperatorBracesTest) {
    ASSERT_EQ(a[1], 2);
    ASSERT_EQ(a[3], 0);
    ASSERT_EQ(a[3555], 0);
    ASSERT_EQ(b[3555], 0);
    ASSERT_EQ(b[0], 2);
    a[1] = 4;
    ASSERT_EQ(a[1], 4);
}

TEST_F(TermFixture, degTest) {
    ASSERT_EQ(deg(a), 7);
    ASSERT_EQ(deg(c), 4);
}

TEST_F(TermFixture, isDivisibleByTest) {
    ASSERT_TRUE(a.isDivisibleBy(b));
    ASSERT_FALSE(c.isDivisibleBy(b));
}

TEST_F(TermFixture, MunusTest) {
    Term a_copy = {{8, -6},
                   {4, 2, 1, 0}};
    ASSERT_EQ(-a, a_copy);
}


TEST_F(TermFixture, MultiplyTest) {
    Term a_copy = {{16, 3},
                   {6,  2, 1, 0}};
    ASSERT_EQ(a * b, a_copy);

    Term c_copy = {{-8},
                   {2, 0, 3, 1}};
    ASSERT_EQ(c * b, c_copy);
}

TEST_F(TermFixture, DivideTest) {
    Term a_copy = {{1, 3},
                   {2,  2, 1, 0}};
    ASSERT_EQ(a / b, a_copy);
}

TEST_F(TermFixture, OutputTest) {
    std::stringstream out;
    out << a;
    ASSERT_STRCASEEQ(out.str().data(), "(4 / 3)*x_(1)^{4}*x_(2)^{2}*x_(3)");
    out = std::stringstream();
    out << b;
    ASSERT_STRCASEEQ(out.str().data(),  "4*x_(1)^{2}");
}
