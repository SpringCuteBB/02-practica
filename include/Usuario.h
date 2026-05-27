#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

class Usuario {
private:
    std::string correoelectronico;
    std::string nombreusuario;
    int id;
    int numpeliculas;
    int* idAmigos;
    int numAmigos;
    int numreservadoAmigos;
    static const int INCREMENTO = 5;

public:
    Usuario();
    Usuario(const Usuario& orig);
    Usuario(int newid, std::string newnombreusuario, std::string newcorreoelectronico);
    ~Usuario();

    std::string getCorreoElectronico() const;
    std::string getNombreUsuario() const;
    int getId() const;
    int getNumPeliculas() const;

    int& setId();
    std::string& putNombreUsuario();
    std::string& putCorreoElectronico();

    bool anaideAmigo(int idnuevoamigo);
    bool eliminaAmigo(int idamigo);

    int& operator[](int i) const;
    void incrementaNumPeliculas();
    void decrementaNumPeliculas();

    Usuario& operator=(const Usuario& orig);

    friend std::ostream& operator<<(std::ostream& flujo, const Usuario& user);

    bool operator<(const Usuario& other) const;
    bool operator>(const Usuario& other) const;
    bool operator==(const Usuario& other) const;
    bool operator<=(const Usuario& other) const;
    bool operator>=(const Usuario& other) const;
};

#endif // USUARIO_H
