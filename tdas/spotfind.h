#ifndef SPOTFIND_H
#define SPOTFIND_H
#include "spotfind.h"
#include "map.h"
#include <stdbool.h>

// Declaración de estructuras utilizadas en el sistema
typedef struct Song Song;
typedef struct listaReproduccion listaReproduccion;

// Funciones de comparación para claves string e int
int is_equal_str(void *key1, void *key2);
int is_equal_int(void *key1, void *key2);

// Muestra el menú principal con las opciones disponibles para el usuario
void mostrarMenuPrincipal();

// Carga las canciones desde un archivo csv y las organiza en distintos mapas
void cargarCanciones(Map *songsByGenres, Map *songsByArtists, Map *songsByTempo, Map *songsById);

// Muestra las canciones almacenadas en un mapa específico, junto con un mensaje descriptivo
void mostrarPor(Map *mapaCanciones, char *mensaje);

// Crea una nueva lista de reproducción
void crearListaReproduccion(Map *mapaListas);

// Agrega una canción a una lista de reproducción
void agregarCancionALista(Map *mapaListas, Map *songsById);

// Muestra todas las canciones de una lista de reproducción
void mostrarCancionesDeUnaLista(Map *listaDeReproducciones);

// Libera toda la memoria usada por el programa.
void liberarTodo(Map *songsByGenres, Map *songsByArtists, Map *songsByTempo,
                 Map *songsById, Map *listaDeReproducciones);

#endif