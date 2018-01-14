#ifndef LIST_TRIVIAL_STRING_H
#define LIST_TRIVIAL_STRING_H

#include <cstring>

namespace trivial {

class String {
  public:
    String() : data_{new char[1]{'\0'}} {};

    String(const char* cstr) {
        auto size = strlen(cstr);
        data_ = new char[size + 1];
        memmove(data_, cstr, size + 1);
    }

    String(const String& rhs) {
        auto size = strlen(rhs.data_);
        data_ = new char[size + 1];
        memmove(data_, rhs.data_, size + 1);
    }

    String(String&& rhs) noexcept {
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }

    String& operator=(String rhs) {
        swap(rhs);
        return *this;
    }

    ~String() noexcept { delete[] data_; }

    const char* c_str() const { return data_; }

    std::size_t size() const { return strlen(data_); }

    void swap(String& rhs) { std::swap(data_, rhs.data_); }

  private:
    char* data_;
};

} // namespace trivial

#endif // LIST_TRIVIAL_STRING_H
