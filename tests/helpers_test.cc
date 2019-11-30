//
// Created by 方泓睿 on 2019/11/29.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "helpers.h"

#include <gtest/gtest.h>

#include <array>
#include <list>
#include <sstream>
#include <string>
#include <valarray>
#include <vector>

class HelpersTestGroup : public testing::Test {};

TEST_F(HelpersTestGroup, EqualShouldWorkOnVector) {
  auto vec = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto vec_equal = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto vec_not_equal_1 = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto vec_not_equal_2 = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  ASSERT_TRUE(equal(vec, vec_equal));
  ASSERT_FALSE(equal(vec, vec_not_equal_1));
  ASSERT_FALSE(equal(vec, vec_not_equal_2));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnZeroLengthVector) {
  auto vec = std::vector<int>{};
  auto vec_equal = std::vector<int>{};
  ASSERT_TRUE(equal(vec, vec_equal));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnList) {
  auto list = std::list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto list_equal = std::list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto list_not_equal_1 = std::list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  auto list_not_equal_2 = std::list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  ASSERT_TRUE(equal(list, list_equal));
  ASSERT_FALSE(equal(list, list_not_equal_1));
  ASSERT_FALSE(equal(list, list_not_equal_2));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnZeroLengthList) {
  auto list = std::list<int>{};
  auto list_equal = std::list<int>{};
  ASSERT_TRUE(equal(list, list_equal));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnValarray) {
  auto arr = std::valarray{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto arr_equal = std::valarray{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto arr_not_equal_1 = std::valarray{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto arr_not_equal_2 = std::valarray{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  ASSERT_TRUE(equal(arr, arr_equal));
  ASSERT_FALSE(equal(arr, arr_not_equal_1));
  ASSERT_FALSE(equal(arr, arr_not_equal_2));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnZeroLengthValarray) {
  auto arr = std::valarray<int>{};
  auto arr_equal = std::valarray<int>{};
  ASSERT_TRUE(equal(arr, arr_equal));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnArray) {
  auto arr = std::array{1, 2, 3, 4, 5, 6, 7, 8};
  auto arr_equal = std::array{1, 2, 3, 4, 5, 6, 7, 8};
  auto arr_not_equal = std::array{1, 2, 3, 4, 5, 6, 7, 9};
  ASSERT_TRUE(equal(arr, arr_equal));
  ASSERT_FALSE(equal(arr, arr_not_equal));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnZeroLengthArray) {
  auto arr = std::array<int, 0>();
  auto arr_equal = std::array<int, 0>();
  ASSERT_TRUE(equal(arr, arr_equal));
}

TEST_F(HelpersTestGroup, EqualShouldWorkOnLeftValue) {
  auto arr = std::valarray{1, 2, 3};
  ASSERT_TRUE(equal(std::valarray{1, 2, 3}, std::valarray{1, 2, 3}));
  ASSERT_FALSE(equal(std::valarray{1, 2, 3}, std::valarray{1, 2, 3, 4}));
  ASSERT_FALSE(equal(std::valarray{1, 2, 3}, std::valarray{1, 2, 4}));
  ASSERT_TRUE(equal(std::valarray{1, 2, 3}, arr));
  ASSERT_TRUE(equal(arr, std::valarray{1, 2, 3}));
  ASSERT_FALSE(equal(std::valarray{1, 2, 3, 4}, arr));
  ASSERT_FALSE(equal(arr, std::valarray{1, 2, 3, 4}));
  ASSERT_FALSE(equal(std::valarray{1, 2, 4}, arr));
  ASSERT_FALSE(equal(arr, std::valarray{1, 2, 4}));
}

TEST_F(HelpersTestGroup, MakeValarrayShouldWorkAsExpected) {
  auto arr_made = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto arr_expected = std::valarray<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(arr_made.size(), 10);
  ASSERT_TRUE(equal(arr_made, arr_expected));
}

TEST_F(HelpersTestGroup, MakeVectorShouldWorkAsExpected) {
  auto vec_made = make<std::vector<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto vec_expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(vec_made.size(), 10);
  ASSERT_TRUE(equal(vec_made, vec_expected));
}

TEST_F(HelpersTestGroup, MakeListShouldWorkAsExpected) {
  auto list_made = make<std::list<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto list_expected = std::list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(list_made.size(), 10);
  ASSERT_TRUE(equal(list_made, list_expected));
}

TEST_F(HelpersTestGroup, MakeArrayShouldWorkAsExpected) {
  auto arr_made = make_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto arr_expected = std::array{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(arr_made.size(), 10);
  ASSERT_TRUE(equal(arr_made, arr_expected));
}

TEST_F(HelpersTestGroup, ZeroLengthContainerCanAlsoBeMade) {
  auto val_arr_made = make<std::valarray<int>>();
  auto vec_made = make<std::vector<int>>();
  auto list_made = make<std::list<int>>();
  auto arr_made = make_array<int>();
  ASSERT_EQ(val_arr_made.size(), 0);
  ASSERT_EQ(vec_made.size(), 0);
  ASSERT_EQ(list_made.size(), 0);
  ASSERT_EQ(arr_made.size(), 0);
}

TEST_F(HelpersTestGroup, LeftShiftOperatorShouldWorkOnArray) {
  auto arr = make_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto expected_result = std::string("[1,2,3,4,5,6,7,8,9,10]");
  auto result = std::string();
  auto buf = std::stringstream();
  buf << arr;
  buf >> result;
  ASSERT_EQ(result, expected_result);
}

TEST_F(HelpersTestGroup, LeftShiftOperatorShouldWorkOnZeroLengthArray) {
  auto arr = make_array<int>();
  auto expected_result = std::string("[]");
  auto result = std::string();
  auto buf = std::stringstream();
  buf << arr;
  buf >> result;
  ASSERT_EQ(result, expected_result);
}

TEST_F(HelpersTestGroup, LeftShiftOperatorShouldWorkOnVector) {
  auto vec = make<std::vector<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto expected_result = std::string("[1,2,3,4,5,6,7,8,9,10]");
  auto result = std::string();
  auto buf = std::stringstream();
  buf << vec;
  buf >> result;
  ASSERT_EQ(result, expected_result);
}

TEST_F(HelpersTestGroup, LeftShiftOperatorShouldWorkOnZeroLengthVector) {
  auto vec = make<std::vector<int>>();
  auto expected_result = std::string("[]");
  auto result = std::string();
  auto buf = std::stringstream();
  buf << vec;
  buf >> result;
  ASSERT_EQ(result, expected_result);
}

TEST_F(HelpersTestGroup, LeftShiftOperatorShouldWorkOnValarray) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto expected_result = std::string("[1,2,3,4,5,6,7,8,9,10]");
  auto result = std::string();
  auto buf = std::stringstream();
  buf << arr;
  buf >> result;
  ASSERT_EQ(result, expected_result);
}

TEST_F(HelpersTestGroup, LeftShiftOperatorShouldWorkOnZeroLengthValarray) {
  auto arr = make<std::valarray<int>>();
  auto expected_result = std::string("[]");
  auto result = std::string();
  auto buf = std::stringstream();
  buf << arr;
  buf >> result;
  ASSERT_EQ(result, expected_result);
}

TEST_F(HelpersTestGroup, ResizeValarrayShouldResultInCorrectSize) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  resize_valarray(arr, 10);
  ASSERT_EQ(arr.size(), 10);
  resize_valarray(arr, 11);
  ASSERT_EQ(arr.size(), 11);
  resize_valarray(arr, 30);
  ASSERT_EQ(arr.size(), 30);
  resize_valarray(arr, 5);
  ASSERT_EQ(arr.size(), 5);
  resize_valarray(arr, 0);
  ASSERT_EQ(arr.size(), 0);
  resize_valarray(arr, 20);
  ASSERT_EQ(arr.size(), 20);
}

TEST_F(HelpersTestGroup, ResizeValarrayShouldNotCorruptOldData) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  resize_valarray(arr, 11);
  auto arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0);
  ASSERT_TRUE(equal(arr, arr_expected));
  resize_valarray(arr, 5);
  arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5);
  ASSERT_TRUE(equal(arr, arr_expected));
  resize_valarray(arr, 10);
  arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5, 0, 0, 0, 0, 0);
  ASSERT_TRUE(equal(arr, arr_expected));
}

TEST_F(HelpersTestGroup, VectorCanBeConvertedToValarray) {
  auto vec = make<std::vector<int>>(1, 2, 3, 4, 5);
  auto arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5);
  ASSERT_TRUE(equal(to_valarray(vec), arr_expected));
}

TEST_F(HelpersTestGroup, ZeroLengthVectorCanBeConvertedToValarray) {
  auto vec = make<std::vector<int>>();
  auto arr_expected = make<std::valarray<int>>();
  ASSERT_TRUE(equal(to_valarray(vec), arr_expected));
}

TEST_F(HelpersTestGroup, ListCanBeConvertedToValarray) {
  auto list = make<std::list<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  ASSERT_TRUE(equal(to_valarray(list), arr_expected));
}

TEST_F(HelpersTestGroup, ValarrayCanBeConvertedToValarray) {
  auto list = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  ASSERT_TRUE(equal(to_valarray(list), arr_expected));
}

TEST_F(HelpersTestGroup, ArrayCanBeConvertedToValarray) {
  auto arr = make_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  auto arr_expected = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  ASSERT_TRUE(equal(to_valarray(arr), arr_expected));
}

TEST_F(HelpersTestGroup, ZeroLengthArrayCanBeConvertedToValarray) {
  auto arr = make_array<int>();
  auto arr_expected = make<std::valarray<int>>();
  ASSERT_TRUE(equal(to_valarray(arr), arr_expected));
}

TEST_F(HelpersTestGroup, LeftValueCanBeConvertedToValarray) {
  ASSERT_TRUE(equal(to_valarray(make<std::vector<int>>(1, 2, 3, 4)), make<std::valarray<int>>(1, 2, 3, 4)));
}

TEST_F(HelpersTestGroup, AppendNoValueOnValarraySHouldWorkAsExpected) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  append(arr);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)));
}

TEST_F(HelpersTestGroup, AppendValuesOnValarrayShouldResultInCorrectSize) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  append(arr, 11, 12, 13);
  ASSERT_EQ(arr.size(), 13);
  append(arr, 14, 15, 16);
  ASSERT_EQ(arr.size(), 16);
  resize_valarray(arr, 0);
  append(arr, 1, 2, 3);
  ASSERT_EQ(arr.size(), 3);
  append(arr);
  ASSERT_EQ(arr.size(), 3);
}

TEST_F(HelpersTestGroup, AppendValuesOnValarryShouldNotCorruptData) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  append(arr, 11, 12, 13);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13)));
  resize_valarray(arr, 0);
  append(arr, 1, 2, 3);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3)));
}

TEST_F(HelpersTestGroup, AppendValuesOnZeroLengthValarrayShouldAlsoWork) {
  auto arr = make<std::valarray<int>>();
  append(arr);
  ASSERT_EQ(arr.size(), 0);
  append(arr, 1, 2, 3);
  ASSERT_EQ(arr.size(), 3);
}

TEST_F(HelpersTestGroup, ValuesCanAlsoBeAppendedToALeftValueValarray) {
  ASSERT_TRUE(equal(append(make<std::valarray<int>>(), 1, 2, 3, 4), make<std::valarray<int>>(1, 2, 3, 4)));
  ASSERT_TRUE(equal(append(make<std::valarray<int>>(1, 2), 3, 4), make<std::valarray<int>>(1, 2, 3, 4)));
}

TEST_F(HelpersTestGroup, AppendNoContainerOnValarrayShouldWorkAsExpected) {
  auto arr = make<std::valarray<int>>(1, 2, 3, 4);
  ;
  append_container(arr);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3, 4)));
}

TEST_F(HelpersTestGroup, AppendOneContainerOnValarrayShouldWorkAsExpected) {
  auto cont_1 = make<std::vector<int>>(5, 6, 7, 8);
  auto cont_2 = make<std::list<int>>(9, 10, 11, 12);
  auto arr = make<std::valarray<int>>(1, 2, 3, 4);
  append_container(arr, cont_1);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8)));
  append_container(arr, cont_2);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)));
}

TEST_F(HelpersTestGroup, AppendContainersOnValarrayShouldWorkAsExpected) {
  auto cont_1 = make<std::vector<int>>(5, 6, 7, 8);
  auto cont_2 = make<std::vector<int>>(9, 10, 11, 12);
  auto cont_3 = make<std::vector<int>>(13, 14);
  auto arr = make<std::valarray<int>>(1, 2, 3, 4);
  append_container(arr, cont_1, cont_2, cont_3);
  ASSERT_TRUE(equal(arr, make<std::valarray<int>>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14)));
}

#pragma clang diagnostic pop