
//#ifndef MAXSTACK_H
//#define MAXSTACK_H

#include <iostream>
#include <queue>

/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author
 *
 * Implementación del TDA MaxStack
 */

struct element {
  int value;
  int max_value;
};

/**
  @brief T.D.A. MaxStack

  Una instancia del tipo de dato abstracto MaxStack es una pila de máximos. Cada elemento de la pila
  es un struct que contiene dos registros:
  - El valor del elemento
  - El máximo valor que se encuentra en la pila hasta el momento

  El TDA MaxStack proporciona además distintas herramientas para la manipulación de
  los elementos en la pila. La finalidad es que trabaje con una pila de la libreria stl.

  Para poder usar el TDA MaxStack se debe incluir el fichero

  \#include <maxstack.h>

  @author Maria Gallego Siles y Juan Reche Aguilar
  @date Octubre 2024

**/
class MaxStack {
    /**
      @page repMaxStack Representación del TDA MaxStack .

      @section invMaxStack Invariante de la representación.

      Un objeto válido 1 del TDA MaxStack debe cumplir
        -MaxStack contiene elements
        -element.value es un int
        -element.mas_value es un int

      @section faImagen Función de abstracción

      Un objeto válido del TDA MaxStack representa una pila que nos proporciona herramientas para trabajar de
      forma óptima con el máximo de la pila y la cuál funciona de forma similar a una pila de la libreria stl.

    **/

private:
    /**
      @brief Cola de elementos

      Los elementos son registros de numeros enteros que recoge su valor además de el maximo valor que está en la cola
    **/
  std::queue<element> elements;

  /**
      @brief Cola con prioridad de elementos máximos

      Cola que se ordena de mayor a menor en función del valor del elemento.

    **/
  //std::priority_queue<int> maxValues;

/**************************************************************************************/
public:

  MaxStack();
  ~MaxStack();

  /**
    @brief Initialize una imagen.
    @param nrows Número de filas que tendrá la imagen. Por defecto, 0
    @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
    @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
    @pre filas >= O y columnas >= O
    @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
  void push(int value);

  /**
  @brief Initialize una imagen.
  @param nrows Número de filas que tendrá la imagen. Por defecto, 0
  @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
  @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
  @pre filas >= O y columnas >= O
  @post Reserva memoria para almacenar la imagen y la prepara para usarse.
  **/
  void pop();

  /**
    @brief Initialize una imagen.
    @param nrows Número de filas que tendrá la imagen. Por defecto, 0
    @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
    @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
    @pre filas >= O y columnas >= O
    @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
  element top();
  /**
  @brief Initialize una imagen.
  @param nrows Número de filas que tendrá la imagen. Por defecto, 0
  @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
  @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
  @pre filas >= O y columnas >= O
  @post Reserva memoria para almacenar la imagen y la prepara para usarse.
  **/
  int max();
  /**
    @brief Initialize una imagen.
    @param nrows Número de filas que tendrá la imagen. Por defecto, 0
    @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
    @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
    @pre filas >= O y columnas >= O
    @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
  int size();
  /**
    @brief Initialize una imagen.
    @param nrows Número de filas que tendrá la imagen. Por defecto, 0
    @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
    @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
    @pre filas >= O y columnas >= O
    @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
  bool empty();
};
std::ostream& operator<<(std::ostream& os, const element& elem);
