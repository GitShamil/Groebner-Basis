#include <iostream>
#include "GroebnerLib/includes/Rational.h"

int main() {
    gb::fields::Rational a(20,5);
    std::cout<<a.getNumerator();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
