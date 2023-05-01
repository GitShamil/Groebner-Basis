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

    const container &getPolynomials() const noexcept;

    const Polynom<Field, C> &getPolynomial(int64_t = 0) const;

    bool empty() const noexcept;

    size_t size() const noexcept;

    // if return true, then it is 100% GroebnerBasis, but false doesn't mean anything
    bool isGroebnerBasis() const noexcept;

    bool isGroebnerBasisSure() const noexcept;

    typename container::iterator pushBackPolynom(const Polynom<Field, C> &) noexcept;

    void removePolynomial(const Polynom<Field, C> &);

    iterator removePolynomial(iterator);

    iterator find(const Polynom<Field, C> &) const noexcept;

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
const typename PolynomSet<Field, C>::container &PolynomSet<Field, C>::getPolynomials() const noexcept {
    return polynoms_;
}

template<typename Field, typename C>
const Polynom<Field, C> &PolynomSet<Field, C>::getPolynomial(int64_t index) const {
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
void PolynomSet<Field, C>::removePolynomial(const Polynom<Field, C> &polynom) {
    for (auto it = polynoms_.begin(); it != polynoms_.end(); ++it) {
        if (*it == polynom) {
            polynoms_.erase(it);
            return;
        }
    }
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::removePolynomial(PolynomSet::iterator it) {
    return polynoms_.erase(it);
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::find(const Polynom<Field, C> &polynom) const noexcept {
    return std::find(polynoms_.begin(), polynoms_.end(), polynom);
}


}

#endif //PROGRAMM_POLYNOMSET_H

#pragma clang diagnostic pop