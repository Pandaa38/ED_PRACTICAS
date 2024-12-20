/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el �rbol de preguntas para jugar al �Qui�n es qui�n?.
 */

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>
#include "pregunta.h"
#include "bintree.h"
#include "ventana.h"
#include "consola.h"
#include "tablerografico.h"
using namespace std;

/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su �ndice en
	  *        este vector corresponde con el �ndice de su
	  *        descripci�n en el tablero.
	  */
	vector<string> personajes;

	 /**
      * @brief Almacena el nombre de las imagenes en disco de los  personajes. Su �ndice en
      *        este vector corresponde con el �ndice de su
      *        descripci�n en el tablero.
      */
    vector<string> personajes_images;


	/**
	  * @brief Almacena los atributos.  Su �ndice en este vector
	  *        corresponde con el �ndice correspondiente de cada
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada
	  *        actual.
	  */
	bintree<Pregunta>::node nodo_actual;

	 /**
     * @brief tg es el tablero grafico donde se muestra los personajes
     */
    TableroGrafico *tg;

    /**
     * @brief con consola para interactuar con el usuario
     */
    Consola *con;

    /**
     * @brief imagen_ocultar nombre de la imagen en disco para ocultar el personaje
     */
    string imagen_ocultar;

    /**
     * @brief modo_graph flag que indica si se usa el modelo grafico o solo texto
     */
    bool modo_graph;


	/**
	  * @brief Funcion auxiliar para crear el arbol de preguntas.
	  *
	  * @param atributos vector de atring que contiene los atributos por los que se pregunta.
	  * @param indice_atributo indica la posicion del atributo en el vector de atributos de la pregunta actual.
	  * @param personajes vector de string con los nombres de los personajes.
	  * @param personajes_restantes vector booleano en el que cada posicion se corresponde con la posicion en el
	  *        vector de personajes, indicandonos si el correspondiente personaje sigue vivo.
	  *        personajes_restantes[i] == true si personaje[i] sigue vivo
	  *        personajes_restantes[i] == false si personaje[i] no sigue vivo
	  * @param tablero matriz de booleanos que nos indica si para un personaje la pregunta relacionada con un atributo
	  *        es afirmativa(true) o negativa(false).
	  *        tablero[i][indice_atributo] == true si personaje[i] tiene atributo[indice_atributo]
	  *        tablero[i][indice_atributo] == false si personaje[i] no tiene atributo[indice_atributo]
	  *
	  * @return arbol de preguntas.
	  * @post se modifica this->tablero y this->atributos.
	  */
	 bintree<Pregunta> crear_arbol(vector<string> atributos,
                                    int indice_atributo,
                                    vector<string> personajes,
                                    vector<bool> personajes_restantes,
                                    vector<vector<bool>> tablero);
public:
	/**
	  * @brief Constructor b�sico de la clase
	  */
	QuienEsQuien();
	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);
	/**
	  * @brief Destructor del pregunta.
	  */
	~QuienEsQuien();
	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();
	/**
	* @brief Sobrecarga del operador de asignaci�n.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Operador de extracci�n de flujo.
	  * @param is Stream de entrada
          * @param quienEsQuien Quien es quien a leer.
	  * @return Referencia al stream de entrada.
	  *
	  * Lee de @e is un quien es quien y lo almacena en @e
	  * quienEsQuien. El formato aceptado para la lectura es un TSV
	  * (tab-separated values) en el que las columnas tienen cabecera y
	  * son las preguntas. La �ltima columna corresponde al nombre del
	  * personaje. Tras la cabecera se especifica en cada l�nea un
	  * personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	  * atributo de la columna. En la �ltima columna se da el
	  * nombre del personaje.
	  */
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);

	/**
	  * @brief Operador de inserci�n de flujo.
	  * @param os Stream de salida
	  * @param quienEsQuien Quien es quien a escribir.
	  * @return Referencia al stream de salida.
	  *
	  * Escribe en @e is un quien es quien.
	  * El formato usado para la escritura es un TSV
	  * (tab-separated values) en el que las columnas tienen cabecera y
	  * son las preguntas. La �ltima columna corresponde al nombre del
	  * personaje. Tras la cabecera se especifica en cada l�nea un
	  * personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	  * atributo de la columna. En la �ltima columna se da el
	  * nombre del personaje.
	  */
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandard las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
	  * @brief Este m�todo construye el �rbol de preguntas para todos los personajes del tablero.
	  */
	bintree<Pregunta> crear_arbol();

	/**
	  * @brief Sustituye el �rbol actual por el �rbol pasado por par�metro.
	  *
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  *
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
	  * @brief Metodo que modifica el arbol de preguntas para que no haya preguntas redundantes.
	  * @param nodo_actual nodo actual en el que nos encontramos
	  * @post El �rbol de preguntas se modifica.
	  */
	void eliminar_nodos_redundantes_recursiva(bintree<Pregunta>::node nodo_actual);

	/**
	  * @brief Metodo que modifica el arbol de preguntas para que haya preguntas redundantes.
	  *
	  * @post El �rbol de preguntas se modifica.
	  * Nota: Pasa la raiz del arbol al metodo eliminar_nodos_redundantes_recursiva.
	  */
	void eliminar_nodos_redundantes();

	/**
	  * @brief Inicializa el juego.
	  * @post  Si la partida anterior no hab�a terminado se
	  *        pierde el progreso.
	  */
	void iniciar_juego();

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de
	  *        los personajes que a�n no han sido tumbados en el
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  *
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  *
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);


	/**
	  * @brief Este metodo permite calcular la profundidad de todas las hojas del arbol.
	  *
	  * @param profundidad profundidad que tiene hasta el momento
	  * @param nivel_actual nodo actual en el que nos encontramos
	  * @param prof_hojas referencia a un vector de tipo int donde en cada posición se recoge la profundidad
	  *        de una hoja distinta del arbol
	  * @return void
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	void profundidad_hojas(int profundidad, bintree<Pregunta>::node nivel_actual, vector<int>& prof_hojas);


	/**
	  * @brief Este m�todo permite calcular la media de la profundidad de las hojas del �rbol.
	  * Este valor representa el n�mero (promedio) de preguntas necesarias para adivinar cada personaje.
	  * A menor profundidad promedio, mejor soluci�n. Esta m�trica es un indicador para evaluar la calidad de vuestra soluci�n.
	  *
	  * @return Profundidad media del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas();


	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  *
	  * @param numero_de_personajes N�mero de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);

    /**
     * @brief setImagenOcultar Modifica el nombre de la imagen en disco para ocultar los personajes en modo
     * grafico
     * @param n:nombre del fichero en disco
     */
    void setImagenOcultar(const char * n);

    /**
     * @brief setModoGraph Modifica el modelo grafico
     * @param m: True si se desea modo grafico false solo texto
     */
    void setModoGraph(bool m);

     /**
     * @brief Oculta en el tablero grafico los personajes que no estan activos
     * @param personajes_activos: personajes que est�n activos
     */
    void ocultar_personajes_graph(const set<string> &personajes_activos);


	/**
	************************************************************************************************************
	*                                        MÉTODOS ADICIONALES                                               *
	************************************************************************************************************
	**/

	// Podemos plantearlo como una función que devuleve un flujo de salida
	/**
	* @brief Este método se aplica sobre un nodo del árbol de preguntas (jugada) para obtener una
	* descripción de las preguntas formuladas anteriormente y las respuestas dadas por el usuario
	* hasta ahora. Por ejemplo:
	* “El personaje oculto tiene las siguientes características:
	*	Mujer – no
	*	Ojos Marrones – si
	* pero aún no sé cuál es”
	*
	* @param jugada nodo actual del árbol de Preguntas donde nos enocntramos
	* @post escribe un mensaje en la salida estándar
	*/
	void preguntas_formuladas (bintree<Pregunta>::node jugada);


	/**
	* @brief Este método inserta el personaje nuevo en el árbol ya construido.
	*
	* Se recorrerá el árbol desde la raíz hasta encontrar dónde se inserta el nuevo personaje. Este recorrido por el
	* árbol nos lleva a un nodo hoja (otro personaje del tablero) y tendremos que añadir un nivel más
	* (una pregunta más) para distinguir al nuevo personaje del nodo hoja que ya estaba en el árbol.
	*
	* @param nombre nombre del personaje que se añade
	* @param caracteristicas vector de características para el personaje a añadir
	* @param nombre_imagen_personaje nombre de la imagen en disco del personaje que se añade (modo grafico)
	* @return void
	*
	* @pre 1) El arbol de preguntas debe haber sido construido previamente.
	*		2) vector<bool> de características tiene el mismo tamaño y los atributos están en el mismo orden que el
	*		especificado en el fichero de entrada.
	* @post El arbol de preguntas es modificado
	**/
	void aniade_personaje (string nombre, vector<bool> caracteristicas,string nombre_imagen_personaje="");

	/**
	* @brief Este método elimina un personaje del árbol ya construido.
	*
	* Utilizaremos las características del personaje para recorrer el árbol desde la raíz y encontrar su nodo hoja
	* asociado. Al eliminarlo, tendremos que eliminar también a su padre (porque ahora será una pregunta inútil),
	* esto es, reemplazar a su padre por su otro nodo hijo.
	*
	* @param nombre nombre del personaje que se elimina
	* @return void
	*
	* @pre El arbol de preguntas debe haber sido construido previamente.
	* @post El arbol de preguntas es modificado
	**/
	void elimina_personaje (string nombre);

private:
	/**
	* @brief Reorganiza el tablero y los atributos del objeto implicito al encontrar una pregunta que sea mejor
	* de realizar.
	*
	* @param pos_mejor_atributo posicion del vector de atributos, marca el atributo correspondiente a la mejor pregunta.
	* @param indice_atributo posicion del vector de atributos, marca el inicio del vector a partir del cuál
	*        hay preguntas que no se han realizado.
	*
	* @return void
	* @post modifica el orden del this->atributos y this>tablero
	*
	*/
	void reorganizar_tablero(int pos_mejor_atributo, int indice_atributo);

	/**
	* @brief Escoge la mejor pregunta sabiendo las preguntas que ya se han realizado.
	*  La mejor pregunta será aquella cuyo vector correspondiente a atributos (columnas) de tablero
	*  tengán el numero de 0 (false) y 1(true) mas equiparado. Esto ocurre cuando el numero de true o de false
	*  es igual a num_personajes_vivos/2.
	*
	* @param personajes_restantes vector booleano que nos indica que personaje sigue vivo en la rama
	* @param indice_atributo posicion del vector de atributos, marca el inicio del vector a partir del cuál
	*        hay preguntas que no se han realizado.
	*
	* @return void
	* @post modifica el orden del this->atributos y this>tablero
	*
	*/
	void MejorPregunta(const vector<bool>& personajes_restantes, int indice_atributo);
};

#endif

