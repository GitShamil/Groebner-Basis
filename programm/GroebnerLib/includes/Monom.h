#ifndef PROGRAMM_MONOM_H
#define PROGRAMM_MONOM_H

#include "Utils.h"

namespace gb {
class Monom {
public:
    Monom();
    Monom(const std::vector<int64_t>&) noexcept;
    Monom(std::initializer_list<int64_t>) noexcept;

    int64_t operator[](int64_t) const;

    int64_t & operator[](int64_t);

    friend int64_t deg(const Monom&) noexcept;

    const std::vector<int64_t>& getData() const noexcept;

    bool isDivisibleBy(const Monom&) const noexcept;

    bool isInteger() const noexcept;

    size_t size() const noexcept;

    Monom& operator*=(const Monom&) noexcept;
    friend Monom operator*(const Monom&, const Monom&) noexcept;

    Monom& operator/=(const Monom&) noexcept;
    friend Monom operator/(const Monom&, const Monom&) noexcept;

    friend bool operator==(const Monom&, const Monom&) noexcept;
    friend bool operator!=(const Monom&, const Monom&) noexcept;

    friend Monom lcm(const Monom&, const Monom&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Monom&) noexcept;
private:
    friend size_t max_size(const Monom& one,const Monom& two);
    void resizeTo(const Monom& another);
    std::vector<int64_t> data_{};
};

}

#endif //PROGRAMM_MONOM_H
