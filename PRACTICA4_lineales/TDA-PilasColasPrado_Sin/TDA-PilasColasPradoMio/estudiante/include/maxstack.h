
//#ifndef MAXSTACK_H
//#define MAXSTACK_H

#include <iostream>
#include <queue>

/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author
 */

struct element {
  int value;
  int max_value;
};

class MaxStack {

private:
    std::queue<element> elements;
    //std::priority_queue<int> maxValues;

/**************************************************************************************/
public:
    void push(int value);
    void pop();

    element top();
    int max();

    int size();
    bool empty();
};

std::ostream& operator<<(std::ostream& os, const element& elem);
