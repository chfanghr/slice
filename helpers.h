//
// Created by 方泓睿 on 2019/11/29.
//

#ifndef SLICE__HELPERS_H_
#define SLICE__HELPERS_H_

#include <iostream>
#include <string>

#include "type_traits.h"

template <typename ContainerType, typename... Values, typename ValueType = std::common_type_t<Values...>,
          typename _valueType = typename ContainerType::value_type,
          typename = typename std::enable_if_t<std::is_same_v<ValueType, _valueType>, void>,
          typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
inline auto make(const Values &... ele) -> ContainerType {
  return {std::forward<const Values &>(ele)...};
}

template <typename ContainerType, typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
inline auto make() -> ContainerType {
  return {};
}

template <typename... Values, typename ValueType = std::common_type_t<Values...>>
inline auto make_array(const Values &... ele) -> std::array<ValueType, sizeof...(ele)> {
  return make<std::array<ValueType, sizeof...(ele)>>(ele...);
}

template <typename ValueType>
inline auto make_array() -> std::array<ValueType, 0> {
  return {};
}

template <typename ValueType>
auto resize_valarray(std::valarray<ValueType> &arr, size_t size) -> std::valarray<ValueType> & {
  std::valarray<ValueType> tmp{};
  std::swap(tmp, arr);
  arr.resize(size);
  if (size == 0) return arr;
  std::copy(std::begin(tmp), size > tmp.size() ? std::end(tmp) : std::begin(tmp) + size, std::begin(arr));
  return arr;
}

template <typename ValueType, typename... Values, typename _valueType = std::common_type_t<Values...>,
          typename = typename std::enable_if_t<std::is_same_v<ValueType, _valueType>, void>>
auto append(std::valarray<ValueType> &arr, const Values &... ele) -> std::valarray<ValueType> & {
  auto ele_num = sizeof...(ele);
  if (!ele_num) return arr;
  auto ori_size = arr.size();
  resize_valarray(arr, ori_size + ele_num);
  auto ele_arr = make_array(ele...);
  std::copy(std::begin(ele_arr), std::end(ele_arr), std::begin(arr) + ori_size);
  return arr;
}

template <typename ValueType, typename... Values, typename _valueType = std::common_type_t<Values...>,
          typename = typename std::enable_if_t<std::is_same_v<ValueType, _valueType>, void>>
auto append(std::valarray<ValueType> &&arr, const Values &... ele) -> std::valarray<ValueType> {
  append(arr, ele...);
  return std::move(arr);
}

template <typename ValueType>
auto append(std::valarray<ValueType> &arr) -> std::valarray<ValueType> {
  return arr;
}

template <typename ValueType>
auto append(std::valarray<ValueType> &&arr) -> std::valarray<ValueType> {
  return std::move(arr);
}

template <typename ValueType, typename... Containers, typename _containerType = std::common_type_t<Containers...>,
          typename _valueType = typename _containerType::value_type,
          typename = typename std::enable_if_t<std::is_same_v<ValueType, _valueType>, void>,
          typename = typename std::enable_if_t<is_container_v<_containerType>, void>>
auto append_container(std::valarray<ValueType> &arr, const Containers &... cont) -> std::valarray<ValueType> {
  auto cont_num = sizeof...(cont);
  if (!cont_num) return arr;
  auto cont_arr = make_array(cont...);
  for (const auto &c : cont_arr) {
    auto ori_size = arr.size();
    resize_valarray(arr, ori_size + c.size());
    std::copy(std::begin(c), std::end(c), std::begin(arr) + ori_size);
  }
  return arr;
}

template <typename ValueType, typename... Containers, typename _containerType = std::common_type_t<Containers...>,
          typename _valueType = typename _containerType::value_type,
          typename = typename std::enable_if_t<std::is_same_v<ValueType, _valueType>, void>,
          typename = typename std::enable_if_t<is_container_v<_containerType>, void>>
auto append_container(std::valarray<ValueType> &&arr, const Containers &... cont) -> std::valarray<ValueType> {
  append_container(arr, cont...);
  return std::move(arr);
}

template <typename ValueType>
auto append_container(std::valarray<ValueType> &arr) -> std::valarray<ValueType> {
  return arr;
}

template <typename ValueType>
auto append_container(std::valarray<ValueType> &&arr) -> std::valarray<ValueType> {
  return std::move(arr);
}

template <typename ContainerType, typename = typename std::enable_if_t<is_container_v<ContainerType>, void>,
          typename = typename std::enable_if_t<!std::is_same_v<std::string, ContainerType>, void>>
auto operator<<(std::ostream &os, const ContainerType &cont) -> std::ostream & {
  os << "[";
  auto is_first = true;
  for (const auto &ele : cont) {
    if (is_first)
      is_first = false;
    else
      os << ",";
    os << ele;
  }
  os << "]";
  return os;
}

template <typename ContainerType, typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
auto operator<<(std::ostream &os, const ContainerType &&cont) -> std::ostream & {
  return os << cont;
}

template <typename ContainerAType, typename ContainerBType,
          typename ContainerType = std::common_type_t<ContainerAType, ContainerBType>,
          typename ValueType = typename ContainerType::value_type,
          typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
auto equal(const ContainerAType &a, const ContainerBType &b) -> bool {
  if (std::size(a) != std::size(b)) return false;
  auto iter_a = std::begin(a);
  auto iter_b = std::begin(b);
  for (; iter_a != std::end(a) && iter_b != std::end(b); ++iter_a, ++iter_b)
    if (*iter_a != *iter_b) return false;
  return true;
}

template <typename ContainerAType, typename ContainerBType,
          typename ContainerType = std::common_type_t<ContainerAType, ContainerBType>,
          typename ValueType = typename ContainerType::value_type,
          typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
auto equal(const ContainerAType &&a, const ContainerBType &&b) -> bool {
  return equal(a, b);
}

template <typename ContainerAType, typename ContainerBType,
          typename ContainerType = std::common_type_t<ContainerAType, ContainerBType>,
          typename ValueType = typename ContainerType::value_type,
          typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
auto equal(const ContainerAType &a, const ContainerBType &&b) -> bool {
  return equal(a, b);
}

template <typename ContainerAType, typename ContainerBType,
          typename ContainerType = std::common_type_t<ContainerAType, ContainerBType>,
          typename ValueType = typename ContainerType::value_type,
          typename = typename std::enable_if_t<is_container_v<ContainerType>, void>>
auto equal(const ContainerAType &&a, const ContainerBType &b) -> bool {
  return equal(a, b);
}

template <typename ContainerType, typename = typename std::enable_if_t<is_container_v<ContainerType>, void>,
          typename ValueType = typename ContainerType::value_type>
auto to_valarray(const ContainerType &cont) -> std::valarray<ValueType> {
  auto res = std::valarray<ValueType>(cont.size());
  auto iter_cont = std::begin(cont);
  auto iter_res = std::begin(res);
  for (; iter_cont != std::end(cont) && iter_res != std::end(res); ++iter_cont, ++iter_res) *iter_res = *iter_cont;
  return res;
}

template <typename ContainerType, typename = typename std::enable_if_t<is_container_v<ContainerType>, void>,
          typename ValueType = typename ContainerType::value_type>
auto to_valarray(const ContainerType &&cont) -> std::valarray<ValueType> {
  return to_valarray(cont);
}

#endif  // SLICE__HELPERS_H_
