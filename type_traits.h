//
// Created by 方泓睿 on 2019/11/28.
//

#ifndef SLICE__TYPE_TRAITS_H_
#define SLICE__TYPE_TRAITS_H_

#include <array>
#include <type_traits>
#include <valarray>

template <typename T>
struct has_const_iterator {
 private:
  typedef char yes;
  typedef struct {
    char array[2];
  } no;

  template <typename C>
  static yes test(typename C::const_iterator *) {
    return 0;
  }

  template <typename C>
  static no test(...) {
    return no();
  }

 public:
  static const bool value = sizeof(test<T>(0)) == sizeof(yes);
  typedef T type;
};

template <typename T>
inline constexpr bool has_const_iterator_v = has_const_iterator<T>::value;

template <typename T>
struct has_begin_end {
  template <typename C>
  static char (&f(
      typename std::enable_if<std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::begin)),
                                           typename C::const_iterator (C::*)() const>::value,
                              void>::type *))[1];

  template <typename C>
  static char (&f(...))[2];

  template <typename C>
  static char (
      &g(typename std::enable_if<std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::end)),
                                              typename C::const_iterator (C::*)() const>::value,
                                 void>::type *))[1];

  template <typename C>
  static char (&g(...))[2];

  static bool const beg_value = sizeof(f<T>(0)) == 1;
  static bool const end_value = sizeof(g<T>(0)) == 1;
  static bool const value = beg_value && end_value;
};

template <typename T>
inline constexpr bool has_begin_end_v = has_begin_end<T>::value;

template <typename T>
struct is_container : std::integral_constant<bool, has_const_iterator<T>::value && has_begin_end<T>::beg_value &&
                                                       has_begin_end<T>::end_value> {};

template <typename T>
struct is_container<std::valarray<T>> {
  static const bool value = true;
};

template <typename T, size_t S>
struct is_container<std::array<T, S>> {
  static const bool value = true;
};

template <class T>
inline constexpr bool is_container_v = is_container<T>::value;

#endif  // SLICE__TYPE_TRAITS_H_
