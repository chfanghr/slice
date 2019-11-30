//
// Created by 方泓睿 on 2019/11/29.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "slice.h"

#include <gtest/gtest.h>  // Put gtest header in front of our own header in order to avoid conflicts of operator<<

#include <sstream>

class SliceTestGroup : public testing::Test {
 public:
  std::valarray<int> arr_{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
};

struct MyType {};

TEST_F(SliceTestGroup, SliceIsContainer) {
  ASSERT_TRUE(is_container_v<slice<int>>);
  ASSERT_TRUE(is_container_v<slice<unsigned>>);
  ASSERT_TRUE(is_container_v<slice<float>>);
  ASSERT_TRUE(is_container_v<slice<MyType>>);
}

TEST_F(SliceTestGroup, ConstructorPosOnlyAcceptsPoskAll) {
  ASSERT_NO_THROW(slice(arr_, Pos::kAll));
  ASSERT_THROW(slice(arr_, Pos::kBegin), std::invalid_argument);
  ASSERT_THROW(slice(arr_, Pos::kEnd), std::invalid_argument);
}

TEST_F(SliceTestGroup, ConstructorFromPosDoesnNotAcceptsPoskAll) {
  ASSERT_NO_THROW(slice(arr_, 0, Pos::kEnd));
  ASSERT_NO_THROW(slice(arr_, 0, Pos::kBegin));
  ASSERT_THROW(slice(arr_, 0, Pos::kAll), std::invalid_argument);
}

TEST_F(SliceTestGroup, ConstructorPosToDoesNotAcceptsPosAll) {
  ASSERT_NO_THROW(slice(arr_, Pos::kEnd, arr_.size()));
  ASSERT_NO_THROW(slice(arr_, Pos::kBegin, arr_.size()));
  ASSERT_THROW(slice(arr_, Pos::kAll, 0), std::invalid_argument);
  ;
}

TEST_F(SliceTestGroup, ConstructorFromPosThrowWhenArgumentIsInvalid) {
  ASSERT_THROW(slice(arr_, arr_.size() + 1, Pos::kEnd), std::invalid_argument);
  ASSERT_THROW(slice(arr_, arr_.size(), Pos::kBegin), std::invalid_argument);
  ASSERT_THROW(slice(arr_, arr_.size() + 1, Pos::kBegin), std::invalid_argument);
}

TEST_F(SliceTestGroup, ConstructorPosToThrowWhenArgumentIsInvalid) {
  ASSERT_NO_THROW(slice(arr_, Pos::kEnd, arr_.size()));
  ASSERT_THROW(slice(arr_, Pos::kEnd, arr_.size() - 1), std::invalid_argument);
  ASSERT_THROW(slice(arr_, Pos::kEnd, arr_.size() + 1), std::out_of_range);
  ASSERT_THROW(slice(arr_, Pos::kBegin, arr_.size() + 1), std::out_of_range);
  ASSERT_NO_THROW(slice(arr_, Pos::kBegin, arr_.size() - 1));
}

TEST_F(SliceTestGroup, ConstructorFromToThrowWhenArgumentIsInvalid) {
  ASSERT_NO_THROW(slice(arr_, 0, arr_.size()));
  ASSERT_NO_THROW(slice(arr_, 0, 0));
  ASSERT_NO_THROW(slice(arr_, arr_.size(), arr_.size()));
  ASSERT_THROW(slice(arr_, arr_.size(), 0), std::invalid_argument);
  ASSERT_THROW(slice(arr_, 0, arr_.size() + 1), std::out_of_range);
}

TEST_F(SliceTestGroup, SizeShouldWorkAsExpected) {
  auto sli = slice(arr_, Pos::kAll);
  ASSERT_EQ(sli.size(), arr_.size());
  sli = slice(arr_, 0, 0);
  ASSERT_EQ(sli.size(), 0);
  sli = slice(arr_, Pos::kEnd, arr_.size());
  ASSERT_EQ(sli.size(), 0);
  sli = slice(arr_, Pos::kBegin, 0);
  ASSERT_EQ(sli.size(), 0);
  sli = slice(arr_, arr_.size(), arr_.size());
  ASSERT_EQ(sli.size(), 0);
  sli = slice(arr_, 3, 5);
  ASSERT_EQ(sli.size(), 2);
}

TEST_F(SliceTestGroup, GetArrayShouldWorkAsExpected) {
  auto sli = slice(arr_, Pos::kAll);
  ASSERT_EQ(&sli.get_array(), &arr_);
  sli = slice(arr_, 0, 0);
  ASSERT_EQ(&sli.get_array(), &arr_);
}

TEST_F(SliceTestGroup, LeftShiftOperatorShouldWorkOnSlice) {
  auto buf = std::stringstream();
  auto result = std::string();
  auto expected = std::string();
  {
    auto sli = slice(arr_, 0, arr_.size());
    buf << arr_;
    buf >> expected;
    buf.clear();
    buf << sli;
    buf >> result;
    buf.clear();
    ASSERT_EQ(result, expected);
    expected.clear();
    result.clear();
  }
  {
    auto sli = slice(arr_, 0, 3);  // [1,2,3]
    expected = "[1,2,3]";
    buf << sli;
    buf >> result;
    ASSERT_EQ(result, expected);
    expected.clear();
    result.clear();
  }
}

TEST_F(SliceTestGroup, SliceValarrayWithPos) { ASSERT_TRUE(equal(to_valarray(slice(arr_, Pos::kAll)), arr_)); }

TEST_F(SliceTestGroup, SliceValarrayWithFromPos) {
  ASSERT_TRUE(equal(to_valarray(slice(arr_, 0, Pos::kBegin)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, 5, Pos::kEnd)), make<std::valarray<int>>(6, 7, 8, 9, 10)));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, 5)), make<std::valarray<int>>(6, 7, 8, 9, 10)));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, 8)), make<std::valarray<int>>(9, 10)));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, arr_.size())), make<std::valarray<int>>()));
}

TEST_F(SliceTestGroup, SliceValarrayWithPosTo) {
  ASSERT_TRUE(equal(to_valarray(slice(arr_, Pos::kBegin, 0)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, Pos::kEnd, arr_.size())), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, Pos::kBegin, 3)), make<std::valarray<int>>(1, 2, 3)));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, Pos::kBegin, 5)), make<std::valarray<int>>(1, 2, 3, 4, 5)));
}

TEST_F(SliceTestGroup, SliceValarrayWithFromTo) {
  ASSERT_TRUE(equal(to_valarray(slice(arr_, 0, 0)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, arr_.size(), arr_.size())), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(arr_, 1, 3)), make<std::valarray<int>>(2, 3)));
}

TEST_F(SliceTestGroup, SliceSliceWithPos) {
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_))), arr_));
  ASSERT_TRUE(equal(to_valarray(slice(slice(slice(arr_)))), arr_));
}

TEST_F(SliceTestGroup, SliceSliceWithPosTo) {
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 0), Pos::kBegin, 0)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 7), Pos::kBegin, 0)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 7), Pos::kBegin, 3)), make<std::valarray<int>>(1, 2, 3)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 7), Pos::kBegin, 3)), make<std::valarray<int>>(1, 2, 3)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 7), Pos::kBegin, 3)), make<std::valarray<int>>(4, 5, 6)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 8), Pos::kBegin, 3)), make<std::valarray<int>>(4, 5, 6)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 7), Pos::kBegin, 2)), make<std::valarray<int>>(4, 5)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 7), Pos::kEnd, 7)), make<std::valarray<int>>()));
}

TEST_F(SliceTestGroup, SliceSliceWithFromPos) {
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 0), 0, Pos::kEnd)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 0), 0, Pos::kBegin)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 7), 0, Pos::kEnd)), make<std::valarray<int>>(4, 5, 6, 7)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 6), 0, Pos::kEnd)), make<std::valarray<int>>(4, 5, 6)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 8), 0, Pos::kEnd)), make<std::valarray<int>>(4, 5, 6, 7, 8)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 2, 7), 0, Pos::kEnd)), make<std::valarray<int>>(3, 4, 5, 6, 7)));
}

TEST_F(SliceTestGroup, SliceSliceWithFromTo) {
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 0), 0, 0)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 7), 0, 0)), make<std::valarray<int>>()));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 0, 7), 0, 3)), make<std::valarray<int>>(1, 2, 3)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 7), 0, 3)), make<std::valarray<int>>(4, 5, 6)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 8), 0, 3)), make<std::valarray<int>>(4, 5, 6)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 7), 1, 3)), make<std::valarray<int>>(5, 6)));
  ASSERT_TRUE(equal(to_valarray(slice(slice(arr_, 3, 7), 0, 2)), make<std::valarray<int>>(4, 5)));
}

TEST_F(SliceTestGroup, SliceCanBeRandomlyAccess) {
  std::valarray<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto sli = slice(arr);
  ASSERT_EQ(sli[0], 1);
  ASSERT_EQ(sli[1], 2);
  ASSERT_EQ(sli[2], 3);
  ASSERT_EQ(sli[3], 4);
  ASSERT_EQ(sli[4], 5);
  ASSERT_EQ(sli[5], 6);
  ASSERT_EQ(sli[6], 7);
  ASSERT_EQ(sli[7], 8);
  ASSERT_EQ(sli[8], 9);
  ASSERT_EQ(sli[9], 10);
  ASSERT_THROW(sli[10], std::out_of_range);
  sli = slice(arr, 1, 3);
  ASSERT_EQ(sli[0], 2);
  ASSERT_EQ(sli[1], 3);
  ASSERT_THROW(sli[2], std::out_of_range);
  sli = slice(arr, 2, 6);
  sli[0] = 11;
  ASSERT_EQ(sli[0], 11);
}

TEST_F(SliceTestGroup, ModifySliceElementShouldResultInChangeOfUnderlyingValarray) {
  std::valarray<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  (slice(arr))[0] = 11;
  ASSERT_EQ(arr[0], 11);
  (slice(arr, 1))[0] = 11;
  ASSERT_EQ(arr[1], 11);
  (slice(arr, 1))[1] = 11;
  ASSERT_EQ(arr[2], 11);
  (slice(arr, 1, 3))[0] = 12;
  ASSERT_EQ(arr[1], 12);
}

TEST_F(SliceTestGroup, AppendToASliceShouldWorkAsExpected) {
  auto sli = slice(arr_, 0, 4);
  auto arr_appended = append(sli, 11);
  ASSERT_TRUE(equal(arr_appended, make<std::valarray<int>>(1, 2, 3, 4, 11)));
  arr_appended = append(sli, 11, 12, 13);
  ASSERT_TRUE(equal(arr_appended, make<std::valarray<int>>(1, 2, 3, 4, 11, 12, 13)));
}

TEST_F(SliceTestGroup, SliceCanBeConvertedToValarray) {
  auto sli = slice(arr_, 1, 3);
  auto arr_converted = to_valarray(sli);
  ASSERT_TRUE(equal(arr_converted, make<std::valarray<int>>(2, 3)));
}

#pragma clang diagnostic pop
