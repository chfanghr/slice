//
// Created by 方泓睿 on 2019/11/29.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "type_traits.h"

#include <gtest/gtest.h>

#include <array>
#include <list>
#include <valarray>
#include <vector>

struct MyType {};

class TypeTraitsTestGroup : public testing::Test {};

TEST_F(TypeTraitsTestGroup, VectorHasConstIterator) {
  ASSERT_TRUE(has_const_iterator_v<std::vector<int>>);
  ASSERT_TRUE(has_const_iterator_v<std::vector<unsigned>>);
  ASSERT_TRUE(has_const_iterator_v<std::vector<double>>);
  ASSERT_TRUE(has_const_iterator_v<std::vector<long>>);
  ASSERT_TRUE(has_const_iterator_v<std::vector<MyType>>);
}

TEST_F(TypeTraitsTestGroup, ListHasConstIterator) {
  ASSERT_TRUE(has_const_iterator_v<std::list<int>>);
  ASSERT_TRUE(has_const_iterator_v<std::list<unsigned>>);
  ASSERT_TRUE(has_const_iterator_v<std::list<double>>);
  ASSERT_TRUE(has_const_iterator_v<std::list<long>>);
  ASSERT_TRUE(has_const_iterator_v<std::list<MyType>>);
}

TEST_F(TypeTraitsTestGroup, MyTypeDoesNotHaveConstIterator) { ASSERT_FALSE(has_const_iterator_v<MyType>); }

TEST_F(TypeTraitsTestGroup, VectorHasBeginEnd) {
  ASSERT_TRUE(has_begin_end_v<std::vector<int>>);
  ASSERT_TRUE(has_begin_end_v<std::vector<unsigned>>);
  ASSERT_TRUE(has_begin_end_v<std::vector<long>>);
  ASSERT_TRUE(has_begin_end_v<std::vector<double>>);
  ASSERT_TRUE(has_begin_end_v<std::vector<MyType>>);
}

TEST_F(TypeTraitsTestGroup, ListHasBeginEnd) {
  ASSERT_TRUE(has_begin_end_v<std::list<int>>);
  ASSERT_TRUE(has_begin_end_v<std::list<unsigned>>);
  ASSERT_TRUE(has_begin_end_v<std::list<long>>);
  ASSERT_TRUE(has_begin_end_v<std::list<double>>);
  ASSERT_TRUE(has_begin_end_v<std::list<MyType>>);
}

TEST_F(TypeTraitsTestGroup, MyTypeDoesntHaveBeginEnd) { ASSERT_FALSE(has_begin_end_v<MyType>); }

TEST_F(TypeTraitsTestGroup, VectorIsContainer) {
  ASSERT_TRUE(is_container_v<std::vector<int>>);
  ASSERT_TRUE(is_container_v<std::vector<float>>);
  ASSERT_TRUE(is_container_v<std::vector<long>>);
  ASSERT_TRUE(is_container_v<std::vector<unsigned>>);
  ASSERT_TRUE(is_container_v<std::vector<MyType>>);
}

TEST_F(TypeTraitsTestGroup, ListIsContainer) {
  ASSERT_TRUE(is_container_v<std::list<int>>);
  ASSERT_TRUE(is_container_v<std::list<float>>);
  ASSERT_TRUE(is_container_v<std::list<long>>);
  ASSERT_TRUE(is_container_v<std::list<unsigned>>);
  ASSERT_TRUE(is_container_v<std::list<MyType>>);
}

TEST_F(TypeTraitsTestGroup, MyTypeIsNotContainer) { ASSERT_FALSE(is_container_v<MyType>); }

TEST_F(TypeTraitsTestGroup, ValarrayIsContainer) {
  ASSERT_TRUE(is_container_v<std::valarray<int>>);
  ASSERT_TRUE(is_container_v<std::valarray<float>>);
  ASSERT_TRUE(is_container_v<std::valarray<long>>);
  ASSERT_TRUE(is_container_v<std::valarray<unsigned>>);
  ASSERT_TRUE(is_container_v<std::valarray<MyType>>);
}

#pragma clang diagnostic pop