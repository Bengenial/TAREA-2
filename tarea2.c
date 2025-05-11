#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include "tdas/spotfind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario

  // Creamos los mapas para almacenar las canciones
  Map *songsByGenres = map_create(is_equal_str);
  Map *songsByArtists = map_create(is_equal_str);
  Map *songsByTempo = map_create(is_equal_int);
  Map *songsById = map_create(is_equal_int);
  // Recuerda usar un mapa por criterio de búsqueda

  //Creamos la lista de listas de reproducciones
  //List *listaDeReproducciones = list_create();
  Map *listaDeReproducciones = map_create(is_equal_str);  

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);
    puts("");
    
    switch (opcion) {
    case '1':          //Cargar Canciones
      cargarCanciones(songsByGenres, songsByArtists, songsByTempo, songsById);
      break;
    case '2':          //Buscar por Género
      mostrarPor(songsByGenres, "genero");
      break;
    case '3':          //Buscar por Artista
      mostrarPor(songsByArtists, "artista");
      break;
    case '4':          //Buscar por Tempo
      printf("||Lenta||Moderada||Rapida||\n");
      mostrarPor(songsByTempo, "tempo");
      break;
    case '5':          //Crear Lista de Reproducción
      crearListaReproduccion(listaDeReproducciones);
      break;
    case '6':          //Agregar Canción a la Lista
      agregarCancionALista(listaDeReproducciones, songsById);
      break;
    case '7':          //Mostrar Canciones de una Lista
      mostrarCancionesDeUnaLista(listaDeReproducciones);
      break;
    case '8':          //Salir
      printf("Saliendo...\n");
      liberarTodo(songsByGenres, songsByArtists, songsByTempo, songsById, listaDeReproducciones);
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');
  

  return 0;
}