/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Pelicula.cpp
 * 
 */

#include "Pelicula.h"
#include <sstream>

Pelicula::Pelicula() : id(-1), nombre(""), valoracion(-1.0f), genero(""), anio(-1) {
	// Constructor por defecto: inicializa campos con valores indicativos "vacíos".
}

Pelicula::Pelicula(int newid, string newnombre, int newanio, float newvaloracion, string newgenero)
: id(newid), nombre(newnombre), valoracion(newvaloracion), genero(newgenero), anio(newanio)
{
		// Constructor parametrizado: inicializa la película con los datos proporcionados.
}
  
Pelicula::Pelicula(const Pelicula& orig)
: id(orig.id), nombre(orig.nombre), valoracion(orig.valoracion), genero(orig.genero), anio(orig.anio)
{
		// Constructor copia: copia todos los campos desde `orig`.
}

string Pelicula::to_string(){
	std::ostringstream oss;
	oss << id << " " << nombre << " " << genero << " " << anio << " " << valoracion;
	return oss.str();
}

void Pelicula::setId(int newid){
	id = newid;
}

void Pelicula::setNombre(const string &newnombre){
    nombre = newnombre;
}

void Pelicula::setValoracion(float newvaloracion){
    valoracion = newvaloracion;
}

void Pelicula::setGenero(const string &newgenero){
    genero = newgenero;
}

void Pelicula::setAnio(int newanio){
    anio = newanio;
}

Pelicula::~Pelicula() {
	// Destructor: no requiere acciones especiales (manejo automático).
}

int Pelicula::getId(){
	// Devuelve el identificador de la película.
	return id;
}

string Pelicula::getNombre(){
	// Devuelve el título/nombre de la película.
	 return nombre;
}       

string Pelicula::getGenero(){
	// Devuelve el género de la película.
	 return genero;
}

int Pelicula::getAnio(){
	// Devuelve el año de estreno.
	 return anio;
}

float Pelicula::getValoracion(){
	// Devuelve la valoración/nota de la película.
	return valoracion;
}
