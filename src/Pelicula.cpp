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
  
}

Pelicula::Pelicula(int newid, string newnombre, int newanio, float newvaloracion, string newgenero)
: id(newid), nombre(newnombre), valoracion(newvaloracion), genero(newgenero), anio(newanio)
{
}
  
Pelicula::Pelicula(const Pelicula& orig)
: id(orig.id), nombre(orig.nombre), valoracion(orig.valoracion), genero(orig.genero), anio(orig.anio)
{
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

}

int Pelicula::getId(){
	return id;
}

string Pelicula::getNombre(){
	 return nombre;
}       

string Pelicula::getGenero(){
	 return genero;
}

int Pelicula::getAnio(){
	 return anio;
}

float Pelicula::getValoracion(){
	return valoracion;
}
