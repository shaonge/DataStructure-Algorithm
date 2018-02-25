//
// Created by 14667 on 2018/2/25.
//

#ifndef LIST_HEAP_SORT_H
#define LIST_HEAP_SORT_H

#include "heap.h"

template <typename ValueType>
static void heapSort(std::vector<ValueType>& data) {
    make_heap(data);
    for (int i = data.size() - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        _percolate_down_bound(data, 0, i);
    }
}

template <typename ValueType, typename Compare>
static void heapSort(std::vector<ValueType>& data, Compare cmp) {
    make_heap(data);
    for (int i = data.size() - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        _percolate_down_bound(data, 0, i, cmp);
    }
}

#endif //LIST_HEAP_SORT_H
