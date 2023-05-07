#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Monom = gb::Monom;

class MonomFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a = Monom{4, 2, 1};
        b = Monom{2};
        c = Monom{5, 5};
        d = Monom{0, 2, 0, 0, 3, 0};
    }

    Monom a;
    Monom b;
    Monom c;
    Monom d;
};

TEST_F(MonomFixture, EqualTest) {
    ASSERT_EQ(a, Monom(std::vector<int64_t>{4, 2, 1, 0, 0}));
    ASSERT_EQ(b, Monom(std::vector<int64_t>{2}));
    ASSERT_NE(b, Monom(std::vector<int64_t>{2, 1}));
    ASSERT_NE(c, Monom(std::vector<int64_t>{5, 0, 5}));
}

TEST_F(MonomFixture, OperatorBracesTest) {
    ASSERT_EQ(a[1], 2);
    ASSERT_EQ(a[3], 0);
    ASSERT_EQ(a[3555], 0);
    ASSERT_EQ(b[3555], 0);
    ASSERT_EQ(b[0], 2);
    a[1] = 4;
    ASSERT_EQ(a[1], 4);
}

TEST_F(MonomFixture, degTest) {
    ASSERT_EQ(deg(a), 7);
    ASSERT_EQ(deg(d), 5);
}

TEST_F(MonomFixture, isDivisibleByTest) {
    ASSERT_TRUE(a.isDivisibleBy(b));
    ASSERT_TRUE(c.isDivisibleBy(b));
    ASSERT_FALSE(a.isDivisibleBy(d));
    ASSERT_FALSE(c.isDivisibleBy(d));
}

TEST_F(MonomFixture, isIntegerByTest) {
    ASSERT_TRUE(Monom().isInteger());
    ASSERT_FALSE(a.isInteger());
    ASSERT_FALSE(b.isInteger());
    ASSERT_FALSE(c.isInteger());
    ASSERT_FALSE(d.isInteger());
}

TEST_F(MonomFixture, sizeTest) {
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(b.size(), 1);
    ASSERT_EQ(c.size(), 2);
    ASSERT_EQ(d.size(), 6);
}

TEST_F(MonomFixture, MultiplyTest) {
    ASSERT_EQ(a * b, Monom(std::vector<int64_t>{6, 2, 1, 0, 0}));
    ASSERT_EQ(b * d, Monom(std::vector<int64_t>{2, 2, 0, 0, 3, 0}));
    c *= b;
    ASSERT_EQ(c, Monom(std::vector<int64_t>{7, 5}));
}

TEST_F(MonomFixture, DivisibleTestTest) {
    ASSERT_EQ(a / b, Monom(std::vector<int64_t>{2, 2, 1, 0, 0}));
    ASSERT_EQ(c / b, Monom(std::vector<int64_t>{3, 5}));
}

TEST_F(MonomFixture, LcmTest) {
    ASSERT_EQ(lcm(a, b), a);
    ASSERT_EQ(lcm(a, c), Monom(std::vector<int64_t>{5, 5, 1}));
    ASSERT_EQ(lcm(c, d), Monom(std::vector<int64_t>{5, 5, 0, 0, 3}));
}

TEST_F(MonomFixture, OutputTest) {
    std::stringstream out;
    out << a;
    ASSERT_STRCASEEQ(out.str().data(), "x_(1)^{4}*x_(2)^{2}*x_(3)");
    out = std::stringstream();
    out << b;
    ASSERT_STRCASEEQ(out.str().data(), "x_(1)^{2}");
    out = std::stringstream();
    out << d;
    ASSERT_STRCASEEQ(out.str().data(), "x_(2)^{2}*x_(5)^{3}");
}