
#include "../includes/Rational.h"

namespace gb::fields {
Rational::Rational(int64_t numerator, int64_t denominator){
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    numerator_ = numerator;
    denominator_ = denominator;
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    reduce_();
}


Rational::Rational() noexcept {
    numerator_ = 0;
    denominator_ = 1;
}

const int64_t &Rational::getNumerator() const noexcept {
    return numerator_;
}

const int64_t &Rational::getDenominator() const noexcept {
    return denominator_;
}

bool operator<(const Rational &one, const Rational &two) noexcept {
    return one.getNumerator() * two.getDenominator() < two.getNumerator() * one.getDenominator();
}

bool operator>(const Rational &one, const Rational &two) noexcept {
    return two < one;
}

bool operator<=(const Rational &one, const Rational &two) noexcept {
    return !(two < one);
}

bool operator>=(const Rational &one, const Rational &two) noexcept {
    return !(one < two);
}

bool operator==(const Rational &one, const Rational &two) noexcept {
    return one.getNumerator() == two.getNumerator() && one.getDenominator() == two.getDenominator();
}

bool operator!=(const Rational &left, const Rational &right) noexcept {
    return !(left == right);
}

void Rational::reduce_() {
    auto gcd = std::gcd(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;
}

Rational Rational::operator+() const noexcept {
    return *this;
}

Rational Rational::operator-() const noexcept {
    return {-getNumerator(), getDenominator()};
}

Rational &Rational::operator+=(const Rational &other) noexcept {
    numerator_ = getNumerator() * other.getDenominator() + other.getNumerator() * getDenominator();
    denominator_ *= other.getDenominator();
    reduce_();
    return *this;
}

Rational operator+(const Rational &one, const Rational &two) noexcept {
    return {one.getNumerator() * two.getDenominator() + two.getNumerator() * one.getDenominator(),
            one.getDenominator() * two.getDenominator()};
}

Rational &Rational::operator-=(const Rational &other) noexcept {
    numerator_ = getNumerator() * other.getDenominator() - other.getNumerator() * getDenominator();
    denominator_ *= other.getDenominator();
    reduce_();
    return *this;
}

Rational operator-(const Rational &one, const Rational &two) noexcept {
    return {one.getNumerator() * two.getDenominator() - two.getNumerator() * one.getDenominator(),
            one.getDenominator() * two.getDenominator()};
}

Rational &Rational::operator*=(const Rational &other) noexcept {
    numerator_ *= other.getNumerator();
    denominator_ *= other.getDenominator();
    reduce_();
    return *this;
}

Rational operator*(const Rational &one, const Rational &two) noexcept {
    return {one.getNumerator() * two.getNumerator(), one.getNumerator() * two.getDenominator()};
}

Rational &Rational::operator/=(const Rational &other) {
    if (other.getNumerator() == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    numerator_ *= other.getDenominator();
    denominator_ *= other.getNumerator();
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    return *this;
}

Rational operator/(const Rational &one, const Rational &two) {
    return {one.getNumerator() * two.getDenominator(),
            one.getDenominator() * two.getNumerator()};
}

bool Rational::isZero() const noexcept {
    return numerator_ == 0;
}

} // namespace gb::fields
