#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
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
  morph[i] = I1 * (1-i/nframes) + (I2*(1-i/nframes));
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

 std::filesystem::path filepath_in1 = argv[1];
 std::filesystem::path filepath_in2 = argv[2];
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
 Image I1(filepath_in1);
 Image I2(filepath_in2);

 Video video_morph = Morphing(I1,I2,nframes);

 video_morph.EscribirVideo(argv[2], PREFIJO);

 return 0;
}