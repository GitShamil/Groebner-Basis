#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Term = gb::Term<Rational>;
using Polynom = gb::Polynom<gb::fields::Rational, gb::Lex>;
using Monom = gb::Monom;
using PolynomSet = gb::PolynomSet<gb::fields::Rational, gb::Lex>;

class AlgorithmFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a = {
                {{{4},  {4, 2, 1}},
                        {{4}, {2}}},

                {{{-2}, {0, 2}}}
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

TEST_F(AlgorithmFixture, OneRedTest) {
    Polynom red = {{3,  {2, 2}},
                   {-2, {1}}};
    Polynom not_red = {{{3}, {2, 1}}};
    Polynom not_red_copy = not_red;
    ASSERT_TRUE(gb::oneRedByPolynoms(a, red));
    ASSERT_FALSE(gb::oneRedByPolynoms(a, not_red));
    Polynom red_answer = {{-2, {1}}};
    ASSERT_EQ(red_answer, red);
    ASSERT_EQ(not_red_copy, not_red);
}

TEST_F(AlgorithmFixture, RedTest) {
    Polynom polynom1 = {{4, {7, 3, 1}},
                        {3, {0, 3}}};
    Polynom answer1 = {{-4, {5, 1}}};
    gb::redByPolynoms(a, polynom1);
    ASSERT_EQ(polynom1, answer1);
    Polynom polynom2 = {{2, {0, 0, 0, 3}},
                        {4, {7, 3, 1}},
                        {3, {0, 3}}};
    Polynom answer2 = {{2,  {0, 0, 0, 3}},
                       {-4, {5, 1}}};
    gb::redByPolynoms(a, polynom2);
    ASSERT_EQ(polynom2, answer2);
}


