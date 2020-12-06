#include <iostream>

using namespace std;
template <class X>
class ListNode {
  public:
    ListNode();
    ListNode(X d);
    ~ListNode();

    X data;
    ListNode *next;
    ListNode *prev;
};
template <class X>
class DoublyLinkedList{
//single linked list
  private:
    ListNode<X> *front;
    ListNode<X> *back;
    int size;
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insertFront(X d);
    void insertBack(X d);
    X atPos(int pos);
    int removeFront();
    int find(int value);
    int deletePos(int pos);
    int removeNode(int key); //Find the key value and then proceed to delete.


    void printList();
    void printListToFile(ofstream& outfile);
    bool isEmpty();
    unsigned int getSize();
};
template <class X>
DoublyLinkedList<X>::DoublyLinkedList() {
  front = NULL;
  back = NULL;
  size = 0;
}
template <class X>
DoublyLinkedList<X>::~DoublyLinkedList() {
  // Do this yourself.
  delete front;
  delete back;
}

template <class X>
unsigned int DoublyLinkedList<X>::getSize() {
  return size;
}

template <class X>
void DoublyLinkedList<X>::insertFront(X d) {
  ListNode<X> *node = new ListNode<X>(d);
  if(size==0){ //Indicates an empty list.
    back = node;
  } 
  else {
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <class X>
bool DoublyLinkedList<X>::isEmpty() {
      if(size == 0)
        return true;
      return false;
}
template <class X>
void DoublyLinkedList<X>::insertBack(X d) {
  ListNode<X> *node = new ListNode<X>(d);
  if(front == NULL) {
    front = back;
  }
  else {
    node->prev = back;
	  back->next = node;
  }
  back = node;
  ++size;
}
template <class X>
void DoublyLinkedList<X>::printList() {
  ListNode<X> *curr = front;

  while (curr != NULL) {
    cout << curr->data << endl;
    curr = curr->next;
  }
}
template <class X>
void DoublyLinkedList<X>::printListToFile(ofstream& outfile) {
  ListNode<X> *curr = front;

  while (curr != NULL) {
    outfile << curr->data << endl;
    curr = curr->next;
  }
}

template <class X>
int DoublyLinkedList<X>::find(int value) {
  int pos = -1;
  ListNode<X> *curr = front;
  while (curr != NULL) {
    //iterate until we reach the end and hopefully we find what we are looking for.
    ++pos;
    if (curr->data == value) {
      break;
    }
    curr = curr->next;
  }
    if(curr == NULL) {
      pos = -1;
    }
  return pos;
}
template <class X>
int DoublyLinkedList<X>::deletePos(int pos) {
  int p = 0;
  ListNode<X> *curr = front;
  ListNode<X> *prev = front;

  //iterate to the correcet position
  while (p != pos) {
    prev = curr;
    curr = curr->next;
    p++;
  }
  //We found the position and our pointers are in their respective positions.
  prev->next = curr->next;
  curr->next = NULL;

  int temp = curr->data;
  size--;
  delete curr;
  return temp;
}
template <class X>
int DoublyLinkedList<X>::removeFront() {
  int temp = front ->data;
  ListNode<X> *ft = front;
  front = front->next;
  ft->next = NULL;
  --size;
  delete ft;
  return temp;
}
template <class X>
X DoublyLinkedList<X>::atPos(int pos){
      int p = 0;
      ListNode<X> *curr = front;
      ListNode<X> *prev = front;

      //iterate to the correcet position
      while (p != pos) {
        curr = curr->next;
        p++;
      }

      return curr->data;
    }


template <class X>
ListNode<X>::ListNode() {}
template <class X>
ListNode<X>::ListNode(X d) {
  data = d;
  next = NULL;
}
template <class X>
ListNode<X>::~ListNode() {
  // Do this yourself.
}