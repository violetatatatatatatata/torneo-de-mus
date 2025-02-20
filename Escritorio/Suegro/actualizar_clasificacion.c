#include "mus.h"

void actualizar_puntuaciones(Pareja participantes[], int num_part) {
	FILE *clasificacion;
	char linea[BUFFER_SIZE];
	int puntos1, puntos2;
	char pareja1[MAX_NOMBRE], pareja2[MAX_NOMBRE];

	clasificacion = fopen("clasificacion.txt", "r");
	if (clasificacion == NULL) {
		printf("Error al abrir 'clasificacion.txt'.\n");
		return;
	}

	// Leer cada línea y actualizar puntuaciones
	while (fgets(linea, sizeof(linea), clasificacion) != NULL) {
		if (sscanf(linea, "%s - %s [ %d - %d ]", pareja1, pareja2, &puntos1,
			&puntos2) == 4) {
			for (int i = 0; i < num_part; i++) {
				if (strcmp(participantes[i].nombre, pareja1) == 0) {
					if (puntos1 > puntos2) {
						participantes[i].puntos += 1;
					}
					participantes[i].diferencia_juego += (puntos1 - puntos2);
				}
				if (strcmp(participantes[i].nombre, pareja2) == 0) {
					if (puntos2 > puntos1) {
						participantes[i].puntos += 1;
					}
					participantes[i].diferencia_juego += (puntos2 - puntos1);
				}
			}
		}
	}
	fclose(clasificacion);
}

void ordenar_por_puntos(Pareja participantes[], int num_part) {
	Pareja temp;
	for (int i = 0; i < num_part - 1; i++) {
		for (int j = i + 1; j < num_part; j++) {
			if (participantes[j].puntos > participantes[i].puntos ||
				(participantes[j].puntos == participantes[i].puntos && 
				participantes[j].diferencia_juego >
					participantes[i].diferencia_juego)) {
				temp = participantes[i];
				participantes[i] = participantes[j];
				participantes[j] = temp;
			}
		}
	}
}

void actualizar_clasificacion(Pareja participantes[], int num_part) {
	FILE *clasificacion;
	
	ordenar_por_puntos(participantes, num_part);

	clasificacion = fopen("clasificacion.txt", "w");
	if (clasificacion == NULL) {
		printf("Error al abrir 'clasificacion.txt' para escribir.\n");
		return;
	}

	for (int i = 0; i < num_part; i++) {
		fprintf(clasificacion, "%s - Puntos: %d - Diferencia: %d\n", 
			participantes[i].nombre, participantes[i].puntos, participantes[i].diferencia_juego);
	}

	fclose(clasificacion);

	printf("Clasificación actualizada correctamente en 'clasificacion.txt'.\n");
}
