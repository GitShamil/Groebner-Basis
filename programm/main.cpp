#include <iostream>
#include "GroebnerLib/includes/Lib.h"
#include <chrono>


/*auto monom3 = gb::Monom(std::vector<int64_t>{2, 1});
auto monom4 = gb::Monom(std::vector<int64_t>{0, 2});
auto monom5 = gb::Monom(std::vector<int64_t>{1, 0});
auto term1 = gb::Term<gb::fields::Rational>(gb::fields::Rational(1), monom1);
auto term2 = gb::Term<gb::fields::Rational>(gb::fields::Rational(-2), monom2);
auto term3 = gb::Term<gb::fields::Rational>(gb::fields::Rational(1), monom3);
auto term4 = gb::Term<gb::fields::Rational>(gb::fields::Rational(-2), monom4);
auto term5 = gb::Term<gb::fields::Rational>(gb::fields::Rational(1), monom5);*/
void test1() {
    using Monom = gb::Monom;
    using Rational = gb::fields::Rational;
    using Term = gb::Term<Rational>;
    using Polynom = gb::Polynom<gb::fields::Rational, gb::GrLex>;
    using PolynomSet = gb::PolynomSet<gb::fields::Rational, gb::GrLex>;
    Polynom polynom1 = {{1,{3,0}}, {-2,{1,1}}};
    Polynom polynom2 = {{1,{2,1}}, {-2,{0,2}}, {1,{1,0}}};
    PolynomSet polynoms = {polynom1, polynom2, polynom2 + polynom1};
    for (int i = 0; i < 100; ++i) {
        polynoms.pushBackPolynom(polynom2);
    }
    auto answer = gb::reduceGroebnerBasis(gb::buchberg(polynoms, false));
}

void test2(){
    using Monom = gb::Monom;
    using Rational = gb::fields::Rational;
    using Term = gb::Term<Rational>;
    using Polynom = gb::Polynom<gb::fields::Rational, gb::GrLex>;
    using PolynomSet = gb::PolynomSet<gb::fields::Rational, gb::GrLex>;
    Polynom polynom1 = {{Rational(2,-5),{3,0}}, {-2,{1,1}}};
    Polynom polynom2 = {{1,{2,1}}, {-2,{0,2}}, {1,{1,0}}};
    PolynomSet polynoms = {polynom1, polynom2, polynom2 + polynom1};
    std::cout << polynoms;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1; ++i) {
        test2();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "\n Time taken by function: " << duration.count() << " microseconds" << std::endl;
}
