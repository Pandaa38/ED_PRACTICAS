#ifndef MAXQUEUE_H
#define MAXQUEUE_H

#include <iostream>
#include <list>

/**
 * @file maxqueue.h
 * @brief Archivo de especificación del TDA MaxQueue
 *
 * Este archivo contiene la definición del TDA `MaxQueue`, una cola con la capacidad
 * de devolver el valor máximo en cualquier momento.
 *
 * @note La clase utiliza una lista de la STL para manejar los elementos.
 *
 * @date Octubre 2024
 */

/**
 * @struct element
 *
 * Estructura que representa un elemento en la `MaxQueue`.
 * Cada elemento contiene:
 * - `value`: El valor del elemento.
 * - `max_value`: El máximo valor en la cola en el momento en que se insertó este elemento.
 */
struct element {
    int value;       /**< Valor del elemento */
    int max_value;   /**< Máximo valor en la cola hasta el momento de inserción */
};

/**
 * @brief Función de comparación para elementos de tipo `element`
 *
 * Compara dos elementos `element` para determinar cuál contiene un mayor valor.
 *
 * @param i_element Primer elemento a comparar.
 * @param j_element Segundo elemento a comparar.
 * @return `true` si `i_element` es menor que `j_element` en términos de `value`.
 */
bool compare_element(const element& i_element, const element& j_element);

/**
 * @brief Sobrecarga del operador de inserción para `element`
 *
 * Permite mostrar un objeto `element` en un flujo de salida.
 *
 * @param os Flujo de salida.
 * @param elem Elemento a mostrar.
 * @return std::ostream& El flujo de salida después de insertar el elemento.
 */
std::ostream &operator<<(std::ostream &os, const element &elem);

/**
 * @brief T.D.A. MaxQueue
 *
 * `MaxQueue` es una cola que permite, además de las operaciones habituales de
 * encolado y desencolado, consultar el valor máximo de la cola en cualquier
 * momento. Cada elemento de la cola contiene:
 * - `value`: el valor del elemento.
 * - `max_value`: el máximo valor actual de la cola al momento de la inserción.
 *
 * Para usar este TDA, incluye el archivo:
 * @code
 * #include "maxqueue.h"
 * @endcode
 *
 * @authors
 * Maria Gallego Siles, Juan Reche Aguilar
 */
class MaxQueue {
    /**
     * @page repMaxQueue Representación del TDA MaxQueue
     *
     * @section invMaxQueue Invariante de la representación
     *
     * - `MaxQueue` almacena elementos de tipo `element`.
     * - Cada `element` contiene un valor `int` y el máximo `int` de la cola hasta su inserción.
     * - element.max_value >= element.value
     *
     * @section faMaxQueue Función de abstracción
     *
     * Un objeto válido de `MaxQueue` representa una cola que permite manipular
     * sus elementos y consultar en cualquier momento el valor máximo.
     */

private:
    /**
     * @brief Lista de elementos que actúa como base de la cola
     *
     * Contiene una lista de `element`, donde cada uno representa un valor y el
     * máximo de la cola en el momento de inserción.
     */
    std::list<element> elements_;

public:
    /**
     * @brief Constructor por defecto de la clase MaxQueue
     *
     * Inicializa una cola vacía sin elementos.
     */
    MaxQueue();

    /**
     * @brief Destructor de la clase MaxQueue
     *
     * Libera los recursos asociados con la cola, si existen.
     */
    ~MaxQueue();

    /**
     * @brief Inserta un nuevo elemento en la cola
     *
     * Inserta un elemento con el valor `value` en la cola y actualiza el máximo
     * si es necesario.
     *
     * @param value Valor del nuevo elemento a insertar.
     * @post El elemento se añade al final de la cola y el máximo se ajusta si corresponde.
     */
    void push(int value);

    /**
     * @brief Elimina el elemento en la parte frontal de la cola
     *
     * Quita el elemento más antiguo de la cola.
     *
     * @pre La cola no debe estar vacía.
     * @post El elemento en el frente es eliminado y el máximo se reajusta si es necesario.
     */
    void pop();

    /**
     * @brief Devuelve el elemento en el frente de la cola sin eliminarlo
     *
     * @return El `element` en el frente de la cola.
     * @pre La cola no debe estar vacía.
     */
    element front();

    /**
     * @brief Devuelve el valor máximo actual en la cola
     *
     * @return El valor máximo de la cola en el momento actual.
     * @pre La cola no debe estar vacía.
     */
    int max();

    /**
     * @brief Devuelve el número de elementos en la cola
     *
     * @return El tamaño actual de la cola.
     */
    int size();

    /**
     * @brief Comprueba si la cola está vacía
     *
     * @return `true` si la cola no contiene elementos, `false` en caso contrario.
     */
    bool empty();
};

#endif /* MAXQUEUE_H */
