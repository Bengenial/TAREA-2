#include "extra.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    List *artists;
    char albumName[250];   //100 
    char trackName[550];  //100
    float tempo;
    char trackGenre[100];  //100

} Song;

typedef struct {
    char nombre[100];
    List *canciones;
}listaReproduccion;

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("                Spotfind");
    puts("========================================");

    puts("1) Cargar Canciones");
    puts("2) Buscar por Genero");
    puts("3) Buscar por Artista");
    puts("4) Buscar por Tempo");
    puts("5) Crear Lista de Reproduccion");
    puts("6) Agregar Cancion a la Lista");
    puts("7) Mostrar Canciones de una Lista");
    puts("8) Salir");
}

int is_equal_str(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
}

int is_equal_int(void *key1, void *key2) {
    return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

void cargarCanciones(Map *songsByGenres, Map *songsByArtists, Map *songsByTempo, Map *songsById){
    FILE *archivo = fopen("data/song_dataset_.csv", "r"); // Encuentra el archivo en la carpeta data
    if (archivo == NULL) {
      perror("Error al abrir el archivo");
      return;
    }
  
    char **campos;
  
    campos = leer_linea_csv(archivo, ',');
    //int k = 0;
    while ((campos = leer_linea_csv(archivo, ',')) != NULL){
      //k++;
      //if (k>10000) break; //condicion para no cargar todo el archivo con propositos de testeo 
      
      Song *cancion = (Song *)malloc(sizeof(Song));
  
      cancion->id = atoi(campos[0]);           // Asigna ID
      cancion->artists = split_string(campos[2], ";"); //crea la lista de artistas
      
      strcpy(cancion->albumName, campos[3]);   // Asigna album
      strcpy(cancion->trackName, campos[4]);   // Asigna nombre cancion
      cancion->tempo = atof(campos[18]);       // Asigna tempo
          
      strcpy(cancion->trackGenre, campos[20]); // Asigna genero
  
      //Lista generos
      MapPair *pairGenero = map_search(songsByGenres, cancion->trackGenre);
      List *listaGeneros;
      
      if (pairGenero == NULL){
        listaGeneros = list_create();
        map_insert(songsByGenres, cancion->trackGenre, listaGeneros);
      }
      else{
        listaGeneros = pairGenero->value;
      }
      
      list_pushBack(listaGeneros, cancion);
  
  
      //Lista artistas
      char *artista = list_first(cancion->artists);
      while (artista != NULL){
        MapPair *pairArtista = map_search(songsByArtists, artista);
        List *listaArtistas;
        if (pairArtista == NULL){
          listaArtistas = list_create();
          map_insert(songsByArtists, artista, listaArtistas);
        }
        else{
          listaArtistas = pairArtista->value;
        }
        list_pushBack(listaArtistas, cancion);
        artista = list_next(cancion->artists);
        
      }
      
      //Lista tempo
      //Mi clave va a ser un string que diga si es rapida, moderada o lenta
      char *clave;
      if (cancion->tempo < 80)
        clave = "Lenta";
      else if (cancion->tempo <= 120)
        clave = "Moderada";
      else
        clave = "Rapida";
      
      MapPair *pairTempo = map_search(songsByTempo, clave);
      List *listaTempo;
  
      if (pairTempo == NULL){
        listaTempo = list_create();
        map_insert(songsByTempo, clave, listaTempo);
      }
      else{
        listaTempo = pairTempo->value;
      }
      list_pushBack(listaTempo, cancion);
  
      //Lista id
      map_insert(songsById, &cancion->id, cancion);
    
    }
    printf("SE CARGARON LAS CANCIONES\n");
    fclose(archivo);
}

void mostrarPor(Map *mapaCanciones, char *mensaje){
    char texto[100];
    printf("Ingrese el %s de la cancion: ", mensaje);
    scanf(" %[^\n]", texto);
    
    MapPair *pair = map_search(mapaCanciones, texto);
    if (pair != NULL){ // si exite la clave se muestra la lista de canciones del genero, artista o tempo
        List *canciones = pair->value;
        Song *cancion = list_first(canciones);
        
        int contador;
        char opcion[10];
        printf(" Desea ver todas las canciones? (s)\n");
        scanf(" %s", opcion);
      
        if (strcmp(opcion, "s")) contador = 0;
        else contador = -1;
      
        printf("\n===========================================================================\n");
        printf("          Lista de canciones con %s %s:\n", mensaje, texto);
        printf("===========================================================================\n\n");
      
        while (cancion != NULL){
          char *artista = list_first(cancion->artists);
          printf("---------------------------------------------------------------------------\n");
          printf("ID: %-23d Artista: %s", cancion->id, artista);
          artista = list_next(cancion->artists);
          while (artista != NULL){
            printf(", %s", artista);
            artista = list_next(cancion->artists);
          }
          puts("");
          printf("Tempo: %-20.2f Album:   %s\n", cancion->tempo, cancion->albumName);
          printf("Genero: %-19s Cancion: %s\n", cancion->trackGenre, cancion->trackName);
          
          
          if (contador != -1) contador++;
          if (contador == 20){
            printf("Si desea ver mas canciones escriba (s)\n");
            scanf(" %s", opcion);
            if (strcmp(opcion, "s")) break;
            limpiarPantalla();
            contador = 0;
            
          }
          cancion = list_next(canciones);
        }
      printf("===========================================================================\n");
      printf("Fin de la lista\n\n");
        
    }
    else printf("El %s %s no existe\n", mensaje, texto);
  
}

void crearListaReproduccion(Map *mapaListas){
  printf("Ingrese el nombre de la nueva lista: ");
  char nombreLista[100];
  scanf(" %[^\n]", nombreLista);

  // Verificar si ya existe
  MapPair *existente = map_search(mapaListas, nombreLista);
  if (existente != NULL){
    printf("La lista ya existe\n");
    return;
  }
  
  listaReproduccion *listaRep = (listaReproduccion *)malloc(sizeof(listaReproduccion));
  if (listaRep == NULL){
    printf("Error al crear la lista\n");
    return;
  }
  strcpy(listaRep->nombre, nombreLista);
  listaRep->canciones = list_create();
  
  map_insert(mapaListas, listaRep->nombre, listaRep);
  printf("Se creo la lista '%s'\n", listaRep->nombre);
  return;
  

}

void agregarCancionALista(Map *mapaListas, Map *songsById){
  printf("Ingrese el Nombre de la lista: ");
  char nombreLista[100];
  scanf(" %[^\n]", nombreLista);

  MapPair *pair = map_search(mapaListas, nombreLista);
  if (pair == NULL){
    printf("La lista no existe\n");
    return;
  }
  
  listaReproduccion *lista = pair->value;
  
  printf("Ingrese el ID de la cancion: ");
  
  int id;
  scanf("%d", &id);
  MapPair *cancionAgre = map_search(songsById, &id);
  
  if (cancionAgre == NULL){
    printf("La cancion no existe\n");
    return;
  }
  
  Song *cancion = cancionAgre->value;
  //listaReproduccion * listaPrueba = lista->canciones; //list_pushBack(lista, cancion); //prueba
  list_pushBack(lista->canciones, cancion);
  
  //list_pushBack(lista->canciones, cancion);
  printf("Se agrego la cancion %s a la lista\n", cancion->trackName);
  
}

void mostrarCancionesDeUnaLista(Map *listaDeReproducciones){
    printf("Ingrese el Nombre de la lista: ");
    char nombreLista[100];
    scanf(" %[^\n]", nombreLista);
  
    MapPair *pair = map_search(listaDeReproducciones, nombreLista);
    if (pair == NULL){
      printf("La lista no existe\n");
      return;
    }
    listaReproduccion *lista = pair->value;
    if (list_first(lista->canciones) == NULL){
      printf("La lista esta vacia\n");
      return;
    }
    
    Song *cancion = list_first(lista->canciones);
    while(cancion != NULL){ //imprime la lista de canciones
      char *artista = list_first(cancion->artists);
      printf("---------------------------------------------------------------------------\n");
      printf("ID: %-23d Artista: %s", cancion->id, artista);
      artista = list_next(cancion->artists);
      while (artista != NULL){
        printf(", %s", artista);
        artista = list_next(cancion->artists);
      }
      puts("");
      printf("Tempo: %-20.2f Album:   %s\n", cancion->tempo, cancion->albumName);
      printf("Genero: %-19s Cancion: %s\n", cancion->trackGenre, cancion->trackName);
      cancion = list_next(lista->canciones);
      
    }
}

/// Libera toda la memoria dinámica usada por los mapas y listas del programa.
void liberarTodo(Map *songsByGenres, Map *songsByArtists, Map *songsByTempo,
                 Map *songsById, Map *listaDeReproducciones) {
  MapPair *par;

  // Liberar canciones desde songsById
  par = map_first(songsById);
  while (par != NULL) {
    Song *song = par->value;
    if (song != NULL) {
      if (song->artists != NULL)
        free(song->artists);  // liberar lista de artistas
      free(song);             // liberar canción
    }
    par = map_next(songsById);
  }
  free(songsById);

  // Liberar listas de genres
  par = map_first(songsByGenres);
  while (par != NULL) {
    List *lista = par->value;
    if (lista != NULL) free(lista);
    par = map_next(songsByGenres);
  }
  free(songsByGenres);

  // Liberar listas de artistas
  par = map_first(songsByArtists);
  while (par != NULL) {
    List *lista = par->value;
    if (lista != NULL) free(lista);
    par = map_next(songsByArtists);
  }
  free(songsByArtists);

  // Liberar listas por tempo
  par = map_first(songsByTempo);
  while (par != NULL) {
    List *lista = par->value;
    if (lista != NULL) free(lista);
    par = map_next(songsByTempo);
  }
  free(songsByTempo);

  // Liberar listas de reproducción
  par = map_first(listaDeReproducciones);
  while (par != NULL) {
    listaReproduccion *lista = par->value;
    if (lista != NULL) {
      if (lista->canciones != NULL)
        free(lista->canciones);
      free(lista);
    }
    par = map_next(listaDeReproducciones);
  }
  free(listaDeReproducciones);

  printf("Memoria liberada correctamente.\n");
}

