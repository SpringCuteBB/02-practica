cmake_minimum_required(VERSION 3.16)
project(Practica VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fuentes de la libreria (funcionalidad principal)
set(PRACTICA_LIB_SOURCES
		src/Carta.cpp
		src/Mano.cpp
		src/utils.cpp
)

add_library(practica_lib STATIC ${PRACTICA_LIB_SOURCES})
target_include_directories(practica_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Ejecutable
add_executable(practica src/main.cpp)
target_link_libraries(practica PRIVATE practica_lib)

# Colocar los targets en el directorio bin.
set_target_properties(practica practica_lib PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

# Reglas del install
install(TARGETS practica RUNTIME DESTINATION bin
												ARCHIVE DESTINATION lib
												LIBRARY DESTINATION lib)
