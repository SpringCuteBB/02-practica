#include "Usuario.h"

// ─── Constructores ────────────────────────────────────────────────────────────

Usuario::Usuario()
    : correoelectronico(""), nombreusuario(""), id(0),
      numpeliculas(0), numAmigos(0), numreservadoAmigos(INCREMENTO)
{
    idAmigos = new int[INCREMENTO];
}

Usuario::Usuario(const Usuario& orig)
    : correoelectronico(orig.correoelectronico),
      nombreusuario(orig.nombreusuario),
      id(orig.id),
      numpeliculas(orig.numpeliculas),
      numAmigos(orig.numAmigos),
      numreservadoAmigos(orig.numreservadoAmigos)
{
    idAmigos = new int[numreservadoAmigos];
    for (int i = 0; i < numAmigos; ++i)
        idAmigos[i] = orig.idAmigos[i];
}

Usuario::Usuario(int newid, std::string newnombreusuario, std::string newcorreoelectronico)
    : correoelectronico(newcorreoelectronico),
      nombreusuario(newnombreusuario),
      id(newid),
      numpeliculas(0),
      numAmigos(0),
      numreservadoAmigos(INCREMENTO)
{
    idAmigos = new int[INCREMENTO];
}

// ─── Destructor ───────────────────────────────────────────────────────────────

Usuario::~Usuario() {
    delete[] idAmigos;
}

// ─── Getters ──────────────────────────────────────────────────────────────────

std::string Usuario::getCorreoElectronico() const {
    return correoelectronico;
}

std::string Usuario::getNombreUsuario() const {
    return nombreusuario;
}

int Usuario::getId() const {
    return id;
}

int Usuario::getNumPeliculas() const {
    return numpeliculas;
}

// ─── Setters (referencias) ────────────────────────────────────────────────────

int& Usuario::setId() {
    return id;
}

std::string& Usuario::putNombreUsuario() {
    return nombreusuario;
}

std::string& Usuario::putCorreoElectronico() {
    return correoelectronico;
}

// ─── Gestión de amigos ────────────────────────────────────────────────────────

bool Usuario::anaideAmigo(int idnuevoamigo) {
    // Comprobar duplicados
    for (int i = 0; i < numAmigos; ++i)
        if (idAmigos[i] == idnuevoamigo)
            return false;

    // Ampliar si está lleno
    if (numAmigos >= numreservadoAmigos) {
        int nuevo_tam = numreservadoAmigos + INCREMENTO;
        int* nuevo = new int[nuevo_tam];
        for (int i = 0; i < numAmigos; ++i)
            nuevo[i] = idAmigos[i];
        delete[] idAmigos;
        idAmigos = nuevo;
        numreservadoAmigos = nuevo_tam;
    }

    idAmigos[numAmigos++] = idnuevoamigo;
    return true;
}

bool Usuario::eliminaAmigo(int idamigo) {
    int pos = -1;
    for (int i = 0; i < numAmigos; ++i)
        if (idAmigos[i] == idamigo) { pos = i; break; }

    if (pos == -1) return false;

    // Desplazar hacia la izquierda
    for (int i = pos; i < numAmigos - 1; ++i)
        idAmigos[i] = idAmigos[i + 1];

    --numAmigos;
    return true;
}

// ─── Operadores ───────────────────────────────────────────────────────────────

int& Usuario::operator[](int i) const {
    return idAmigos[i];
}

void Usuario::incrementaNumPeliculas() {
    ++numpeliculas;
}

void Usuario::decrementaNumPeliculas() {
    if (numpeliculas > 0)
        --numpeliculas;
}

Usuario& Usuario::operator=(const Usuario& orig) {
    if (this == &orig) return *this;

    correoelectronico  = orig.correoelectronico;
    nombreusuario      = orig.nombreusuario;
    id                 = orig.id;
    numpeliculas       = orig.numpeliculas;
    numAmigos          = orig.numAmigos;
    numreservadoAmigos = orig.numreservadoAmigos;

    delete[] idAmigos;
    idAmigos = new int[numreservadoAmigos];
    for (int i = 0; i < numAmigos; ++i)
        idAmigos[i] = orig.idAmigos[i];

    return *this;
}

std::ostream& operator<<(std::ostream& flujo, const Usuario& user) {
    flujo << user.id << " " << user.nombreusuario << " "
          << user.correoelectronico << " " << user.numpeliculas << " "
          << user.numAmigos << ":";
    for (int i = 0; i < user.numAmigos; ++i)
        flujo << " " << user.idAmigos[i];
    return flujo;
}

// Comparadores basados en numpeliculas
bool Usuario::operator<(const Usuario& other) const  { return numpeliculas <  other.numpeliculas; }
bool Usuario::operator>(const Usuario& other) const  { return numpeliculas >  other.numpeliculas; }
bool Usuario::operator==(const Usuario& other) const { return numpeliculas == other.numpeliculas; }
bool Usuario::operator<=(const Usuario& other) const { return numpeliculas <= other.numpeliculas; }
bool Usuario::operator>=(const Usuario& other) const { return numpeliculas >= other.numpeliculas; }
