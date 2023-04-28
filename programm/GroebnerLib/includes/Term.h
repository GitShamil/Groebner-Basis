

#ifndef PROGRAMM_TERM_H
#define PROGRAMM_TERM_H

#include "Monom.h"

namespace gb {

template<typename Field>
class Term {
public:
    Term();

    Term(Field);

    Term(Field, const Monom &);

    const Field &getCoefficient() const noexcept;

    const Monom &getMonom() const noexcept;

    bool isInteger() const noexcept;

    friend int64_t deg(const Term<Field> &) noexcept;

    bool isDivisibleBy(const Term<Field> &) const noexcept;

    Term<Field> operator-() const noexcept;

    Term<Field> &operator*=(const Term<Field> &) noexcept;

    Term<Field> &operator/=(const Term<Field> &);

    Term<Field> &operator*=(const Field &) noexcept;

    Term<Field> &operator/=(const Field &);

    template<typename Temp>
    friend Term<Temp> operator*(const Term<Temp> &, const Term<Temp> &) noexcept;

    template<typename Temp>
    friend Term<Temp> operator/(const Term<Temp> &, const Term<Temp> &) noexcept;

    template<typename Temp>
    friend Term<Temp> operator/(const Term<Temp> &, const Temp &) noexcept;

    template<typename Temp>
    friend Term<Temp> operator*(const Term<Temp> &, const Temp &) noexcept;

    template<typename Temp>
    friend bool operator==(const Term<Temp> &, const Term<Temp> &) noexcept;

    template<typename Temp>
    friend bool operator!=(const Term<Temp> &, const Term<Temp> &) noexcept;

    template<typename Temp>
    friend bool operator==(const Term<Temp> &, const Temp &) noexcept;

    template<typename Temp>
    friend bool operator!=(const Term<Temp> &, const Temp &) noexcept;

    template<typename Temp>
    friend bool operator==(const Temp &, const Term<Temp> &) noexcept;

    template<typename Temp>
    friend bool operator!=(const Temp &, const Term<Temp> &) noexcept;


private:
    Monom monom_{};
    Field coef_{};
};

template<typename Field>
Term<Field>::Term() = default;


template<typename Field>
Term<Field>::Term(Field num) {
    coef_ = num;
}

template<typename Field>
Term<Field>::Term(Field num, const Monom &monom) {
    coef_ = num;
    monom_ = monom;
}

template<typename Field>
const Field &Term<Field>::getCoefficient() const noexcept {
    return coef_;
}

template<typename Field>
const Monom &Term<Field>::getMonom() const noexcept {
    return monom_;
}

template<typename Field>
bool Term<Field>::isInteger() const noexcept {
    return monom_.isInteger();
}


template<typename Field>
int64_t deg(const Term<Field> &term) noexcept {
    return deg(term.getMonom());
}

template<typename Field>
bool Term<Field>::isDivisibleBy(const Term<Field> &another) const noexcept {
    return this->getMonom().isDivisibleBy(another.getMonom()) && another.coef_.isZero();
}

template<typename Field>
Term<Field> Term<Field>::operator-() const noexcept {
    return {-coef_, monom_};
}

template<typename Field>
Term<Field> &Term<Field>::operator*=(const Term<Field> &another) noexcept {
    coef_ *= another.getCoefficient();
    monom_ *= another.getMonom();
    return *this;
}

template<typename Field>
Term<Field> &Term<Field>::operator/=(const Term<Field> &another) {
    coef_ /= another.getCoefficient();
    monom_ /= another.getMonom();
    return *this;
}

template<typename Field>
Term<Field> &Term<Field>::operator*=(const Field &num) noexcept {
    coef_ *= num;
    return *this;
}

template<typename Field>
Term<Field> &Term<Field>::operator/=(const Field &num) {
    coef_ /= num;
    return *this;
}

template<typename Field>
Term<Field> operator*(const Term<Field> &one, const Term<Field> &two) noexcept {
    Term<Field> answer = one;
    answer *= two;
    return answer;
}

template<typename Field>
Term<Field> operator/(const Term<Field> &one, const Term<Field> &two) noexcept {
    Term<Field> answer = one;
    answer /= two;
    return answer;
}

template<typename Field>
Term<Field> operator/(const Term<Field> &term, const Field &num) noexcept {
    Term<Field> answer = term;
    term /= num;
    return term;
}

template<typename Field>
Term<Field> operator*(const Term<Field> &term, const Field &num) noexcept {
    Term<Field> answer = term;
    term *= num;
    return term;
}

template<typename Field>
bool operator==(const Term<Field> &one, const Term<Field> &two) noexcept {
    return one.monom_ == two.monom_ && one.coef_ == two.coef_;
}

template<typename Field>
bool operator!=(const Term<Field> &one, const Term<Field> &two) noexcept {
    return !(one == two);
}

template<typename Field>
bool operator==(const Term<Field> &term, const Field &num) noexcept {
    return term.isInteger() && num == term.coef_;
}

template<typename Field>
bool operator!=(const Term<Field> &term, const Field &num) noexcept {
    return !(term == num);
}

template<typename Field>
bool operator==(const Field &num, const Term<Field> &term) noexcept {
    return term == num;
}

template<typename Field>
bool operator!=(const Field &num, const Term<Field> &term) noexcept {
    return !(term == num);
}

}
#endif //PROGRAMM_TERM_H