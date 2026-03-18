/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   ConjuntoPeliculas.h
 * 
 */

/**
 * @class ConjuntoPeliculas
 * 
 * @brief Esta clase almacena un vector cuyo objetivo es representar un conjunto de objetos Película.
 *        Posteriormente, utilizaremos esta clase para almacenar las películas sobre las que construiremos nuestro
 *        sistema de recomendación. Esta primera versión utiliza memoria estática con lo que tenemos las siguientes
 *        variables miembro:
 *        reservado: Espacio en memoria reservado durante todo el programa para almacenar las películas.
 *        conj: Vector de objetos películas que almacena las películas. El número máximo de películas a almacenar lo 
 *        define la variable reservado.
 *        numpeliculas: Número de películas que tiene en cada momento el vector conj. 
 */

#ifndef CONJUNTOPELICULAS_H
#define CONJUNTOPELICULAS_H

#include "Pelicula.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class ConjuntoPeliculas {
public:
    /**
     * @brief Constructor por defecto de la clase. Genera un vector vacío, sin ninguna película almacenada.
     */
    ConjuntoPeliculas();
    
    /**
     * @brief Constructor de copia. Si el vector es estático, no hace falta implementarla. 
     * @param orig
     */
    ConjuntoPeliculas(const ConjuntoPeliculas& orig);
    
    /**
     * @brief Este método lee numdatos películas y las almacena en el vector de películas. Si el vector contuviera
     * alguna película previamente, entonces lo vaciamos. En posteriores versiones no estáticas de este método quitaremos la 
     * varaible numdatos permitiendo que se agreguen todas las peliculas que haya almacenadas en un fichero. Además, permitiremos
     * que se agruegue información de varios ficheros sin borrar la información que ya hubiera previamente.
     * @param rutaFichero ruta del fichero que contiene la información de las películas a almacenar en el objeto. 
     * @param numdatos Número de películas que vamos a leer de ese fichero (siempre leeremos las numdatos primeras películas almacenadas). 
     */
    void leerFichero(string rutaFichero, int numdatos);
    
    /**
     * @brief Destructor de la clase ConjuntoPeliculas. Sólo es necesario implementarlo si se usa memoria dinámica. 
     */
    ~ConjuntoPeliculas();
    
    /**
     * @brief Aniade una nueva película al vector de películas. La película se añade en la siguiente 
     * posición libre del vector. El método tiene como entradas todas las variables que definirán la nueva
     * película.  
     * @param newid id de la película a introducir. 
     * @param newnombre nombre de la película a introducir. 
     * @param newanio año de la película a introducir. 
     * @param newvaloracion valoración IMDB de la película a introducir. 
     * @param newgenero género de la película a introducir. 
     */
    void aniadePelicula(int newid, string newnombre, int newanio, float newvaloracion,string newgenero);
    
    /**
     * @brief Genera un string que contiene toda la información de todas las películas contenidas en el vector. 
     *  El objetivo de este método es poder generar un string que poder mostrar por pantalla.
     * @return Devuelve un string en donde se muestra una película en cada línea. 
     * (Las películas se separan por el caracter \n). 
     * Puede usarse el to_string de la clase Película dentro de este método.   
     */
    string to_string();
    
    /**
     * @brief Almacena las películas que hay almacenadas en el vector en un fichero csv. El fichero csv generado debe seguir
     * exactamente el mismo formato que el que tiene el fichero de entrada utilizado en la práctica. Por tanto, el fichero 
     * que genera el método escribeFichero debe de ser capaz de ser leído por el método leerFichero. 
     * @param rutaFichero Ruta en donde queremos que se almacene el fichero generado. 
     */
    void escribeFichero(string rutaFichero);
    
    /**
     * @brief Ordena las películas del vector conj de mayor a menor puntuación IMDB (utilizando la variable valoración). 
     * Este método funciona sobre el propio vector del objeto con lo cual no se generar ningún vector aparte y el orden 
     * previo que hubiera se pierde. 
     */
    void ordenaporranking();
    
    /**
     * @brief Elimina una única película del vector de películas. Concretamente la que tenga el id indicado. Si no hubiera
     * ninguna película con el id introducido, entonces el método no hace nada. 
     * @param id de la película que queremos eliminar. 
     */
    void borrar(int id);
    
    /**
     * @brief Devuelve un objeto película del vector de películas. Concretamente, aquella que tenga como id la indicada como 
     * parámetro. 
     * @param id id de la película a obtener. 
     * @return Devuelve el objeto película que tenga la id indicada. Si no existiera, se devuelve una película vacía. 
     */
    Pelicula at(int id);
    
    /**
     * @brief Elimina toda la información del vector. Dependiendo de si el vector es estático o dinámico la implementación varía. 
     */
    void clear();
    
private:
    static const int reservado=100;
    Pelicula conj[reservado];
    int numpeliculas=0;
    
    
};

#endif /* CONJUNTOPELICULAS_H */

