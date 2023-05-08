#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Term = gb::Term<Rational>;
using Polynom = gb::Polynom<gb::fields::Rational, gb::Lex>;
using Monom = gb::Monom;

class PolynomFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        a = {{{4, 3}, {4, 2, 1}},
             {{4},    {2}}};
        b = {{{-2}, {0, 2}}};
        c = {{{-2},
                      {0, 0, 3, 1}},
             {{1, 3}, {4, 0, 2}},
             {-2,     {0, 0, 0, 3}}};
    }

    Polynom a;
    Polynom b;
    Polynom c;
};

TEST_F(PolynomFixture, EqualTest) {
    Polynom a_copy = {{{12, 9}, {4, 2, 1}},
                      {{4},     {2}}};
    ASSERT_EQ(a, a_copy);
    Polynom b_copy = b = {{{-8, 2},
                           {0, 2, 0}}};
    ASSERT_EQ(b, b_copy);
    Polynom c_copy = b = {{{-9, 2},
                           {0, 2, 0}}};
    ASSERT_NE(b, b_copy);
}

TEST_F(PolynomFixture, GetTermTest) {
    Term a_copy = {{4},
                   {2}};
    ASSERT_EQ(a.getTerm(1), a_copy);
    Term c_copy = {{1, 3},
                   {4, 0, 2}};
    ASSERT_EQ(c.getTerm(0), c_copy);
}

TEST_F(PolynomFixture, GetMonomTest) {
    Monom a_copy = {2};
    ASSERT_EQ(a.getMonom(1), a_copy);
    Monom c_copy = {4, 0, 2};
    ASSERT_EQ(c.getMonom(0), c_copy);
}

TEST_F(PolynomFixture, GetCoefTest) {
    ASSERT_EQ(a.getCoefficient(1), Rational(4));
    ASSERT_EQ(c.getCoefficient(0), Rational(1, 3));
}

TEST_F(PolynomFixture, IsZeroTest) {
    ASSERT_FALSE(a.isZero());
    ASSERT_FALSE(b.isZero());
    ASSERT_TRUE((a - a).isZero());
}

TEST_F(PolynomFixture, DegTest) {
    ASSERT_EQ(deg(a), 7);
    ASSERT_EQ(deg(c), 6);
}

TEST_F(PolynomFixture, SPolynomTest) {
    Polynom answer1 = {{3, {2}}};
    ASSERT_EQ(sPolynom(a, b), answer1);
    Polynom answer2 = {{6, {0, 2, 3, 1, 0}},
                       {6, {0, 2, 0, 3}}};
    ASSERT_EQ(sPolynom(b, c), answer2);
}

TEST_F(PolynomFixture, PlusTest) {
    Polynom answer1 = {{{4, 3}, {4, 2, 1}},
                       {{4},    {2}},
                       {{-2},   {0, 2}}};
    ASSERT_EQ(a + b, answer1);
    Polynom answer2 = {{-4, {0, 2}}};
    ASSERT_EQ(b + b, answer2);
}

TEST_F(PolynomFixture, MinusTest) {
    Polynom answer1 = {{{4, 3}, {4, 2, 1}},
                       {{4},    {2}},
                       {{2},    {0, 2}}};
    ASSERT_EQ(a - b, answer1);
    Polynom answer2 = {};
    ASSERT_EQ(b - b, answer2);
}

TEST_F(PolynomFixture, MultiplyTest) {
    Polynom answer1 = {{{-8, 3}, {4, 4, 1}},
                       {{-8},    {2, 2}}};
    ASSERT_EQ(a * b, answer1);
    Polynom answer2 = {{{4,  9}, {8, 2, 3}},
                       {{4,  3}, {6, 0, 2}},
                       {{-8, 3}, {4, 2, 4, 1}},
                       {{-8, 3}, {4, 2, 1, 3}},
                       {-8,      {2, 0, 3, 1}},
                       {-8,      {2, 0, 0, 3}}};
    ASSERT_EQ(a * c, answer2);
}

TEST_F(PolynomFixture, OutputTest) {
    std::stringstream out;
    out << a;
    ASSERT_STRCASEEQ(out.str().data(), "(4 / 3)*x_(1)^{4}*x_(2)^{2}*x_(3)+4*x_(1)^{2}");
    out = std::stringstream();
    out << b;
    ASSERT_STRCASEEQ(out.str().data(),  "-2*x_(2)^{2}");
}