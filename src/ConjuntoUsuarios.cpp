#include "ConjuntoUsuarios.h"
#include <algorithm>
#include <sstream>

// ─── Constructores ────────────────────────────────────────────────────────────

ConjuntoUsuarios::ConjuntoUsuarios(int k)
    : numusuarios(0), tamreservado(k)
{
    vectorUsuarios = new Usuario[tamreservado];
}

ConjuntoUsuarios::ConjuntoUsuarios(const ConjuntoUsuarios& orig)
    : numusuarios(orig.numusuarios), tamreservado(orig.tamreservado)
{
    vectorUsuarios = new Usuario[tamreservado];
    for (int i = 0; i < numusuarios; ++i)
        vectorUsuarios[i] = orig.vectorUsuarios[i];
}

ConjuntoUsuarios::ConjuntoUsuarios(int n, std::string* nombresusuario, std::string* correoselectronicos)
    : numusuarios(n), tamreservado(n)
{
    vectorUsuarios = new Usuario[n];
    for (int i = 0; i < n; ++i)
        vectorUsuarios[i] = Usuario(i, nombresusuario[i], correoselectronicos[i]);
}

// ─── Destructor ───────────────────────────────────────────────────────────────

ConjuntoUsuarios::~ConjuntoUsuarios() {
    delete[] vectorUsuarios;
}

// ─── resize ───────────────────────────────────────────────────────────────────

void ConjuntoUsuarios::resize(int newtam) {
    if (newtam == -1)
        newtam = tamreservado + INCREMENTO;

    if (newtam <= tamreservado) return;

    Usuario* nuevo = new Usuario[newtam];
    for (int i = 0; i < numusuarios; ++i)
        nuevo[i] = vectorUsuarios[i];

    delete[] vectorUsuarios;
    vectorUsuarios = nuevo;
    tamreservado   = newtam;
}

// ─── ordenaporId (privado) ────────────────────────────────────────────────────

void ConjuntoUsuarios::ordenaporId() {
    // Insertion sort sobre los numusuarios primeros elementos
    for (int i = 1; i < numusuarios; ++i) {
        Usuario tmp = vectorUsuarios[i];
        int j = i - 1;
        while (j >= 0 && vectorUsuarios[j].getId() > tmp.getId()) {
            vectorUsuarios[j + 1] = vectorUsuarios[j];
            --j;
        }
        vectorUsuarios[j + 1] = tmp;
    }
}

// ─── rankingUsuarios ──────────────────────────────────────────────────────────

std::string ConjuntoUsuarios::rankingUsuarios() const {
    // Copia temporal para ordenar sin modificar el original
    Usuario* copia = new Usuario[numusuarios];
    for (int i = 0; i < numusuarios; ++i)
        copia[i] = vectorUsuarios[i];

    // Ordenar descendente por numpeliculas (selection sort)
    for (int i = 0; i < numusuarios - 1; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < numusuarios; ++j)
            if (copia[j] > copia[max_idx]) max_idx = j;
        if (max_idx != i) {
            Usuario tmp    = copia[i];
            copia[i]       = copia[max_idx];
            copia[max_idx] = tmp;
        }
    }

    std::ostringstream oss;
    for (int i = 0; i < numusuarios; ++i) {
        oss << copia[i].getNombreUsuario() << " "
            << copia[i].getCorreoElectronico() << " : "
            << copia[i].getNumPeliculas();
        if (i < numusuarios - 1) oss << "\n";
    }

    delete[] copia;
    return oss.str();
}

// ─── Operador de asignación ───────────────────────────────────────────────────

ConjuntoUsuarios& ConjuntoUsuarios::operator=(const ConjuntoUsuarios& orig) {
    if (this == &orig) return *this;

    delete[] vectorUsuarios;

    numusuarios  = orig.numusuarios;
    tamreservado = orig.tamreservado;
    vectorUsuarios = new Usuario[tamreservado];
    for (int i = 0; i < numusuarios; ++i)
        vectorUsuarios[i] = orig.vectorUsuarios[i];

    return *this;
}

// ─── operator+= ───────────────────────────────────────────────────────────────

ConjuntoUsuarios& ConjuntoUsuarios::operator+=(const Usuario& newuser) {
    if (numusuarios >= tamreservado)
        resize();

    vectorUsuarios[numusuarios++] = newuser;
    return *this;
}

void ConjuntoUsuarios::clear() {
    delete[] vectorUsuarios;
    tamreservado = INCREMENTO;
    numusuarios = 0;
    vectorUsuarios = new Usuario[tamreservado];
}

int ConjuntoUsuarios::numUsuarios() const {
    return numusuarios;
}

std::istream& operator>>(std::istream& is, ConjuntoUsuarios& conjuser) {
    int n;
    if (!(is >> n)) return is;

    conjuser.clear();

    if (n > conjuser.tamreservado) {
        delete[] conjuser.vectorUsuarios;
        conjuser.vectorUsuarios = new Usuario[n];
        conjuser.tamreservado = n;
    }

    conjuser.numusuarios = n;

    for (int i = 0; i < n; ++i) {
        int fid_from_file;
        std::string name, email;
        int numpel, numAmigos;
        if (!(is >> fid_from_file >> name >> email >> numpel >> numAmigos)) {
            conjuser.numusuarios = i;
            return is;
        }
        char colon;
        is >> colon;

        conjuser.vectorUsuarios[i] = Usuario(i, name, email);

        for (int k = 0; k < numpel; ++k)
            conjuser.vectorUsuarios[i].incrementaNumPeliculas();

        for (int j = 0; j < numAmigos; ++j) {
            int friendid;
            if (!(is >> friendid)) break;
            conjuser.vectorUsuarios[i].anaideAmigo(friendid);
        }
    }

    return is;
}

// ─── operator[] ───────────────────────────────────────────────────────────────

Usuario& ConjuntoUsuarios::operator[](int i) const {
    return vectorUsuarios[i];
}

// ─── eliminaUsuario ───────────────────────────────────────────────────────────

void ConjuntoUsuarios::eliminaUsuario(int userid) {
    int pos = buscaUsuario(userid);
    if (pos == -1) return;

    for (int i = pos; i < numusuarios - 1; ++i)
        vectorUsuarios[i] = vectorUsuarios[i + 1];

    --numusuarios;
}

// ─── buscaUsuario ─────────────────────────────────────────────────────────────

int ConjuntoUsuarios::buscaUsuario(int userid) const {
    for (int i = 0; i < numusuarios; ++i)
        if (vectorUsuarios[i].getId() == userid) return i;
    return -1;
}

int ConjuntoUsuarios::buscaUsuario(std::string nombreusuario) const {
    for (int i = 0; i < numusuarios; ++i)
        if (vectorUsuarios[i].getNombreUsuario() == nombreusuario) return i;
    return -1;
}

// ─── optimizar ────────────────────────────────────────────────────────────────

void ConjuntoUsuarios::optimizar() {
    if (tamreservado == numusuarios) return;

    Usuario* nuevo = new Usuario[numusuarios];
    for (int i = 0; i < numusuarios; ++i)
        nuevo[i] = vectorUsuarios[i];

    delete[] vectorUsuarios;
    vectorUsuarios = nuevo;
    tamreservado   = numusuarios;
}

// ─── operator<< ───────────────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& flujo, const ConjuntoUsuarios& conjuser) {
    flujo << conjuser.numusuarios << "\n";
    for (int i = 0; i < conjuser.numusuarios; ++i) {
        flujo << conjuser.vectorUsuarios[i];
        if (i < conjuser.numusuarios - 1) flujo << "\n";
    }
    return flujo;
}

// ─── operator+ ────────────────────────────────────────────────────────────────

ConjuntoUsuarios operator+(const ConjuntoUsuarios& left, const ConjuntoUsuarios& right) {
    ConjuntoUsuarios resultado(left);

    for (int i = 0; i < right.numusuarios; ++i) {
        // Omitir usuarios con id duplicado
        if (resultado.buscaUsuario(right.vectorUsuarios[i].getId()) == -1)
            resultado += right.vectorUsuarios[i];
    }

    return resultado;
}
