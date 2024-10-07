
#include "video.h"
//COMPLETAR POR EL ESTUDIANTE

void read_directory(const std::string& name, vector<string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {

        v.push_back(dp->d_name);

    }
    closedir(dirp);
}


Video::Video(){
    //COMPLETAR POR EL ESTUDIANTE
}
/**************************************************/
Video::Video(int n){
//COMPLETAR POR EL ESTUDIANTE
}
/**************************************************/
Video::Video(const Video &V){
//COMPLETAR POR EL ESTUDIANTE

}
/**************************************************/
Video::~Video(){}
/**************************************************/
Video &Video::operator=(const Video &V){
//COMPLETAR POR EL ESTUDIANTE
}
/**************************************************/
int Video::size() const{
    //COMPLETAR POR EL ESTUDIANTE
}
/**************************************************/
Image &Video::operator[](int foto){
    //COMPLETAR POR EL ESTUDIANTE
}

const Image &Video::operator[](int foto)const{
    //COMPLETAR POR EL ESTUDIANTE
}

void Video::Insertar(int k, const Image &I){
    //COMPLETAR POR EL ESTUDIANTE

}

void Video::Borrar(int k){
    //COMPLETAR POR EL ESTUDIANTE
}

bool Video::LeerVideo(const string &path){

    //USA read_directory PARA LEER los fichero de un directorio
    //COMPLETAR POR EL ESTUDIANTE
}

bool Video::EscribirVideo(const string & path, const string &prefijo)const{

    bool exito=true;
    std::filesystem::path filepath =path;
    bool filepathExists = std::filesystem::is_directory(filepath);

    if (!filepathExists){

        bool created_new_directory= std::filesystem::create_directory(filepath);
        if (!created_new_directory){
            cout<<"No se puede crear el directorio "<<path<<endl;
            return false;
        }
        else{
            cout<<" Se ha creado el directorio "<< path<<endl;
        }
    }

    //COMPLETAR POR EL ESTUDIANTE

}
