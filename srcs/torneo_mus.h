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

// variable global para las rondas
extern int ronda_actual;

// Estructura para representar una pareja
typedef struct {
	int	id;                     // Identificador único de la pareja
	char	nombre[MAX_NOMBRE];     // Nombre de la pareja
	int	puntos;                 // Puntos acumulados en el torneo
	int	diferencia_juego;        // Diferencia de juego (en caso de empate)
	int	oponentes[MAX_PAREJAS];  // Historial de enfrentamientos (IDs de parejas ya enfrentadas)
	int	num_oponentes;           // Contador de enfrentamientos
} Pareja;

// Estructura para representar un partido
typedef struct {
	int	pareja1;     // ID de la primera pareja
	int	pareja2;     // ID de la segunda pareja
	int	resultado1;  // Puntos obtenidos por la primera pareja
	int	resultado2;  // Puntos obtenidos por la segunda pareja
} Partido;

// Estructura para representar la clasificación
typedef struct {
	int	id;                 // ID de la pareja
	int	puntos;             // Puntos acumulados
	int	diferencia_juego;   // Diferencia de juego
} Clasificacion;

int	leer_participantes(FILE *f, Pareja participantes[], int *num_part);
void	generar_parejas(Pareja participantes[], FILE *new_f, int num_part);
void	mezclar_indices(int indices[], int num_part);
int	verificar_duplicados(Pareja participantes[], int num_part);
int	validar_archivo_participantes(FILE *f);
void	generar_puntuaciones();
void	actualizar_clasificacion(Pareja participantes[], int num_part);
void	actualizar_puntuaciones(Pareja participantes[], int num_part);
void	ordenar_por_puntos(Pareja participantes[], int num_part);
int	leer_parejas(Pareja participantes[]);
int	generar_enfrentamientos(Pareja participantes[], int num_part, Partido enfrentamientos[]);
int	ya_se_enfrentaron(Pareja pareja1, Pareja pareja2);
void	guardar_enfrentamientos(Partido enfrentamientos[], int num_enfrentamientos, Pareja participantes[]);
void	actualizar_historial(Pareja participantes[], Partido enfrentamientos[], int num_enfrentamientos);
void	sobreescribir_puntuaciones();

#endif
