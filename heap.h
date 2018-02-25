//
// Created by 14667 on 2018/2/25.
//

#ifndef LEETCODE_HEAP_H
#define LEETCODE_HEAP_H

#include <vector>
#include <cassert>
#include <functional>

template <typename ValueType, typename Compare = std::less<ValueType>>
class Heap {
public:
    Heap() {
        data_.resize(1);
    }

    void push(ValueType elem) {
        data_.push_back(elem);
        _percolate_up(data_.size() - 1);
    }

    void pop() {
        assert(data_.size() > 1);
        data_[1] = data_.back();
        data_.pop_back();
        _percolate_down(1);
    }

    ValueType &top() {
        assert(data_.size() > 1);
        return data_[1];
    }

    const ValueType &top() const {
        assert(data_.size() > 1);
        return data_[1];
    }

    std::size_t size() const {
        return data_.size() - 1;
    }

    bool empty() const {
        return data_.size() == 1;
    }

private:
    void _percolate_down(std::size_t top) {
        auto i = top;
        while (2 * i < data_.size()) {
            auto j = 2 * i;
            if (j + 1 < data_.size() && cmp_(data_[j], data_[j + 1])) {
                j += 1;
            }
            if (!cmp_(data_[i], data_[j])) {
                return;
            }
            std::swap(data_[i], data_[j]);
            i = j;
        }
    }

    void _percolate_up(std::size_t bottom) {
        auto i = bottom;
        while (i / 2 > 0) {
            auto j = i / 2;
            if (!cmp_(data_[j], data_[i])) {
                return;
            }
            std::swap(data_[i], data_[j]);
            i = j;
        }
    }

private:
    std::vector<ValueType> data_;
    Compare cmp_;
};

#endif // LEETCODE_HEAP_H
