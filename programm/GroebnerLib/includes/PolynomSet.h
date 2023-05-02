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
    using const_iterator = typename container::const_iterator;

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

    iterator fastRemovePolynom(iterator);

    const_iterator find(const Polynom<Field, C> &) const noexcept;

    iterator find(const Polynom<Field, C> &) noexcept;

    iterator begin() noexcept;

    iterator end() noexcept;

    const_iterator begin() const noexcept;

    const_iterator end() const noexcept;

    template<typename Temp, typename AnotherC>
    friend bool oneRedByPolynoms(const PolynomSet<Temp, AnotherC> &, Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool redByPolynoms(const PolynomSet<Temp, AnotherC> &, Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend PolynomSet<Temp, AnotherC> buchberg(const PolynomSet<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend PolynomSet<Temp, AnotherC> buchbergV2(const PolynomSet<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend PolynomSet<Temp, AnotherC> reduceGroebnerBasis(const PolynomSet<Temp, AnotherC> &) noexcept;


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
bool PolynomSet<Field, C>::isGroebnerBasisSure() const noexcept {
    return (buchbergV2(*this) == *this);
}


template<typename Field, typename C>
typename PolynomSet<Field, C>::container::iterator
PolynomSet<Field, C>::pushBackPolynom(const Polynom<Field, C> &polynom) noexcept {
    polynoms_.push_back(polynom);
    return polynoms_.end() - 1;
}

template<typename Field, typename C>
void PolynomSet<Field, C>::removePolynom(const Polynom<Field, C> &polynom) {
    for (auto it = polynoms_.begin(); it != polynoms_.end(); ++it) {
        if (*it == polynom) {
            polynoms_.erase(it);
            groebner_Basis_ = false;
            return;
        }
    }
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::removePolynom(PolynomSet::iterator it) {
    groebner_Basis_ = false;
    return polynoms_.erase(it);
}


template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::fastRemovePolynom(PolynomSet::iterator it) {
    groebner_Basis_ = false;
    std::swap(*it, *std::prev(end()));
    polynoms_.resize(polynoms_.size() - 1);
    return it;
}


template<typename Field, typename C>
typename PolynomSet<Field, C>::const_iterator
PolynomSet<Field, C>::find(const Polynom<Field, C> &polynom) const noexcept {
    return std::find(polynoms_.begin(), polynoms_.end(), polynom);
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::find(const Polynom<Field, C> &polynom) noexcept {
    return std::find(polynoms_.begin(), polynoms_.end(), polynom);
}


template<typename Field, typename C>
typename PolynomSet<Field, C>::container::iterator PolynomSet<Field, C>::begin() noexcept {
    return polynoms_.begin();
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::container::iterator PolynomSet<Field, C>::end() noexcept {
    return polynoms_.end();
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::container::const_iterator PolynomSet<Field, C>::begin() const noexcept {
    return polynoms_.begin();
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::container::const_iterator PolynomSet<Field, C>::end() const noexcept {
    return polynoms_.end();
}

template<typename Temp, typename AnotherC>
bool oneRedByPolynoms(const PolynomSet<Temp, AnotherC> &polynomSet, Polynom<Temp, AnotherC> &polynom) noexcept {
    if (polynom.isZero() || polynomSet.empty()) {
        return false;
    }
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

template<typename Temp, typename AnotherC>
PolynomSet<Temp, AnotherC> buchberg(const PolynomSet<Temp, AnotherC> &polynoms) noexcept {
    if (polynoms.isGroebnerBasis()) {
        return polynoms;
    }
    PolynomSet<Temp, AnotherC> groebner_basis = polynoms;
    int64_t t = polynoms.size() - 1;
    std::unordered_map<int64_t, std::unordered_set<int64_t>> B{};
    for (int64_t i = 0; i < polynoms.size(); ++i) {
        for (int64_t j = i + 1; j < polynoms.size(); ++j) {
            B[i].insert(j);
        }
    }
    while (!B.empty()) {
        auto pair = *B.begin();
        std::pair<int64_t, int64_t> critical_pair = std::make_pair(pair.first, *pair.second.begin());
        auto s_polynom = sPolynom(groebner_basis.getPolynom(critical_pair.first),
                                  groebner_basis.getPolynom(critical_pair.second));
        redByPolynoms(groebner_basis, s_polynom);
        if (!s_polynom.isZero()) {
            groebner_basis.pushBackPolynom(s_polynom);
            ++t;
            for (int64_t i = 0; i < t; ++i) {
                B[i].insert(t);
            }
        }
        B[critical_pair.first].erase(critical_pair.second);
        if (B[critical_pair.first].empty()) {
            B.erase(critical_pair.first);
        }
    }
    groebner_basis.groebner_Basis_ = true;
    return groebner_basis;
}


template<typename Temp, typename AnotherC>
PolynomSet<Temp, AnotherC> buchbergV2(const PolynomSet<Temp, AnotherC> &polynoms) noexcept {
    return buchberg(polynoms);
}

template<typename Temp, typename AnotherC>
PolynomSet<Temp, AnotherC> reduceGroebnerBasis(const PolynomSet<Temp, AnotherC> &polynoms) noexcept {
    if (!polynoms.isGroebnerBasis()) {
        auto groebner_basis = buchbergV2(polynoms);
        return reduceGroebnerBasis(groebner_basis);
    }
    PolynomSet<Temp, AnotherC> groebner_basis = polynoms;
    auto it = groebner_basis.begin();
    int64_t number_polynoms = polynoms.size();
    for (int64_t i = 0; i < number_polynoms; i++) {
        auto polynom = std::move(*it);
        if (it == groebner_basis.begin()) {
            if (groebner_basis.size() == 1) {
                break;
            }
            *it = Polynom<Temp, AnotherC>((it + 1)->getTerm(0));
        } else {
            *it = Polynom<Temp, AnotherC>((it - 1)->getTerm(0));
        }
        if (!oneRedByPolynoms(groebner_basis, polynom)) {
            *it = std::move(polynom);
            it++;
        } else {
            it = groebner_basis.fastRemovePolynom(it);
        }
    }
    for (it = groebner_basis.begin(); it != groebner_basis.end(); it++) {
        Temp coef = it->getCoefficient(0);
        coef = Temp(1) / coef;
        Term<Temp> term(coef);
        (*it) *= term;
        auto polynom = std::move(*it);
        if (it == groebner_basis.begin()) {
            if (groebner_basis.size() == 1) {
                break;
            }
            *it = *(it + 1);
        } else {
            *it = *(it - 1);
        }
        redByPolynoms(groebner_basis, polynom);
        *it = std::move(polynom);
    }
    groebner_basis.groebner_Basis_ = true;
    return groebner_basis;
}


}

#endif //PROGRAMM_POLYNOMSET_H

#pragma clang diagnostic pop