

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
    const Monom& getMonom() const noexcept;

    friend int64_t deg(const Term<Field>&) noexcept;

    bool isDivisibleBy(const Term<Field>&) const noexcept;

    Term<Field> operator-() const noexcept;

    Term<Field>& operator*=(const  Term<Field>&) noexcept;
    Term<Field>& operator/=(const  Term<Field>&);

    Term<Field>& operator*=(const Field&) noexcept;
    Term<Field>& operator/=(const Field&);


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
int64_t deg(const Term<Field> & term) noexcept {
    return deg(term.getMonom());
}

template<typename Field>
bool Term<Field>::isDivisibleBy(const Term<Field> & another) const noexcept {
    return this->getMonom().isDivisibleBy(another.getMonom()) && another.coef_.isZero();
}

template<typename Field>
Term<Field> Term<Field>::operator-() const noexcept {
    return {-coef_, monom_};
}

template<typename Field>
Term<Field> &Term<Field>::operator*=(const Term<Field> & another) noexcept {
   coef_ *= another.getCoefficient();
   monom_ *= another.getMonom();
   return *this;
}

template<typename Field>
Term<Field> &Term<Field>::operator/=(const Term<Field> & another) {
    coef_ /= another.getCoefficient();
    monom_ /= another.getMonom();
    return *this;
}

template<typename Field>
Term<Field> &Term<Field>::operator*=(const Field & num) noexcept {
    coef_ *= num;
    return *this;
}

template<typename Field>
Term<Field> &Term<Field>::operator/=(const Field & num) {
    coef_ /= num;
    return *this;
}


}
#endif //PROGRAMM_TERM_H