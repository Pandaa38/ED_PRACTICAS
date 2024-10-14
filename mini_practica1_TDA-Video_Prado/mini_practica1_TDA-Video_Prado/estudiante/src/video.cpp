#include <iomanip>
#include <fstream>

#include "video.h"

void read_directory(const std::string& name, vector<string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {

        //modificacion no se si peudo tocar esta parte del codigo
        std::string file_name(dp->d_name);
        if (file_name != "." && file_name != "..") {
            v.push_back(file_name);
        }

        //v.push_back(dp->d_name);

    }
    closedir(dirp);
}

// Constructor por defecto
Video::Video(){
    seq.clear();
}
/*******************Constructor por defecto**************/
Video::Video(int n){
    seq.reserve(n);
}
/**************************************************/
Video::Video(const Video &V){
    seq = V.seq;
}
/**************************************************/
Video::~Video(){}

//**************************************************/
Video &Video::operator=(const Video &V){
    if (this != &V) { //si no son el mismo objeto
        seq = V.seq;
    }
    return *this;
}
/**************************************************/
int Video::size() const{
    return seq.size();
}
/**************************************************/
Image &Video::operator[](int foto){
    return seq[foto];
}

const Image &Video::operator[](int foto)const{
    return seq[foto];
}
//mal seq[i+1]
void Video::Insertar(int k, const Image &I){
    seq.resize(size()+1);
    for (int i = size() - 1; i > k; --i) {
        seq[i] = seq[i - 1]; // Desplazamos hacia la derecha
    }
    seq[k] = I; // Agregamos el nuevo fotograma
}
//mal seq[i+1]
void Video::Borrar(int k){
    if (k >= 0 && k < size()) {
        for (int i = k; i < size() - 1; i++) {
            seq[i] = seq[i + 1]; // Desplazamos hacia la izquierda
        }
        seq.resize(size() - 1); // Ajustamos el tamaño
    }
}

bool Video::LeerVideo(const std::string &path) {
    bool exito = true;
    std::vector<std::string> seqStrings;     // Vector para almacenar los nombres de las imágenes

    // Llama a read_directory para llenar seqStrings
    read_directory(path, seqStrings);

    if (seqStrings.empty()) {   // Si no se ha leído nada, la secuencia estará vacía
        exito = false;
    } else {
        // Carga las imágenes utilizando los nombres de archivo
        seq.clear();  // Limpia la secuencia actual antes de cargar nuevas imágenes
        for (size_t i = 0; i < seqStrings.size(); i++) {

            //otra posible sol es filtrar aqui el dir actual y dir padre (. y ..)
            cout << seqStrings[i].c_str() << endl;

            Image img((path + seqStrings[i]).c_str());

            if (!img.Empty()) {
                seq.push_back(img);
            } else {
                std::cerr << "Error al cargar la imagen: " << seqStrings[i] << std::endl;
                exito = false; // Marca como fallido si alguna imagen no se carga
            }

        }
    }

    return exito;
}

bool Video::EscribirVideo(const std::string &path, const std::string &prefijo ) const {
    bool exito = true;
    std::filesystem::path filepath = path;
    bool filepathExists = std::filesystem::is_directory(filepath);

    // Verifica si el directorio existe, si no, lo crea
    if (!filepathExists) {
        bool created_new_directory = std::filesystem::create_directory(filepath);
        if (!created_new_directory) {
            std::cout << "No se puede crear el directorio " << path << std::endl;
            return false;
        } else {
            std::cout << "Se ha creado el directorio " << path << std::endl;
        }
    }

    // Recorre la secuencia de fotogramas para escribir cada uno en un archivo
    for (size_t i = 0; i < seq.size(); i++) {
        std::ostringstream filename;
        filename << path << "/" << prefijo << "_" << std::setw(2) << std::setfill('0') << (i) << ".pgm"; //i+1

        int rows = seq[i].get_rows();
        int cols = seq[i].get_cols();
        std::vector<unsigned char> imgData(rows * cols); // Crear un vector para almacenar todos los píxeles

        // Copia los datos de la imagen a imgData
        for (int f = 0; f < rows; f++) {
            for (int c = 0; c < cols; c++) {
                imgData[f * cols + c] = seq[i].get_pixel(f, c); // Accede a cada píxel
            }
        }

        // Escribir cada imagen en el archivo correspondiente
        exito = WritePGMImage(filename.str().c_str(), imgData.data(), rows, cols);
    }
    return exito;
}
