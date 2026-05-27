#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <filesystem>
#include "Usuario.h"
#include "ConjuntoUsuarios.h"
#include "ConjuntoPeliculas.h"
#include "Pelicula.h"
#include "Opiniones.h"

int main(int argc, char* argv[]) {
    // Analiza los argumentos de la línea de comandos en un mapa: parámetro -> valor
    std::map<std::string,std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string key = argv[i];
        if (!key.empty() && key[0] == '-') {
            if (i + 1 < argc) {
                args[key] = argv[i+1];
                ++i;
            } else {
                std::cerr << "Missing value for option " << key << "\n";
                return 1;
            }
        }
    }

    auto get = [&](const std::string &k)->std::string{
        auto it = args.find(k);
        if (it == args.end()) return std::string();
        return it->second;
    };

    std::string action = get("-a");
    if (action.empty()) {
        std::cerr << "Missing -a action parameter\n";
        return 1;
    }

    // Encontrar data/ relativa a la ubicación del ejecutable (un nivel arriba de bin/)
    namespace fs = std::filesystem;
    fs::path exeDir = fs::path(argv[0]).parent_path();
    fs::path dataDirPath = exeDir / ".." / "data";
    const std::string dataDir = dataDirPath.string() + "/";
    std::string fu = get("-fu");
    std::string fo = get("-fo");
    std::string fp = get("-fp");

    if (fu.empty() || fo.empty() || fp.empty()) {
        std::cerr << "Missing one of -fu, -fo or -fp file parameters\n";
        return 1;
    }

    std::string pathUsers = dataDir + fu;
    std::string pathOpin  = dataDir + fo;
    std::string pathPelis = dataDir + fp;

    if (action == "recomendacion") {
        std::string su = get("-u");
        std::string sn = get("-n");
        if (su.empty() || sn.empty()) { std::cerr << "Missing -u or -n for recomendacion\n"; return 1; }
        int iduser = 0, numusers = 0;
        try { iduser = std::stoi(su); numusers = std::stoi(sn); } catch(...) { std::cerr << "Invalid numeric parameter\n"; return 1; }

        Opiniones op(pathOpin, pathPelis, pathUsers);
        generaRecomendacionUsuario(op, iduser, numusers);
        return 0;
    }

    if (action == "valoracionpelicula") {
        std::string pname = get("-p");
        if (pname.empty()) { std::cerr << "Missing -p movie name for valoracionpelicula\n"; return 1; }
        std::replace(pname.begin(), pname.end(), '_', ' ');

        Opiniones op(pathOpin, pathPelis, pathUsers);
        calculaConsensoPelicula(op, pname);
        return 0;
    }

    if (action == "modificacion") {
        std::string pname = get("-p");
        std::string su = get("-u");
        std::string sop = get("-op");
        if (pname.empty() || su.empty() || sop.empty()) { std::cerr << "Missing -p, -u or -op for modificacion\n"; return 1; }
        std::replace(pname.begin(), pname.end(), '_', ' ');
        int iduser = 0; float valor = 0.0f;
        try { iduser = std::stoi(su); valor = std::stof(sop); } catch(...) { std::cerr << "Invalid numeric parameter\n"; return 1; }

        Opiniones op(pathOpin, pathPelis, pathUsers);
        cambiaOpinion(iduser, pname, valor, op, pathOpin, pathPelis, pathUsers);
        return 0;
    }

    std::cerr << "Unknown action: " << action << "\n";
    return 1;
}
