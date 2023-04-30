#ifndef PROGRAMM_ORDERINGTERM_H
#define PROGRAMM_ORDERINGTERM_H

#include "Term.h"

namespace gb {
class Lex {
public:
    template<typename Field>
    bool operator()(const Term<Field> &one, const Term<Field> &two) const noexcept {
        size_t minim_size = std::min(one.size(), two.size());
        for (size_t i = 0; i < minim_size; ++i) {
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
