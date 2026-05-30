#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using ordo::DoublyLinkedList;

// ── get_size ──────────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, SizeIsZeroOnInit) {
	DoublyLinkedList<int> list;
	EXPECT_EQ(list.get_size(), 0u);
}

TEST(DoublyLinkedListTest, SizeGrowsWithPushBack) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_EQ(list.get_size(), 3u);
}

// ── has_item ──────────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, HasItemEmptyList) {
	DoublyLinkedList<int> list;
	EXPECT_FALSE(list.has_item(0));
}

TEST(DoublyLinkedListTest, HasItemFindsExisting) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	EXPECT_TRUE(list.has_item(10));
	EXPECT_TRUE(list.has_item(20));
}

TEST(DoublyLinkedListTest, HasItemReturnsFalseForMissing) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	EXPECT_FALSE(list.has_item(99));
}

// ── push_back ─────────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, PushBackSingleElement) {
	DoublyLinkedList<int> list;
	list.push_back(42);
	EXPECT_EQ(list.get_size(), 1u);
	EXPECT_TRUE(list.has_item(42));
}

TEST(DoublyLinkedListTest, PushBackMultipleElements) {
	DoublyLinkedList<int> list;
	for (int i = 0; i < 10; ++i)
		list.push_back(i);
	EXPECT_EQ(list.get_size(), 10u);
	EXPECT_TRUE(list.has_item(0));
	EXPECT_TRUE(list.has_item(9));
}

// ── remove_first ──────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, RemoveFirstReturnsFalseOnEmpty) {
	DoublyLinkedList<int> list;
	EXPECT_FALSE(list.remove_first(1));
}

TEST(DoublyLinkedListTest, RemoveFirstReturnsFalseIfNotFound) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	EXPECT_FALSE(list.remove_first(99));
	EXPECT_EQ(list.get_size(), 1u);
}

TEST(DoublyLinkedListTest, RemoveFirstDecreasesSize) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_TRUE(list.remove_first(2));
	EXPECT_EQ(list.get_size(), 2u);
	EXPECT_FALSE(list.has_item(2));
}

TEST(DoublyLinkedListTest, RemoveFirstHead) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	EXPECT_TRUE(list.remove_first(1));
	EXPECT_FALSE(list.has_item(1));
	EXPECT_TRUE(list.has_item(2));
	EXPECT_EQ(list.get_size(), 1u);
}

TEST(DoublyLinkedListTest, RemoveFirstTail) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	EXPECT_TRUE(list.remove_first(2));
	EXPECT_FALSE(list.has_item(2));
	EXPECT_TRUE(list.has_item(1));
	EXPECT_EQ(list.get_size(), 1u);
}

TEST(DoublyLinkedListTest, RemoveOnlyElement) {
	DoublyLinkedList<int> list;
	list.push_back(7);
	EXPECT_TRUE(list.remove_first(7));
	EXPECT_EQ(list.get_size(), 0u);
	EXPECT_FALSE(list.has_item(7));
}

TEST(DoublyLinkedListTest, RemoveFirstOnlyRemovesOneOfDuplicates) {
	DoublyLinkedList<int> list;
	list.push_back(5);
	list.push_back(5);
	list.push_back(5);
	EXPECT_TRUE(list.remove_first(5));
	EXPECT_EQ(list.get_size(), 2u);
	EXPECT_TRUE(list.has_item(5));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}