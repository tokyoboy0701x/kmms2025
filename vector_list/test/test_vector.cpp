#include <gtest/gtest.h>

#include "vector.hpp"

using ordo::Vector;

// ── get_size ──────────────────────────────────────────────────────────────────

TEST(VectorTest, SizeIsZeroOnInit) {
	Vector<int> v;
	EXPECT_EQ(v.get_size(), 0u);
}

TEST(VectorTest, SizeGrowsWithPushBack) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	EXPECT_EQ(v.get_size(), 3u);
}

// ── has_item ──────────────────────────────────────────────────────────────────

TEST(VectorTest, HasItemEmptyVector) {
	Vector<int> v;
	EXPECT_FALSE(v.has_item(0));
}

TEST(VectorTest, HasItemFindsExisting) {
	Vector<int> v;
	v.push_back(10);
	v.push_back(20);
	EXPECT_TRUE(v.has_item(10));
	EXPECT_TRUE(v.has_item(20));
}

TEST(VectorTest, HasItemReturnsFalseForMissing) {
	Vector<int> v;
	v.push_back(10);
	EXPECT_FALSE(v.has_item(99));
}

// ── push_back ─────────────────────────────────────────────────────────────────

TEST(VectorTest, PushBackSingleElement) {
	Vector<int> v;
	v.push_back(42);
	EXPECT_EQ(v.get_size(), 1u);
	EXPECT_TRUE(v.has_item(42));
}

TEST(VectorTest, PushBackTriggerGrow) {
	Vector<int> v;
	for (int i = 0; i < 100; ++i)
		v.push_back(i);
	EXPECT_EQ(v.get_size(), 100u);
	EXPECT_TRUE(v.has_item(0));
	EXPECT_TRUE(v.has_item(99));
}

// ── insert ────────────────────────────────────────────────────────────────────

TEST(VectorTest, InsertAtBeginning) {
	Vector<int> v;
	v.push_back(2);
	v.push_back(3);
	EXPECT_TRUE(v.insert(0, 1));
	EXPECT_EQ(v.get_size(), 3u);
	EXPECT_TRUE(v.has_item(1));
}

TEST(VectorTest, InsertAtEnd) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	EXPECT_TRUE(v.insert(2, 3));
	EXPECT_EQ(v.get_size(), 3u);
	EXPECT_TRUE(v.has_item(3));
}

TEST(VectorTest, InsertInMiddle) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(3);
	EXPECT_TRUE(v.insert(1, 2));
	EXPECT_EQ(v.get_size(), 3u);
	EXPECT_TRUE(v.has_item(2));
}

TEST(VectorTest, InsertOutOfBoundsReturnsFalse) {
	Vector<int> v;
	v.push_back(1);
	EXPECT_FALSE(v.insert(5, 99));
	EXPECT_EQ(v.get_size(), 1u);
}

TEST(VectorTest, InsertOnEmptyAtZero) {
	Vector<int> v;
	EXPECT_TRUE(v.insert(0, 42));
	EXPECT_EQ(v.get_size(), 1u);
	EXPECT_TRUE(v.has_item(42));
}

TEST(VectorTest, InsertTriggerGrow) {
	Vector<int> v;
	for (int i = 0; i < 4; ++i)
		v.push_back(i);
	// capacity is full (START_CAPACITY = 4), insert should grow
	EXPECT_TRUE(v.insert(0, 99));
	EXPECT_EQ(v.get_size(), 5u);
	EXPECT_TRUE(v.has_item(99));
}

// ── remove_first ──────────────────────────────────────────────────────────────

TEST(VectorTest, RemoveFirstReturnsFalseOnEmpty) {
	Vector<int> v;
	EXPECT_FALSE(v.remove_first(1));
}

TEST(VectorTest, RemoveFirstReturnsFalseIfNotFound) {
	Vector<int> v;
	v.push_back(1);
	EXPECT_FALSE(v.remove_first(99));
	EXPECT_EQ(v.get_size(), 1u);
}

TEST(VectorTest, RemoveFirstDecreasesSize) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	EXPECT_TRUE(v.remove_first(2));
	EXPECT_EQ(v.get_size(), 2u);
	EXPECT_FALSE(v.has_item(2));
}

TEST(VectorTest, RemoveFirstOnlyRemovesOneOfDuplicates) {
	Vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	EXPECT_TRUE(v.remove_first(5));
	EXPECT_EQ(v.get_size(), 2u);
	EXPECT_TRUE(v.has_item(5));
}

TEST(VectorTest, RemoveOnlyElement) {
	Vector<int> v;
	v.push_back(7);
	EXPECT_TRUE(v.remove_first(7));
	EXPECT_EQ(v.get_size(), 0u);
	EXPECT_FALSE(v.has_item(7));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}