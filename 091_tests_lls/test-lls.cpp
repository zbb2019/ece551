#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  // WRITE ME
  void trackConsecutiveIntList(IntList * ilp) {
    assert(ilp->head->prev == NULL);
    assert(ilp->tail->next == NULL);

    IntList::Node * tracker = ilp->head;
    for (int i = 0; i < 5; i++) {
      assert((*ilp)[i] == i);
      assert((*ilp)[i] == tracker->data);
      tracker = tracker->next;
    }
    tracker = ilp->tail;
    for (int i = 5; i > 0; i--) {
      assert((*ilp)[i - 1] == tracker->data);
      tracker = tracker->prev;
    }
  }

  void testAddFront() {
    IntList il;
    for (int i = 5; i > 0; i--) {
      il.addFront(i - 1);
      assert(il.head->data == i - 1);
      assert(il.head->prev == NULL);
      assert(il.tail->data == 5 - 1);
      assert(il.tail->next == NULL);
    }
    assert(il.getSize() == 5);
    this->trackConsecutiveIntList(&il);
  }

  void testAddBack() {
    IntList il;
    for (int i = 0; i < 5; i++) {
      il.addBack(i);

      // test
      assert(il.head->data == 0);
      assert(il.head->prev == NULL);
      assert(il.tail->data == i);
      assert(il.tail->next == NULL);
    }
    assert(il.getSize() == 5);
    this->trackConsecutiveIntList(&il);
  }

  void testCopyConstructor() {
    IntList rhs;
    IntList il(rhs);

    // test
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testAssignmentOperator() {
    IntList rhs;
    IntList il = rhs;

    // test
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testDeepCopy(IntList * ilp, IntList * rhsp) {
    assert(ilp->getSize() == rhsp->getSize());

    IntList::Node * tracker = ilp->head;
    IntList::Node * tracker_rhs = rhsp->head;
    for (int i = 0; i < 5; i++) {
      assert(tracker != tracker_rhs);
      assert(tracker->data == tracker_rhs->data);
      tracker = tracker->next;
      tracker_rhs = tracker_rhs->next;
    }
  }

  void testCopyConstructor2() {
    IntList rhs;
    for (int i = 0; i < 5; i++) {
      rhs.addBack(i);
    }
    IntList il(rhs);

    // test
    this->trackConsecutiveIntList(&il);
    this->testDeepCopy(&il, &rhs);
  }

  void testAssignmentOperator2() {
    IntList rhs;
    for (int i = 0; i < 5; i++) {
      rhs.addBack(i);
    }
    IntList il;
    il.addBack(9);
    il = rhs;

    // test
    this->trackConsecutiveIntList(&il);
    this->testDeepCopy(&il, &rhs);
  }

  void testRemove() {
    IntList il;  // 0 1 2 3 4
    for (int i = 0; i < 5; i++) {
      il.addBack(i);
    }

    // test non-existing element
    assert(il.remove(9) == false);
    this->trackConsecutiveIntList(&il);

    // remove elements in mid of the list
    IntList::Node * tracker = il.head->next->next;  // 2
    assert(il.remove(1) == true);                   // 0 2 3 4
    assert(il.getSize() == 4);
    assert(il.head->data == 0);
    assert(il.tail->data == 4);
    assert(il.head->next == tracker);
    assert(tracker->prev == il.head);
    assert(il.head->next->data == 2);
    assert(tracker->prev->data == 0);

    // remove the head element
    il.remove(0);  // 2 3 4
    assert(il.getSize() == 3);
    assert(il.head->data == 2);
    assert(il.tail->data == 4);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);

    // remove the tail element
    il.remove(4);  // 2 3
    assert(il.getSize() == 2);
    assert(il.head->data == 2);
    assert(il.tail->data == 3);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);

    // remove all the elements
    il.remove(2);
    il.remove(3);  // empty
    assert(il.getSize() == 0);
    assert(il.head == NULL);
    assert(il.tail == NULL);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testCopyConstructor();
  t.testCopyConstructor2();
  t.testAssignmentOperator();
  t.testAssignmentOperator2();
  t.testRemove();
  return EXIT_SUCCESS;
}
