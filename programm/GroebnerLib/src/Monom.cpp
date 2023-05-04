//
// Created by Наиль on 27.04.2023.
//
#include "../includes/Monom.h"


gb::Monom::Monom() = default;

gb::Monom::Monom(const std::vector<int64_t> &input) noexcept {
    data_ = input;
}

size_t gb::max_size(const gb::Monom &one, const gb::Monom &two) {
    return std::max(one.data_.size(), two.data_.size());
}

void gb::Monom::resizeTo(const gb::Monom &another) {
    data_.resize(max_size(*this, another));
}

int64_t gb::Monom::operator[](int64_t index) const {
    if (index >= data_.size()){
        return 0;
    }
    return data_[index];
}

int64_t &gb::Monom::operator[](int64_t index) {
    if (data_.size() <= index) {
        data_.resize(index + 1);
    }
    return data_[index];
}


int64_t gb::deg(const gb::Monom &monom) noexcept {
    int64_t degree = 0;
    for (auto el : monom.getData()) {
        degree += el;
    }
    return degree;
}

const std::vector<int64_t> &gb::Monom::getData() const noexcept {
    return data_;
}

bool gb::Monom::isDivisibleBy(const gb::Monom &another) const noexcept {
    for (size_t i = 0; i < another.getData().size(); ++i) {
        if (this->operator[](i) < another[i]) {
            return false;
        }
    }
    return true;
}


bool gb::Monom::isInteger() const noexcept {
    return deg(*this) == 0;
}

size_t gb::Monom::size() const noexcept {
    return data_.size();
}


gb::Monom &gb::Monom::operator*=(const gb::Monom &another) noexcept {
    resizeTo(another);
    for (int i = 0; i < getData().size(); ++i) {
        this->operator[](i) += another[i];
    }
    return *this;
}

gb::Monom gb::operator*(const gb::Monom &one, const gb::Monom &two) noexcept {
    Monom answer = one;
    answer *= two;
    return answer;
}

gb::Monom &gb::Monom::operator/=(const gb::Monom &another) noexcept {
    resizeTo(another);
    for (int i = 0; i < getData().size(); ++i) {
        if ((this->operator[](i) -= another[i]) < 0) {
            std::runtime_error("division isn't possible");
        }
    }
    return *this;
}

gb::Monom gb::operator/(const gb::Monom &one, const gb::Monom &two) noexcept {
    Monom answer = one;
    answer /= two;
    return answer;
}


bool gb::operator==(const gb::Monom &one, const gb::Monom &two) noexcept {
    size_t maxim_size = max_size(one, two);
    for (int i = 0; i < maxim_size; ++i) {
        if (one[i] != two[i]) {
            return false;
        }
    }
    return true;
}

bool gb::operator!=(const gb::Monom &one, const gb::Monom &two) noexcept {
    return !(one == two);
}

gb::Monom gb::lcm(const gb::Monom &one, const gb::Monom &two) noexcept {
    auto answer = one;
    for (int i = 0; i < two.size(); ++i) {
        answer[i] = std::max(one[i], two[i]);
    }
    return answer;
}

