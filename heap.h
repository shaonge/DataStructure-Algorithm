//
// Created by 14667 on 2018/2/25.
//

#ifndef LEETCODE_HEAP_H
#define LEETCODE_HEAP_H

#include <vector>
#include <cassert>
#include <functional>

// [top, end)
template <typename ValueType, typename Compare>
static void _percolate_down_bound(std::vector<ValueType>& data, std::size_t top, size_t end, Compare cmp) {
    auto i = top + 1;
    while (2 * i <= end) {
        auto j = 2 * i;
        if (j + 1 <= end && cmp(data[j - 1], data[j])) {
            j += 1;
        }
        if (!cmp(data[i - 1], data[j - 1])) {
            return;
        }
        std::swap(data[i - 1], data[j - 1]);
        i = j;
    }
}

template <typename ValueType>
static void _percolate_down_bound(std::vector<ValueType>& data, std::size_t top, size_t end) {
    auto i = top + 1;
    while (2 * i <= end) {
        auto j = 2 * i;
        if (j + 1 <= end && data[j - 1] < data[j]) {
            j += 1;
        }
        if (data[i - 1] >= data[j - 1]) {
            return;
        }
        std::swap(data[i - 1], data[j - 1]);
        i = j;
    }
}

// [top, data.size())
template <typename ValueType, typename Compare>
static void _percolate_down(std::vector<ValueType>& data, std::size_t top, Compare cmp) {
    auto i = top + 1;
    while (2 * i <= data.size()) {
        auto j = 2 * i;
        if (j + 1 <= data.size() && cmp(data[j - 1], data[j])) {
            j += 1;
        }
        if (!cmp(data[i - 1], data[j - 1])) {
            return;
        }
        std::swap(data[i - 1], data[j - 1]);
        i = j;
    }
}

template <typename ValueType>
static void _percolate_down(std::vector<ValueType>& data, std::size_t top) {
    auto i = top + 1;
    while (2 * i <= data.size()) {
        auto j = 2 * i;
        if (j + 1 <= data.size() && data[j - 1] < data[j]) {
            j += 1;
        }
        if (data[i - 1] >= data[j - 1]) {
            return;
        }
        std::swap(data[i - 1], data[j - 1]);
        i = j;
    }
}

template <typename ValueType, typename Compare>
static void _percolate_up(std::vector<ValueType>& data, std::size_t bottom, Compare cmp) {
    auto i = bottom + 1;
    while (i / 2 > 0) {
        auto j = i / 2;
        if (!cmp(data[j - 1], data[i - 1])) {
            return;
        }
        std::swap(data[i - 1], data[j - 1]);
        i = j;
    }
}

template <typename ValueType>
static void _percolate_up(std::vector<ValueType>& data, std::size_t bottom) {
    auto i = bottom + 1;
    while (i / 2 > 0) {
        auto j = i / 2;
        if (data[j - 1] >= data[i - 1]) {
            return;
        }
        std::swap(data[i - 1], data[j - 1]);
        i = j;
    }
}

template <typename ValueType, typename Compare>
static void make_heap(std::vector<ValueType>& data, Compare cmp) {
    for (size_t i = data.size() / 2; i >= 1; --i) {
        _percolate_down(data, i - 1, cmp);
    }
}

template <typename ValueType>
static void make_heap(std::vector<ValueType>& data) {
    for (size_t i = data.size() / 2; i >= 1; --i) {
        _percolate_down(data, i - 1);
    }
}

template <typename ValueType, typename Compare = std::less<ValueType>>
class Heap {
public:
    void push(ValueType elem) {
        data_.push_back(elem);
        _percolate_up(data_, data_.size() - 1, cmp_);
    }

    void pop() {
        assert(!data_.empty());
        data_[0] = data_.back();
        _percolate_down(data_, 0, cmp_);
        data_.pop_back();
    }

    ValueType &top() {
        assert(!data_.empty());
        return data_[0];
    }

    const ValueType &top() const {
        assert(!data_.empty());
        return data_[0];
    }

    std::size_t size() const {
        return data_.size();
    }

    bool empty() const {
        return data_.empty();
    }

private:
    std::vector<ValueType> data_;
    Compare cmp_;
};

#endif // LEETCODE_HEAP_H
