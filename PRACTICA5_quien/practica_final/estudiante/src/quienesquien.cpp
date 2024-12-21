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
     // Numero de personajes que quedan en la rama
     int num_personajes = count(personajes_restantes.begin(),personajes_restantes.end(),true);

     if (num_personajes == 0) return arbol;  //Si no quedan más personajes devuelvo un arbol vacio

     // Caso en el que solo me queda un nodo hoja
     if (num_personajes == 1) {   // Si solo me quedan un personaje es un nodo hoja
          int pos_personaje = 0;
          bool encontrado = false;

          while (!encontrado && pos_personaje < personajes_restantes.size()) {
               if(personajes_restantes[pos_personaje]) encontrado = true;
               else pos_personaje++;
          }

          if (encontrado) {
               personajes_restantes[pos_personaje] = false;      // Actualizo personajes_restantes
               Pregunta preg_hoja(personajes[pos_personaje], num_personajes);   // Creo una pregunta con el nombre
                                                                                  // del personaje
               arbol = bintree<Pregunta>(preg_hoja);
          }
          return arbol; // Retornar el árbol hoja o vacio en caso de que no se haya encontrado el personaje
     }

     MejorPregunta(personajes_restantes, indice_atributo);   // Modifica this->atributos y this->tablero
     tablero = this->tablero;                                // con el mejor orden
     atributos = this->atributos;

     // Inicializo los siguientes vectores booleanos para separar los personajes según cumplan el atributo actual o no
     vector<bool> personajes_cumplen(personajes_restantes.size(), false);
     vector<bool> personajes_no_cumplen(personajes_restantes.size(), false);

     for (int i = 0; i < personajes_restantes.size(); i++) {
          if (personajes_restantes[i]) {     // Divido según cumplan o no el atributo
               if (tablero[i][indice_atributo]) personajes_cumplen[i] = true;
               else personajes_no_cumplen[i] = true;
          }
     }

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

     // Prueba de aniade_personaje
     /*string nombre="prueba";
     vector<bool> caracteristicas={1, 0, 1,1}; //Es mujer, no tiene ojos marrones, si tiene gafas(para distinguirlo de Ana)
     string nombre_imagen_personaje = "prueba_aniade";
     aniade_personaje(nombre, caracteristicas,nombre_imagen_personaje);
     escribir_arbol_completo();
     cout << endl;

     //Prueba para elimina_personaje
     elimina_personaje(nombre);
     escribir_arbol_completo();*/

     nodo_actual = arbol.root();   // Se asigna como nodo actual la raiz del árbol
     while (!(*nodo_actual).es_personaje()) { // Recorremos el árbol hasta llegar a un nodo hoja
          //Prueba informacion_jugada
          /*set<string> personajes_restantes = informacion_jugada(nodo_actual);
          cout << "Personajes restantes:\n";
          for (const auto& personaje : personajes_restantes) {
               cout << "- " << personaje << "\n";
          }*/
          // Hacemos la pregunta asociada al nodo actual jugada_actual
          std::cout << "Pregunta: " << (*nodo_actual).obtener_pregunta() << std::endl;
          string resp;
          do {
               std::cout << "Responde 1 para Sí o 0 para No: ";
               cin >> resp;
          }while (resp != "0" && resp != "1");

          int respuesta = stoi(resp);

          if (respuesta) nodo_actual = nodo_actual.left();  // Respuesta afirmativa -> hijo izquierda
          else nodo_actual = nodo_actual.right();           // Respuesta negativa -> hijo derecha

          //preguntas_formuladas(nodo_actual);    //Para probar preguntas_formuladas descomentar
     }

     // Si llegamos a un nodo hoja, identificamos el personaje
     cout << "¡Ya lo sé! Tu personaje es: " << (*nodo_actual).obtener_personaje() << std::endl;

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
     if (jugada_actual.null()) return {}; // Es un nodo nulo devolvemos el conjunto vacío

     if ((*jugada_actual).es_personaje()) { // Es un nodo hoja==> un único personaje
          set<string> personajes_levantados;
          personajes_levantados.insert((*jugada_actual).obtener_pregunta()); // Insertar el personaje
          return personajes_levantados;
     }

     // Es un nodo intermedio llamo recursivamente con el subárbol izquierdo y derecho
     set<string> personajes_izquierdo = informacion_jugada(jugada_actual.left());
     set<string> personajes_derecho = informacion_jugada(jugada_actual.right());

     // Combinar los resultados de ambos conjuntos(derecho e izquierdo)
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

QuienEsQuien::eliminar_nodos_redundantes_recursiva(bintree<Pregunta>::node nodo_actual) {
     if (nodo_actual.null()) return; // Si el nodo es nulo, no hacemos nada

     if (nodo_actual.left().null() && nodo_actual.right().null()) return; // Si es nodo hoja(personaje), no hacemos nada

     // Si tiene ambos hijos, no es redundante, seguimos recorriendo el arbol
     if (!nodo_actual.left().null() && !nodo_actual.right().null()) {
          eliminar_nodos_redundantes_recursiva(nodo_actual.left());
          eliminar_nodos_redundantes_recursiva(nodo_actual.right());
          return;   // Para que si el nodo no es redundante no ejecute el resto del código
     }

     bintree<Pregunta> subarbol, rama_izq, rama_dcha;
     bintree<Pregunta>::node siguiente_nodo;

     // Nodo con un solo hijo derecha, hemos encontrado un nodo redundante
     if (nodo_actual.left().null() && !nodo_actual.right().null())
          siguiente_nodo = nodo_actual.right();

     // Nodo con un solo hijo izquierda, hemos encontrado un nodo redundante
     else siguiente_nodo = nodo_actual.left();

     // Construimos el subarbol
     subarbol = bintree<Pregunta>(*siguiente_nodo); // Asignamos la nueva raiz del subarbol
     if (!siguiente_nodo.left().null()) {
          arbol.prune_left(siguiente_nodo, rama_izq);       // Conseguimos la rama izquierda
          subarbol.insert_left(subarbol.root(), rama_izq);  // Construimos el subarbol con la rama podada
     }
     if (!siguiente_nodo.right().null()) {
          arbol.prune_right(siguiente_nodo, rama_dcha);          // Conseguimos la rama derecha
          subarbol.insert_right(subarbol.root(), rama_dcha);     // Construimos el subarbol con la rama podada
     }

     // Hacemos el reemplazo de subarbol
     bintree<Pregunta>::node padre = nodo_actual.parent();

     if (nodo_actual == nodo_actual.parent().right()) {     // Si el nodo redundante era hijo derecha
          arbol.insert_right(padre, subarbol);
          nodo_actual=padre.right(); // Recuperamos el nodo actual
     }
     else {    // Si el nodo redundante era hijo izquierda
          arbol.insert_left(padre, subarbol);
          nodo_actual=padre.left(); // Recuperamos el nodo actual
     }

     eliminar_nodos_redundantes_recursiva(nodo_actual); // Continuar con el nuevo nodo
}


void QuienEsQuien::eliminar_nodos_redundantes() {
     // Llamamos a la función recursiva para empezar desde la raíz del árbol
     eliminar_nodos_redundantes_recursiva(arbol.root());
}

void QuienEsQuien::profundidad_hojas(int profundidad, bintree<Pregunta>::node nodo_actual, vector<int>& prof_hojas) {
     if (nodo_actual.null()) return; //Si el nodo es nulo, terminamos

     if (nodo_actual.left().null() && nodo_actual.right().null()) // Si es un nodo hoja
          prof_hojas.push_back(profundidad);

     // Seguimos recorriendo las ramas, incrementando la profundidad
     profundidad_hojas(profundidad+1, nodo_actual.left(), prof_hojas);
     profundidad_hojas(profundidad+1, nodo_actual.right(), prof_hojas);
}

float QuienEsQuien::profundidad_promedio_hojas() {
     bintree<Pregunta>::node nodo_actual = arbol.root();
     vector<int> prof_hojas;

     // Comenzamos desde la raiz y con una profundidad=0;
     profundidad_hojas(0, nodo_actual, prof_hojas);

     if (prof_hojas.empty()) return 0.0;     // Si no hay hojas en el árbol, retornamos 0

     float suma_prof = 0.0;
     for (auto it:prof_hojas) suma_prof += it;     // Sumo todas las profundidades

     return static_cast<float>(suma_prof)/prof_hojas.size();  // Devolvemos el promedio de las profundidades
}

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
     if (!jugada.left().null() || !jugada.right().null()) { // Si no es un nodo hoja, es decir, aún no se el personaje
          cout << endl << "El personaje oculto tiene las siguientes características:" << endl;

          while (jugada != arbol.root()) { // Siguen quedando preguntas formuladas
               string atributo = (*jugada.parent()).obtener_pregunta();
               cout << "\t" << atributo << " - ";

               if (jugada == jugada.parent().left()) cout << "si" << endl; // Si era hijo a la izquierda cumplia el atributo
               else cout << "no" << endl;    // Si era hijo a la derecha no lo cumplia

               jugada = jugada.parent();     // Ascendemos un nível
          }
          cout <<"\tpero aún no sé cuál es." << endl<< endl;
     }
}

void QuienEsQuien:: aniade_personaje (string nombre, vector<bool> caracteristicas, string nombre_imagen_personaje) {
     bintree<Pregunta>::node nodo_actual=arbol.root(); // Empezamos recorriendo el arbol por la raiz

     int pos_caracteristicas=0;
     while (pos_caracteristicas<caracteristicas.size() && !nodo_actual.left().null() || !nodo_actual.right().null()) {
          Pregunta pregunta_nueva;

          // Modifico cada nodo añadiendo un personaje a num_personajes
          if ((*nodo_actual).es_personaje()) {
               Pregunta preg((*nodo_actual).obtener_personaje(), (*nodo_actual).obtener_num_personajes()+1);
               pregunta_nueva = preg;
          }
          else {
               Pregunta preg((*nodo_actual).obtener_pregunta(), (*nodo_actual).obtener_num_personajes()+1);
               pregunta_nueva = preg;
          }
          *nodo_actual = pregunta_nueva;

          if (caracteristicas[pos_caracteristicas]) nodo_actual = nodo_actual.left(); // El personaje cumple atributo ==> hijo izquierda
          else nodo_actual = nodo_actual.right(); // El personaje no cumple atributo ==> hijo derecha

          ++pos_caracteristicas;
     }

     // Una vez que hemos salido del bucle estamos en el padre del nodo hoja, nuestro nuevo personaje y el nodo hoja
     // iguales caracteristicas difiriendo en caracteristicas[pos_caracteristicas+1]

     // Creamos las nuevas estructuras
     Pregunta preg_hoja = (*nodo_actual);              // La pregunta correspondiente al nodo hoja que estaba en el arbol
     Pregunta preg_nueva(nombre, 1);    // La pregunta correspondiente al nuevo personaje que se añade

     bintree<Pregunta>subarbol_dcho, subarbol_izq;     // Creamos dos árboles cada uno con un único nodo
     if (caracteristicas[pos_caracteristicas+1]) {
          subarbol_izq = bintree<Pregunta>(preg_nueva); // Nuevo personaje cumple la ultima caracteristica ==> hijo izquierda
          subarbol_dcho = bintree<Pregunta>(preg_hoja); // El personaje que ya estaba no la cumple ==> hijo derecha
     }
     else {
          subarbol_dcho = bintree<Pregunta>(preg_nueva); // Nuevo personaje no cumple la ultima caracteristica ==> hijo derecha
          subarbol_izq = bintree<Pregunta>(preg_hoja); // El personaje que ya estaba si la cumple ==> hijo izquierda
     }

     //Inserto los subarboles desde el nodo_actual que es el nodo que actua como padre de los dos nodos creados
     arbol.insert_left(nodo_actual, subarbol_izq);
     arbol.insert_right(nodo_actual, subarbol_dcho);

     // Modificamos el padre, el atributo del padre es la nueva pregunta en la difieren ambos personajes
     Pregunta pregunta_padre(atributos[pos_caracteristicas+1], 2);
     (*nodo_actual) = pregunta_padre;

     // Actualizamos this->personajes y this->tablero con el nombre del nuevo personaje y con sus caracteristicas
     personajes.push_back(nombre);
     tablero.push_back(caracteristicas);
}

void QuienEsQuien::elimina_personaje (string nombre) {
     bintree<Pregunta>::node nodo_actual=arbol.root(); // Empezamos recorriendo el arbol por la raiz

     // Buscamos la posicion del nombre del personaje que queremos borrar en this->personajes
     bool encontrado = false;
     int pos_personaje = 0;
     while (!encontrado && pos_personaje < personajes.size()) {
          if (personajes[pos_personaje] == nombre) encontrado = true;
          else pos_personaje++;
     }
     if (!encontrado) return; //No hacemos nada

     //Formamos el vector de caracteristicas correspondiente al personaje que borramos para luego actualizar tablero
     vector<bool> caracteristicas;
     int pos_caracteristicas = 0;

     // Nos desplazamos hasta el nodo correspondiente al personaje que queremos borrar
     while (pos_caracteristicas< atributos.size() && !nodo_actual.left().null() || !nodo_actual.right().null()){

          //Modifico cada nodo quitando el personaje
          Pregunta pregunta_nueva((*nodo_actual).obtener_pregunta(), (*nodo_actual).obtener_num_personajes()-1);
          *nodo_actual =  pregunta_nueva;

          if (tablero[pos_personaje][pos_caracteristicas]) {
               nodo_actual = nodo_actual.left(); // El personaje cumple la caracteristica ==> me voy a la izquierda
               caracteristicas.push_back(true);
          }
          else {
               nodo_actual = nodo_actual.right(); // El personaje no cumple la caracteristica ==> me voy a la derecha
               caracteristicas.push_back(false);
          }

          ++pos_caracteristicas;
     }

     bintree<Pregunta>::node nodo_padre(nodo_actual.parent()); //Nos desplazamos hacia el padre del nodo hoja que queremos borrar
     string nombre_reemplazo; // Nombre asociado al nodo hoja que reemplaza al padre

     if (tablero[pos_personaje][pos_caracteristicas]) {
          // El personaje que borramos cumplia la ultima caracteristica==> hijo izquierda
          nombre_reemplazo = (*nodo_padre.right()).obtener_personaje(); // Obtenemos el nombre de su hermano==> hijo dcha
     }
     else {
          // El personaje que borramos no cumplia la ultima caracteristica==> hijo derecha
          nombre_reemplazo = (*nodo_padre.left()).obtener_personaje(); // Obtenemos el nombre de su hermano==> hijo izq
     }

     nodo_actual.left().remove();  // Borro los dos hijos del padre
     nodo_actual.right().remove();

     // Modificamos el atributo del padre por el nombre del prsonaje qe lo reemplaza
     Pregunta pregunta_reemplazo(nombre_reemplazo, 1);

     bintree<Pregunta>subarbol_reemplazo(pregunta_reemplazo);    //Creamos el subarbol
     bintree<Pregunta>::node nodo_abuelo = nodo_padre.parent();

     if (nodo_padre == nodo_abuelo.left())   // Si el padre era hijo izquierda
          arbol.insert_left(nodo_abuelo, subarbol_reemplazo);
     else                                    // Si el padre era hijo derecha
          arbol.insert_right(nodo_abuelo, subarbol_reemplazo);

     // Actualizamos this->personajes y this->tablero
     personajes.erase(personajes.begin() + pos_personaje);  // Elimino el nombre del personaje

     // Encuentro la fila que coincide con 'caracteristicas' y la elimino de this->tablero
     auto it = std::find(tablero.begin(), tablero.end(), caracteristicas);
     if (it != tablero.end())  tablero.erase(it);
}

void QuienEsQuien::reorganizar_tablero(int pos_mejor_atributo, int indice_atributo) {
     //Intercambio this->atributos para formular la mejor pregunta
     swap(atributos[indice_atributo], atributos[pos_mejor_atributo]);

     for (auto& fila : tablero)  // Intercambiar las columnas correspondientes en this->tablero
          swap(fila[indice_atributo], fila[pos_mejor_atributo]);
}

void QuienEsQuien::MejorPregunta(const vector<bool>& personajes_restantes, int indice_atributo) {
     // Notemos que solo se contabilizaran las posiciones de los personajes que aún queden vivos
     // personajes_restantes[i] = true, i poisicion del personaje que sigue vive en this->personajes
     int num_personajes_vivos = count(personajes_restantes.begin(), personajes_restantes.end(), true);

     int contador = 0; // Contabiliza los trues del tablero dada una pregunta teniendo en cuenta solo los personajes vivos
     int pos_mejor_atributo;  // Posicion ocupada por el mejor atributo por el que preguntar

     int pos_atributo = indice_atributo;   // Controlamos no repetir preguntas
     bool mejor_pregunta_encontrada = false;

     int i = 0;     // Variabel que nos ayuda a calcular mejor_pregunta_encontrada
     while (pos_atributo < atributos.size() && !mejor_pregunta_encontrada) {
          cout << atributos[pos_atributo]<<endl;
          for (int j=0; j < personajes.size(); j++)  // Mientras que el personaje siga vivo y tablero sea true
               if (personajes_restantes[j] && tablero[j][pos_atributo]) contador++;

          if (contador == 1) return; // Solo queda un personaje vivo que verifica el atributo que toca, no hacemos nada

          // No haria falta seguir en el bucle si encontramos un contador de trues/falses igual a num_personajes_vivos/2
          // USO del i: En cada iteración hacemos que se compare este numero de trues/falses con una unidad inferior
          mejor_pregunta_encontrada = contador == (num_personajes_vivos/2-i) ||
                                        (num_personajes_vivos-contador) == (num_personajes_vivos/2-i);
          // Hemos encontrado la mejor pregunta
          if (mejor_pregunta_encontrada) pos_mejor_atributo =  pos_atributo;
          else {
               ++i;
               ++pos_atributo; // Sigo por el siguiente
               contador = 0;  // Actualizo contador para la siguiente iteración
          }
     }

     string mejor_atributo = atributos[pos_mejor_atributo]; // Mejor atributo por el que preguntar
     if (mejor_atributo.empty()) return;     // Si no se encontro mejor_atributo no hacer nada

     // Como solución modificamos el orden de atributos de manera que el mejor atributo, ocupe la posicon siguiente en
     // el vector a la pregunta realizada con anteorioridad. Por consecuente tambien se modifican las filas del tablero
     reorganizar_tablero(pos_mejor_atributo, indice_atributo);  // Modificamos this->tablero y this->atributos
}