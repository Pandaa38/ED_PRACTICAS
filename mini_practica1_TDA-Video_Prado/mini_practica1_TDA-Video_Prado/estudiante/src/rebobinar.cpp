#include <cstring>

#include "image.h"
#include "video.h"
#include <iostream>
using namespace std;

/**
 * @brief Muestra un mensaje de ayuda en inglés en el flujo de salida especificado.
 *
 * Esta función imprime un mensaje de error en caso de que se proporcionen incorrectamente
 * los parámetros del programa.
 *
 * @param outputStream flujo de salida donde se imprimirá el mensaje de ayuda.
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "-------------------------" << endl;
    outputStream << "ERROR in parameters" << endl;
    outputStream << "Run with the following parameters" << endl;
    outputStream << "Rebobinar /(in directory) /(out directory)" << endl;
    outputStream << "-------------------------" << endl;
    outputStream << endl;
}

void showEnglishHelp(ostream& outputStream) {
    outputStream << "-------------------------" << endl;
    outputStream << "ERROR in parameters" << endl;
    outputStream << "Run with the following parameters" << endl;
    outputStream << "Rebobinar /(in directory) /(out directory)" << endl;
    outputStream << "-------------------------" << endl;
    outputStream << endl;
}

/**
 * @brief Invierte el orden de los fotogramas de un vídeo.
 *
 * Esta función recibe un vídeo constante y genera un nuevo vídeo que contiene los fotogramas
 * en orden inverso.
 *
 * @pre Elvídeo de entrada tiene al menos un fotograma.
 * @param V Un objeto constante de tipo `Video`, que representa el vídeo de entrada.
 * @return Video Un nuevo objeto de tipo `Video` que contiene los fotogramas en orden inverso.
 *
 */
Video Rebobinar(Video V){
/*
    int first = 0;
    int last = V.size();
    Image image;
    while ((first!=last)&&(first!=--last)) {
        std::iter_swap (V[first],V[last]);
        //std::swap (V[first],V[last]);
        //T c(a); a=b; b=c;

        ++first;
    }
*/
/*************************************/
/*
    int tam = V.size();
    Video rebobinado(tam);

    //error aqui nose por que
    //acede posiciones incorrectas creo
    for(int i = 0; i < tam; i++) {
        rebobinado[i] = V[(tam-1)-i]; //si const Video &V => aborta
    }
*/
    //casi seguro que funciona pero tal vez abria que ordenarlos
    //incluso si la funcion no hace nada hay errores

    int tam = V.size();
    //Video rebobinado(V); //una posibilidad es pasar el video V por valor y de esa forma no usar constructor de copia
    Image temp;
    for(int i = 0; i < tam/2; i++) {
        temp = V[i];
        V[i] = V[(tam-1)-i];
        V[(tam-1)-i] = temp;
    }
    //cout << "hola, aprende a programr " << endl;

    return V;
}

int main(int argc, char * argv[]){

    const string PREFIJO = "REBOBINAR";

    //argv[0] = programa
    //argv[1] = fotogramas video de entrada
    //argv[2] = directorio guardar video rebobinado

    if(argc != 3) {
        showEnglishHelp(cerr);
        return 1;
    }

    std::filesystem::path filepath_in = argv[1];
    bool filepathExists = std::filesystem::is_directory(filepath_in);

    if(!filepathExists) {
        showEnglishHelp(cerr);
        return 1;
    }

    //usar LeerVideo => path entrada
    //usar EscribirVideo => path salida

    Video video_raw;
    //cout << "se crea video constructor bien" << endl;

    bool read_ok = video_raw.LeerVideo(argv[1]);
    //cout << "read: " << boolalpha << read_ok << endl;

    if(read_ok) {
        Video video_back = Rebobinar(video_raw);
        //cout << "rebobinar no aborta" << endl;

        bool write_ok = video_back.EscribirVideo(argv[2], PREFIJO);
        //cout << boolalpha << write_ok << " write" << endl;
    }
    return 0;
}
