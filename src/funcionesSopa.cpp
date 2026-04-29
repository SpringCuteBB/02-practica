#include "funcionesSopa.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

// ---------------------------------------------------------------------------
// leerSopa
// Formato del fichero:
//   Linea 1: numero de filas
//   Linea 2: numero de columnas
//   Siguientes lineas: letras separadas por espacios
// ---------------------------------------------------------------------------
void leerSopa(const std::string& fichero, std::vector<std::vector<char>>& sopa) {
    std::ifstream f(fichero);
    if (!f.is_open())
        throw std::runtime_error("No se pudo abrir el fichero: " + fichero);

    int filas, cols;
    f >> filas >> cols;

    sopa.assign(filas, std::vector<char>(cols));
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < cols; ++j)
            f >> sopa[i][j];
}

// ---------------------------------------------------------------------------
// leerPalabras
// Formato del fichero:
//   Linea 1: numero de palabras
//   Siguientes lineas: una palabra por linea
// ---------------------------------------------------------------------------
void leerPalabras(const std::string& fichero, std::vector<std::string>& palabras) {
    std::ifstream f(fichero);
    if (!f.is_open())
        throw std::runtime_error("No se pudo abrir el fichero: " + fichero);

    int n;
    f >> n;
    palabras.resize(n);
    for (int i = 0; i < n; ++i)
        f >> palabras[i];
}

// ---------------------------------------------------------------------------
// mostrarSopa
// ---------------------------------------------------------------------------
void mostrarSopa(const std::vector<std::vector<char>>& sopa) {
    for (const auto& fila : sopa) {
        for (size_t j = 0; j < fila.size(); ++j) {
            if (j > 0) std::cout << ' ';
            std::cout << fila[j];
        }
        std::cout << '\n';
    }
}

// ---------------------------------------------------------------------------
// buscarPalabra
// Busca en las 8 direcciones: derecha, izquierda, abajo, arriba y las
// 4 diagonales. Devuelve true si la encuentra.
// ---------------------------------------------------------------------------
bool buscarPalabra(const std::vector<std::vector<char>>& sopa,
                   const std::string& palabra,
                   int& fila, int& col, std::string& direccion) {
    // Cada entrada: {delta_fila, delta_col, nombre}
    const int dfilas[] = { 0,  0,  1, -1,  1,  1, -1, -1 };
    const int dcols[]  = { 1, -1,  0,  0,  1, -1,  1, -1 };
    const std::string nombres[] = {
        "derecha", "izquierda", "abajo", "arriba",
        "diagonal abajo-derecha", "diagonal abajo-izquierda",
        "diagonal arriba-derecha", "diagonal arriba-izquierda"
    };

    const int nfilas = static_cast<int>(sopa.size());
    if (nfilas == 0) return false;
    const int ncols  = static_cast<int>(sopa[0].size());
    const int len    = static_cast<int>(palabra.size());

    for (int i = 0; i < nfilas; ++i) {
        for (int j = 0; j < ncols; ++j) {
            for (int d = 0; d < 8; ++d) {
                // Comprobar que cabe la palabra en esta direccion
                int fi = i + dfilas[d] * (len - 1);
                int fj = j + dcols[d]  * (len - 1);
                if (fi < 0 || fi >= nfilas || fj < 0 || fj >= ncols)
                    continue;

                // Comparar letra a letra
                bool ok = true;
                for (int k = 0; k < len && ok; ++k) {
                    if (sopa[i + dfilas[d] * k][j + dcols[d] * k] != palabra[k])
                        ok = false;
                }

                if (ok) {
                    fila      = i;
                    col       = j;
                    direccion = nombres[d];
                    return true;
                }
            }
        }
    }
    return false;
}
