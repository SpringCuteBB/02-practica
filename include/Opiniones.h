#ifndef OPINIONES_H
#define OPINIONES_H

#include "ConjuntoUsuarios.h"
#include "ConjuntoPeliculas.h"
#include <string>
#include <iostream>

class Opiniones {
private:
    ConjuntoUsuarios users;
    ConjuntoPeliculas pelis;
    float **opiniones; // opiniones[u][p]

    void allocOpiniones();
    void freeOpiniones();

public:
    Opiniones(ConjuntoUsuarios newusers, ConjuntoPeliculas newpelis);
    Opiniones(std::string fichopiniones, std::string fichpelis, std::string fichusuarios);
    Opiniones(const Opiniones & orig);
    ~Opiniones();

    void saveData(std::string fichopiniones, std::string fichpelis, std::string fichusuarios) const;
    void cargaOpiniones(std::string fichopiniones);

    void introduceOpinion(int iduser, int idpelicula, float valor);
    void eliminaOpinion(int iduser, int idpelicula);

    std::string to_string() const;

    friend std::ostream & operator<<(std::ostream & flujo, const Opiniones & conjop);

    ConjuntoUsuarios & getusers() const;
    ConjuntoPeliculas & getpelis() const;

    ConjuntoPeliculas peliculasrecomendadas(int userid, int numusers);
    float similitud(int userid1, int userid2) const;
    ConjuntoUsuarios usuariosSimilares(int userid,int numusers);

    float consensoPelicula(int idpelicula) const;
    float consenso() const;
    float mediaPelicula(int idpelicula) const;
};

// funciones fuera de la clase
void generaRecomendacionUsuario(Opiniones op, int idusuario, int numusers);
void calculaConsensoPelicula(Opiniones op, std::string nombrepelicula);
void cambiaOpinion(int idusuario, std::string nombrepelicula, float valor, Opiniones &op, std::string fichopiniones, std::string fichpeliculas,std::string fichusuarios);

#endif // OPINIONES_H
