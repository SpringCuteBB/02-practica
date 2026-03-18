cmake_minimum_required(VERSION 4.1)
project(vectorParescLion)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(p2ConjuntoPeliculasClion src/main.cpp src/ConjuntoPeliculas.cpp src/Pelicula.cpp)
