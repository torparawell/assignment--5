#include <iostream>
using namespace std;

template <class X>
class GenStack {
  public:
    GenStack();//default
    GenStack(int maxSize); //overload
    ~GenStack(); //destructor

    void push(X data);
    X pop();
    X peek();

    bool isFull();
    bool isEmpty();
    int getSize();
    
    void printStack(GenStack<X> stack);

    int top;
    int mSize;

    X *myArray;
};
// Template class for GenStack
template <class X>
GenStack<X>::GenStack(){
  myArray = new X[128];
  mSize = 128;
  top = -1;
}

template <class X>
GenStack<X>::GenStack(int maxSize) {
  myArray = new X[maxSize];
  mSize = maxSize;
  top = -1;
}
template <class X>
GenStack<X>::~GenStack(){
  delete[] myArray;
}
template <class X>
void GenStack<X>::push(X data) {
  //check if full before proceeding
  myArray[++top] = data;
}
template <class X>
X GenStack<X>::pop() {
  //check if empty before proceeding
  if(isEmpty()) {
    cout << "Error: Stack is empty and cannot perform pop() function." << endl;
    exit(EXIT_FAILURE);
  }
  return myArray[top--];
}
template <class X>
X GenStack<X>::peek() {
  //check if empty before proceeding
  return myArray[top];
}
template <class X>
bool GenStack<X>::isFull() {
  return (top == mSize-1);
}
template <class X>
bool GenStack<X>::isEmpty() {
  return (top == -1);
}
template <class X>
int GenStack<X>::getSize() {
  return top + 1;
}
