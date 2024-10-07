
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
using namespace std;

//Lee los ficheros de un directorio
//name es el nombre del directorio
//v el vector donde almacena los nombres

void read_directory(const std::string& name, vector<string>& v);


class Video {
private:
    vector<Image> seq;
public:

    Video();

    Video(int n);

    Video(const Video &V);

    ~Video();

    Video &operator=(const Video &V);

    int size() const;

    Image &operator[](int foto);

    const Image &operator[](int foto)const;

    void Insertar(int k, const Image &I);

    void Borrar(int k);

    bool LeerVideo(const string & path);

    bool EscribirVideo(const string & path, const string &prefijo)const;
};

#endif //PRACTICA2_VIDEO_H
