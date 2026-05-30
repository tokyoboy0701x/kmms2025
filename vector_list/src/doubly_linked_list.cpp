#include "doubly_linked_list.hpp"

#include <iostream>

using ordo::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = begin;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t count = 0;
	Node* current = begin;
	while (current != nullptr) {
		++count;
		current = current->next;
	}
	return count;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = begin;
	while (current != nullptr) {
		if (current->value == value) return true;
		current = current->next;
	}
	return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node* current = begin;
	while (current != nullptr) {
		std::cout << current->value;
		if (current->next != nullptr) std::cout << ' ';
		current = current->next;
	}
	std::cout << '\n';
}	

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* node = new Node(value);
	if (end == nullptr) {
		begin = end = node;
	} else {
		node->prev = end;
		end->next = node;
		end = node;
	}
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current = begin;
	while (current != nullptr) {
		if (current->value == value) {
			if (current->prev != nullptr)
				current->prev->next = current->next;
			else
				begin = current->next;

			if (current->next != nullptr)
				current->next->prev = current->prev;
			else
				end = current->prev;

			delete current;
			return true;
		}
		current = current->next;
	}
	return false;
}