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

    Polynom(const Term<Field> &);

    Polynom(const container &);

    const Term<Field> &getTerm(int64_t index) const;

    const Monom &getMonom(int64_t index) const;

    const Field &getCoefficient(int64_t index) const;

    const container &getTerms() const noexcept;

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
Polynom<Field, C>::Polynom(const Term<Field> &term) {
    terms_.insert(term);
}

template<typename Field, typename C>
Polynom<Field, C>::Polynom(const Polynom::container &another_terms) {
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
    Polynom < Field, C > answer;
    for (auto &term : getTerms()) {
        answer.terms_.insert(-term);
    }
    return answer;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator+=(const Term<Field> &term) noexcept {
    auto pair = terms_.insert(term);
    if (term.getCoefficient().isZero())
        if (pair.second) {
            auto it_term = pair.first;
            auto it_same_monom = terms_.end();
            if (it_term != terms_.begin() && (std::prev(it_term))->getMonom() == it_term->getMonom()) {
                it_same_monom = std::prev(it_term);
            } else if (std::next(it_term) != terms_.end() && (std::next(it_term))->getMonom() == it_term->getMonom()) {
                it_same_monom = std::next(it_term);
            }
            if (it_same_monom != terms_.end()) {
                Field coef_new = it_same_monom->getCoefficient();
                terms_.erase(it_same_monom);
                terms_.erase(it_term);
                terms_.insert(Term<Field>(term.getCoefficient() + coef_new, term.getMonom()));
            }
        } else {
            auto it_term = pair.first;
            terms_.erase(it_term);
            terms_.insert(Term<Field>(term.getCoefficient() + term.getCoefficient(), term.getMonom()));
        }
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator-=(const Term<Field> &term) noexcept {
    *this += -term;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator*=(const Term<Field> &term) noexcept {
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
    for (auto &term : another.getTerms()) {
        *this += term;
    }
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator-=(const Polynom<Field, C> &another) noexcept {
    for (auto &term : another.getTerms()) {
        *this += -term;
    }
    return *this;
}

template<typename Field, typename C>
Polynom<Field, C> &Polynom<Field, C>::operator*=(const Polynom<Field, C> &another) noexcept {
    for (auto &term : another.getTerms()) {
        *this *= term;
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
