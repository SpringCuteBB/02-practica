#ifndef CONJUNTOUSUARIOS_H
#define CONJUNTOUSUARIOS_H

#include "Usuario.h"
#include <string>
#include <iostream>

class ConjuntoUsuarios {
private:
    Usuario* vectorUsuarios;
    int numusuarios;
    int tamreservado;
    static const int INCREMENTO = 5;

    void ordenaporId();

public:
    ConjuntoUsuarios(int k = INCREMENTO);
    ConjuntoUsuarios(const ConjuntoUsuarios& orig);
    ConjuntoUsuarios(int n, std::string* nombresusuario, std::string* correoselectronicos);
    ~ConjuntoUsuarios();

    std::string rankingUsuarios() const;

    void clear();
    int numUsuarios() const;

    ConjuntoUsuarios& operator=(const ConjuntoUsuarios& orig);
    ConjuntoUsuarios& operator+=(const Usuario& newuser);
    Usuario& operator[](int i) const;

    void eliminaUsuario(int userid);
    int  buscaUsuario(int userid) const;
    int  buscaUsuario(std::string nombreusuario) const;
    void optimizar();
    void resize(int newtam = -1);

    friend std::ostream& operator<<(std::ostream& flujo, const ConjuntoUsuarios& conjuser);
    friend std::istream& operator>>(std::istream& is, ConjuntoUsuarios& conjuser);
    friend ConjuntoUsuarios operator+(const ConjuntoUsuarios& left, const ConjuntoUsuarios& right);
};

#endif // CONJUNTOUSUARIOS_H
