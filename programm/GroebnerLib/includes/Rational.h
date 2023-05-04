#ifndef PROGRAMM_RATIONAL_H
#define PROGRAMM_RATIONAL_H

#include "Utils.h"

namespace gb::fields {
    class Rational {

    public:
        Rational() noexcept;
        Rational(int64_t, int64_t = 1);

        const int64_t &getNumerator() const noexcept;
        const int64_t &getDenominator() const noexcept;

        bool isZero() const noexcept;

        friend bool operator<(const Rational &, const Rational &) noexcept;
        friend bool operator>(const Rational &, const Rational &) noexcept;
        friend bool operator<=(const Rational &, const Rational &) noexcept;
        friend bool operator>=(const Rational &, const Rational &) noexcept;
        friend bool operator==(const Rational &, const Rational &) noexcept;
        friend bool operator!=(const Rational &, const Rational &) noexcept;

        Rational operator+() const noexcept;
        Rational operator-() const noexcept;
        Rational& operator+=(const Rational&) noexcept;
        friend Rational operator+(const Rational&, const Rational&) noexcept;
        Rational& operator-=(const Rational&) noexcept;
        friend Rational operator-(const Rational&, const Rational&) noexcept;

        Rational& operator*=(const Rational&) noexcept;
        friend Rational operator*(const Rational&, const Rational&) noexcept;
        Rational& operator/=(const Rational&);
        friend Rational operator/(const Rational&, const Rational&);

    private:
        void reduce_();

        int64_t numerator_;
        int64_t denominator_;
    };
}
#endif //PROGRAMM_RATIONAL_H
