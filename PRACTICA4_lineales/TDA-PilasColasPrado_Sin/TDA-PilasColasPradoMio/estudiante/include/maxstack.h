#ifndef MAXSTACK_H
#define MAXSTACK_H

#include <iostream>
#include <queue>

/**
 * @file maxstack.h
 * @brief Archivo de especificación del TDA MaxStack
 *
 * Implementación del TDA MaxStack, una pila con capacidad para almacenar
 * y obtener el máximo elemento en cualquier momento.
 *
 * @note La pila se implementa mediante una cola de la STL y otros contenedores
 * de apoyo.
 *
 * @date Octubre 2024
 */

struct element {
  int value;       /**< Valor del elemento */
  int max_value;   /**< Máximo valor en la pila hasta el momento de inserción */
};

/**
 * @brief T.D.A. MaxStack
 *
 * Una instancia del tipo de dato abstracto MaxStack representa una pila que,
 * además de las operaciones típicas de una pila, permite consultar el valor
 * máximo actual en cualquier momento. Cada elemento de la pila es un `struct`
 * que contiene:
 * - `value`: el valor del elemento.
 * - `max_value`: el valor máximo actual de la pila en el momento de inserción.
 *
 * Para usar este TDA, es necesario incluir el archivo:
 * @code
 * #include "maxstack.h"
 * @endcode
 *
 * @authors
 * Maria Gallego Siles, Juan Reche Aguilar
 */
class MaxStack {
    /**
     * @page repMaxStack Representación del TDA MaxStack
     *
     * @section invMaxStack Invariante de la representación
     *
     * - La pila almacena elementos de tipo `element`.
     * - Cada `element` contiene un valor `int` y el máximo actual `int`.
     * - element.max_value >= element.value
     *
     * @section faMaxStack Función de abstracción
     *
     * Una instancia válida del TDA `MaxStack` representa una pila que permite
     * manipular sus elementos y consultar en cualquier momento el valor máximo.
     */

private:
    /**
     * @brief Cola de elementos que actúa como la estructura base de la pila
     *
     * Contiene una serie de `element` que representan los valores y sus máximos
     * en el momento de inserción.
     */
    std::queue<element> elements;

public:
    /**
     * @brief Constructor por defecto de la clase MaxStack
     *
     * Inicializa una pila vacía sin elementos.
     */
    MaxStack();

    /**
     * @brief Destructor de la clase MaxStack
     *
     * Libera los recursos asociados con la pila, si existen.
     */
    ~MaxStack();

    /**
     * @brief Inserta un nuevo elemento en la pila
     *
     * Inserta un elemento con valor `value` en la parte superior de la pila y
     * actualiza el máximo si es necesario.
     *
     * @param value Valor del nuevo elemento a insertar.
     * @post El elemento se añade a la pila y el máximo se ajusta si corresponde.
     */
    void push(int value);

    /**
     * @brief Elimina el elemento en la parte superior de la pila
     *
     * Quita el elemento más recientemente insertado en la pila.
     *
     * @pre La pila no debe estar vacía.
     * @post El elemento en la cima es eliminado y el máximo se reajusta si es necesario.
     */
    void pop();

    /**
     * @brief Devuelve el elemento en la cima de la pila sin eliminarlo
     *
     * @return El `element` en la cima de la pila.
     * @pre La pila no debe estar vacía.
     */
    element top();

    /**
     * @brief Devuelve el valor máximo actual de la pila
     *
     * @return El valor máximo de la pila en el momento actual.
     * @pre La pila no debe estar vacía.
     */
    int max();

    /**
     * @brief Devuelve el número de elementos en la pila
     *
     * @return El tamaño actual de la pila.
     */
    int size();

    /**
     * @brief Comprueba si la pila está vacía
     *
     * @return `true` si la pila no contiene elementos, `false` en caso contrario.
     */
    bool empty();
};

/**
 * @brief Sobrecarga del operador de inserción de flujo para `element`
 *
 * Permite mostrar un elemento `element` en un flujo de salida (por ejemplo, std::cout).
 *
 * @param os Flujo de salida.
 * @param elem Elemento a mostrar.
 * @return std::ostream& El flujo de salida tras insertar el elemento.
 */
std::ostream& operator<<(std::ostream& os, const element& elem);

#endif /* MAXSTACK_H */

