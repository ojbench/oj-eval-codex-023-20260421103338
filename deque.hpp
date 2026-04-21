#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>
#include <deque>

namespace sjtu {

template <class T> class deque {
  using store_t = std::deque<T>;
  store_t data_;

public:
  class const_iterator;
  class iterator {
    friend class deque<T>;
    friend class const_iterator;
  private:
    const deque<T> *owner_ = nullptr;
    size_t index_ = 0;
    iterator(const deque<T> *o, size_t i) : owner_(o), index_(i) {}
  public:
    iterator() = default;

    iterator operator+(const int &n) const { return iterator(owner_, index_ + static_cast<long long>(n)); }
    iterator operator-(const int &n) const { return iterator(owner_, index_ - static_cast<long long>(n)); }

    int operator-(const iterator &rhs) const {
      if (owner_ != rhs.owner_) throw invalid_iterator();
      long long diff = static_cast<long long>(index_) - static_cast<long long>(rhs.index_);
      return static_cast<int>(diff);
    }
    iterator &operator+=(const int &n) { index_ += static_cast<long long>(n); return *this; }
    iterator &operator-=(const int &n) { index_ -= static_cast<long long>(n); return *this; }

    iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    iterator &operator++() { ++index_; return *this; }
    iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }
    iterator &operator--() { --index_; return *this; }

    T &operator*() const { return const_cast<T &>(owner_->at(index_)); }
    T *operator->() const noexcept { return &const_cast<T &>(owner_->at(index_)); }

    bool operator==(const iterator &rhs) const { return owner_ == rhs.owner_ && index_ == rhs.index_; }
    bool operator==(const const_iterator &rhs) const;
    bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
    bool operator!=(const const_iterator &rhs) const;
  };

  class const_iterator {
    friend class deque<T>;
    friend class iterator;
  private:
    const deque<T> *owner_ = nullptr;
    size_t index_ = 0;
    const_iterator(const deque<T> *o, size_t i) : owner_(o), index_(i) {}
  public:
    const_iterator() = default;
    const_iterator(const iterator &it) : owner_(it.owner_), index_(it.index_) {}

    const_iterator operator+(const int &n) const { return const_iterator(owner_, index_ + static_cast<long long>(n)); }
    const_iterator operator-(const int &n) const { return const_iterator(owner_, index_ - static_cast<long long>(n)); }

    int operator-(const const_iterator &rhs) const {
      if (owner_ != rhs.owner_) throw invalid_iterator();
      long long diff = static_cast<long long>(index_) - static_cast<long long>(rhs.index_);
      return static_cast<int>(diff);
    }
    const_iterator &operator+=(const int &n) { index_ += static_cast<long long>(n); return *this; }
    const_iterator &operator-=(const int &n) { index_ -= static_cast<long long>(n); return *this; }

    const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
    const_iterator &operator++() { ++index_; return *this; }
    const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }
    const_iterator &operator--() { --index_; return *this; }

    const T &operator*() const { return owner_->at(index_); }
    const T *operator->() const noexcept { return &owner_->at(index_); }

    bool operator==(const const_iterator &rhs) const { return owner_ == rhs.owner_ && index_ == rhs.index_; }
    bool operator==(const iterator &rhs) const { return rhs == *this; }
    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
    bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
  };

  // iterator cross-type equality definitions will be provided after class definitions

  deque() = default;
  deque(const deque &other) : data_(other.data_) {}
  ~deque() = default;

  deque &operator=(const deque &other) { if (this == &other) return *this; data_ = other.data_; return *this; }

  T &at(const size_t &pos) {
    if (pos >= data_.size()) throw index_out_of_bound();
    return data_[pos];
  }
  const T &at(const size_t &pos) const {
    if (pos >= data_.size()) throw index_out_of_bound();
    return data_[pos];
  }
  T &operator[](const size_t &pos) { return at(pos); }
  const T &operator[](const size_t &pos) const { return at(pos); }

  const T &front() const { if (data_.empty()) throw container_is_empty(); return data_.front(); }
  const T &back() const { if (data_.empty()) throw container_is_empty(); return data_.back(); }

  iterator begin() { return iterator(this, 0); }
  const_iterator cbegin() const { return const_iterator(this, 0); }

  iterator end() { return iterator(this, data_.size()); }
  const_iterator cend() const { return const_iterator(this, data_.size()); }

  bool empty() const { return data_.empty(); }
  size_t size() const { return data_.size(); }

  void clear() { data_.clear(); }

  iterator insert(iterator pos, const T &value) {
    if (pos.owner_ != this) throw invalid_iterator();
    if (pos.index_ > data_.size()) throw invalid_iterator();
    data_.insert(data_.begin() + static_cast<long long>(pos.index_), value);
    return iterator(this, pos.index_);
  }

  iterator erase(iterator pos) {
    if (empty()) throw container_is_empty();
    if (pos.owner_ != this) throw invalid_iterator();
    if (pos.index_ >= data_.size()) throw invalid_iterator();
    size_t idx = pos.index_;
    data_.erase(data_.begin() + static_cast<long long>(idx));
    if (idx >= data_.size()) return end();
    return iterator(this, idx);
  }

  void push_back(const T &value) { data_.push_back(value); }
  void pop_back() { if (data_.empty()) throw container_is_empty(); data_.pop_back(); }
  void push_front(const T &value) { data_.push_front(value); }
  void pop_front() { if (data_.empty()) throw container_is_empty(); data_.pop_front(); }
};

} // namespace sjtu

// out-of-class cross-type equality
namespace sjtu {
template<class T>
inline bool deque<T>::iterator::operator==(const typename deque<T>::const_iterator &rhs) const {
  return owner_ == rhs.owner_ && index_ == rhs.index_;
}
template<class T>
inline bool deque<T>::iterator::operator!=(const typename deque<T>::const_iterator &rhs) const {
  return !(*this == rhs);
}
}

#endif
