#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "hashmap.h"
#include "list.h"

typedef struct {
    char nombre[101];
    char tipo[101];
    char direccion[101];
    char horario[101];
    char descripcion[101];
} puntoInteres;

typedef struct {
    char pasaporte[101];
    char nombre[101];
    char pais[101];
    List *favoritePlaces;
} turista;

void imprimirMenu();
void leerDato(char **dato, int max);
void registrarPunto(HashMap *puntoInteres_tipo, HashMap *puntoInteres_nombre, const char nombreInteres[], const char tipo[], const char direccion[], const char horario[], const char descripcion[]);
void mostrarDatos_PuntoInteres(HashMap *puntoInteres_nombre, const char nombreInteres[]);
void eliminar_PuntoInteres(HashMap *puntoInteres_nombre, const char nombreInteres[]);
void registrarTurista(HashMap *turistas_pasaporte, HashMap *turistas_pais, const char pasaporte[], const char nombreTurista[], const char pais[], const char favoritePlace[]);
void agregarLugarFavorito(HashMap *turistas_pasaporte, const char pasaporte[], const char nombre_lugar[]);
void mostrarTuristasPorPais(HashMap *turistas_pasaporte, const char pais[]);
void mostrarPuntosDeInteresPorTipo(HashMap *puntoInteres_nombre, const char tipo[]);
void importarDesdeCSV(HashMap *puntoInteres_tipo, HashMap *puntoInteres_nombre, HashMap *turistas_pasaporte, HashMap *turistas_pais, const char *nombre_archivo_puntos, const char *nombre_archivo_turistas);
void exportarPuntosDeInteresACSV(HashMap *puntoInteres_nombre, const char *nombre_archivo_puntos);
void exportarTuristasACSV(HashMap *turistas_pasaporte, const char *nombre_archivo_turistas);

#endif  // FUNCIONES_H