#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <iterator>

template<typename T>
struct ListNode {
    ListNode *prev;
    ListNode *next;
    T data;

    ListNode() : prev(nullptr), next(nullptr), data() {}

    ListNode(ListNode *p, ListNode *n, T d) : prev(p), next(n), data(d) {}
};

template<typename T>
class ListIterator;

template<typename T>
class List {
public:
    friend class ListIterator<T>;

public:
    typedef ListNode<T> node_type;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef ListIterator<T> iterator;

public:
    List() : head_(new node_type()) { _init(); };

    List(std::initializer_list<T> il) : List() {
        for (auto beg = il.begin(), end = il.end(); beg != end; ++beg) {
            auto new_node = new node_type{nullptr, nullptr, *beg};
            _addNodeBefore(head_, new_node);
            ++size_;
        }
    }

    List(const List &rhs) : List() {
        _deepCopy(rhs.head_, this->head_);
        this->size_ = rhs.size_;
    }

    List(List &&rhs) noexcept : List() { swap(rhs); }

    ~List() {
        clear();

        delete head_;
    }

    List &operator=(const List &rhs) {
        clear();

        _deepCopy(rhs.head_, this->head_);
        this->size_ = rhs.size_;

        return *this;
    }

    List &operator=(List &&rhs) noexcept {
        swap(rhs);

        return *this;
    }

    size_type size() const { return size_; }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        for (auto p = head_->next; p != head_;) {
            node_type *pp = p->next;
            delete p;
            p = pp;
        }

        _init();
    }

    reference front() {
        if (size_ == 0) {
            throw std::out_of_range("");
        }

        return head_->next->data;
    }

    const_reference front() const {
        if (size_ == 0) {
            throw std::out_of_range("");
        }

        return head_->next->data;
    }

    reference back() {
        if (size_ == 0) {
            throw std::out_of_range("");
        }

        return head_->prev->data;
    }

    const_reference back() const {
        if (size_ == 0) {
            throw std::out_of_range("");
        }

        return head_->prev->data;
    }

    void push_back(const T &elem) {
        auto *new_node = new node_type(nullptr, nullptr, elem);
        _addNodeBefore(head_, new_node);
        ++size_;
    }

    void push_front(const T &elem) {
        auto *new_node = new node_type(nullptr, nullptr, elem);
        _addNodeAfter(head_, new_node);
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("");
        }

        node_type *p = head_->prev;
        _deleteNode(p);
        delete p;

        --size_;
    }

    void pop_front() {
        if (size_ == 0) {
            throw std::out_of_range("");
        }

        node_type *p = head_->next;
        _deleteNode(p);
        delete p;

        --size_;
    }

    iterator insert(iterator pos, const value_type &value) {
        auto *new_node = new node_type(nullptr, nullptr, value);
        _addNodeBefore(pos.cur_, new_node);
        ++size_;
        return iterator(pos.cur_->prev);
    }

    iterator erase(iterator pos) {
        if (pos.cur_ == head_) {
            throw std::out_of_range("");
        }

        auto pp = pos.cur_->next;
        _deleteNode(pos.cur_);
        delete pos.cur_;
        --size_;
        return iterator(pp);
    }

    iterator begin();

    iterator end();

    void swap(List &rhs) noexcept {
        std::swap(this->head_, rhs.head_);
        std::swap(this->size_, rhs.size_);
    }

private:
    void _addNodeBetween(node_type *prev, node_type *next,
                         node_type *new_node) {
        prev->next = new_node;
        new_node->prev = prev;
        new_node->next = next;
        next->prev = new_node;
    }

    void _addNodeBefore(node_type *cur, node_type *new_node) {
        _addNodeBetween(cur->prev, cur, new_node);
    }

    void _addNodeAfter(node_type *cur, node_type *new_node) {
        _addNodeBetween(cur, cur->next, new_node);
    }

    void _deleteNode(node_type *cur) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }

    void _deepCopy(node_type *from, node_type *to) {
        for (auto p = from->next; p != from; p = p->next) {
            auto new_node = new node_type{nullptr, nullptr, p->data};
            _addNodeBefore(to, new_node);
        }
    }

    void _init() {
        head_->prev = head_;
        head_->next = head_;
        size_ = 0;
    }

private:
    node_type *head_;
    std::size_t size_;
};

template<typename T>
class ListIterator {
public:
    friend class List<T>;

public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
    typedef typename List<T>::node_type node_type;

public:
    ListIterator() : cur_(nullptr) {}

    explicit ListIterator(node_type *p) : cur_(p) {}

    ListIterator(const ListIterator &rhs) = default;

    ListIterator &operator=(const ListIterator &rhs) = default;

    ListIterator(ListIterator &&rhs) noexcept : cur_(nullptr) { swap(rhs); }

    ListIterator &operator=(ListIterator &&rhs) noexcept { swap(rhs); }

    bool operator==(const ListIterator &rhs) const {
        return this->cur_ == rhs.cur_;
    }

    bool operator!=(const ListIterator &rhs) const {
        return this->cur_ != rhs.cur_;
    }

    pointer operator->() { return &this->operator*(); }

    reference operator*() { return cur_->data; }

    explicit operator bool() const { return cur_ != nullptr; }

    ListIterator &operator++() {
        cur_ = cur_->next;
        return *this;
    }

    ListIterator operator++(int) {
        node_type *p = cur_;
        cur_ = cur_->next;
        return ListIterator{p};
    }

    ListIterator &operator--() {
        cur_ = cur_->prev;
        return *this;
    }

    ListIterator operator--(int) {
        node_type *p = cur_;
        cur_ = cur_->prev;
        return ListIterator{p};
    }

    void swap(ListIterator &rhs) noexcept { std::swap(this->cur_, rhs.cur_); }

private:
    node_type *cur_;
};

template<typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator{head_->next};
}

template<typename T>
typename List<T>::iterator List<T>::end() {
    return iterator{head_};
}

#endif // LIST_LIST_H
