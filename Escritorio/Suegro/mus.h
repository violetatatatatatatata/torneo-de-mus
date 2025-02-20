#ifndef TORNEO_MUS_H
# define TORNEO_MUS_H

# define BUFFER_SIZE 1024
# define MAX_PARTICIPANTES 60
# define MAX_NOMBRE 1024
# define MAX_PAREJAS 30

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Estructura para representar una pareja
typedef struct {
    int id;                     // Identificador único de la pareja
    char nombre[MAX_NOMBRE];     // Nombre de la pareja
    int puntos;                 // Puntos acumulados en el torneo
    int diferencia_juego;        // Diferencia de juego (en caso de empate)
    int oponentes[MAX_PAREJAS];  // Historial de enfrentamientos (IDs de parejas ya enfrentadas)
    int num_oponentes;           // Contador de enfrentamientos
} Pareja;

// Estructura para representar un partido
typedef struct {
    int pareja1;     // ID de la primera pareja
    int pareja2;     // ID de la segunda pareja
    int resultado1;  // Puntos obtenidos por la primera pareja
    int resultado2;  // Puntos obtenidos por la segunda pareja
} Partido;

// Estructura para representar la clasificación
typedef struct {
    int id;                 // ID de la pareja
    int puntos;             // Puntos acumulados
    int diferencia_juego;   // Diferencia de juego
} Clasificacion;

int leer_participantes(FILE *f, Pareja participantes[], int *num_part);
void generar_parejas(Pareja participantes[], FILE *new_f, int num_part);
void mezclar_indices(int indices[], int num_part);
void generar_clasificacion();

#endif
