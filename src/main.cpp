#include <iostream>
#include <vector>
#include <string>

#include "funcionesSopa.h"

int main() {
    const std::string ficheroSopa    = "data/sopa.txt";
    const std::string ficheroPalabras = "data/palabras.txt";

    // --- Cargar datos ---
    std::vector<std::vector<char>> sopa;
    std::vector<std::string> palabras;

    try {
        leerSopa(ficheroSopa, sopa);
        leerPalabras(ficheroPalabras, palabras);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    // --- Mostrar la sopa ---
    std::cout << "=== Sopa de letras ===\n";
    mostrarSopa(sopa);
    std::cout << '\n';

    // --- Buscar cada palabra ---
    std::cout << "=== Busqueda de palabras ===\n";
    for (const auto& palabra : palabras) {
        int fila = -1, col = -1;
        std::string dir;

        if (buscarPalabra(sopa, palabra, fila, col, dir))
            std::cout << "\"" << palabra << "\" encontrada en ("
                      << fila << ", " << col << ") direccion: " << dir << '\n';
        else
            std::cout << "\"" << palabra << "\" NO encontrada\n";
    }

    return 0;
}


