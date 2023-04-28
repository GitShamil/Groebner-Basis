#ifndef PROGRAMM_MODULAR_H
#define PROGRAMM_MODULAR_H

#include "Utils.h"

namespace gb::fields {
template<uint64_t Order>
class Modular {
public:
    Modular(int64_t = 0);

    const int64_t &getNumber() const noexcept;

    bool isZero() const noexcept;

    Modular<Order> operator+() const noexcept;

    Modular<Order> operator-() const noexcept;

    Modular<Order> &operator+=(const Modular &) noexcept;

    Modular<Order> &operator-=(const Modular &) noexcept;

    Modular<Order> &operator*=(const Modular &) noexcept;

    Modular<Order> &operator/=(const Modular &);

    friend Modular<Order> operator+(Modular left, const Modular &right) noexcept {
        left += right;
        return left;
    }

    friend Modular<Order> operator-(Modular left, const Modular &right) noexcept {
        left -= right;
        return left;
    }

    friend Modular<Order> operator*(Modular left, const Modular &right) noexcept {
        left *= right;
        return left;
    }

    friend Modular<Order> operator/(Modular left, const Modular &right) {
        left /= right;
        return left;
    }

    friend bool operator<(const Modular &left, const Modular &right) noexcept {
        return left.getNumber() < right.getNumber();
    }

    friend bool operator>(const Modular &left, const Modular &right) noexcept {
        return right < left;
    }

    friend bool operator<=(const Modular &left, const Modular &right) noexcept {
        return !(left > right);
    }

    friend bool operator>=(const Modular &left, const Modular &right) noexcept {
        return !(left < right);
    }

    friend bool operator==(const Modular &left, const Modular &right) noexcept {
        return left.getNumber() == right.getNumber();
    }

    friend bool operator!=(const Modular &left, const Modular &right) noexcept {
        return !(left == right);
    }

    template<uint64_t OtherBase>
    friend Modular<OtherBase> pow(const Modular<OtherBase> &, const uint64_t &);

    template<uint64_t OtherBase>
    friend Modular<OtherBase> inverseElement(const Modular<OtherBase> &);

private:
    void reduce_() noexcept;

    int64_t number_{};
};

template<uint64_t Order>
Modular<Order>::Modular(int64_t num) {
    number_ = num;
    reduce_();
}

template<uint64_t Order>
const int64_t &Modular<Order>::getNumber() const noexcept {
    return number_;
}

template<uint64_t Order>
void Modular<Order>::reduce_() noexcept {
    if (getNumber() < 0) {
        number_ += (-getNumber() / Order + 1) * Order;
    }
    number_ = getNumber() % Order;
}

template<uint64_t Order>
Modular<Order> Modular<Order>::operator+() const noexcept {
    return *this;
}

template<uint64_t Order>
Modular<Order> Modular<Order>::operator-() const noexcept {
    return {Order - getNumber()};
}

template<uint64_t Order>
Modular<Order> &Modular<Order>::operator+=(const Modular &another) noexcept {
    number_ += another.getNumber();
    reduce_();
    return *this;
}

template<uint64_t Order>
Modular<Order> &Modular<Order>::operator-=(const Modular &another) noexcept {
    number_ -= another.getNumber();
    reduce_();
    return *this;
}

template<uint64_t Order>
Modular<Order> &Modular<Order>::operator*=(const Modular &another) noexcept {
    number_ *= another.getNumber();
    reduce_();
    return *this;
}

template<uint64_t Order>
Modular<Order> &Modular<Order>::operator/=(const Modular &another) {
    number_ *= inverseElement(another).getNumber();
    reduce_();
    return *this;
}

template<uint64_t Order>
Modular<Order> pow(const Modular<Order> &num, const uint64_t &power) {
    if (power < 0) {
        return pow(inverseElement(num), -power);
    }
    if (power == 0) {
        return {1};
    }
    if (power % 2 != 0) {
        return num * pow(num, power - 1);
    }
    auto tmp = pow(num, power / 2);
    return tmp * tmp;
}

template<uint64_t Order>
Modular<Order> inverseElement(const Modular<Order> &num) {
    if (num.getNumber() == 0) {
        throw std::invalid_argument("Trying inverse zero in modul field");
    }
    return pow(num, Order - 2);
}

template<uint64_t Order>
bool Modular<Order>::isZero() const noexcept {
    return number_ == 0;
}


}

#endif //PROGRAMM_MODULAR_H
