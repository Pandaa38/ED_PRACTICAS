#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "image.h"
#include "video.h"

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
    outputStream << "morphing /(in directory) /(in directory) /(out directory) /(nframes)" << endl;
    outputStream << "-------------------------" << endl;
    outputStream << endl;
}

/**
 * @brief Realiza un morphing entre dos imágenes, creando una transición suave.
 *
 * El morphing es un proceso que transforma una imagen en otra, proporcionando
 * una transición fluida entre ellas.
 *
 * @pre Las imágenes tienen las mismas dimensiones y formatos.
 * @param I1 La imagen fuente de tipo `Image`, que representa el estado inicial.
 * @param I2 La imagen destino de tipo `Image`, que representa el estado final.
 * @param nframes El número de fotogramas a generar durante la transición.
 * @return Video Un objeto de tipo `Video` que contiene los fotogramas generados
 *         que representan la transición de I1 a I2.
 *
 */
Video Morphing(const Image &I1, const Image &I2, int nframes) {
    Video morph(nframes);  // Inicializa el vector morph con el tamaño adecuado
    for (int i = 0; i < nframes; i++) {
        float alpha = static_cast<float>(i) / (nframes - 1);
        morph[i] = I1 * (1 - alpha) + I2 * alpha;
    }
    return morph;
}


int main(int argc, char *argv[]) {

    const string PREFIJO = "MORPHING_";

    // argv[0] = programa
    // argv[1] = fotogramas video de entrada
    // argv[2] = fotogramas video de entrada
    // argv[3] = directorio guardar video
    // argv[4] = pasos a realizar

    if (argc != 5) {
        showEnglishHelp(cerr);
    return 1;
    }

    const char* filepath_in1 = argv[1];
    const char* filepath_in2 = argv[2];
    int nframes = atoi(argv[4]);

    // Comprobamos si los directorios en los que se encunetran las
    // imágenes existen
    bool filepathExists = std::filesystem::is_regular_file(filepath_in1) &&
                          std::filesystem::is_regular_file(filepath_in2);
    if (!filepathExists) {
        showEnglishHelp(cerr);
        return 1;
    }

    // Cargamos las imágenes del primer y segundo fichero
    Image I1, I2;
    I1.Load(filepath_in1);
    I2.Load(filepath_in2);

    Video video_morph = Morphing(I1, I2, nframes);
    video_morph.EscribirVideo(argv[3], PREFIJO);

    return 0;
}
