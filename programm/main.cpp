#include <iostream>
#include "GroebnerLib/includes/Rational.h"
#include "GroebnerLib/includes/Modular.h"

int main() {
    gb::fields::Modular<7> a(-20);
    std::cout<<a.getNumber();
}
