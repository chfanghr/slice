//
// Created by 方泓睿 on 2019/11/29.
//

#ifndef SLICE__SLICE_H_
#define SLICE__SLICE_H_

#include <functional>
#include <iterator>
#include <stdexcept>

#include "helpers.h"

enum class Pos { kBegin, kEnd, kAll };

// Use STL code style in slice
template <typename T>
class slice {
 public:
  class Iterator {
   private:
    slice slice_;
    size_t current_offset_;

   private:
    friend class slice;
    explicit Iterator(slice slice, size_t offset) : slice_(slice), current_offset_(offset) {}

   public:
    bool operator==(const Iterator &iter) const { return iter.current_offset_ == current_offset_; }

    bool operator!=(const Iterator &iter) const { return !operator==(iter); }

    Iterator &operator++() {
      if (slice_.from_ + current_offset_ < slice_.to_) current_offset_++;
      return *this;
    }

    Iterator operator++(int) {
      auto tmp = Iterator(*this);
      if (slice_.from_ + current_offset_ < slice_.to_) current_offset_++;
      return tmp;
    }

    Iterator &operator--() {
      if (current_offset_ > 0) current_offset_--;
      return *this;
    }

    Iterator operator--(int) {
      auto tmp = Iterator(*this);
      if (current_offset_ > 0) current_offset_++;
      return tmp;
    }

    Iterator &operator+=(size_t n) {
      if (current_offset_ + n + slice_.from_ <= slice_.to_)
        current_offset_ += n;
      else
        current_offset_ = slice_.to_ - slice_.from_;
      return *this;
    }

    Iterator &operator-=(size_t n) {
      if (n <= current_offset_)
        current_offset_ -= n;
      else
        current_offset_ = 0;
      return *this;
    }

    Iterator operator+(size_t n) {
      auto tmp = Iterator(*this);
      tmp += n;
      return tmp;
    }

    Iterator operator-(size_t n) {
      auto tmp = Iterator(*this);
      tmp -= n;
      return tmp;
    }

    T &operator*() { return slice_[current_offset_]; }

    const T &operator*() const { return slice_[current_offset_]; }
  };

 public:
  using value_type = T;
  using self_type = slice<T>;

  explicit slice(std::valarray<T> &arr, Pos pos = Pos::kAll) : arr_(arr), from_(0), to_(arr.size()) {
    if (pos != Pos::kAll) throw std::invalid_argument("pos can only be Pos::kAll");
  }

  slice(std::valarray<T> &arr, Pos pos, size_t to) : arr_(arr), from_(pos == Pos::kBegin ? 0 : arr.size()), to_(to) {
    if (pos == Pos::kAll) throw std::invalid_argument("pos can not be Pos::kAll");
    if (to_ < from_) throw std::invalid_argument("from_ should not be bigger than to_");
    if (to > arr.size()) throw std::out_of_range("to should be less than std::size(arr)");
  }

  slice(std::valarray<T> &arr, size_t from, Pos pos = Pos::kEnd)
      : arr_(arr), from_(from), to_(pos == Pos::kEnd ? arr.size() : 0) {
    if (pos == Pos::kAll) throw std::invalid_argument("pos can not be Pos::kAll");
    if (to_ < from_) throw std::invalid_argument("from_ should not be bigger than to_");
    if (from > arr.size()) throw std::out_of_range("from should be less than std::size(arr)");
  }

  slice(std::valarray<T> &arr, size_t from, size_t to) : arr_(arr), from_(from), to_(to) {
    if (to_ < from_) throw std::invalid_argument("from should not be bigger than to");
    if (to_ > arr.size()) throw std::out_of_range("to should be less than std::size(arr)");
  }

  slice(slice &slice) = default;

  slice(const slice<T> &old_slice) = default;

  slice(const slice<T> &old_slice, Pos pos) : slice(old_slice) {
    if (pos != Pos::kAll) throw std::invalid_argument("pos can only be Pos::kAll");
  }

  slice(const slice &old, size_t from, size_t to) : arr_(old.arr_), from_(from + old.from_), to_(to + old.from_) {
    if (to_ < from_) throw std::invalid_argument("from should not be bigger than to");
    if (from_ > old.to_ || to_ > old.to_) throw std::out_of_range("[from_,to_] should be the subset of that of old");
  }

  slice(const slice &old, size_t from, Pos pos = Pos::kEnd)
      : arr_(old.arr_), from_(from + old.from_), to_(pos == Pos::kEnd ? old.to_ : old.from_) {
    if (pos == Pos::kAll) throw std::invalid_argument("pos cannot be Pos::kAll");
    if (to_ < from_) throw std::invalid_argument("from should not be bigger than to");
    if (from_ > old.to_ || to_ > old.to_) throw std::out_of_range("[from_,to_] should be the subset of that of old");
  }

  slice(const slice &old, Pos pos, size_t to)
      : arr_(old.arr_), from_(pos == Pos::kEnd ? old.to_ : old.from_), to_(old.from_ + to) {
    if (pos == Pos::kAll) throw std::invalid_argument("pos cannot be Pos::kAll");
    if (to_ < from_) throw std::invalid_argument("from should not be bigger than to");
    if (from_ > old.to_ || to_ > old.to_) throw std::out_of_range("[from_,to_] should be the subset of that of old");
  }

  slice sub(Pos pos = Pos::kAll) const { return slice(*this, pos); }

  slice sub(size_t from, size_t to) const { return slice(*this, from, to); }

  slice sub(size_t from, Pos pos = Pos::kEnd) const { return slice(*this, from, pos); }

  slice sub(Pos pos, size_t to) const { return slice(*this, pos, to); }

  [[nodiscard]] size_t size() const { return to_ - from_; }

  std::valarray<T> &get_array() { return arr_; }

  [[nodiscard]] const std::valarray<T> &get_array() const { return arr_; }

  T &at(size_t i) {
    validate(i);
    return arr_.get()[from_ + i];
  }

  [[nodiscard]] const T &at(size_t i) const {
    validate(i);
    return arr_.get()[from_ + i];
  }

  T &operator[](size_t i) { return at(i); }

  const T &operator[](size_t i) const { return at(i); }

  using iterator = Iterator;
  using const_iterator = Iterator;

  [[nodiscard]] iterator begin() const { return Iterator(*this, 0); }

  [[nodiscard]] iterator end() const { return Iterator(*this, to_ - from_); }

  [[nodiscard]] const_iterator cbegin() const { return Iterator(*this, 0); }

  [[nodiscard]] const_iterator cend() const { return Iterator(*this, 0); }

 private:
  auto validate(size_t i) const -> void {
    i += from_;
    if (i < from_ || i >= to_)
      throw std::out_of_range("index " + std::to_string(i) + " is not in [" + std::to_string(from_) + "," +
                              std::to_string(to_) + ").");
  }

  std::reference_wrapper<std::valarray<T>> arr_;
  size_t from_{}, to_{};  // [from,to)
};

template <typename ValueType, typename... Values, typename _valueType = std::common_type_t<Values...>,
          typename = typename std::enable_if_t<std::is_same_v<ValueType, _valueType>, void>>
auto append(const slice<ValueType> &sli, const Values &... ele) -> std::valarray<ValueType> {
  return append(to_valarray(sli), ele...);
}
#endif  // SLICE__SLICE_H_
