#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//
// Created by Наиль on 01.05.2023.
//

#ifndef PROGRAMM_POLYNOMSET_H
#define PROGRAMM_POLYNOMSET_H

#include "Polynom.h"

namespace gb {

template<typename Field, typename C = Lex>
class PolynomSet {
public:
    using container = std::vector<Polynom<Field, C>>;
    using iterator = typename container::iterator;

    PolynomSet();

    PolynomSet(const Polynom<Field, C> &);

    PolynomSet(const container &);

    const container &getPolynoms() const noexcept;

    const Polynom<Field, C> &getPolynom(int64_t = 0) const;

    bool empty() const noexcept;

    size_t size() const noexcept;

    // if return true, then it is 100% GroebnerBasis, but false doesn't mean anything
    bool isGroebnerBasis() const noexcept;

    bool isGroebnerBasisSure() const noexcept;

    typename container::iterator pushBackPolynom(const Polynom<Field, C> &) noexcept;

    void removePolynom(const Polynom<Field, C> &);

    iterator removePolynom(iterator);

    iterator find(const Polynom<Field, C> &) const noexcept;

    iterator begin() const noexcept;

    iterator end() const noexcept;

    template<typename Temp, typename AnotherC>
    friend bool oneRedByPolynoms(const PolynomSet<Temp, AnotherC> &, Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool redByPolynoms(const PolynomSet<Temp, AnotherC> &, Polynom<Temp, AnotherC> &) noexcept;


private:
    bool groebner_Basis_ = false;
    container polynoms_{};
};

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet() = default;

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet(const Polynom<Field, C> &polynom) {
    polynoms_.push_back(polynom);
}

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet(const PolynomSet::container &polynoms) {
    polynoms_ = polynoms;
}

template<typename Field, typename C>
const typename PolynomSet<Field, C>::container &PolynomSet<Field, C>::getPolynoms() const noexcept {
    return polynoms_;
}

template<typename Field, typename C>
const Polynom<Field, C> &PolynomSet<Field, C>::getPolynom(int64_t index) const {
    return polynoms_[index];
}

template<typename Field, typename C>
bool PolynomSet<Field, C>::empty() const noexcept {
    return polynoms_.empty();
}

template<typename Field, typename C>
size_t PolynomSet<Field, C>::size() const noexcept {
    return polynoms_.size();
}

template<typename Field, typename C>
bool PolynomSet<Field, C>::isGroebnerBasis() const noexcept {
    return groebner_Basis_;
}

template<typename Field, typename C>
typename std::vector<gb::Polynom<Field, C>>::iterator
PolynomSet<Field, C>::pushBackPolynom(const Polynom<Field, C> &polynom) noexcept {
    polynoms_.push_back(polynom);
    return polynoms_.end() - 1;
}

template<typename Field, typename C>
void PolynomSet<Field, C>::removePolynom(const Polynom<Field, C> &polynom) {
    for (auto it = polynoms_.begin(); it != polynoms_.end(); ++it) {
        if (*it == polynom) {
            polynoms_.erase(it);
            return;
        }
    }
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::removePolynom(PolynomSet::iterator it) {
    return polynoms_.erase(it);
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::find(const Polynom<Field, C> &polynom) const noexcept {
    return std::find(polynoms_.begin(), polynoms_.end(), polynom);
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::begin() const noexcept {
    return polynoms_.begin();
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::end() const noexcept {
    return polynoms_.end();
}

template<typename Temp, typename AnotherC>
bool oneRedByPolynoms(const PolynomSet<Temp, AnotherC> &polynomSet, Polynom<Temp, AnotherC> &polynom) noexcept {
    for (const auto &reducer : polynomSet) {
        if (polynom.getTerm(0).isDivisibleBy(reducer.getTerm(0))) {
            auto divided_term = polynom.getTerm(0) / reducer.getTerm(0);
            auto quotient_polynom = reducer * divided_term;
            polynom -= quotient_polynom;
            return true;
        }
    }
    return false;
}


template<typename Temp, typename AnotherC>
bool redByPolynoms(const PolynomSet<Temp, AnotherC> &polynomSet, Polynom<Temp, AnotherC> &polynom) noexcept {
    bool changed;
    int number_of_changes = -1;
    do {
        ++number_of_changes;
        changed = false;
        changed = oneRedByPolynoms(polynomSet, polynom);
    } while (changed);
    return number_of_changes > 0;
}


}

#endif //PROGRAMM_POLYNOMSET_H

#pragma clang diagnostic pop