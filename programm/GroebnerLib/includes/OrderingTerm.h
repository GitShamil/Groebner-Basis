#ifndef PROGRAMM_ORDERINGTERM_H
#define PROGRAMM_ORDERINGTERM_H

#include "Term.h"

namespace gb {
class Lex {
public:
    template<typename Field>
    bool operator()(const Term<Field> &one, const Term<Field> &two) const noexcept {
        size_t maxim_size = std::max(one.size(), two.size());
        for (size_t i = 0; i < maxim_size; ++i) {
            if (one[i] != two[i]) {
                return one[i] < two[i];
            }
        }
        return false;
    }
};

class GrLex {
public:
    template<typename Field>
    bool operator()(const Term<Field> &one, const Term<Field> &two) const noexcept {
        int64_t deg_one = deg(one);
        int64_t deg_two= deg(two);
        if (deg_one < deg_two){
            return true;
        }
        if (deg_one > deg_two){
            return false;
        }
        size_t maxim_size = std::max(one.size(), two.size());
        for (size_t i = 0; i < maxim_size; ++i) {
            if (one[i] != two[i]) {
                return one[i] < two[i];
            }
        }
        return false;
    }
};

template<typename C>
class Reverse {
public:
    template<typename Field>
    bool operator()(const Term<Field> &one, const Term<Field> &two) const noexcept {
        if (one.getMonom() == two.getMonom()){
            return false;
        }
        C comp;
        return !(comp(one, two));
    }
};

}


#endif //PROGRAMM_ORDERINGTERM_H
