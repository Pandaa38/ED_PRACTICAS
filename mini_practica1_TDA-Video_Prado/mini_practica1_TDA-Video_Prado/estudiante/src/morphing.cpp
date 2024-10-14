#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "image.h"
#include "video.h"

using namespace std;

void showEnglishHelp(ostream& outputStream) {
 outputStream << "-------------------------" << endl;
 outputStream << "ERROR in parameters" << endl;
 outputStream << "Run with the following parameters" << endl;
 outputStream << "morphing /(in directory) /(in directory) /(out directory) /(nframes)" << endl;
 outputStream << "-------------------------" << endl;
 outputStream << endl;
}

Video Morphing(const Image &I1,const Image &I2,int nframes){
 Video morph;
 for (int i=0;i<nframes;i++) {
  morph[i] = (I1 * (1-i/nframes) + I2*(i/nframes));
 }
 return morph;
}

int main(int argc, char * argv[]){

 const string PREFIJO = "MORPHING_";

 //argv[0] = programa
 //argv[1] = fotogramas video de entrada
 //argv[2] = fotogramas video de entrada
 //argv[3] = directorio guardar video
 //argv[4] = pasos a realizar

 if(argc != 5) {
  showEnglishHelp(cerr);
  return 1;
 }

 const char* filepath_in1 = argv[1];
 const char* filepath_in2 = argv[2];
 int nframes = atoi(argv[3]);

 // Comprobamos si los directorios en los que se encunetran las
 // imágenes existen
 bool filepathExists = std::filesystem::is_directory(filepath_in1) &&
                       std::filesystem::is_directory(filepath_in2);

 if(!filepathExists) {
  showEnglishHelp(cerr);
  return 1;
 }

 //Cargamos las imagenes del primer y segundo fichero
 Image I1, I2;
 I1.Load(filepath_in1);
 I2.Load(filepath_in2);

 Video video_morph = Morphing(I1,I2,nframes);

 video_morph.EscribirVideo(argv[2], PREFIJO);

 return 0;
}