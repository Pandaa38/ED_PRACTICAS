#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>

QuienEsQuien::QuienEsQuien(){
}

QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
}

QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
     return *this;
}

QuienEsQuien::~QuienEsQuien(){
     this->limpiar() ;
}

void QuienEsQuien::limpiar(){
     this->personajes.clear();
     this->atributos.clear();
     this->personajes_images.clear();
     for(vector<vector<bool>>::iterator it_tablero = this->tablero.begin();
         it_tablero != this->tablero.end();
         it_tablero++){
          (*it_tablero).clear();
     }
     this->tablero.clear();
     this->arbol.clear() ;
}

template <typename T>
std::ostream& operator<<  (std::ostream& out, const std::vector<T>& v) {
     if ( !v.empty() ) {
          out <<  '[' ;
          std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
          out <<  "\b\b]";
     }

     return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
     cout <<  "personajes: " <<  (this->personajes) <<  endl;
     cout <<  "atributos: " <<  (this->atributos) <<  endl;
     cout <<  "tablero:    " <<  endl;
     // Escribe la cabecera del tablero
     for(vector<string>::iterator it_atributos = this->atributos.begin() ;
         it_atributos != this->atributos.end() ;
         it_atributos++){
          cout <<  *it_atributos << "\t";
     }
     cout << endl;

     int indice_personaje = 0;
     for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
         it_tablero_atributos!= tablero.end();
         it_tablero_atributos++){
          string personaje = this->personajes[indice_personaje];
          int indice_atributo = 0;
          for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
              it_atributos_personaje != (*it_tablero_atributos).end() ;
              it_atributos_personaje++){
               cout <<  *it_atributos_personaje<< "\t";
               indice_atributo++;
          }
          cout <<  personaje <<  endl;
          indice_personaje++;
     }
}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */


string limpiar_string(string cadena_original,string cadena_a_eliminar){
     string linea(cadena_original);
     while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
          linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
     }

     return linea;
}

istream& operator >>  (istream& is, QuienEsQuien &quienEsQuien) {
     quienEsQuien.limpiar();
     if(is.good()){ //Lee la linea con los nombres de las columnas
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");
          bool salir=false;
          while(!salir && linea.find('\t') != string::npos ){
               string atributo = linea.substr(0,linea.find('\t'));
               quienEsQuien.atributos.push_back(atributo);
               linea = linea.erase(0,linea.find('\t')+1);
               if (linea.substr(0,linea.find('\t'))=="Nombre personaje")
                   salir=true;
          }
     }
     //LEE los atributos para cada personaje
     while( is.good()) {
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");

          //Si la linea contiene algo extrae el personaje.
          //Si no la ignora.
          if(linea != ""){;
               vector<bool> atributos_personaje;
               int indice_atributo=0;
               bool salir=false;
               while(!salir && linea.find('\t') != string::npos){
                   string valor = linea.substr(0,linea.find('\t'));
                   if (valor == "0" || valor == "1"){
                    bool valor_atributo = valor == "1";
                    atributos_personaje.push_back(valor_atributo);
                    linea = linea.erase(0,linea.find('\t')+1) ;
                    indice_atributo++;
                   }
                   else{
                       salir=true;
                   }
               }
               string nombre_personaje;
               string imagen_personaje;
               if (linea.find('\t') == string::npos){
                nombre_personaje = linea;
                imagen_personaje=""; //no tiene imagen
               }
               else{
                nombre_personaje=linea.substr(0,linea.find('\t'));
                linea = linea.erase(0,linea.find('\t')+1) ;
                imagen_personaje=linea;

               }
               quienEsQuien.personajes.push_back(nombre_personaje);
               quienEsQuien.tablero.push_back(atributos_personaje);
               quienEsQuien.personajes_images.push_back(imagen_personaje);
          }
     }
     quienEsQuien.mostrar_estructuras_leidas();
     quienEsQuien.arbol = quienEsQuien.crear_arbol();
     quienEsQuien.tg=nullptr; //puntero al tablero grafico
     quienEsQuien.con=nullptr; //puntero a la consola
     if (quienEsQuien.modo_graph){
        int nper = quienEsQuien.personajes.size();
        int nrows,ncols=3;
        if (nper<8)
           nrows = nper/ncols;
        else{
            ncols=4;
            nrows = nper/ncols;
        }
        //se crea un tablero grafico
        quienEsQuien.tg = new TableroGrafico(400,400,nrows,ncols);
        //ponemos en el tablero grafico las im�genes
        for (int i=0;i<nper;i++){

            quienEsQuien.tg->putImagen(i/ncols,i%ncols,quienEsQuien.personajes_images[i].c_str());
        }
        //creamos la consola
        quienEsQuien.con=new Consola();
     }
     return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){
     //Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre

     cout<<"NUmero de Atributos "<<quienEsQuien.atributos.size()<<endl;
     for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
         it_atributos != quienEsQuien.atributos.end();
         it_atributos++){
          os << *it_atributos << "\t";
     }

     os << "Nombre personaje" << endl;
     
     //Rellenamos con ceros y unos cada linea y al final ponemos el nombre del personaje.
     for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
          for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){
               os << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
          }
          os << quienEsQuien.personajes[indice_personaje] << endl;
     }
     
     return os;
}

/**
* @brief Convierte un numero a un vector de bool que corresponde
*        con su representadon en binario con un numero de digitos
*              f i j o.
*
* @param n Numero a convertir en binario.
* @param digitos Numero de digitos de la representaddn binaria.
*
* @return Vector de booleanos con la representadon en binario de @e n
*      con el numero de elementos especificado por @e digitos.
*/
vector<bool> convertir_a_vector_bool(int n, int digitos) {
     vector<bool> ret;
     while(n) {
          if (n&1)
               ret.push_back(true);
          else
               ret.push_back(false);

          n>>=1;
     }

     while(ret.size()<digitos)
          ret.push_back(false);

     reverse(ret.begin(),ret.end());
     return ret;
}

bintree<Pregunta> QuienEsQuien::crear_arbol (vector<string> atributos,
                                             int indice_atributo,
                                             vector<string> personajes,
                                             vector<bool> personajes_restantes,
                                             vector<vector<bool>> tablero) {
     bintree<Pregunta> arbol;
     // Son los personajes con valor true en el vector de booleanos personajes_restantes
     int num_personajes = count(personajes_restantes.begin(),personajes_restantes.end(),true);

     if (num_personajes == 0) return arbol;  //Si no quedan más personajes devuelvo un arbol vacio

     // Caso en el que solo me queda un nodo hoja
     int pos_personaje = -1;
     bool encontrado = false;
     if (num_personajes == 1) {   // Si solo me quedan un personaje es un nodo hoja
          for(int i = 0; i < personajes_restantes.size() && !encontrado; ++i) {
               if (personajes_restantes[i]) {   // Extraigo su posición para conseguir el
                    pos_personaje = i;          // nombre del personaje
                    encontrado = true;
               }
               personajes_restantes[i] = false;
          }

          // Crear un nodo hoja con el nombre del personaje
          Pregunta preg_hoja(personajes[pos_personaje], num_personajes);

          arbol = bintree<Pregunta>(preg_hoja); // Crear un árbol con un único nodo
          return arbol; // Retornar el árbol hoja
     }

     // Inicializo los siguientes vectores booleanos para separar los personajes según cumplan el atributo actual o no
     vector<bool> personajes_cumplen(personajes_restantes.size(), false);
     vector<bool> personajes_no_cumplen(personajes_restantes.size(), false);

     for (int i = 0; i < personajes_restantes.size(); i++) {
          if (personajes_restantes[i]) {     // Divido según cumplan o no el atributo
               if (tablero[i][indice_atributo]) personajes_cumplen[i] = true;
               else personajes_no_cumplen[i] = true;
          }
     }

     MejorPregunta(personajes_cumplen, indice_atributo);
     // Crear el nodo actual con el atributo y el número total de personajes en esta rama
     Pregunta nodo_actual(atributos[indice_atributo], num_personajes);
     arbol = bintree<Pregunta>(nodo_actual);

     // Construir subárbol izquierdo (cumplen el atributo)
     bintree<Pregunta> subarbol_izq = crear_arbol(atributos, indice_atributo + 1, personajes, personajes_cumplen, tablero);

     arbol.insert_left(arbol.root(), subarbol_izq);

     // Construir subárbol derecho (no cumplen el atributo)
     bintree<Pregunta> subarbol_der = crear_arbol(atributos, indice_atributo + 1, personajes, personajes_no_cumplen, tablero);
     arbol.insert_right(arbol.root(), subarbol_der);

     return arbol;
}

bintree<Pregunta> QuienEsQuien::crear_arbol(){
     int indice_atributo = 0;
     vector<bool> personajes_restantes;
     for(vector<string>::iterator it = personajes.begin();it!=personajes.end();it++){
          personajes_restantes.push_back(true);
     }

     return crear_arbol( this->atributos, indice_atributo, this->personajes,
                         personajes_restantes, this->tablero);
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
     arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
     Ventana v(tg,con,"WisW");
     if (modo_graph){
          v.show();
     }

     nodo_actual = arbol.root(); // Se asigna como primera jugada el nodo raiz del árbol
     while ((*nodo_actual).obtener_num_personajes() != 1) { // Recorremos el árbol hasta llegar a un nodo hoja
          // Hacemos la pregunta asociada al nodo actual jugada_actual
          std::cout << "Pregunta: " << (*nodo_actual).obtener_pregunta() << std::endl;
          std::cout << "Responde 1 para Sí o 0 para No: ";

          bool respuesta;
          cin >> respuesta;

          if (respuesta) nodo_actual = nodo_actual.left();  // Respuesta afirmativa -> hijo izquierda
          else nodo_actual = nodo_actual.right();           // Respuesta negativa -> hijo derecha
     }

     // Si llegamos a un nodo hoja, identificamos el personaje
     // Los nodos hoja tienen como atributo el nombre del personaje según crear_arbol()
     cout << "¡Ya lo sé! Tu personaje es: " << (*nodo_actual).obtener_personaje() << std::endl;

     nodo_actual = arbol.root(); // Reiniciamos la jugada_actual al nodo raíz

     if (modo_graph){
          con->WriteText("Cuando completes QuienEsQuien, este mensaje lo podr�s quitar");
          char c;
     do {
          con->WriteText("Pulsa 0 para salir");
          c = con->ReadChar();

     } while (c!='0');

     }
     v.cerrar();
}	

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual) {
     // Caso 1: Nodo nulo
     if (jugada_actual.null()) return {}; // Devolver conjunto vacío

     // Caso 2: Nodo hoja asociado (tenemos un único personaje)
     if ((*jugada_actual).obtener_num_personajes() == 1) {
          set<string> personajes_levantados;
          personajes_levantados.insert((*jugada_actual).obtener_pregunta()); // Insertar el personaje
          return personajes_levantados;
     }

     // Caso 3: Nodo intermedio
     // Llamadas recursivas para los subárboles izquierdo y derecho
     set<string> personajes_izquierdo = informacion_jugada(jugada_actual.left());
     set<string> personajes_derecho = informacion_jugada(jugada_actual.right());

     // Combinar los resultados de ambos conjuntos
     personajes_izquierdo.insert(personajes_derecho.begin(), personajes_derecho.end());
     return personajes_izquierdo;
}

void escribir_esquema_arbol(ostream& ss, const bintree <Pregunta>& a,
                            bintree<Pregunta>::node n, string& pre){
     if (n.null())
          ss <<  pre <<  "-- x" <<  endl;
     else {
          ss <<  pre <<  "-- " <<  (*n) <<  endl;
          if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
               pre += "   |";
               escribir_esquema_arbol(ss,a, n.right(), pre);
               pre.replace(pre.size()-4, 4, "    ");
               escribir_esquema_arbol (ss,a, n.left(), pre);
               pre.erase(pre.size()-4, 4);
          }
     }
}

void QuienEsQuien::escribir_arbol_completo() const{
     string pre = "";
     escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}


// nodo_actual incializado a la raiz
// a lo mejor hay que usar el atrbibuto propio de la clase jugada_actual
void QuienEsQuien::eliminar_nodos_redundantes_recursiva(bintree<Pregunta>::node nodo_actual) {
     if (nodo_actual.null()) return;  // Si el nodo es nulo, no hay nada que hacer

     // Seguimos recorriendo los nodos que tinen hijos
     if (!nodo_actual.left().null()) eliminar_nodos_redundantes_recursiva(nodo_actual.left());
     if (!nodo_actual.right().null()) eliminar_nodos_redundantes_recursiva(nodo_actual.right());

     // Si el nodo tiene un solo hijo, hemos llegado a un nodo redundante
     bintree<Pregunta> subarbol;
     if (nodo_actual.left().null() && !nodo_actual.right().null()) {
          // No tiene hijo izquierdo ==> colgamos del padre el subárbol derecho
          subarbol.assign_subtree(arbol, nodo_actual.right());
          arbol.insert_left(nodo_actual.parent(), subarbol); // Reemplazar el nodo actual por el subárbol derecho
     }
     else if (!nodo_actual.left().null() && nodo_actual.right().null()) {
          // No tiene hijo derecha ==> colgamos del padre el subárbol izquierdo
          subarbol.assign_subtree(arbol, nodo_actual);
          arbol.insert_right(nodo_actual.parent(), subarbol);
     }
     // Si tiene ambos hijos, no es redundante, así que no hacemos nada
}

// La he creado para no modificar el main
void QuienEsQuien::eliminar_nodos_redundantes() {
     // Llamamos a la función recursiva para empezar desde la raíz del árbol
     eliminar_nodos_redundantes_recursiva(arbol.root());
}


void QuienEsQuien::profundidad_hojas(int profundidad, bintree<Pregunta>::node nivel_actual, vector<int>& prof_hojas) {
     if (nivel_actual.null()) return; //Si el nodo es nulo, terminamos

     if (nivel_actual.left().null() && nivel_actual.right().null()) { //Es un nodo hoja
          prof_hojas.push_back(profundidad); // Es una hojo
          return;
     }

     // Seguimos recorriendo las ramas, incrementando la profundidad
     profundidad++;
     profundidad_hojas(profundidad, nivel_actual.left(), prof_hojas);
     profundidad_hojas(profundidad, nivel_actual.right(), prof_hojas);
}

float QuienEsQuien::profundidad_promedio_hojas() {
     bintree<Pregunta>::node nivel_actual = arbol.root();
     vector<int> prof_hojas;

     // Comenzamos desde la raiz y con una profundidad=0;
     profundidad_hojas(0, nivel_actual, prof_hojas);

     // Si no hay hojas en el árbol, retornamos 0
     if (prof_hojas.empty()) return 0.0;

     // Calculamos el promedio de las profundidades
     float suma_prof = 0.0;
     for (vector<int>::iterator it=prof_hojas.begin(); it!=prof_hojas.end(); ++it) {
          suma_prof += (*it);     // Sumo todas las profundidades
     }
     //cout <<"suma_prof:" << suma_prof << endl;
     return static_cast<float>(suma_prof)/prof_hojas.size();  // Divido las profundidades entre num_hijos ==>
}                                                             // Promedio de profundidades

/**
* @brief Genera numero enteros positivos aleatorios en el rango [min,max].
**/
int generaEntero(int min, int max){
     int tam= max-min;
     return ((rand( )%tam)+min) ;
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
     srand(0);
     this->limpiar();
     float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);
     int numero_de_atributos = ceil(log_2_numero_de_personajes);

     cout <<  "Peticion para generar " <<  numero_de_personajes << " personajes ";
     cout <<  "con " << numero_de_atributos <<  " atributos" << endl;
     cout <<  "Paso 1: generar " <<  pow(2, numero_de_atributos) <<  " personajes" << endl;

     //Fase 1: completar el tablero con todos los personajes posibles
     //Complete el tablero y los nombres de personajes a la vez
     for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
          vector<bool> atributos_personaje =
                                    convertir_a_vector_bool(indice_personaje,numero_de_atributos);
          string nombre_personaje = "Personaje_"+to_string(indice_personaje);

          this->personajes.push_back(nombre_personaje);
          this->tablero.push_back(atributos_personaje);
     }

     // Completo los nombres de los atributos.
     for( int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
          string nombre_atributo = "Atributo_"+to_string(indice_atributo);
          this->atributos.push_back(nombre_atributo);
     }
     cout <<  "Paso 2: eliminar " << (pow(2,numero_de_atributos)-numero_de_personajes) <<  "personajes" << endl;

     //Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
     while(personajes.size()>numero_de_personajes){
          int personaje_a_eliminar = generaEntero(0,personajes.size());
          personajes.erase(personajes.begin()+personaje_a_eliminar);
          tablero.erase(tablero.begin()+personaje_a_eliminar);
     }
}
void QuienEsQuien::ocultar_personajes_graph(const set<string> &personajes_activos){
    //ocultamos los personajes
    int idx=0;
    int ncols=tg->getNcols();
    for (auto it=personajes.begin();it!=personajes.end();++it,idx++){
        if ( personajes_activos.find(*it)==personajes_activos.end())
            tg->putImagen(idx/ncols,idx%ncols,imagen_ocultar.c_str());
    }
}


void QuienEsQuien::setImagenOcultar(const char * n){
    imagen_ocultar=n;
}

void QuienEsQuien::setModoGraph(bool m){
    modo_graph=m;
}

void QuienEsQuien::preguntas_formuladas (bintree<Pregunta>::node jugada) {
     while (jugada != arbol.root()) { // Siguen quedando preguntas formuladas
          string atributo = (*jugada.parent()).obtener_pregunta();
          cout << atributo << " - ";

          if (jugada == jugada.parent().left()) cout << "si" << endl;
          else cout << "no" << endl;

          jugada = jugada.parent();     // Ascendemos un nível
     }
}

void QuienEsQuien:: aniade_personaje (string nombre, vector<bool> caracteristicas,string nombre_imagen_personaje) {
     bintree<Pregunta>::node nodo_actual=arbol.root(); // Empezamos recorriendo el arbol por la raiz

     for(int pos_caracteristicas = 0; pos_caracteristicas < caracteristicas.size()-1; ++pos_caracteristicas) {
          if (caracteristicas[pos_caracteristicas])
               nodo_actual = nodo_actual.left(); // El personaje cumple la caracteristica ==> me voy a la izquierda
          else
               nodo_actual = nodo_actual.right(); // El personaje no cumple la caracteristica ==> me voy a la derecha
     }

     // Creamos las nuevas estructuras, nodos, que necitamos
     // 1) El nodo hoja que estaba en el arbol
     // 2) El nuevo personaje que se añade
     Pregunta preg_hoja = *nodo_actual; // Tiene el valor de su padre
     Pregunta preg_nueva(nombre, 1);

     bintree<Pregunta>::node nodo_hoja, nodo_nuevo;
     *nodo_hoja = preg_hoja;
     *nodo_nuevo = preg_nueva;

     // Una vez que hemos salido del bucle estamos en el padre del nodo hoja, nuestro nuevo personaje y el nodo hoja
     // cumplen caracteristicas[caracteristicas.size()-2] pero difieren en caracteristicas[caracteristicas.size()-1]
     if (caracteristicas[caracteristicas.size()-1]) {
          // Nuevo personaje se añade a la izquierda y el nodo hoja que estaba es el hijo derecha
          nodo_actual.left() = nodo_nuevo;
          nodo_actual.right() = nodo_hoja;
     }
     else {
          // Nuevo personaje se añade a la derecha y el nodo hoja que estaba es el hijo izquierda
          nodo_actual.right() = nodo_nuevo;
          nodo_actual.left() = nodo_hoja;
     }

     // 3) EL nuevo padre pues hay que modificar el atributo que antes era el nombre del personaje correspondiente
     // al nodo hijo que estaba por la nueva pregunta
     Pregunta pregunta_padre(atributos[caracteristicas.size()-1], 2);
     *nodo_actual = pregunta_padre;
}

void QuienEsQuien::elimina_personaje (string nombre) {
     bintree<Pregunta>::node nodo_actual=arbol.root(); // Empezamos recorriendo el arbol por la raiz

     // Buscamos la posicion del nombre en el vector de string personajes
     bool encontrado = false;
     int pos_personaje = 0;
     while (!encontrado) {
          if (personajes[pos_personaje] == nombre) encontrado = true;
          else pos_personaje++;
     }

     for (int pos_caracteristicas = 0; pos_caracteristicas< atributos.size()-1; ++pos_caracteristicas) {
          if (tablero[pos_personaje][pos_caracteristicas])
               nodo_actual = nodo_actual.left(); // El personaje cumple la caracteristica ==> me voy a la izquierda
          else
               nodo_actual = nodo_actual.right(); // El personaje no cumple la caracteristica ==> me voy a la derecha
     }

     // Creamos las nuevas estructuras, nodos, que necitamos
     // 1) El nombre asociado al nodo hoja que se mantiene en el arbol y que reemplaza al padre
     string nombre_reemplazo;

     // Una vez que hemos salido del bucle estamos en el padre del nodo hoja que queremos borrar
     if (tablero[pos_personaje][atributos.size()-1]) {
          // El personaje que borramos cumplia la ulrima caracteristicas==> hijo izquierda
          nombre_reemplazo = (*nodo_actual.right()).obtener_pregunta();
          nodo_actual.left().remove();  // Personaje que se quiere borrar
          nodo_actual.right().remove(); // Persnaje que reemplaza al padre
     }
     else {
          // El perosnaje que borramos no cumplia la ulrima caracteristicas==> hijo derecha
          nombre_reemplazo = (*nodo_actual.left()).obtener_pregunta();
          nodo_actual.right().remove(); // Personaje que se quiere borrar
          nodo_actual.left().remove();  // Persnaje que reemplaza al padre
     }

     // 3) EL nuevo padre pues hay que modificar el atributo que antes era la pregunta por el nombre del personaje
     // correspondiente al nodo hijo que sobrevive en el arbol
     Pregunta pregunta_padre(nombre_reemplazo, 1);
     *nodo_actual = pregunta_padre;
}

void QuienEsQuien::MejorPregunta(const vector<bool>& personajes_restantes, int indice_atributo) {
     // Notemos que solo se contabilizaran las posiciones de los personajes que aún queden vivos
     // personajes_restantes[i] = true, i poisicion del perosnaje que sigue vive en el vector<string> personajes
     int num_personajes_vivos = count(personajes_restantes.begin(), personajes_restantes.end(), true);
     if (num_personajes_vivos % 2 == 1) num_personajes_vivos++;

     int contador = 0; // Contabiliza los trues del tablero dada una pregunta y los personajes que quedan
     int mejor_contador = 0;
     string mejor_atributo;   // Mejor atributo por el que preguntar

     // No haria falta seguir en el bucle si encontramos un contador de trues igual a num_personajes_vivos/2
     int pos_atrib = indice_atributo;   // Controlamos no repetir preguntasd
     while (pos_atrib < atributos.size() && mejor_contador!= num_personajes_vivos/2) {
          for (int j=0; j < personajes.size(); j++) {
               // Mientras que el personaje siga vivo y tablero sea true
               if (personajes_restantes[j] && tablero[j][pos_atrib])
                    contador++;
          }

          if (contador > mejor_contador && contador <= num_personajes_vivos/2) {
               //Hemos encontrado la mejor pregunta
               mejor_atributo = atributos[pos_atrib];
               mejor_contador = contador;
          }
          else {
               pos_atrib++; // Sigo por el siguiente
               contador = 0;  // actualizo contador para la siguiente vuelta
          }
     }

     // Como solución modificamos el orden de atributos de manera que el mejor atributo, ocupe la posiicon siguiente en
     // el vector a la pregunta realizada con anteorioridad
     atributos[pos_atrib] = atributos[indice_atributo];
     atributos[indice_atributo] = mejor_atributo;
}
