//#ifndef MAXSTACK_H
//#define MAXSTACK_H

#include <iostream>
#include <list>

/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author
 */

//interesante clase element
struct element {
    int value;
    int max_value;
};
//voy a fumarme un porro potente con esto de los funtores luego le pregunto al profe si esta bien o mejor usar clase
bool compare_elemet(const element& i_element, const element& j_element);
std::ostream &operator<<(std::ostream &os, const element &elem);

class MaxQueue {
private:
    std::list<element> elements_;

/**************************************************************************************/
public:
    MaxQueue();

    ~MaxQueue();

    void push(int value);

    void pop();

    element front();

    int max();

    int size();

    bool empty();
};
