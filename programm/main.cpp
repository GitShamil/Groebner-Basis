#include <iostream>
#include "GroebnerLib/includes/Rational.h"
#include "GroebnerLib/includes/Modular.h"
#include "GroebnerLib/includes/PolynomSet.h"

#include <chrono>

void test1() {
    auto monom1 = gb::Monom(std::vector<int64_t>{3, 0});
    auto monom2 = gb::Monom(std::vector<int64_t>{1, 1});
    auto monom3 = gb::Monom(std::vector<int64_t>{2, 1});
    auto monom4 = gb::Monom(std::vector<int64_t>{0, 2});
    auto monom5 = gb::Monom(std::vector<int64_t>{1, 0});
    auto term1 = gb::Term<gb::fields::Rational>(gb::fields::Rational(1), monom1);
    auto term2 = gb::Term<gb::fields::Rational>(gb::fields::Rational(-2), monom2);
    auto term3 = gb::Term<gb::fields::Rational>(gb::fields::Rational(1), monom3);
    auto term4 = gb::Term<gb::fields::Rational>(gb::fields::Rational(-2), monom4);
    auto term5 = gb::Term<gb::fields::Rational>(gb::fields::Rational(1), monom5);
    gb::Polynom<gb::fields::Rational, gb::GrLex> polinom1{};
    polinom1 += term1;
    polinom1 += term2;
    gb::Polynom<gb::fields::Rational,gb::GrLex> polinom2{};
    polinom2 += term3;
    polinom2 += term4;
    polinom2 += term5;
    auto polynoms = gb::PolynomSet<gb::fields::Rational,gb::GrLex>{};
    polynoms.pushBackPolynom(polinom1);
    polynoms.pushBackPolynom(polinom2);
    auto answer = gb::reduceGroebnerBasis(polynoms);
    std::cout << answer.isGroebnerBasis();
}

int main() {
    /*gb::fields::Modular<7> a(-20);
    auto b= a;
    b+=3;
    std::cout<<a.getNumber() << b.getNumber();*/

    /*   int a = 55;
       int b = 11;
       if ((a-=b) < 0){
           std::cout<<5;
       }*/
/*
    auto start_time = std::chrono::high_resolution_clock::now();
    auto a = gb::Monom(std::vector<int64_t>{2,2,6,4});
    auto b = gb::Monom(std::vector<int64_t>{1,1,2,6});
    gb::Term<gb::fields::Modular<7>> c(gb::fields::Modular<7>(-20), a);
    gb::Term<gb::fields::Modular<7>> d(gb::fields::Modular<7>(3), b);
    gb::Polynom<gb::fields::Modular<7>> polinom1(c);
    for (int i = 0; i < 8; ++i) {
        polinom1 += d;
        polinom1 += c;
        auto anther = polinom1;
        polinom1 *= anther;
    }
    std::cout<<polinom1.getTerms().size() <<"\n";

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;*/
    test1();
    std::set<int> a{1, 2, 3};
    auto b = a;
    a.insert(5);
    for (auto el : b) {
        std::cout << el;
    }

}
