#ifndef __RSTACK_H
#define __RSTACK_H

const int INITIAL_CAPACITY = 10;
const int EMPTY_STACK = -1;
const int RESIZE_FACTOR = 2;

class ResizingStack {
  // представяне
  int* a;            // указател към масив в динамичната памет за стека
  int top;           // връх на стека
                     // индекс на последно включения елемент в стека
  int capacity;      // големина на текущо заделената памет за стека

  // проверка за пълен стек
  bool full() const;

  // разширяване на стека
  void resize();

  // копиране на стека
  void copy(ResizingStack const& rs);

public:
  // създаване на празен стек
  ResizingStack();

  // конструктор за копиране
  ResizingStack(ResizingStack const&);

  // операция за присвояване
  ResizingStack& operator=(ResizingStack const&);

  // проверка за празнота на стек
  bool empty() const;

  // включване на елемент и връща дали е било успешно
  bool push(int x);

  // изключване на елемент
  int pop();

  // поглеждане на последно включения елемент
  int peek() const;

  ~ResizingStack();
};

#endif
