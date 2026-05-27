#include "Opiniones.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

// --- utilitarios de memoria ---
void Opiniones::allocOpiniones() {
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    opiniones = new float*[filas];
    for (int i = 0; i < filas; ++i) {
        opiniones[i] = new float[cols];
        for (int j = 0; j < cols; ++j) opiniones[i][j] = -1.0f;
    }
}

void Opiniones::freeOpiniones() {
    if (!opiniones) return;
    int filas = users.numUsuarios();
    for (int i = 0; i < filas; ++i) delete [] opiniones[i];
    delete [] opiniones;
    opiniones = nullptr;
}

// --- constructores / destructor ---
Opiniones::Opiniones(ConjuntoUsuarios newusers, ConjuntoPeliculas newpelis)
    : users(newusers), pelis(newpelis), opiniones(nullptr)
{
    allocOpiniones();
}

Opiniones::Opiniones(std::string fichopiniones, std::string fichpelis, std::string fichusuarios)
    : users(), pelis(), opiniones(nullptr)
{
    // Cargar usuarios
    std::ifstream ifsU(fichusuarios);
    if (ifsU.is_open()) {
        ifsU >> users;
        ifsU.close();
    }

    // Cargar películas (intentamos leer todo el fichero)
    pelis.leerFichero(fichpelis, pelis.numPeliculas());

    // Reservar matriz basada en lo leído
    allocOpiniones();

    // Cargar opiniones
    cargaOpiniones(fichopiniones);
}

Opiniones::Opiniones(const Opiniones & orig)
    : users(orig.users), pelis(orig.pelis), opiniones(nullptr)
{
    allocOpiniones();
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < cols; ++j)
            opiniones[i][j] = orig.opiniones[i][j];
}

Opiniones::~Opiniones() {
    freeOpiniones();
}

// --- I/O ---
void Opiniones::saveData(std::string fichopiniones, std::string fichpelis, std::string fichusuarios) const {
    // Guardar matriz de opiniones
    std::ofstream ofs(fichopiniones);
    if (ofs.is_open()) {
        int filas = users.numUsuarios();
        int cols  = pelis.numPeliculas();
        ofs << filas << " " << cols << "\n";
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (j) ofs << " ";
                ofs << opiniones[i][j];
            }
            ofs << "\n";
        }
        ofs.close();
    }

    // Guardar películas
    pelis.escribeFichero(fichpelis);

    // Guardar usuarios
    std::ofstream ofu(fichusuarios);
    if (ofu.is_open()) {
        ofu << users;
        ofu.close();
    }
}

void Opiniones::cargaOpiniones(std::string fichopiniones) {
    std::ifstream ifs(fichopiniones);
    if (!ifs.is_open()) return;

    int filas_file = 0, cols_file = 0;
    ifs >> filas_file >> cols_file;

    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();

    // Si la matriz actual no coincide con el fichero, realineamos pero no cambiamos users/pelis
    freeOpiniones();
    opiniones = new float*[filas];
    for (int i = 0; i < filas; ++i) {
        opiniones[i] = new float[cols];
        for (int j = 0; j < cols; ++j) opiniones[i][j] = -1.0f;
    }

    // Leer valores; si el fichero tiene dimensiones distintas, sólo usamos el mínimo
    for (int i = 0; i < filas_file && i < filas; ++i) {
        for (int j = 0; j < cols_file && j < cols; ++j) {
            float v; ifs >> v; opiniones[i][j] = v;
        }
        // Saltar el resto de columnas del fichero si cols_file > cols
        for (int j = cols_file; j < cols_file; ++j) { float tmp; ifs >> tmp; }
    }

    ifs.close();
}

// --- modificación de opiniones ---
void Opiniones::introduceOpinion(int iduser, int idpelicula, float valor) {
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    if (iduser < 0 || iduser >= filas || idpelicula < 0 || idpelicula >= cols) return;

    float prev = opiniones[iduser][idpelicula];
    opiniones[iduser][idpelicula] = valor;
    if (prev < 0.0f && valor >= 0.0f) {
        users[iduser].incrementaNumPeliculas();
    }
}

void Opiniones::eliminaOpinion(int iduser, int idpelicula) {
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    if (iduser < 0 || iduser >= filas || idpelicula < 0 || idpelicula >= cols) return;

    float prev = opiniones[iduser][idpelicula];
    if (prev < 0.0f) return; // no había opinión
    opiniones[iduser][idpelicula] = -1.0f;
    users[iduser].decrementaNumPeliculas();
}

// --- representación ---
std::string Opiniones::to_string() const {
    std::ostringstream oss;
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (j) oss << " ";
            oss << opiniones[i][j];
        }
        if (i + 1 < filas) oss << "\n";
    }
    return oss.str();
}

std::ostream & operator<<(std::ostream & flujo, const Opiniones & conjop) {
    flujo << conjop.users << "\n";
    flujo << conjop.pelis.to_string() << "\n";
    flujo << conjop.to_string();
    return flujo;
}

// --- accesores ---
ConjuntoUsuarios & Opiniones::getusers() const { return const_cast<ConjuntoUsuarios&>(users); }
ConjuntoPeliculas & Opiniones::getpelis() const { return const_cast<ConjuntoPeliculas&>(pelis); }

// --- recomendaciones y similitudes ---
float Opiniones::similitud(int userid1, int userid2) const {
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    if (userid1 < 0 || userid1 >= filas || userid2 < 0 || userid2 >= filas) return -1.0f;

    float dot = 0.0f, norm1 = 0.0f, norm2 = 0.0f;
    int comunes = 0;
    for (int j = 0; j < cols; ++j) {
        float v1 = opiniones[userid1][j];
        float v2 = opiniones[userid2][j];
        if (v1 >= 0.0f && v2 >= 0.0f) {
            dot += v1 * v2;
            norm1 += v1 * v1;
            norm2 += v2 * v2;
            ++comunes;
        }
    }
    if (comunes == 0) return -1.0f;
    if (norm1 <= 0.0f || norm2 <= 0.0f) return -1.0f;
    return dot / (std::sqrt(norm1) * std::sqrt(norm2));
}

ConjuntoUsuarios Opiniones::usuariosSimilares(int userid,int numusers) {
    int filas = users.numUsuarios();
    ConjuntoUsuarios resultado;
    if (userid < 0 || userid >= filas) return resultado;

    std::vector<std::pair<float,int>> sims;
    for (int i = 0; i < filas; ++i) {
        if (i == userid) continue;
        float s = similitud(userid, i);
        if (s >= 0.0f) sims.push_back({s, i});
    }

    std::sort(sims.begin(), sims.end(), [](const std::pair<float,int>& a, const std::pair<float,int>& b){ return a.first > b.first; });

    int take = std::min((int)sims.size(), numusers);
    for (int k = 0; k < take; ++k) {
        int uid = sims[k].second;
        resultado += users[uid];
    }

    return resultado;
}

ConjuntoPeliculas Opiniones::peliculasrecomendadas(int userid, int numusers) {
    ConjuntoPeliculas resultado;
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    if (userid < 0 || userid >= filas) return resultado;

    ConjuntoUsuarios similares = usuariosSimilares(userid, numusers);
    int nSim = similares.numUsuarios();

    for (int i = 0; i < nSim; ++i) {
        int simId = similares[i].getId();
        for (int j = 0; j < cols; ++j) {
            if (opiniones[simId][j] >= 0.0f && opiniones[userid][j] < 0.0f) {
                // añadir si no está ya
                int pid = pelis[j].getId();
                if (resultado.busquedaPelicula(pid) == -1) resultado += pelis[j];
            }
        }
    }

    resultado.ordenaporranking();
    return resultado;
}

// --- consenso y medias ---
float Opiniones::mediaPelicula(int idpelicula) const {
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    if (idpelicula < 0 || idpelicula >= cols) return -1.0f;
    float sum = 0.0f; int count = 0;
    for (int i = 0; i < filas; ++i) {
        float v = opiniones[i][idpelicula];
        if (v >= 0.0f) { sum += v; ++count; }
    }
    if (count == 0) return -1.0f;
    return sum / count;
}

float Opiniones::consensoPelicula(int idpelicula) const {
    int filas = users.numUsuarios();
    int cols  = pelis.numPeliculas();
    if (idpelicula < 0 || idpelicula >= cols) return -1.0f;

    std::vector<float> ratings;
    for (int i = 0; i < filas; ++i) {
        float v = opiniones[i][idpelicula];
        if (v >= 0.0f) ratings.push_back(v);
    }
    int count = (int)ratings.size();
    if (count < 2) return -1.0f;

    float sumDiff = 0.0f;
    int pairs = 0;
    for (int i = 0; i < count; ++i)
        for (int j = i + 1; j < count; ++j) {
            sumDiff += std::abs(ratings[i] - ratings[j]);
            ++pairs;
        }
    return sumDiff / (pairs * 10.0f);
}

float Opiniones::consenso() const {
    int cols  = pelis.numPeliculas();
    float sum = 0.0f; int count = 0;
    for (int j = 0; j < cols; ++j) {
        float c = consensoPelicula(j);
        if (c >= 0.0f) { sum += c; ++count; }
    }
    if (count == 0) return -1.0f;
    return sum / count;
}

// --- funciones externas ---
void generaRecomendacionUsuario(Opiniones op, int idusuario, int numusers) {
    ConjuntoPeliculas rec = op.peliculasrecomendadas(idusuario, numusers);
    std::string nombre = op.getusers()[idusuario].getNombreUsuario();
    std::cout << "Recomendamos al usuario " << nombre << " las siguientes peliculas:\n";
    for (int i = 0; i < rec.numPeliculas(); ++i) {
        std::cout << rec[i].to_string() << "\n";
    }
}

void calculaConsensoPelicula(Opiniones op, std::string nombrepelicula) {
    int id = op.getpelis().busquedaPelicula(nombrepelicula);
    if (id == -1) {
        std::cout << "No existe la pelicula: " << nombrepelicula << "\n";
        return;
    }
    float media = op.mediaPelicula(id);
    float cons  = op.consensoPelicula(id);
    float consG = op.consenso();
    std::cout << "Pelicula: " << nombrepelicula << " (id=" << id << ")\n";
    std::cout << "Media: " << media << "\n";
    std::cout << "Consenso: " << cons << "\n";
    std::cout << "Consenso global: " << consG << "\n";
}

void cambiaOpinion(int idusuario, std::string nombrepelicula, float valor, Opiniones &op, std::string fichopiniones, std::string fichpeliculas,std::string fichusuarios) {
    int id = op.getpelis().busquedaPelicula(nombrepelicula);
    if (id == -1) {
        std::cout << "No existe la pelicula: " << nombrepelicula << "\n";
        return;
    }
    if (valor < 0.0f) {
        op.eliminaOpinion(idusuario, id);
    } else {
        op.introduceOpinion(idusuario, id, valor);
    }
    op.saveData(fichopiniones, fichpeliculas, fichusuarios);
}
