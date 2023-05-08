#include <gtest/gtest.h>
#include "../GroebnerLib/includes/Lib.h"
#include <sstream>

using Rational = gb::fields::Rational;
using Term = gb::Term<Rational>;
using Polynom = gb::Polynom<gb::fields::Rational, gb::Lex>;
using Monom = gb::Monom;
using Lex = gb::Lex;
using GrLex = gb::GrLex;
using ReverseLex = gb::Reverse<Lex>;
using ReverseGrLex = gb::Reverse<GrLex>;

class OrderingTermFixture : public ::testing::Test {
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
    Lex lex;
    GrLex gr_lex;
    ReverseLex reverse_lex;
    ReverseGrLex reverse_gr_lex;
};

TEST_F(OrderingTermFixture, LexTest) {
    ASSERT_TRUE(lex(b,a));
    ASSERT_TRUE(lex(c,b));
    ASSERT_TRUE(lex(c,a));
    ASSERT_FALSE(lex(a,c));
    ASSERT_FALSE(lex(a,a));
}

TEST_F(OrderingTermFixture, ReverseLexTest) {
    ASSERT_FALSE(reverse_lex(b,a));
    ASSERT_FALSE(reverse_lex(c,b));
    ASSERT_FALSE(reverse_lex(c,a));
    ASSERT_TRUE(reverse_lex(a,c));
    ASSERT_FALSE(reverse_lex(a,a));
}

TEST_F(OrderingTermFixture, GrLexTest) {
    ASSERT_TRUE(gr_lex(b,a));
    ASSERT_FALSE(gr_lex(c,b));
    ASSERT_TRUE(gr_lex(c,a));
    ASSERT_FALSE(gr_lex(a,c));
    ASSERT_FALSE(gr_lex(a,a));
}

TEST_F(OrderingTermFixture, ReverseGrLexTest) {
    ASSERT_FALSE(reverse_gr_lex(b,a));
    ASSERT_TRUE(reverse_gr_lex(c,b));
    ASSERT_FALSE(reverse_gr_lex(c,a));
    ASSERT_TRUE(reverse_gr_lex(a,c));
    ASSERT_FALSE(reverse_gr_lex(a,a));
}

