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
    using container = std::list<Polynom<Field, C>>;
    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;

    PolynomSet();

    PolynomSet(const Polynom<Field, C> &) noexcept;

    PolynomSet(const container &) noexcept;

    PolynomSet(std::initializer_list<Polynom<Field, C>>) noexcept;

    const container &getPolynoms() const noexcept;

    const Polynom<Field, C> &getPolynom(int64_t = 0) const;

    bool empty() const noexcept;

    size_t size() const noexcept;

    // if return true, then it is 100% GroebnerBasis, but false doesn't mean anything
    bool isGroebnerBasis() const noexcept;

    bool isGroebnerBasisSure() const noexcept;

    typename container::iterator pushBackPolynom(const Polynom<Field, C> &) noexcept;

    iterator insert(const_iterator, const Polynom<Field, C> &);

    iterator insert(const_iterator, Polynom<Field, C> &&);

    void removePolynom(const Polynom<Field, C> &);

    iterator removePolynom(iterator);

//    iterator fastRemovePolynom(iterator);

    const_iterator find(const Polynom<Field, C> &) const noexcept;

    iterator find(const Polynom<Field, C> &) noexcept;

    bool isPolynomInIdeal(const Polynom<Field, C> &) const noexcept;

    iterator begin() noexcept;

    iterator end() noexcept;

    const_iterator begin() const noexcept;

    const_iterator end() const noexcept;

    template<typename Temp, typename AnotherC>
    friend bool operator==(const PolynomSet<Temp, AnotherC> &one, const PolynomSet<Temp, AnotherC> &two) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool oneRedByPolynoms(const PolynomSet<Temp, AnotherC> &, Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend bool redByPolynoms(const PolynomSet<Temp, AnotherC> &, Polynom<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend PolynomSet<Temp, AnotherC> buchberg(const PolynomSet<Temp, AnotherC> &, bool) noexcept;

    template<typename Temp, typename AnotherC>
    friend PolynomSet<Temp, AnotherC> buchbergV2(const PolynomSet<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend PolynomSet<Temp, AnotherC> reduceGroebnerBasis(const PolynomSet<Temp, AnotherC> &) noexcept;

    template<typename Temp, typename AnotherC>
    friend std::ostream &operator<<(std::ostream &, const PolynomSet<Temp, AnotherC> &) noexcept;

private:
    bool groebner_Basis_ = false;
    container polynoms_{};
};

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet() = default;

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet(const Polynom<Field, C> &polynom) noexcept {
    polynoms_.push_back(polynom);
}

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet(const PolynomSet::container &polynoms) noexcept {
    polynoms_ = polynoms;
}

template<typename Field, typename C>
PolynomSet<Field, C>::PolynomSet(std::initializer_list<Polynom<Field, C>> l) noexcept {
    for (auto &polynom : l) {
        polynoms_.push_back(polynom);
    }
}

template<typename Field, typename C>
const typename PolynomSet<Field, C>::container &PolynomSet<Field, C>::getPolynoms() const noexcept {
    return polynoms_;
}

template<typename Field, typename C>
const Polynom<Field, C> &PolynomSet<Field, C>::getPolynom(int64_t index) const {
    auto it = polynoms_.begin();
    std::advance(it, index);
    return *(it);
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
    return std::prev(polynoms_.end());
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator
PolynomSet<Field, C>::insert(PolynomSet::const_iterator pos, const Polynom<Field, C> &value) {
    return polynoms_.insert(pos, value);
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator
PolynomSet<Field, C>::insert(PolynomSet::const_iterator pos, Polynom<Field, C> &&value) {
    return polynoms_.insert(pos, std::move(value));
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
typename PolynomSet<Field, C>::const_iterator
PolynomSet<Field, C>::find(const Polynom<Field, C> &polynom) const noexcept {
    return std::find(polynoms_.begin(), polynoms_.end(), polynom);
}

template<typename Field, typename C>
typename PolynomSet<Field, C>::iterator PolynomSet<Field, C>::find(const Polynom<Field, C> &polynom) noexcept {
    return std::find(polynoms_.begin(), polynoms_.end(), polynom);
}

template<typename Field, typename C>
bool PolynomSet<Field, C>::isPolynomInIdeal(Polynom<Field, C> polynom) const noexcept {
    if (isGroebnerBasis()){
        redByPolynoms(*this, polynom);
        return polynom.isZero();
    }
    auto groebner_basis = buchberg(*this);
    redByPolynoms(groebner_basis, polynom);
    return polynom.isZero();
};


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
bool operator==(const PolynomSet<Temp, AnotherC> &one, const PolynomSet<Temp, AnotherC> &two) noexcept {
    PolynomSet<Temp, AnotherC> one_copy = one;
    PolynomSet<Temp, AnotherC> two_copy = two;
    one_copy.polynoms_.sort();
    two_copy.polynoms_.sort();
    return one_copy.getPolynoms() == two_copy.getPolynoms();
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
    int number_of_changes = -1;
    Polynom remain = {};
    do {
        ++number_of_changes;
        if (!oneRedByPolynoms(polynomSet, polynom)) {
            remain += polynom.getTerm(0);
            polynom -= polynom.getTerm(0);
        }
    } while (!polynom.isZero());
    polynom = std::move(remain);
    return number_of_changes > 0;
}

namespace {
template<typename Temp, typename AnotherC>
Polynom<Temp, AnotherC> getSPolynomOprdered(const Polynom<Temp, AnotherC> &first_polynom,
                                            const Polynom<Temp, AnotherC> &second_polynom,
                                            int64_t index_first, int64_t index_second) {
    if (index_first < index_second) {
        return sPolynom(first_polynom, second_polynom);
    }
    return sPolynom(second_polynom, first_polynom);
}

template<typename Temp, typename AnotherC>
bool buchbergCriterion(const std::pair<int64_t, int64_t> &critical_pair, const Polynom<Temp, AnotherC> &first_polynom,
                       const Polynom<Temp, AnotherC> &second_polynom,
                       const std::unordered_map<int64_t, std::unordered_set<int64_t>> &B,
                       const PolynomSet<Temp, AnotherC> &polynoms) {
    if (lcm(first_polynom.getMonom(0), second_polynom.getMonom(0)) ==
        first_polynom.getMonom(0) * second_polynom.getMonom(0)) {
        return true;
    }
    int64_t i = 0;
    auto s_polynom_i_j = sPolynom(first_polynom, second_polynom);
    for (const auto &polynom : polynoms) {
        if (i == critical_pair.first || i == critical_pair.second) {
            continue;
        }
        if (!lcm(first_polynom.getMonom(0), second_polynom.getMonom(0)).isDivisibleBy(polynom.getMonom(0))) {
            continue;
        }
        auto s_polynom_i_l = getSPolynomOprdered(first_polynom, polynom, critical_pair.first, i);
        auto s_polynom_j_l = getSPolynomOprdered(second_polynom, polynom, critical_pair.second, i);
        auto y_i_j = lcm(first_polynom.getMonom(0), second_polynom.getMonom(0));
        auto y_l_i = lcm(polynom.getMonom(0), first_polynom.getMonom(0));
        auto y_l_j = lcm(polynom.getMonom(0), second_polynom.getMonom(0));
        if (s_polynom_i_j ==
            Term<Temp>((y_i_j / y_l_i)) * s_polynom_i_l - Term<Temp>((y_i_j / y_l_j)) * s_polynom_j_l) {
            return true;
        }
        ++i;
    }
    return false;
}
}


template<typename Temp, typename AnotherC>
PolynomSet<Temp, AnotherC> buchberg(const PolynomSet<Temp, AnotherC> &polynoms, bool version_2 = true) noexcept {
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
        auto first_polynom = groebner_basis.getPolynom(critical_pair.first);
        auto second_polynom = groebner_basis.getPolynom(critical_pair.second);
        if (!(version_2 && buchbergCriterion(critical_pair, first_polynom, second_polynom, B, polynoms))) {
            auto s_polynom = sPolynom(first_polynom, second_polynom);
            redByPolynoms(groebner_basis, s_polynom);
            if (!s_polynom.isZero()) {
                groebner_basis.pushBackPolynom(s_polynom);
                ++t;
                for (int64_t i = 0; i < t; ++i) {
                    B[i].insert(t);
                }
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
        it = groebner_basis.removePolynom(it);
        if (!oneRedByPolynoms(groebner_basis, polynom)) {
            groebner_basis.pushBackPolynom(std::move(polynom));
        }
    }
    for (it = groebner_basis.begin(); it != groebner_basis.end(); it++) {
        Temp coef = it->getCoefficient(0);
        coef = Temp(1) / coef;
        Term<Temp> term(coef);
        (*it) *= term;
        auto polynom = std::move(*it);
        it = groebner_basis.removePolynom(it);
        redByPolynoms(groebner_basis, polynom);
        it = groebner_basis.insert(it, polynom);
    }
    groebner_basis.groebner_Basis_ = true;
    return groebner_basis;
}

template<typename Temp, typename AnotherC>
std::ostream &operator<<(std::ostream &out, const PolynomSet<Temp, AnotherC> &polynoms) noexcept {
    out << "{\n";
    for (const auto &polynom : polynoms) {
        out << polynom << "\n";
    }
    out << "}\n";
    return out;
}




}

#endif //PROGRAMM_POLYNOMSET_H

#pragma clang diagnostic pop