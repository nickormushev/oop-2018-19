#ifndef __LSTACK_H
#define __LSTACK_H

struct StackElement {
  int data;
  StackElement* next;
};

class LinkedStack {
  // представяне
  StackElement* top; // указател към връх на стека

public:
  // създаване на празен стек
  LinkedStack();

  // проверка за празнота на стек
  bool empty() const;

  // включване на елемент и връща дали е било успешно
  bool push(int x);

  // изключване на елемент
  int pop();

  // поглеждане на последно включения елемент
  int peek() const;
};

#endif
