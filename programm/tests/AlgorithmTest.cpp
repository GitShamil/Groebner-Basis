#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Term = gb::Term<Rational>;
using Polynom = gb::Polynom<gb::fields::Rational, gb::Lex>;
using Monom = gb::Monom;
using PolynomSet = gb::PolynomSet<gb::fields::Rational, gb::Lex>;
using PolynomMod = gb::Polynom<gb::fields::Modular<13>, gb::Lex>;
using PolynomSetMod = gb::PolynomSet<gb::fields::Modular<13>, gb::Lex>;
using PolynomGr = gb::Polynom<gb::fields::Rational, gb::GrLex>;
using PolynomSetGr = gb::PolynomSet<gb::fields::Rational, gb::GrLex>;

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

TEST_F(AlgorithmFixture, ReduceGroebnerBasisTest1) {
    PolynomGr polynom1 = {{1,  {3, 0}},
                          {-2, {1, 1}}};
    PolynomGr polynom2 = {{1,  {2, 1}},
                          {-2, {0, 2}},
                          {1,  {1, 0}}};
    PolynomSetGr polynoms1 = {polynom1, polynom2};
    PolynomSetGr answer1 = {
            {{1, {2}}},
            {{1, {0, 2}}, {{-1, 2}, {1}}},
            {{1, {1, 1}}}
    };
    ASSERT_EQ(gb::reduceGroebnerBasis(polynoms1), answer1);
}

TEST_F(AlgorithmFixture, ReduceGroebnerBasisTest2) {
    Polynom polynom1 = {{1,  {3, 0}},
                        {-2, {1, 1}}};
    Polynom polynom2 = {{1,  {2, 1}},
                        {-2, {0, 2}},
                        {1,  {1, 0}}};
    PolynomSet polynoms1 = {polynom1, polynom2};
    PolynomSet answer1 = {
            {{1, {1}}, {-2, {0, 2}}},
            {{1, {0, 3}}}
    };
    ASSERT_EQ(gb::reduceGroebnerBasis(polynoms1), answer1);
}

TEST_F(AlgorithmFixture, CheckTimeBuchbergTest1_1) {
    for (int i = 0; i < 100000; ++i) {
        Polynom polynom1 = {{1,  {3, 0}},
                            {-2, {1, 1}}};
        Polynom polynom2 = {{1,  {2, 1}},
                            {-2, {0, 2}},
                            {1,  {1, 0}}};
        PolynomSet polynoms1 = {polynom1, polynom2};
        auto k = gb::buchberg(polynoms1, false);
    }
}

TEST_F(AlgorithmFixture, CheckTimeBuchbergTest1_2) {
    for (int i = 0; i < 100000; ++i) {
        Polynom polynom1 = {{1,  {3, 0}},
                            {-2, {1, 1}}};
        Polynom polynom2 = {{1,  {2, 1}},
                            {-2, {0, 2}},
                            {1,  {1, 0}}};
        PolynomSet polynoms1 = {polynom1, polynom2};
        auto k = gb::buchberg(polynoms1, true);
    }
}


TEST_F(AlgorithmFixture, CheckTimeBuchbergTest2_1) {
    for (int i = 0; i < 1; ++i) {
        PolynomMod polynom2 = {{1,  {2, 1}},
                               {-2, {0, 2}},
                               {1,  {1, 0}}};
        PolynomMod polynom3 = {{1,  {0, 6, 1}},
                               {-2, {3, 4}}};
        PolynomSetMod polynoms1 = {polynom2, polynom3};
        auto k = gb::buchberg(polynoms1, false);
    }
}


TEST_F(AlgorithmFixture, CheckTimeBuchbergTest2_2) {
    for (int i = 0; i < 1; ++i) {
        PolynomMod polynom2 = {{1,  {2, 1}},
                               {-2, {0, 2}},
                               {1,  {1, 0}}};
        PolynomMod polynom3 = {{1,  {0, 6, 1}},
                               {-2, {3, 4}}};
        PolynomSetMod polynoms1 = {polynom2, polynom3};
        auto k = gb::buchberg(polynoms1, true);
    }
}

TEST_F(AlgorithmFixture, CheckTimeBuchbergTest3_1) {
    for (int i = 0; i < 1; ++i) {
        PolynomMod polynom2 = {{1,  {2, 5}},
                               {-2, {1, 6}},
                               {1,  {3, 1, 1}}};
        PolynomMod polynom3 = {
                {-2, {3, 4}},
                {5,  {6, 0, 2, 2}}};
        PolynomSetMod polynoms1 = {polynom2, polynom3};
        auto k = gb::buchberg(polynoms1, false);
    }
}

TEST_F(AlgorithmFixture, CheckTimeBuchbergTest3_2) {
    for (int i = 0; i < 1; ++i) {
        PolynomMod polynom2 = {{1,  {2, 5}},
                               {-2, {1, 6}},
                               {1,  {3, 1, 1}}};
        PolynomMod polynom3 = {
                {-2, {3, 4}},
                {5,  {6, 0, 2, 2}}};
        PolynomSetMod polynoms1 = {polynom2, polynom3};
        auto k = gb::buchberg(polynoms1, true);
    }
}

TEST_F(AlgorithmFixture, CheckTimeBuchbergTest4_1) {
    for (int i = 0; i < 10; ++i) {
        PolynomMod polynom2 = {{1,  {4, 1}},
                               {-2, {1, 3}}};
        PolynomMod polynom3 = {{4, {5}}};
        PolynomMod polynom4 = {{5, {0, 1, 6}},
                               {9, {2, 0, 4}},
                {9, {1}}};
        PolynomSetMod polynoms1 = {polynom2, polynom3, polynom4};
        auto k = gb::buchberg(polynoms1, false);
    }
}

TEST_F(AlgorithmFixture, CheckTimeBuchbergTest4_3) {
    for (int i = 0; i < 10; ++i) {
        PolynomMod polynom2 = {{1,  {4, 1}},
                               {-2, {1, 3}}};
        PolynomMod polynom3 = {{4, {5}}};
        PolynomMod polynom4 = {{5, {0, 1, 6}},
                               {9, {2, 0, 4}},
                               {9, {1}}};
        PolynomSetMod polynoms1 = {polynom2, polynom3, polynom4};
        auto k = gb::buchberg(polynoms1, true);
    }
}




