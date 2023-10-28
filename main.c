#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashmap.h"
#include "list.h"
#include "funciones.h"

int main( int argc, char *argv[] ){
  
  HashMap *puntoInteres_tipo = createMap(5);
  HashMap *puntoInteres_nombre = createMap(5);
  HashMap *turistas_pasaporte = createMap(5);
  HashMap *turistas_pais = createMap(5);
  
  int menu;
  char *nombreInteres = NULL;
  char *tipo = NULL;
  char *direccion = NULL;
  char *horario = NULL;
  char *descripcion = NULL;

//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\

  char *pasaporte = NULL;
  char *nombreTurista = NULL;
  char *pais = NULL;
  char *favoritePlace = NULL;
 
//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\*//*\\

  char *archivoPuntos = NULL;
  char *archivoTuristas = NULL;
  
  printf("\n");
  //Ciclo iterativo para acceder a las funciones del menu.
  do{
    imprimirMenu();
    printf("\n");
    scanf("%i",&menu);
    getchar();
    printf("\n");
    //En caso de no ser un numero valido para el menu se saltará las lineas de codigo del menu
    if(menu>10 || menu<0) printf("Escriba un número valido");
    else{
      switch(menu){
        case 1: {
          printf("Ingrese el Nombre del Punto de Interés Turistico: ");
          leerDato(&nombreInteres,101);
          
          printf("Ingrese la categoria correspondiente al 'Tipo' de interes turistico: ");
          leerDato(&tipo,101);

          printf("Ingrese dirección del Punto De Interés Turistico: ");
          leerDato(&direccion,101);

          printf("Ingrese el horario del Punto De Interés Turistico: ");
          leerDato(&horario,101);
          
          printf("Describa brevemente el interes turistico: ");
          leerDato(&descripcion,101);
          
          
          registrarPunto(puntoInteres_tipo, puntoInteres_nombre ,nombreInteres,tipo,direccion,horario,descripcion);
          free(nombreInteres);
          free(tipo);
          free(direccion);
          free(horario);
          free(descripcion);
          break;
        }    
        case 2:{
          printf("Ingrese el Nombre del Punto de Interés Turistico: ");
          leerDato(&nombreInteres,101);
          
          mostrarDatos_PuntoInteres(puntoInteres_nombre,  nombreInteres);
          free(nombreInteres);
          break;
        }
        case 3:{
          printf("Ingrese el Nombre del Punto de Interés Turistico: ");
          leerDato(&nombreInteres,101);
          eliminar_PuntoInteres(puntoInteres_nombre, nombreInteres);
          free(nombreInteres);
          break;
        }
        case 4: {
          printf("Ingrese el numero de pasaporte correspondiente: ");
          leerDato(&pasaporte,101);
          
          printf("Ingrese el Nombre del turista: ");
          leerDato(&nombreTurista,101);

          printf("Ingrese pais de origen del turista: ");
          leerDato(&pais,101);

          printf("Ingrese lugares favoritos del turista, separados Solo por ';' si es más de 1: ");
          leerDato(&favoritePlace,101);
          
          registrarTurista(turistas_pasaporte,turistas_pais, pasaporte, nombreTurista, pais,favoritePlace);
          
          free(pasaporte);
          free(nombreTurista);
          free(pais);
          free(favoritePlace);
          break;
            }
        case 5:
          printf("Ingrese el numero de pasaporte correspondiente: ");
          leerDato(&pasaporte,101);
          
          printf("Ingrese el Nombre del lugar a agregar: ");
          leerDato(&favoritePlace,101);
          
          agregarLugarFavorito(turistas_pasaporte, pasaporte, favoritePlace);
          
          free(favoritePlace);
          free(pasaporte);
          break;
        case 6:
          printf("Ingrese el país del cual desea saber sus turistas: ");
          leerDato(&pais,101);

          mostrarTuristasPorPais(turistas_pasaporte,pais);
          free(pais);
          break;
        case 7:
          printf("Ingrese la categoria correspondiente al 'Tipo' de interes turistico: ");
          leerDato(&tipo,101);
          
          mostrarPuntosDeInteresPorTipo(puntoInteres_nombre,tipo);

          free(tipo);
          break;
        case 8:
          printf("Ingrese el nombre del archivo CSV de Puntos de Interes: ");
          leerDato(&archivoPuntos,101);
          
          printf("Ingrese el nombre del archivo CSV de Turistas: ");
          leerDato(&archivoTuristas,101);

          importarDesdeCSV(puntoInteres_tipo,puntoInteres_nombre, turistas_pasaporte, turistas_pais, archivoPuntos, archivoTuristas);
          free(archivoTuristas);
          free(archivoPuntos);
          break;
        case 9:
          printf("Ingrese el nombre del archivo CSV de Puntos de Interes: ");
          leerDato(&archivoPuntos,101);
          exportarPuntosDeInteresACSV(puntoInteres_nombre,archivoPuntos);
          printf("Ingrese el nombre del archivo CSV de Turistas: ");
          leerDato(&archivoTuristas,101);
          exportarTuristasACSV(turistas_pasaporte, archivoTuristas);  
          free(archivoTuristas);
          free(archivoPuntos);
          break;
      }  
    }
    printf("\n");
  } while (menu != 10);
  
  printf("FIN DEL PROGRAMA");
  free(puntoInteres_tipo); // Liberar la estructura de la lista de libros en sí
  free(puntoInteres_nombre); 
  return 0;
}