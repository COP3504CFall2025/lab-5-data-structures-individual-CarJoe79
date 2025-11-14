#pragma once
#include <iostream>

template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
public:

	// Behaviors
	void printForward() const{
		if (head != nullptr) {
			Node* current = head;
			for (int i = 0; i < getCount(); i++){
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << std::endl;
		}
	};
	void printReverse() const{
		if (tail != nullptr) {
			Node* current = tail;
			for (int i = 0; i < getCount(); i++){
				std::cout << current->data << " ";
				current = current->prev;
			}
			std::cout << std::endl;
		}
	};

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return this->count;};
	Node* getHead() {return this->head;};
	const Node* getHead() const {return this->head;};
	Node* getTail() {return this->tail;};
	const Node* getTail() const {return this->tail;};

	// Insertion
	void addHead(const T& data){
		Node* newNode = new Node;
		newNode->data = data;

		newNode->prev = nullptr;
		newNode->next = head;

		if (count == 0) tail = newNode;
		else head->prev = newNode;

		head = newNode;
		count++;
	};
	void addTail(const T& data){
		Node* newNode = new Node;
		newNode->data = data;

		newNode->prev = tail;
		newNode->next = nullptr;

		if (count == 0) head = newNode;
		else tail->next = newNode;

		tail = newNode;
		count++;
	};

	// Removal
	bool removeHead(){
		if (count == 0) return false;
		Node* tempPtr = head->next;
		delete head;
		head = tempPtr;
		count--;
		return true;
	};
	bool removeTail(){
		if (count == 0) return false;
		Node* tempPtr = tail->prev;
		delete tail;
		tail = tempPtr;
		count--;
		return true;
	};
	void clear(){
		while (head != nullptr) {
			Node* nextPtr = head->next;
			delete head;
			head = nextPtr;
		}
		tail = nullptr;
		count = 0;
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if (this != &other){
			clear();
			head = other.head;
			tail = other.tail;
			count = other.count;
			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;
		}

		return *this;
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this != &rhs) {
			clear();
			Node* current = rhs.head;
			for (int i = 0; i < rhs.getCount(); i++) {
				addHead(current->data);
				current = current->next;
				if (i == 0) tail = head;
			}
		}

		return *this;
	};

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};

	LinkedList(const LinkedList<T>& list){
		Node* current = list.head;
		count = 0;
		for (int i = 0; i < list.getCount(); i++) {
			addHead(current->data);
			current = current->next;
			if (i == 0) tail = head;
		}
	};
	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	};
	~LinkedList(){
		clear();
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};


