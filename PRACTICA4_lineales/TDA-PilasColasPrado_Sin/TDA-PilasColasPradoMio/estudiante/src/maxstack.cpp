
#include "maxstack.h"



/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */

void MaxStack::push(int value) {

    int maxVal = elements.empty() ? value : std::max(value, elements.back().max_value );
    //maxValues.top()
    //maxValues.push(maxVal);
    elements.push({value, maxVal});
}
void MaxStack::pop() { //hay que eliminar el ultimo y cambiar si necesario el maxValue
    if (elements.empty()) {
        throw std::out_of_range("ERROR (pop): La pila está vacía.");
    }

    //if(elements.front().value == maxValues.top()) maxValues.pop();

    std::queue<element> tempQueue;
    while (elements.size() > 1) {
        tempQueue.push(elements.front());
        elements.pop();
    }
    // Eliminar el último elemento (que queda en `q`).
    elements.pop();

    // Reemplazar la cola original con la auxiliar
    elements = tempQueue;
}

element MaxStack::top() {
    if (elements.empty()) {
        throw std::out_of_range("ERROR (top): La pila está vacía.");
    }
    return elements.back();
}

int MaxStack::max() {
    if (elements.empty()) { //da igual cual revise por que van a la par de elementos
        throw std::out_of_range("ERROR (max): La pila está vacía.");
    }
    //return maxValues.top();
    return elements.back().max_value;
}

int MaxStack::size() {
    return elements.size();
}

bool MaxStack::empty() {
    return elements.empty();
}

std::ostream& operator<<(std::ostream& os, const element& elem) {
    os << elem.value << ", " << elem.max_value;
    return os;
}