/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   ConjuntoPeliculas.cpp
 * Author: Ismael Valenzuela Mañas
 * 
 * Created on 26 de septiembre de 2022, 11:59
 */

#include "ConjuntoPeliculas.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

ConjuntoPeliculas::ConjuntoPeliculas(int k) : numpeliculas(0), tamreservado(k>0? k: INCREMENTO) {
	conj = new Pelicula[tamreservado];
}

ConjuntoPeliculas::ConjuntoPeliculas(const ConjuntoPeliculas& orig) : numpeliculas(orig.numpeliculas), tamreservado(orig.tamreservado) {
	conj = new Pelicula[tamreservado];
	for(int i = 0; i < numpeliculas; ++i){
		conj[i] = orig.conj[i];
	}
}

ConjuntoPeliculas::~ConjuntoPeliculas() {
	delete [] conj;
	conj = nullptr;
}

void ConjuntoPeliculas::leerFichero(string rutaFichero, int numdatos){
   std::ifstream ifs(rutaFichero);
   if(!ifs.is_open()) return;

	// Vaciar información previa (mantener reserva)
	numpeliculas = 0;

   string line;
   // Saltar la cabecera
   if(!std::getline(ifs, line)) return;

	int leidos = 0;
	while((numdatos <= 0 || leidos < numdatos) && std::getline(ifs, line)){
	   if(line.empty()) continue;
	   std::stringstream ss(line);
	   string idstr, title, yearstr, ratingstr;
	   if(!std::getline(ss, idstr, ';')) continue;
	   if(!std::getline(ss, title, ';')) continue;
	   if(!std::getline(ss, yearstr, ';')) continue;
	   if(!std::getline(ss, ratingstr, ';')) ratingstr = "";

	   // Parse id
	   int id = -1;
	   try{ id = std::stoi(idstr); } catch(...) { continue; }

	   // Parse year
	   int year = -1;
	   try{ year = std::stoi(yearstr); } catch(...) { year = -1; }

	   // Parse rating (coma decimal en el CSV)
	   for(char &c : ratingstr) if(c==',') c='.';
	   float rating = -1.0f;
	   try{
		   if(!ratingstr.empty()) rating = std::stof(ratingstr);
	   } catch(...) { rating = -1.0f; }

	   // No hay género en el CSV: cadena vacía
	   if(numpeliculas >= tamreservado) resize();
	   conj[numpeliculas] = Pelicula(id, title, year, rating, "");
	   numpeliculas++;
	   leidos++;
   }
   ifs.close();
}

void ConjuntoPeliculas::aniadePelicula(int newid, string newnombre, int newanio,float newvaloracion, string newgenero){
	if(numpeliculas >= tamreservado) resize();
	conj[numpeliculas] = Pelicula(newid, newnombre, newanio, newvaloracion, newgenero);
	numpeliculas++;
}

void ConjuntoPeliculas::borrar(int id){
	int idx = -1;
	for(int i = 0; i < numpeliculas; ++i){
		if(conj[i].getId() == id){ idx = i; break; }
	}
	if(idx == -1) return;
	for(int i = idx; i < numpeliculas - 1; ++i) conj[i] = conj[i+1];
	--numpeliculas;
}

Pelicula ConjuntoPeliculas::at(int id){
	for(int i = 0; i < numpeliculas; ++i){
		if(conj[i].getId() == id) return conj[i];
	}
	return Pelicula();
}

int ConjuntoPeliculas::numPeliculas() const {
	return numpeliculas;
}

int ConjuntoPeliculas::busquedaPelicula(int busquedaid) const {
	for(int i = 0; i < numpeliculas; ++i){
		if(conj[i].getId() == busquedaid) return i;
	}
	return -1;
}

int ConjuntoPeliculas::busquedaPelicula(string nombrepelicula) const {
	for(int i = 0; i < numpeliculas; ++i){
		if(conj[i].getNombre().find(nombrepelicula) != string::npos) return conj[i].getId();
	}
	return -1;
}

ConjuntoPeliculas& ConjuntoPeliculas::operator=(const ConjuntoPeliculas& orig) {
	if(this == &orig) return *this;
	delete [] conj;
	numpeliculas = orig.numpeliculas;
	tamreservado = orig.tamreservado;
	conj = new Pelicula[tamreservado];
	for(int i = 0; i < numpeliculas; ++i) conj[i] = orig.conj[i];
	return *this;
}

ConjuntoPeliculas& ConjuntoPeliculas::operator+=(const Pelicula& newpelicula) {
	if(numpeliculas >= tamreservado) resize();
	conj[numpeliculas++] = newpelicula;
	return *this;
}

Pelicula& ConjuntoPeliculas::operator[](int i) const {
	return conj[i];
}

void ConjuntoPeliculas::resize(int newtam){
	int nt = newtam <= 0 ? tamreservado + INCREMENTO : newtam;
	if(nt <= numpeliculas) nt = numpeliculas + INCREMENTO;
	Pelicula* nuevo = new Pelicula[nt];
	for(int i = 0; i < numpeliculas; ++i) nuevo[i] = conj[i];
	delete [] conj;
	conj = nuevo;
	tamreservado = nt;
}

void ConjuntoPeliculas::ordenaporranking(){
	for(int i = 0; i < numpeliculas; ++i){
		int maxidx = i;
		for(int j = i+1; j < numpeliculas; ++j){
			if(conj[j].getValoracion() > conj[maxidx].getValoracion()){
				maxidx = j;
			}
		}
		if(maxidx != i) std::swap(conj[i], conj[maxidx]);
	}
}

string ConjuntoPeliculas::to_string() const {
    std::ostringstream oss;
    for(int i = 0; i < numpeliculas; ++i){
        oss << conj[i].to_string();
        if(i + 1 < numpeliculas) oss << "\n";
    }
    return oss.str();
}  
void ConjuntoPeliculas::escribeFichero(string rutaFichero) const {
	std::ofstream ofs(rutaFichero);
	if(!ofs.is_open()) return;

	// Escribir cabecera igual que el fichero de entrada
	ofs << ";Movie title;Released Year;ImDb Rating\n";

	for(int i = 0; i < numpeliculas; ++i){
		int id = conj[i].getId();
		string title = conj[i].getNombre();
		int year = conj[i].getAnio();
		float rating = conj[i].getValoracion();

		// Formatear rating usando coma decimal; dejar vacío si no válido
		string ratingstr;
		if(rating < 0.0f){
			ratingstr = "";
		} else {
			// si es entero, escribir sin decimal
			if(std::fabs(rating - std::round(rating)) < 1e-6){
				ratingstr = std::to_string((int)std::lround(rating));
			} else {
				std::ostringstream rs;
				rs << std::fixed << std::setprecision(1) << rating;
				ratingstr = rs.str();
			}
			// reemplazar punto por coma
			for(char &c : ratingstr) if(c == '.') c = ',';
		}

		ofs << id << ";" << title << ";" << year << ";" << ratingstr << "\n";
	}
	ofs.close();
}
   
void ConjuntoPeliculas::clear(){
    for(int i = 0; i < numpeliculas; ++i){
        conj[i] = Pelicula();
    }
    numpeliculas = 0;
}