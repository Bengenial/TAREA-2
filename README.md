# Spotfind 

Este programa fue desarrollado como parte de un trabajo para la asignatura **Estructura de Datos**. Aunque el escenario es ficticio —una plataforma musical llamada *Spotfind*—, su objetivo es demostrar el uso de **listas enlazadas**, **tablas hash (mapas)** y una eficiente organización de información para facilitar la búsqueda y manejo de canciones.

---

## Descripción

El sistema permite gestionar una base de datos de canciones a través de diferentes criterios como **género**, **artista** o **tempo**, así como la creación y administración de listas de reproducción personalizadas.

Cada canción contiene:

- Un **ID único**
- Una lista de **artistas** (pueden ser múltiples)
- Un **nombre de álbum**
- Un **nombre de pista**
- Un **tempo** (número flotante)
- Un **género**

Las canciones se almacenan en mapas (hash maps) según diferentes criterios para facilitar búsquedas eficientes:

- Por **género**
- Por **artista**
- Por **tempo** (clasificado como *Lenta*, *Moderada* o *Rápida*)
- Por **ID** (para búsquedas rápidas y agregar a listas)

También el usuario podrá crear listas de reproducciónes y cada lista de reproducción contiene:

- Un **Nombre de la lista de reproducción**
- Una lista de **canciónes** de tipo **Song**
---

## Cómo compilar y ejecutar

### Requisitos

- Tener instalado **Visual Studio Code** o cualquier editor compatible con C.
- Tener un compilador de C como **GCC** (por ejemplo, a través de **MinGW** en Windows).
- Asegurarse de tener los archivos fuente necesarios, incluyendo los de los TDA (`list.h`, `map.h`, `extra.h`, `spotfind.h` y sus respectivos `.c`).

### Pasos para compilar y ejecutar

1. Descargar el proyecto completo.
2. Descomprimir el contenido en una carpeta local.
3. Abrir la carpeta del proyecto en **Visual Studio Code**.
4. Abrir un terminal integrado en el editor.
5. Compilar el programa con el siguiente comando:

```bash
gcc tdas/*.c tarea2.c -Wno-unused-result -o tarea2
```

6. Ejecuta el programa
```bash
./tarea2
```

## Comportamiento de las funcionalidades


A continuación se describen las funcionalidades implementadas, indicando su comportamiento esperado:

### Cargar canciones (Opción 1)

Carga canciones desde el archivo `song_dataset_.csv`, creando mapas para buscarlas por:

- Género
- Artista
- Tempo (clasificado como Lenta, Moderada, Rápida)
- ID (para búsquedas específicas y agregar a listas de reproduccion)


---

### Buscar por género (Opción 2)

Permite ingresar un género musical y muestra una lista de canciones asociadas a ese género.

- El usuario puede decidir si desea mostrar todas las canciones o detenerse cada 20 resultados.

---

### Buscar por artista (Opción 3)

Funciona igual que la búsqueda por género, pero filtrando por el nombre del artista (o uno de los artistas, si la canción tiene múltiples).

---

### Buscar por tempo (Opción 4)

Permite buscar canciones por velocidad:

- Lenta (< 80 BPM)
- Moderada (80–120 BPM)
- Rápida (> 120 BPM)

---

### Crear lista de reproducción (Opción 5)

El usuario puede crear una nueva lista personalizada, asignándole un nombre.

- Si ya existe una lista con ese nombre, se notifica al usuario.

---

### Agregar canción a lista (Opción 6)

Permite buscar una canción por su ID y agregarla a una lista existente.

- Si no se encuentra el ID o no existe la lista, se muestra un mensaje de error.


---

### Mostrar canciones de una lista (Opción 7)

Muestra todas las canciones contenidas en una lista de reproducción específica.

- Se solicita el nombre de la lista al usuario.

---

### Salir del programa (Opción 8)

Finaliza la ejecución del programa de forma segura, liberando memoria.

---

### Funcionalidades adicionales

- Las canciones pueden tener múltiples artistas separados por punto y coma.
- Las búsquedas por artista consideran cada artista individualmente.
- Los mapas utilizan el nombre como clave y listas de canciones como valor, permitiendo manejar múltiples resultados por clave.

### Problemas conocidos:
- El tiempo de carga para todos los datos del archivo csv puede ser un poco larga, para ello está comentada una condicion que solo carga las primeras 10000 canciones en la función `cargarCanciones()`
- Algunas canciones están repetidas, sólo difieren en su id
- No se realiza validacion completa de la entrada: Al inicio del menú principal si se ingresa una cadena con el primer caracter válido `opciones 1,2,3,4,5,6,7,8`, se almacena el resto de la cadena para la siguiente instrucción, por lo que puede realizar tareas que no se desean o acelerar el ingreso de datos (no recomendado).



## Ejemplo de uso

**-------------------------------**  
**MENU PRINCIPAL**  
**-------------------------------**  
`1) Cargar canciones`  
`2) Buscar por genero`  
`3) Buscar por artista`  
`4) Buscar por tempo`  
`5) Crear lista de reproduccion`  
`6) Agregar cancion a lista`  
`7) Mostrar canciones de una lista`   
`8) Salir`  
**-------------------------------**  

### Pasos

1. **Cargar canciones**  
   El sistema carga canciones desde un archivo CSV y las organiza en mapas por género, artista, y tempo. La carga de canciones suele tardar alrededor de 7 minutos.

   **-------------------------------------------------------**  
   `Ingrese su opcion: 1`

   `SE CARGARON LAS CANCIONES`  
   `Presione una tecla para continuar...`
   **-------------------------------------------------------**

    El sistema carga las canciones y las organiza en tres mapas: por género, por artista y por tempo.


---

2. **Buscar por género**  
   El usuario ingresa un género y el sistema devuelve una lista de canciones correspondientes.
   El sistema también preguntará si el usuario desea ver todas las canciones de la lista, sólo por temas de comodidad y visibilidad

   **-------------------------------------------------------**  
   `Ingrese su opcion: 2`  
   `Ingrese el genero de la cancion: acoustic`
   `Desea ver todas las canciones? (s)`
   `n`

   `===========================================================================`  
   `          Lista de canciones con genero acoustic:`  
   `===========================================================================`
   
   `---------------------------------------------------------------------------`
   `ID: 0                       Artista: Gen Hoshino`  
   `Tempo: 87.92                Album:   Comedy`
   `Genero: acoustic            Cancion: Comedy`  
   `----------------------------------------------------------`
   `ID: 1                       Artista: Ben Woodward`
   `Tempo: 77.49                Album:   Ghost (Acoustic)`
   `Genero: acoustic            Cancion: Ghost - Acoustic`
   `.`
   `.`
   `===========================================================================`
   `Fin de la lista`

   `Presione una tecla para continuar...`
   **-------------------------------------------------------**

   Las canciones asociadas con el género "acoustic" son mostradas en pantalla.  

---

3. **Buscar por artista**  
   Se puede buscar por un artista y el sistema devuelve todas las canciones asociadas a ese artista.

   **-------------------------------------------------------**  
   `Ingrese su opcion: 3`  
   `Ingrese el artista de la cancion: Kurt Cobain`
   `Desea ver todas las canciones? (s)`
   `s`

   `===========================================================================`  
   `          Lista de canciones con artista Kurt Cobain:`  
   `===========================================================================`
   
   `---------------------------------------------------------------------------`
   `ID: 62                      Artista: Kurt Cobain`  
   `Tempo: 96.64                Album:   Montage Of Heck: The Home Recordings`
   `Genero: acoustic            Cancion: And I Love Her`  
   `----------------------------------------------------------`
   `ID: 468                     Artista: Kurt Cobain`
   `Tempo: 114.26               Album:   Montage Of Heck: The Home Recordings (Deluxe Soundtrack)`
   `Genero: acoustic            Cancion: Burn The Rain`
   `.`
   `.`
   `.`
   `===========================================================================`
   `Fin de la lista`

   `Presione una tecla para continuar...`
   **-------------------------------------------------------**

   El sistema muestra todas las canciones de "Kurt Cobain".  

---

4. **Buscar por tempo**  
   Se realiza una busqueda por el tempo de la canción. El sistema clasifica las canciones en tres categorias de tempo: Lenta, Moderada o Rápida.    

   **-------------------------------------------------------**  
   `Ingrese su opcion: 4`

   `||Lenta||Moderada||Rapida||`
   `Ingrese el tempo de la cancion: Rapida`
   `Desea ver todas las canciones? (s)`
   `n`

   `===========================================================================`  
   `          Lista de canciones con tempo Rapida:`  
   `===========================================================================`
   
   `---------------------------------------------------------------------------`
   `ID: 3                       Artista: Kina Grannis`  
   `Tempo: 181.74               Album:   Crazy Rich Asians (Original Motion Picture Soundtrack)`
   `Genero: acoustic            Cancion: Can't Help Falling In Love`  
   `----------------------------------------------------------`
   `ID: 6                       Artista: A Great Big World, Christina Aguilera`
   `Tempo: 141.28               Album:   Is There Anybody Out There?`
   `Genero: acoustic            Cancion: Say Something`
   `.`
   `.`
   `.`
   `===========================================================================`
   `Fin de la lista`

   `Presione una tecla para continuar...`
   **-------------------------------------------------------**

   El sistema muestra las canciones clasificadas como "Rápida".

---

5. **Crear lista de reproduccion**  
   El usuario puede crear una lista de reproducción personalizada. Si la lista ya existe, el sistema informa que no se puede crear nuevamente.

   **-------------------------------------------------------**  
   `Ingrese su opcion: 5`

   `Ingrese el nombre de la nueva lista: paraDormir`
   `Se creo la lista 'paraDormir`
   `Presione una tecla para continuar...`
   **-------------------------------------------------------**

   Se crea una nueva lista llamada "paraDormir".

   **Caso especial**
   
   **-------------------------------------------------------**  
   `Ingrese su opcion: 5`

   `Ingrese el nombre de la nueva lista: paraDormir`
   `La lista ya existe`
   `Presione una tecla para continuar...`
   **-------------------------------------------------------**
   
    Al ya haber una lista llamada "paraDormir", el programa te informa que ya existe
    y se sale del Crear lista Reproducción
    
---

6. **Agregar cancion a lista**  
   Se busca por ID de canción y se agrega a la lista de reproducción seleccionada.

   **-------------------------------------------------------**  
   `Ingrese su opcion: 6`

   `Ingrese el Nombre de la lista: paraDormir`
   `Ingrese el ID de la cancion: 22010`  
   `Se agrego la cancion Angel Of Death a la lista`  
   `Cancion con ID 1 agregada a 'paraDormir'.`  

   **-------------------------------------------------------**

   La canción con ID 1 se agrega a la lista "Lista de Verano".

---

7. **Mostrar canciones de una lista**  
   El sistema muestra las canciones almacenadas en una lista de reproducción especifica.

   **-------------------------------------------------------**  
   `Ingrese su opcion: 7`

   `Ingrese el Nombre de la lista: paraDormir`  
   `---------------------------------------------------------------------------`  
   `ID: 22010                   Artista: Slayer`  
   `Tempo: 105.46               Album:   Reign In Blood (Expanded)`  
   `Genero: death-metal         Cancion: Angel Of Death`  
   `----------------------------------------------------------`
   `ID: 16957                   Artista: Wolfgang Amadeus Mozart, The Monteverdi Choir, English Baroque Soloists, John Eliot Gardiner`
   `Tempo: 161.75               Album:   Mozart - Inspiring Classics`
   `Genero: classical           Cancion: Requiem in D minor, K.626: 3. Sequentia: Dies irae`
   **-------------------------------------------------------**

   El sistema muestra las canciones dentro de la lista "paraDormir".

---

   El sistema carga las canciones y las organiza en tres mapas: por genero, por artísta y por tempo.

8. **Salir de la aplicación**
   El sistema termina liberando la memoria de los mapas y listas creadas

   **-------------------------------------------------------**
   `Ingrese su opcion: 8`

   `Saliendo...`
   `Memoria liberada correctamente.`
   `Presione una tecla para continuar...`
   **-------------------------------------------------------**