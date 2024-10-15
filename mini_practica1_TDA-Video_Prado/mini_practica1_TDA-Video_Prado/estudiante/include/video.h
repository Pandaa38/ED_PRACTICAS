#ifndef PRACTICA2_VIDEO_H
#define PRACTICA2_VIDEO_H
#include "image.h"
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <cmath>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
* @brief Lee los ficheros de un directorio
* @param name es el nombre del directorio
* @param v el vector donde almacena los nombres
* @post Genera una instancia de la clase Vídeo con O imágenes.
* @return Vídeo, el objeto vídeo creado.
*/
void read_directory(const std::string& name, vector<string>& v);


/**
  @brief T.D.A. Vídeo

  Una instancia del tipo de dato abstracto Video nos permite almacenar una secuencia temporal de imágenes
  (o fotogramas).

  El TDA Video proporciona además distintas herramientas para la manipulación de dichos video,
  como son las creación y detsrucción de un vídeo, la inseción de una nueva imagen, el borrado de
  una imagen que forma parte del vídeo, el rebobinado o hacer morphing de intensidades de un vídeo a otro.

  Para poder usar el TDA Video se debe incluir el fichero

  \#include <Video.h>

  @author Maria Gallego y Juan
  @date Octubre 2024

**/
class Video {
    /**
      @page repVideo Representación del TDA Video .

      @section invVideo Invariante de la representación.

      Un objeto válido 1 del TDA Vídeo debe cumplir
        -I.seq apunta a una zona de memoria con capacidad para albergar n valores de tipo imagen o a NULL si el vídeo está vacío.

      @section faVideo Función de abstracción

      Un objeto válido 1 del TDA Video representa un video, formado por una secuencia de imágenes en niveles de gris.
      El vídeo tendra dimensión n imágenes.

    **/
private:
    /**
      @brief Puntero al vídeo almacenado

      seq es un array dinámico de la clase vector de la librería stl que contiene una secuencia de imágenes.

    **/
    vector<Image> seq;
public:
    /**
    * @brief Constructor por defecto .
    * @post Genera una instancia de la clase Vídeo con O imágenes.
    * @return Vídeo, el objeto vídeo creado.
    */
    Video();

    /**
    * @brief Constructor con parámetros.
    * @param n Número de imágenes del vídeo.
    * @pre n > O
    * @post El vídeo creado tiene n casillas. Además, el vídeo creado contiene valores “basura” (no está inicializado).
    * @return Video, el objeto video creado.
    */
    Video(int n);

    /**
    * @brief Constructor de copias.
    * @param V Referencia al vídeo original que se quiere copiar.
    * @return Video, el objeto video creado.
    */
    Video(const Video &V);

    /**
    * @brief Operador de tipo destructor. Libera los recursos ocupados por el vídeo.
    * @return void
    * @post El objeto Video destruido no puede usarse salvo que se haga sobre él una operacion Video().
    */
    ~Video();

    /**
    * @brief Operador de asignación.
    * @param V Referencia al vídeo original que desea copiarse.
    * @return Una referencia al objeto vídeo modificado.
    * @post Destroy cualquier información que contuviera previamente el vídeo que llama al operador de asignación.
    */
    Video &operator=(const Video &V);

    /**
    * @brief Calcula el número de imágenes que componen el vídeo.
    * @return numero de imágenes del vídeo.
    * @post El vídeo no se modifica.
    */
    int size() const;

    /**
    * @brief Operador[] permite al usuario consultar un fotograma del vídeo y modificarlo.
    * @pre 0 <= foto < size()
    * @param foto posición de la imagen en el vídeo que se desea consultar o modificar.
    * @return La imagen asociada al fotograma foto-ésimo del vídeo.
    * @post La imagen asociada al fotograma foto-ésimo del vídeo puede modificarse.
    */
    Image &operator[](int foto);

    /**
    * @brief Operador[] permite al usuario consultar un fotograma del vídeo.
    * @pre 0 <= foto < size()
    * @param foto posición de la imagen en el vídeo que se desea consultar.
    * @return La imagen asociada al fotograma foto-ésimo del vídeo.
    * @post La imagen asociada al fotograma foto-ésimo del vídeo no puede modificarse.
    */
    const Image &operator[](int foto)const;

    /**
    * @brief Inserta un nuevo fotograma I en la posición k.
    * @pre 0 <= k <= size()
    * @param k posición en la que se quiere insertar la imagen en el vídeo.
    * @param I imagen que se quiere insertar al vídeo.
    * @return Vídeo modificado con un nuevo fotograma más.
    * @post No se borrará ninguna imagen que el vídeo pudiera contener antes de llamar a este método.
    */
    void Insertar(int k, const Image &I);

    /**
    * @brief Elimina el fotograma que ocupa la posición dada por un entero k en el vídeo.
    * @param k posición de la foto que se desea borrar.
    * @return Vídeo modificado con un nuevo fotograma menos.
    */
    void Borrar(int k);

    /**
    * @brief Lee un vídeo de disco.
    * @pre El directorio path debe contener una secuencia temporal de fotogramas.
    * @param path Directorio que contiene la secuencia de fotogramas.
    * @return Devuelve true si la lectura tiene éxito y false en caso contrario..
    */
    bool LeerVideo(const string & path);

    /**
    * @brief Escribe un vídeo de disco.
    * @pre En el directorio path se almacenará la secuencia temporal de fotogramas. Los
           fotogramas tomarán como nombre <prefijo>_01.pgm .. <prefijo>_0n.pgm siendo n el número de
           fotogramas.
    * @param path Directorio en el que se escribe el vídeo.
    * @ param prefijo forma parte del nombre que tendrán los fotogramas al escribirse en disco.
    * @return Devuelve true si la escritura tiene éxito y false en caso contrario.
    */
    bool EscribirVideo(const string & path, const string &prefijo)const;
};

#endif //PRACTICA2_VIDEO_H
