#ifndef PROGRAMM_MODULAR_H
#define PROGRAMM_MODULAR_H

#include "Utils.h"

namespace gb::fields {
template<int64_t Mod>
class Modular {
public:
    Modular() = default;

    Modular(int64_t) noexcept;

    int64_t getNumber() const noexcept;

    bool isZero() const noexcept;

    Modular<Mod> operator+() const noexcept;

    Modular<Mod> operator-() const noexcept;

    Modular<Mod> &operator+=(const Modular &) noexcept;

    Modular<Mod> &operator-=(const Modular &) noexcept;

    Modular<Mod> &operator*=(const Modular &) noexcept;

    Modular<Mod> &operator/=(const Modular &);

    friend Modular<Mod> operator+(Modular left, const Modular &right) noexcept {
        left += right;
        return left;
    }

    friend Modular<Mod> operator-(Modular left, const Modular &right) noexcept {
        left -= right;
        return left;
    }

    friend Modular<Mod> operator*(Modular left, const Modular &right) noexcept {
        left *= right;
        return left;
    }

    friend Modular<Mod> operator/(Modular left, const Modular &right) {
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

    template<int64_t OtherMod>
    friend Modular<OtherMod> pow(const Modular<OtherMod> &, const int64_t &);

    template<int64_t OtherMod>
    friend Modular<OtherMod> inverseElement(const Modular<OtherMod> &);

    template<int64_t OtherMod>
    friend std::ostream &operator<<(std::ostream &, const Modular<OtherMod> &) noexcept;

private:
    void reduce_() noexcept;

    int64_t number_{};
};

template<int64_t Order>
Modular<Order>::Modular(int64_t num) noexcept {
    number_ = num;
    reduce_();
}

template<int64_t Order>
int64_t Modular<Order>::getNumber() const noexcept {
    return number_;
}

template<int64_t Order>
void Modular<Order>::reduce_() noexcept {
    if (getNumber() < 0) {
        number_ += (-getNumber() / Order + 1) * Order;
    }
    number_ = getNumber() % Order;
}

template<int64_t Order>
Modular<Order> Modular<Order>::operator+() const noexcept {
    return *this;
}

template<int64_t Order>
Modular<Order> Modular<Order>::operator-() const noexcept {
    return {Order - getNumber()};
}

template<int64_t Order>
Modular<Order> &Modular<Order>::operator+=(const Modular &another) noexcept {
    number_ += another.getNumber();
    reduce_();
    return *this;
}

template<int64_t Order>
Modular<Order> &Modular<Order>::operator-=(const Modular &another) noexcept {
    number_ -= another.getNumber();
    reduce_();
    return *this;
}

template<int64_t Order>
Modular<Order> &Modular<Order>::operator*=(const Modular &another) noexcept {
    number_ *= another.getNumber();
    reduce_();
    return *this;
}

template<int64_t Order>
Modular<Order> &Modular<Order>::operator/=(const Modular &another) {
    number_ *= inverseElement(another).getNumber();
    reduce_();
    return *this;
}

template<int64_t Order>
Modular<Order> pow(const Modular<Order> &num, const int64_t &power) {
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

template<int64_t Order>
Modular<Order> inverseElement(const Modular<Order> &num) {
    if (num.getNumber() == 0) {
        throw std::invalid_argument("Trying inverse zero in modul field");
    }
    return pow(num, Order - 2);
}

template<int64_t Order>
bool Modular<Order>::isZero() const noexcept {
    return number_ == 0;
}

template<int64_t OtherMod>
std::ostream &operator<<(std::ostream &one, const Modular<OtherMod> &num) noexcept {
    return one << num.getNumber();
}


}

#endif //PROGRAMM_MODULAR_H
