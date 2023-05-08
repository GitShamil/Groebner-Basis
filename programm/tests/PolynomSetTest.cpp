#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Term = gb::Term<Rational>;
using Polynom = gb::Polynom<gb::fields::Rational, gb::Lex>;
using Monom = gb::Monom;
using PolynomSet = gb::PolynomSet<gb::fields::Rational, gb::Lex>;

class PolynomSetFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a = {
                {{{4, 3}, {4, 2, 1}},
                        {{4}, {2}}},

                {{{-2},   {0, 2}}}
        };
        b = {
                {{{-2}, {0, 0, 3, 1}},
                              {{1, 3}, {4, 0, 2}},
                        {-2, {0, 0, 0, 3}}},

                {{{-2}, {0, 2}}},

                {{{-1}, {5}}, {-3,     {0, 2, 0, 1}}}
        };
    }

    PolynomSet a;
    PolynomSet b;
};

TEST_F(PolynomSetFixture, EqualTest) {
    PolynomSet a_copy = {
            {{{-2},   {0, 2}}},

            {{{4, 3}, {4, 2, 1}},
                    {{4}, {2}}},
    };
    ASSERT_EQ(a_copy, a);
    ASSERT_NE(a, b);
}

TEST_F(PolynomSetFixture, GetPolynomTest) {
    PolynomSet a_copy = {
            {{{-2},   {0, 2}}},

            {{{4, 3}, {4, 2, 1}},
                    {{4}, {2}}},
    };
    ASSERT_EQ(a_copy.getPolynom(0), a.getPolynom(1));
    ASSERT_EQ(b.getPolynom(1), a.getPolynom(1));
    ASSERT_NE(b.getPolynom(2), a.getPolynom(1));
}

TEST_F(PolynomSetFixture, PushBackPolynomTest) {
    Polynom polynom = {{{2}, {0}},
                       {{3}, {4, 5, 6}}};
    PolynomSet a_copy = {
            {{{-2}, {0, 2}}},

            {{{4, 3}, {4, 2, 1}},
             {{4}, {2}}},

            polynom
    };
    a.pushBackPolynom(polynom);
    ASSERT_EQ(a_copy, a);
}

TEST_F(PolynomSetFixture, InsertPolynomTest) {
    Polynom polynom = {{{2}, {0}},
                       {{3}, {4, 5, 6}}};
    for (int i = 0; i < 1000000; ++i) {
        a.insert(std::next(a.begin()), polynom);
    }
    ASSERT_EQ(a.getPolynom(1), polynom);
}

TEST_F(PolynomSetFixture, RemovePolynomTest) {
    a.removePolynom(std::next(a.begin()));
    ASSERT_EQ(a.size(), 1);
}

TEST_F(PolynomSetFixture, sizeTest) {
    ASSERT_EQ(a.size(), 2);
    ASSERT_EQ(b.size(), 3);
}

TEST_F(PolynomSetFixture, emptyTest) {
    ASSERT_FALSE(a.empty());
    ASSERT_FALSE(b.empty());
    a.removePolynom(a.begin());
    a.removePolynom(a.begin());
    b.removePolynom(b.begin());
    b.removePolynom(b.begin());
    b.removePolynom(b.begin());
    ASSERT_TRUE(a.empty());
    ASSERT_TRUE(b.empty());
}

TEST_F(PolynomSetFixture, findTest) {
    Polynom random = {{3,  {2, 2, 2, 2}},
                      {-5, {1, 1, 1, 1, 1, 1}}};
    Polynom included = {{{-2}, {0, 2}}};
    ASSERT_EQ(a.find(random), a.end());
    ASSERT_NE(a.find(included), a.end());
}

