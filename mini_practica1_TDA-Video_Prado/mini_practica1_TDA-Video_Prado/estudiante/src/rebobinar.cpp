#include <cstring>

#include "image.h"
#include "video.h"
#include <iostream>
using namespace std;

void showEnglishHelp(ostream& outputStream) {
    outputStream << "-------------------------" << endl;
    outputStream << "ERROR in parameters" << endl;
    outputStream << "Run with the following parameters" << endl;
    outputStream << "Rebobinar /(in directory) /(out directory)" << endl;
    outputStream << "-------------------------" << endl;
    outputStream << endl;
}
Video Rebobinar(const Video &V){
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
    int tam = V.size();
    Video Rebobinar(tam);

    for(int i = 0; i < tam; i++) {
        Rebobinar[i] = V[(tam-1)-i];
    }
    return Rebobinar;
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
    bool read_ok = video_raw.LeerVideo(argv[1]);

    if(read_ok) {
        Video video_back = Rebobinar(video_raw);

        video_back.EscribirVideo(argv[2], PREFIJO);
    }
    return 0;
}
