//
// Created by Наиль on 29.04.2023.
//

#ifndef PROGRAMM_POLYNOM_H
#define PROGRAMM_POLYNOM_H

#include "OrderingTerm.h"

namespace gb {

template<typename Field, typename C = Lex>
class Polynom {
public:
    using container = std::set<Term<Field>, Reverse<C>>;

    Polynom();

    Polynom(const Term<Field> &) noexcept;

    Polynom(const container &) noexcept;

    const Term<Field> &getTerm(int64_t index = 0) const;

    const Monom &getMonom(int64_t index = 0) const;

    const Field &getCoefficient(int64_t index = 0) const;

    const container &getTerms() const noexcept;

    bool isZero() const noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> sPolynom(const Polynom<Temp, AnotherC> &, const Polynom<Temp, AnotherC> &);

    template<typename Temp, typename AnotherC>
    friend int64_t deg(const gb::Polynom<Temp, AnotherC> &) noexcept;

    Polynom operator-() const noexcept;

    Polynom &operator+=(const Term<Field> &) noexcept;

    Polynom &operator-=(const Term<Field> &) noexcept;

    Polynom &operator*=(const Term<Field> &) noexcept;

    Polynom &operator+=(const Polynom &) noexcept;

    Polynom &operator-=(const Polynom &) noexcept;

    Polynom &operator*=(const Polynom &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator+(const Polynom<Temp, AnotherC> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator-(const Polynom<Temp, AnotherC> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator*(const Polynom<Temp, AnotherC> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator+(const Polynom<Temp, AnotherC> &, const Term<Temp> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator-(const Polynom<Temp, AnotherC> &, const Term<Temp> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator*(const Polynom<Temp, AnotherC> &, const Term<Temp> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator+(const Term<Temp> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator-(const Term<Temp> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend Polynom<Temp, AnotherC> operator*(const Term<Temp> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator==(const Polynom<Temp, AnotherC> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator!=(const Polynom<Temp, AnotherC> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator==(const Polynom<Temp, AnotherC> &, const Term<Temp> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator!=(const Polynom<Temp, AnotherC> &, const Term<Temp> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator==(const Term<Temp> &, const Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator!=(const Term<Temp> &, const Polynom<Temp, AnotherC> &) noexcept;

private:

    container terms_{};
};


template<typename Field, typename C>
Polynom<Field, C>::Polynom() = default;

template<typename Field, typename C>
Polynom<Field, C>::Polynom(const Term<Field> &term) noexcept{
    if (!term.getCoefficient().isZero())
        terms_.insert(term);
}

template<typename Field, typename C>
Polynom<Field, C>::Polynom(const Polynom::container &another_terms) noexcept{
    terms_ = another_terms;
}

template<typename Field, typename C>
const Term<Field> &Polynom<Field, C>::getTerm(int64_t index) const {
    auto it = terms_.begin();
    std::advance(it, index);
    return *it;
}

template<typename Field, typename C>
const Monom &Polynom<Field, C>::getMonom(int64_t index) const {
    auto it = terms_.begin();
    std::advance(it, index);
    return it->getMonom();
}

template<typename Field, typename C>
const Field &Polynom<Field, C>::getCoefficient(int64_t index) const {
    auto it = terms_.begin();
    std::advance(it, index);
    return it->getCoefficient();
}


template<typename Field, typename C>
const typename Polynom<Field, C>::container &Polynom<Field, C>::getTerms() const noexcept {
    return terms_;
}

template<typename Field, typename C>
bool Polynom<Field, C>::isZero() const noexcept {
    return terms_.empty();
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> sPolynom(const Polynom<Temp, AnotherC> &one, const Polynom<Temp, AnotherC> &two) {
    if (one.isZero() || two.isZero()) {
        throw std::runtime_error("No S-Polynomial from 0.");
    }
    auto lead_lcm = Term<Temp>(Temp(1),lcm(one.getMonom(0), two.getMonom(0)));
    auto m1 = lead_lcm / one.getTerm(0);
    auto m2 = lead_lcm / two.getTerm(0);
    return one * m1 - two * m2;
}


template<typename Temp, typename AnotherC>
int64_t deg(const Polynom<Temp, AnotherC> &polinom) noexcept {
    int64_t max_degree = 0;
    for (auto &term : polinom.getTerms()) {
        max_degree = std::max(deg(term), max_degree);
    }
    return max_degree;
}

template<typename Field, typename C>
Polynom<Field, C> Polynom<Field, C>::operator-() const noexcept {
    Polynom<Field, C> answer;
    for (auto &term : getTerms()) {
        answer.terms_.insert(-term);
    }
    return answer;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator+=(const Term<Field> &term1) noexcept {
    auto term = term1;
    if (term.getCoefficient().isZero()) {
        return *this;
    }
    auto pair = terms_.insert(term);
    bool coef_zero = false;
    if (!pair.second) {
        auto &term_cur = *pair.first;
        Term<Field> term_new(term_cur.getCoefficient() + term.getCoefficient(), term.getMonom());
        if (term_new.getCoefficient().isZero()) {
            coef_zero = true;
        }
        auto &unconct_term_cur = const_cast<Term<Field> &>(term_cur);
        unconct_term_cur = term_new;
    }
    if (coef_zero) {
        terms_.erase(pair.first);
    }
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator-=(const Term<Field> &term) noexcept {
    *this += -term;
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator*=(const Term<Field> &term1) noexcept {
    auto term = term1;
    for (auto it_cur = terms_.begin(); it_cur != terms_.end(); it_cur++) {
        auto &term_cur = *it_cur;
        auto multiplied_term = term_cur * term;
        auto &unconct_term_cur = const_cast<Term<Field> &>(term_cur);
        unconct_term_cur = multiplied_term;
    }
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator+=(const Polynom<Field, C> &another) noexcept {
    if (this == &another) {
        auto another_copy = another;
        *this *= another_copy;
    } else {
        for (auto &term : another.getTerms()) {
            *this += term;
        }
    }
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator-=(const Polynom<Field, C> &another) noexcept {
    if (this == &another) {
        auto another_copy = another;
        *this *= another_copy;
    } else {
        for (auto &term : another.getTerms()) {
            *this -= term;
        }
    }
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator*=(const Polynom<Field, C> &another) noexcept {
    if (this == &another) {
        auto another_copy = another;
        *this *= another_copy;
    } else {
        Polynom<Field, C> answer;
        for (auto &term : another.getTerms()) {
            answer += (*this * term);
        }
        *this = std::move(answer);
    }
    return *this;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator+(const Polynom<Temp, AnotherC> &one, const Polynom<Temp, AnotherC> &two) noexcept {
    auto answer = one;
    answer += two;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator-(const Polynom<Temp, AnotherC> &one, const Polynom<Temp, AnotherC> &two) noexcept {
    auto answer = one;
    answer -= two;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator*(const Polynom<Temp, AnotherC> &one, const Polynom<Temp, AnotherC> &two) noexcept {
    auto answer = one;
    answer *= two;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator+(const Polynom<Temp, AnotherC> &polynom, const Term<Temp> &term) noexcept {
    auto answer = polynom;
    answer += term;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator-(const Polynom<Temp, AnotherC> &polynom, const Term<Temp> &term) noexcept {
    auto answer = polynom;
    answer -= term;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator*(const Polynom<Temp, AnotherC> &polynom, const Term<Temp> &term) noexcept {
    auto answer = polynom;
    answer *= term;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator+(const Term<Temp> &term, const Polynom<Temp, AnotherC> &polynom) noexcept {
    auto answer = polynom;
    answer += term;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator-(const Term<Temp> &term, const Polynom<Temp, AnotherC> &polynom) noexcept {
    auto answer = polynom;
    answer -= term;
    return answer;
}

template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> operator*(const Term<Temp> &term, const Polynom<Temp, AnotherC> &polynom) noexcept {
    auto answer = polynom;
    answer *= term;
    return answer;
}

template<typename Temp, typename AnotherC>
bool operator==(const Polynom<Temp, AnotherC> &one, const Polynom<Temp, AnotherC> &two) noexcept {
    return one.getTerms() == two.getTerms();
}

template<typename Temp, typename AnotherC>
bool operator!=(const Polynom<Temp, AnotherC> &one, const Polynom<Temp, AnotherC> &two) noexcept {
    return one.getTerms() != two.getTerms();
}

template<typename Temp, typename AnotherC>
bool operator==(const Polynom<Temp, AnotherC> &polynom, const Term<Temp> &term) noexcept {
    return polynom.getTerms().size() == 1 && polynom.getTerm(0) == term;
}

template<typename Temp, typename AnotherC>
bool operator!=(const Polynom<Temp, AnotherC> &polynom, const Term<Temp> &term) noexcept {
    return !(polynom == term);
}

template<typename Temp, typename AnotherC>
bool operator==(const Term<Temp> &term, const Polynom<Temp, AnotherC> &polynom) noexcept {
    return polynom == term;
}

template<typename Temp, typename AnotherC>
bool operator!=(const Term<Temp> &term, const Polynom<Temp, AnotherC> &polynom) noexcept {
    return !(polynom == term);
}


}

#endif //PROGRAMM_POLYNOM_H
