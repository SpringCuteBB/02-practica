#ifndef FUNCIONESSOPA_H
#define FUNCIONESSOPA_H

#include <string>
#include <vector>

// Lee la sopa de letras desde un fichero y la almacena en una matriz
void leerSopa(const std::string& fichero, std::vector<std::vector<char>>& sopa);

// Lee las palabras a buscar desde un fichero
void leerPalabras(const std::string& fichero, std::vector<std::string>& palabras);

// Muestra la sopa de letras por pantalla
void mostrarSopa(const std::vector<std::vector<char>>& sopa);

// Busca una palabra en la sopa de letras en las 8 direcciones posibles.
// Si la encuentra, devuelve true y rellena fila, col y direccion con la
// posicion inicial (0-indexed) y la direccion encontrada.
bool buscarPalabra(const std::vector<std::vector<char>>& sopa,
                   const std::string& palabra,
                   int& fila, int& col, std::string& direccion);

#endif // FUNCIONESSOPA_H

