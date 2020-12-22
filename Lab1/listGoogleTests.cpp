#include "gtest/gtest.h"
#include "../list.h"
#include <ostream>

class ListFixture : public ::testing::Test {
protected:
    List<int> left;
    List<int> right;
    List<int> list;
    List<int> emptyList;

    void SetUp() override {
        for (int i = 100; i < 500; i += 100) {
            list.push_back(i);
        }
        right = list; // 100 200 300 400
        left = list; // 100 200 300 400
    }
};

int array[] = {5, 6, 7, 8};

std::string listToString(const List<int> &list) {
    std::string listString;
    for (auto item : list) {
        listString += std::to_string(item) + " ";
    }
    listString.pop_back();
    return listString;
}

TEST_F(ListFixture, emptyTest) {
    EXPECT_TRUE(emptyList.empty());
    EXPECT_FALSE(list.empty());
}

TEST_F(ListFixture, throwCheck) {
    ASSERT_THROW(emptyList.front(), ListException);
    ASSERT_THROW(emptyList.pop_front(), ListException);
    ASSERT_NO_THROW(list.front());
    ASSERT_NO_THROW(list.pop_front());

    ASSERT_THROW(emptyList.back(), ListException);
    ASSERT_THROW(emptyList.pop_back(), ListException);
    ASSERT_NO_THROW(list.back());
    ASSERT_NO_THROW(list.pop_back());
}

TEST_F(ListFixture, insertTest) {
    list.insert(++list.begin(), array[0]);
    EXPECT_EQ(*(++list.cbegin()), array[0]);

    list.insert(list.begin(), array[1]);
    EXPECT_EQ(*(list.begin()), array[1]);

    EXPECT_EQ(listToString(list), "6 100 5 200 300 400");
}

TEST_F(ListFixture, removeTest){
    list.push_front(100);
    list.push_back(100);
    EXPECT_EQ(listToString(list), "100 100 200 300 400 100");
    list.remove(100);
    EXPECT_EQ(listToString(list), "200 300 400");
}

TEST_F(ListFixture, eraseTest) {
    list.erase(++list.begin());
    EXPECT_EQ(listToString(list), "100 300 400");

    list.erase(--list.end());
    EXPECT_EQ(listToString(list), "100 300");
}

TEST_F(ListFixture, eraseInRangeTest) {
    list.erase(list.begin()++, --list.end());
    EXPECT_EQ(listToString(list), "400");

    left.erase(++left.begin(), left.end());
    EXPECT_EQ(listToString(left), "100");

    right.erase(right.begin(), --right.end());
    EXPECT_EQ(listToString(right), std::to_string(right.back()));
}

TEST_F(ListFixture, clearTest) {
    list.clear();
    EXPECT_EQ(list.empty(), true);
    EXPECT_EQ(list.size(), 0);

    List<int> emptyList;
    left.clear();
    EXPECT_TRUE(left == emptyList);
}

TEST_F(ListFixture, sizeTest) {
    EXPECT_EQ(list.size(), 4);
    list.erase(list.begin());
    EXPECT_EQ(list.size(), 3);
}

TEST_F(ListFixture, operatorEqualTest) {
    EXPECT_TRUE(left == right);
    right.pop_front();
    left.pop_front();
    EXPECT_TRUE(left == right);
    left.pop_front();
    EXPECT_FALSE(left == right);
}

TEST_F(ListFixture, listConcatenationTest) {
    left += right;
    EXPECT_EQ(listToString(left), "100 200 300 400 100 200 300 400");
    EXPECT_EQ(listToString(right), "100 200 300 400");
}

TEST_F(ListFixture, operatorPlusTest) {
    List<int> sum = left + list + right;
    EXPECT_EQ(listToString(sum), "100 200 300 400 100 200 300 400 100 200 300 400");
}