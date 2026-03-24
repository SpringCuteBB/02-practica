# PRÁCTICA 2: Metodología de la Programación
Autor: Ismael Valenzuela Mañas
<br>
Esta práctica usó el __IDE Visual Studio Code__ y también [CMake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) para ejecutar las importaciones en __C++__. <br>
La configuración de __CMake__ esta en el archivo `CMakeLists`. <br>

## Como ejecutar el código.
Se necesita la instalación de de [CMake](https://cmake.org/download/) <br>

### 1º Forma:
Dentro del proyecto, hay una carpeta de [scripts](scripts) con ejecutables automáticos en powershell y bash.
<br>
### 2º Forma: 

### Windows (PowerShell)
Desde la raíz del proyecto:

```powershell
# Compilar (por defecto Debug). Ejemplo: Release con 4 hilos
.\scripts\win\build.ps1 -Configuration Release -Jobs 4

# Ejecutar (pasa argumentos si los hay)
.\scripts\win\run.ps1 -- arg1 arg2
```

Si usas otro generador (Visual Studio), pásalo con `-Generator 'Visual Studio 17 2022'` al script de build.

### Linux / macOS (bash)
Desde la raíz del proyecto:

```bash
# Compilar (por defecto Debug). Ejemplo: Release, 4 hilos
./scripts/bash/build.sh Release "Unix Makefiles" 4
