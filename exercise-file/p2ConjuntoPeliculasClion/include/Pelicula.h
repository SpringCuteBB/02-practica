/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Pelicula.h
 */

/**
 * @class Pelicula
 * @brief Esta clase almacena la información referente a una película. Dicha información consta de:
 *         id de la película, nombre de la película, valoración de imdb, género y año de estreno. 
 */
#ifndef PELICULA_H
#define PELICULA_H

#include <string>

using namespace std;

class Pelicula {
public:
    /**
     * @brief Inicia los valores de la película a valores no válidos pero identificables.
     * Este constructor se utilizará sobre todo para poder crear un vector de Peliculas y poder trabajar con él. 
     * por el programa(película vacía). 
     */
    Pelicula();
    
    /**
     * @brief Crea un nuevo objeto película inicializando todos los valores de las variables que lo componen. 
     * @param newid id de la película. Debe de ser un valor único para cada película. 
     * @param newnombre nombre de la película. 
     * @param newanio año de estreno de la película. 
     * @param newvaloracion valoración en la base de datos IMDB de la película.
     * @param newgenero genéro de la película. 
     */
    Pelicula(int newid, string newnombre, int newanio, float newvaloracion, string newgenero);
    
    /**
     * @brief Constructor de copia. Como no hay variables con memoria dinámica no hace falta implementarlo. 
     * @param orig
     */
    Pelicula(const Pelicula& orig);
    
    /**
     * @brief Genera un string que contiene todos los valores de las variables del objeto Película separados por espacios.
     *  El objetivo de este método es poder generar un string que poder mostrar por pantalla.
     * @return Devuelve un string conteniendo los siguientes datos: "id nombre género año valoración". 
     */
    string to_string();
    
    /**
     * @brief Destructor del objeto película. Como no hay ahora mismo datos que usen memoria dinámica no hay que implementarlo.
     */
    ~Pelicula();
    
    /**
     * @brief Modifica el id de la película. 
     * @return Devuelve una referencia al entero id que permite modificar su valor.
     */
    int & setId();
    
    /**
     * @brief Modifica el nombre de la película
     * @return Devuelve una referencia al string nombre que permite modificar su valor.
     */
    string & setNombre();
    
    /**
     * @brief Modifica la valoración IMDB de la película 
     * @return Devuelve una referencia al flotante valoracion que permite modificar su valor.
     */
    float & setValoracion();
    
    /**
     * @brief Modifica el género asociado a la película
     * @return Devuelve una referencia al string genero que permite modificar su valor.
     */
    string & setGenero();
    
    /**
     * @brief Modifica el año de estreno de la película
     * @return Devuelve una referencia al valor de año que permite modificar su valor. 
     */
    int & setAnio();
    
    /**
     * @brief Devuelve el id de la película. 
     * @return Valor entero que contiene el id de la película. 
     */
    int getId();
    
    /**
     * @brief Devuelve el nombre de la película.
     * @return String que contiene el nombre de la película. 
     */
    string getNombre();
    
    /**
     * @brief Devuelve el género de la película
     * @return string que contiene el género al que está asociado la película. 
     */
    string getGenero();
    
    /**
     * @brief Devuelve un entero con el año en que fue estrenada la película.
     * @return Entero que contiene el año en que se estrenó la película. 
     */
    int getAnio();
    
    /**
     * @brief Devuelve un valor flotante que contiene la valoración IMDB de la película. 
     * @return Flotante en el intervalo [0,10] que contiene la valoración. 
     */
    float getValoracion();
private:
    int id;
    string nombre;
    float valoracion;
    string genero;
    int anio;
    
};

#endif /* PELICULA_H */

