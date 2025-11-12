#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
public:

	// Behaviors
	void printForward() const{
		Node* current = head;
		for (int i = 0; i < getCount(); i++){
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	};
	void printReverse() const{
		Node* current = tail;
		for (int i = 0; i < getCount(); i++){
			cout << current->data << " ";
			current = current->prev;
		}
		cout << endl;
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
		if (count == 0) {
			head = tail = newNode;
		}
		else {
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
		count++;
	};
	void addTail(const T& data){
		Node* newNode = new Node;
		newNode->data = data;
		if (count == 0) {
			head = tail = newNode;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	};

	// Removal
	void removeHead(){
		Node* tempPtr = head->next;
		delete head;
		head = tempPtr;
		count--;
	};
	void removeTail(){
		Node* tempPtr = tail->prev;
		delete tail;
		tail = tempPtr;
		tail->next = nullptr;
		count--;
	};
	void clear(){
		for (int i = 0; i < getCount(); i++) removeHead();
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
	LinkedList(){
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
		count = 0;
		//cout << "Default constructor called!" << endl;
	};
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
		delete head;
		delete tail;
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};


