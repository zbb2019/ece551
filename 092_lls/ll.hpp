#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class Tester;

template<typename T>
class LinkedList {
 public:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & item) : data(item), next(NULL), prev(NULL) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  // default constructor
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  // addFront
  void addFront(const T & item) {
    if (size == 0) {
      head = new Node(item);
      tail = head;
    }
    else {
      Node * temp = new Node(item);
      head->prev = temp;
      temp->next = head;
      head = temp;
    }
    size += 1;
  }

  // addBack
  void addBack(const T & item) {
    if (size == 0) {
      head = new Node(item);
      tail = head;
    }
    else {
      Node * temp = new Node(item);
      tail->next = temp;
      temp->prev = tail;
      tail = temp;
    }
    size += 1;
  }

  // [] operator
  T & operator[](int index) {
    if (index >= size || index < 0) {
      throw std::exception();
    }

    Node * tracker = head;
    for (int i = 0; i < index; i++) {
      tracker = tracker->next;
    }
    return tracker->data;
  }

  // const [] operator
  const T & operator[](int index) const {
    if (index >= size || index < 0) {
      throw std::exception();
    }

    Node * tracker = head;
    for (int i = 0; i < index; i++) {
      tracker = tracker->next;
    }
    return tracker->data;
  }

  // remove
  bool remove(const T & item) {
    Node * tracker = head;
    for (int i = 0; i < size; i++) {
      if (tracker->data == item) {
        if (size == 1) {  // remove the only 1 element left in the list
          head = NULL;
          tail = NULL;
          delete tracker;
        }
        else if (i == 0) {  // remove 1st element
          head = head->next;
          head->prev = NULL;
          delete tracker;
        }
        else if (i == size - 1) {  // remove last element
          tail = tail->prev;
          tail->next = NULL;
          delete tracker;
        }
        else {  // remove element in the mid
          tracker->prev->next = tracker->next;
          tracker->next->prev = tracker->prev;
          delete tracker;
        }
        size -= 1;
        return true;
      }
      tracker = tracker->next;
    }
    return false;
  }

  // find
  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }

  // copy constructor
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.getSize(); i++) {
      this->addBack(rhs[i]);
    }
    size = rhs.getSize();
  }

  // = operator
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      if (size != 0) {  // delete
        Node * tracker = tail;
        while (tail != head) {  // more than 1 element exist
          tail = tail->prev;
          tail->next = NULL;
          delete tracker;
          tracker = tail;
        }
        delete tracker;
        head = NULL;
        tail = NULL;
        size = 0;
      }
      for (int i = 0; i < rhs.getSize(); i++) {
        this->addBack(rhs[i]);
      }
    }
    return *this;
  }

  // destructor
  ~LinkedList() {
    if (size != 0) {
      Node * tracker = tail;
      for (int i = 0; i < size - 1; i++) {
        tail = tail->prev;
        tail->next = NULL;
        delete tracker;
        tracker = tail;
      }

      head = NULL;
      tail = NULL;
      delete tracker;
    }
  }

  // getSize()
  int getSize() const { return size; }

  friend class Tester;
};

#endif
