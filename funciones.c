#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include "list.h"
#include "funciones.h"

void imprimirMenu(){
/*Función que imprime las opciones del menu para el usuario*/
  printf("Por favor ingrese el número de la función deseada\n");
  printf("1.Registrar punto de interés\n");
  printf("2.Mostrar datos de punto de interés\n");
  printf("3.Eliminar punto de interés\n");
  printf("4.Registrar turista\n");
  printf("5.Agregar lugar favorito a turista\n");
  printf("6.Mostrar turistas por país\n");
  printf("7.Mostrar todos los puntos de interés de un tipo\n");
  printf("8.Importar puntos de interés y turistas desde archivos CSV\n");
  printf("9.Exportar puntos de interés y turistas a archivos CSV\n");
  printf("10.Salir\n");
}

void leerDato(char **dato, int max) {
    // Buffer temporal para leer la entrada
    char buffer[max + 1];

    // Leer la entrada del usuario desde la consola y manejo de error
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error al leer la entrada");
        exit(EXIT_FAILURE);
    }

    // Eliminar el salto de línea si existe al final del buffer
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    // Verificar si la longitud del dato ingresado es válida
    if (strlen(buffer) <= max) {
        // Asignar memoria dinámica para el dato
        *dato = (char *)malloc((strlen(buffer) + 1) * sizeof(char));

        if (*dato == NULL) {
            printf("Error al asignar memoria dinámica");
            exit(EXIT_FAILURE);
        }

        // Copiar el dato ingresado al espacio de memoria asignado
        strcpy(*dato, buffer);
    } else {
        printf("Error: La longitud del dato excede el límite de %i caracteres.\n", max);
        exit(EXIT_FAILURE);
    }
}

//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\

void registrarPunto(HashMap *puntoInteres_tipo, HashMap *puntoInteres_nombre, const char nombreInteres[], const char tipo[], const char direccion[], const char horario[], const char descripcion[]) {
    // Crear un nuevo punto de interés (usando memoria dinámica)
    puntoInteres *nuevoPunto = (puntoInteres *)malloc(sizeof(puntoInteres));

    if (nuevoPunto == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo punto de interés.\n");
        return;
    }

    // Llenar los datos del punto de interés
  strcpy(nuevoPunto->nombre, nombreInteres);
  strcpy(nuevoPunto->tipo, tipo);
  strcpy(nuevoPunto->direccion, direccion);
  strcpy(nuevoPunto->horario, horario);
  strcpy(nuevoPunto->descripcion, descripcion);

  insertMap(puntoInteres_nombre, nuevoPunto->nombre, nuevoPunto);
  insertMap(puntoInteres_tipo, nuevoPunto->tipo, nuevoPunto);
  
    // Verificar si se insertó correctamente en ambos HashMaps
    if (searchMap(puntoInteres_nombre, nuevoPunto->nombre) != NULL &&
        searchMap(puntoInteres_tipo, nuevoPunto->tipo) != NULL) {
        printf("Punto de interés registrado correctamente.\n");
    } else {
        printf("Error: No se pudo registrar el punto de interés correctamente.\n");
        // Si no se pudo insertar correctamente, liberamos la memoria asignada para el punto.
        free(nuevoPunto);
    }
  
}

void mostrarDatos_PuntoInteres(HashMap *puntoInteres_nombre , const char nombreInteres[]) {
    // Buscamos el punto de interés usando su nombre en el mapa "puntoInteres_nombre", para mostrar sus datos.
    Pair *buscarPunto = searchMap(puntoInteres_nombre, (char *)nombreInteres);

    if (buscarPunto != NULL) {
        // Si se encuentra el punto de interés
        puntoInteres *punto = (puntoInteres *)(buscarPunto->value);
        // Mostramos los dato del punto de interés por pantalla
        printf("\nNombre: %s\n", punto->nombre);
        printf("Tipo: %s\n", punto->tipo);
        printf("Dirección: %s\n", punto->direccion);
        printf("Horario: %s\n", punto->horario);
        printf("Descripción: %s\n", punto->descripcion);
    } else {
        // Si no se encuentra el punto de interés se muestra el siguiente mensaje:
        printf("\nPunto de interés llamado %s no se logró encontrar.\n", nombreInteres);
    }
}

void eliminar_PuntoInteres(HashMap *puntoInteres_nombre , const char nombreInteres[]) {
  // Buscamos el punto de interés usando su nombre en el mapa "puntoInteres_nombre", para mostrar sus datos.
  Pair *buscarPunto = searchMap(puntoInteres_nombre, (char *)nombreInteres);

  if (buscarPunto != NULL) {
  // Si se encuentra el punto de interés en el mapa, lo eliminamos usando la función eraseMap
  eraseMap(puntoInteres_nombre, (char *)nombreInteres);
  printf("\nPunto de interés llamado %s se logró eliminar con éxito.\n", nombreInteres);
  } else {
  // Si no se encuentra el punto de interés se muestra el siguiente mensaje:
    printf("\nPunto de interés llamado %s no se logró encontrar.\n", nombreInteres);
  }
}

void registrarTurista(HashMap *turistas_pasaporte, HashMap *turistas_pais, const char pasaporte[], const char nombreTurista[], const char pais[], const char favoritePlace[]) {
    // Crear un nuevo punto de interés (usando memoria dinámica)
      turista *nuevoTurista = (turista *)malloc(sizeof(turista));

    if (nuevoTurista == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo punto de interés.\n");
        return;
    }

    // Llenar los datos del punto de interés
  strcpy(nuevoTurista->pasaporte, pasaporte);
  strcpy(nuevoTurista->nombre, nombreTurista);
  strcpy(nuevoTurista->pais, pais);
  nuevoTurista->favoritePlaces = createList();

  char *token = strtok((char *)favoritePlace, ";");
    while (token != NULL) {
        char *place = (char *)malloc(strlen(token) + 1);
        strcpy(place, token);
        pushBack(nuevoTurista->favoritePlaces, place);
        token = strtok(NULL, ";");
    }
  
  insertMap(turistas_pasaporte, nuevoTurista->pasaporte, nuevoTurista);
  insertMap(turistas_pais, nuevoTurista->pais, nuevoTurista);
  
    // Verificar si se insertó correctamente en ambos HashMaps
    if (searchMap(turistas_pasaporte, nuevoTurista->pasaporte) != NULL &&
        searchMap(turistas_pais, nuevoTurista->pais) != NULL) {
        printf("Punto de interés registrado correctamente.\n");
    } else {
        printf("Error: No se pudo registrar el punto de interés correctamente.\n");
        // Si no se pudo insertar correctamente, liberamos la memoria asignada para el punto.
        free(nuevoTurista);
    }
}

void agregarLugarFavorito(HashMap *turistas_pasaporte, const char pasaporte[], const char nombre_lugar[]) {
    // Buscar al turista por su pasaporte
    Pair *buscarTurista = searchMap(turistas_pasaporte, (char *)pasaporte);

    if (buscarTurista != NULL) {
        turista *t = (turista *)(buscarTurista->value);
        // Agregar el lugar favorito a la lista del turista
        pushBack(t->favoritePlaces, (void *)nombre_lugar);
        printf("Lugar favorito \"%s\" agregado al turista con pasaporte \"%s\".\n", nombre_lugar, pasaporte);
    } else {
        printf("Turista con pasaporte \"%s\" no encontrado.\n", pasaporte);
    }
}

void mostrarTuristasPorPais(HashMap *turistas_pais, const char pais[]) {
      // Iterar sobre el mapa de turistas por país
    for (int i = 0; i < turistas_pais->capacity; i++) {
        Pair *currentPair = turistas_pais->buckets[i];
        // Verificar si hay un par en la posición actual
        while (currentPair != NULL) {
            turista *t = (turista *)(currentPair->value);
            // Verificar si el país coincide
            if (strcmp(t->pais, pais) == 0) {
                printf("Turista con pasaporte: %s\n", t->pasaporte);
                printf("Nombre: %s\n", t->nombre);

                // Mostrar lugares favoritos
                printf("Lugares favoritos:\n");
                Node *current = t->favoritePlaces->head;
                while (current != NULL) {
                    printf("- %s\n", (char *)current->data);  // Modificamos aquí para imprimir correctamente
                    current = current->next;
                }
                printf("\n");
            }
            currentPair = nextMap(turistas_pais);
        }
    }
}

void mostrarPuntosDeInteresPorTipo(HashMap *puntoInteres_nombre, const char tipo[]) {
    // Buscar el tipo en el HashMap
    Pair *buscarTipo = searchMap(puntoInteres_nombre, (char *)tipo);

    if (buscarTipo != NULL) {
        puntoInteres *punto = (puntoInteres *)(buscarTipo->value);
        printf("Puntos de interés del tipo \"%s\":\n", tipo);

        // Imprimir los puntos de interés del mismo tipo
        printf("- %s\n", punto->nombre);

        printf("\n");
    } else {
        printf("No se encontraron puntos de interés del tipo \"%s\".\n", tipo);
    }
}


const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

int countFields(const char *linea) {
  int campos = 0;
  int longitud = strlen(linea);
  int dentro_del_campo = 0;

  for (int i = 0; i < longitud; i++) {
    if (linea[i] == ',') {
      // Si encontramos una coma y no estamos dentro de un campo entre comillas, incrementamos el contador de campos
      if (!dentro_del_campo) {
        campos++;
      }
    } else if (linea[i] == '"') {
      // Cambiamos el estado de "dentro_del_campo" cuando encontramos comillas
      dentro_del_campo = 1 - dentro_del_campo;
    }
  }
  // Agregamos 1 al contador final para incluir el último campo
  return campos + 1;
}

void importarDesdeCSV(HashMap *puntoInteres_tipo, HashMap *puntoInteres_nombre, HashMap *turistas_pasaporte, HashMap *turistas_pais, const char *nombre_archivo_puntos, const char *nombre_archivo_turistas) {
    // Importar puntos de interés
    FILE *archivo_puntos = fopen(nombre_archivo_puntos, "r");
    if (archivo_puntos == NULL) {
        printf("No se pudo abrir el archivo de puntos de interés: %s\n", nombre_archivo_puntos);
        return;
    }

    // Leer y descartar la primera línea (encabezados)
    char linea_puntos[1000];
    if (fgets(linea_puntos, sizeof(linea_puntos), archivo_puntos) == NULL) {
        fclose(archivo_puntos);
        printf("El archivo CSV de puntos de interés está vacío o no se pudo leer.\n");
        return;
    }

    while (fgets(linea_puntos, sizeof(linea_puntos), archivo_puntos)) {
        // Obtener los datos de un punto de interés
        const char *nombreInteres = get_csv_field(linea_puntos, 0);
        const char *tipo = get_csv_field(linea_puntos, 1);
        const char *direccion = get_csv_field(linea_puntos, 2);
        const char *horario = get_csv_field(linea_puntos, 3);
        const char *descripcion = get_csv_field(linea_puntos, 4);

        // Registrar el punto de interés en los mapas
        registrarPunto(puntoInteres_tipo, puntoInteres_nombre, nombreInteres, tipo, direccion, horario, descripcion);
    }

    fclose(archivo_puntos);

    // Importar turistas
    FILE *archivo_turistas = fopen(nombre_archivo_turistas, "r");
    if (archivo_turistas == NULL) {
        printf("No se pudo abrir el archivo de turistas: %s\n", nombre_archivo_turistas);
        return;
    }

    // Leer y descartar la primera línea (encabezados)
    char linea_turistas[1000];
    if (fgets(linea_turistas, sizeof(linea_turistas), archivo_turistas) == NULL) {
        fclose(archivo_turistas);
        printf("El archivo CSV de turistas está vacío o no se pudo leer.\n");
        return;
    }

       while (fgets(linea_turistas, sizeof(linea_turistas), archivo_turistas)) {
        // Obtener los datos de un turista
        const char *pasaporte = get_csv_field(linea_turistas, 0);
        const char *nombreTurista = get_csv_field(linea_turistas, 1);
        const char *pais = get_csv_field(linea_turistas, 2);
        const char *favoritePlaces = get_csv_field(linea_turistas, 3);

        // Registrar el turista después de haber procesado sus lugares favoritos
        registrarTurista(turistas_pasaporte, turistas_pais, pasaporte, nombreTurista, pais, favoritePlaces);

        // Separar los puntos de interés favoritos del turista
        char *token = strtok((char *)favoritePlaces, ";");
        // Flag para indicar si ya hemos encontrado el primer ";"
        int foundFirstSemicolon = 0;

        while (token != NULL) {
            // Si encontramos el primer ";", activamos el flag
            if (!foundFirstSemicolon) {
                foundFirstSemicolon = 1;
            } else {
                agregarLugarFavorito(turistas_pasaporte, pasaporte, token);
            }

            token = strtok(NULL, ";");
        }
    }

    fclose(archivo_turistas);

    printf("Los datos se han importado correctamente desde los archivos CSV.\n");
}

void exportarPuntosDeInteresACSV(HashMap *puntoInteres_nombre, const char *nombre_archivo_puntos) {
    FILE *archivo_puntos = fopen(nombre_archivo_puntos, "w");
    if (archivo_puntos == NULL) {
        printf("No se pudo abrir el archivo %s para escritura.\n", nombre_archivo_puntos);
        return;
    }

    // Escribir encabezados al archivo CSV
    fprintf(archivo_puntos, "Nombre,Tipo,Direccion,Horario,Descripcion\n");

    // Iterar sobre los puntos de interés y escribir cada uno en una línea del archivo CSV
    for (int i = 0; i < puntoInteres_nombre->capacity; i++) {
        Pair *currentPair = puntoInteres_nombre->buckets[i];
        while (currentPair != NULL) {
            puntoInteres *punto = (puntoInteres *)(currentPair->value);
            // Escribir los datos del punto de interés en el archivo CSV
            fprintf(archivo_puntos, "%s,%s,%s,%s,%s\n", punto->nombre, punto->tipo, punto->direccion, punto->horario, punto->descripcion);
            currentPair = nextMap(puntoInteres_nombre);
        }
    }

    fclose(archivo_puntos);
    printf("Los puntos de interés se han exportado correctamente al archivo CSV: %s\n", nombre_archivo_puntos);
}

void exportarTuristasACSV(HashMap *turistas_pasaporte, const char *nombre_archivo_turistas) {
    FILE *archivo_turistas = fopen(nombre_archivo_turistas, "w");
    if (archivo_turistas == NULL) {
        printf("No se pudo abrir el archivo %s para escritura.\n", nombre_archivo_turistas);
        return;
    }

    // Escribir encabezados al archivo CSV
    fprintf(archivo_turistas, "Pasaporte,Nombre,Pais,LugaresFavoritos\n");

    // Iterar sobre los turistas y escribir cada uno en una línea del archivo CSV
    for (int i = 0; i < turistas_pasaporte->capacity; i++) {
        Pair *currentPair = turistas_pasaporte->buckets[i];
        while (currentPair != NULL) {
            turista *t = (turista *)(currentPair->value);
            // Escribir los datos del turista en el archivo CSV
            fprintf(archivo_turistas, "%s,%s,%s,", t->pasaporte, t->nombre, t->pais);

            // Escribir los lugares favoritos del turista en la misma línea
            Node *current = t->favoritePlaces->head;
            while (current != NULL) {
                fprintf(archivo_turistas, "%s", (char *)current->data);

                // Verificar si es el último elemento antes de imprimir la coma
                if (current->next != NULL) {
                    fprintf(archivo_turistas, ";");
                }

                current = current->next;
            }
            fprintf(archivo_turistas, "\n");
            currentPair = nextMap(turistas_pasaporte);
        }
    }

    fclose(archivo_turistas);
    printf("Los turistas se han exportado correctamente al archivo CSV: %s\n", nombre_archivo_turistas);
}
