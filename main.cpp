#include "list.h"
#include <cassert>
#include <iostream>

int main() {
    using gss::List;
    List<int> l1{};
    List<int> l2{1, 2, 3};
    assert(l1.empty());
    assert(l1.size() == 0);
    assert(!l2.empty());
    assert(l2.size() == 3);
    List<int> l3{l2};
    List<int> l4{std::move(l2)};
    l1 = l3;
    l1 = std::move(l4);
    assert(l1.size() == 3);

    l1.clear();
    assert(l1.empty());
    l1.push_back(1);
    l1.push_front(2);
    assert(l1.back() == 1);
    l1.pop_back();
    assert(l1.size() == 1);
    assert(l1.front() == 2);
    l1.front() = 3;
    l1.push_front(2);
    l1.push_front(1);

    for (auto iter = l1.begin(); iter != l1.end(); ++iter) {
        std::cout << *iter << std::endl;
    }

    for (auto iter = l1.begin(); iter != l1.end(); iter++) {
        std::cout << *iter << std::endl;
    }

    auto iter = l1.end();
    assert(iter == l1.end());

    for (auto iter = l1.end(); iter != l1.begin();) {
        std::cout << *(--iter) << std::endl;
    }

    List<std::string> l5{"hello world"};
    auto itor = l5.begin();
    std::cout << itor->c_str() << std::endl;
}