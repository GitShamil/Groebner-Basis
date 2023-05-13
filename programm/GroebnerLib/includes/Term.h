

#ifndef PROGRAMM_TERM_H
#define PROGRAMM_TERM_H

#include "Monom.h"
#include "Rational.h"
#include "Modular.h"

namespace gb {

template<typename Field = fields::Rational>
class Term {
public:
    Term();

    Term(Field) noexcept;

    Term(Field, const Monom &) noexcept;

    Term(const Monom &);

    const Field &getCoefficient() const noexcept;

    const Monom &getMonom() const noexcept;

    bool isInteger() const noexcept;

    size_t size() const noexcept;

    int64_t operator[](int64_t) const;

    int64_t &operator[](int64_t);

    template<typename Temp>
    friend int64_t deg(const Term<Temp> &) noexcept;

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

    template<typename Temp>
    friend std::ostream &operator<<(std::ostream &, const Term<Temp> &) noexcept;


private:
    Monom monom_{};
    Field coef_{};
};

template<typename Field>
Term<Field>::Term() = default;


template<typename Field>
Term<Field>::Term(Field num) noexcept {
    coef_ = num;
}

template<typename Field>
Term<Field>::Term(Field num, const Monom &monom) noexcept {
    coef_ = num;
    monom_ = monom;
}

template<typename Field>
Term<Field>::Term(const Monom &monom) {
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
size_t Term<Field>::size() const noexcept {
    return monom_.size();
}

template<typename Field>
int64_t Term<Field>::operator[](int64_t index) const {
    return monom_[index];
}

template<typename Field>
int64_t &Term<Field>::operator[](int64_t index) {
    return monom_[index];
}

template<typename Field>
int64_t deg(const Term<Field> &term) noexcept {
    return deg(term.getMonom());
}

template<typename Field>
bool Term<Field>::isDivisibleBy(const Term<Field> &another) const noexcept {
    return this->getMonom().isDivisibleBy(another.getMonom()) && !another.coef_.isZero();
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
    return (one.getCoefficient().isZero() || one.monom_ == two.monom_) && one.coef_ == two.coef_;
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

template<typename Temp>
std::ostream &operator<<(std::ostream &out, const Term<Temp> &term) noexcept {
    if (term.isInteger()) {
        return out << term.getCoefficient();
    }

    if (term.getCoefficient() == Temp(-1)) {
        out << '-';
    } else if (term.getCoefficient() != Temp(1)){
        out << term.getCoefficient() << '*';
    }

    return out << term.getMonom();
}


}
#endif //PROGRAMM_TERM_H