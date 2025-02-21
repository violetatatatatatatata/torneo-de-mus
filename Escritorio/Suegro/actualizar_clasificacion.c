#include "mus.h"

int main() {
	Pareja participantes[MAX_PAREJAS];
	int num_part = leer_parejas(participantes);

	// Leer los participantes y sus puntuaciones
	actualizar_puntuaciones(participantes, num_part);

	// Actualizar la clasificación
	actualizar_clasificacion(participantes, num_part);

	return 0;
}

int leer_parejas(Pareja participantes[]) {
	FILE *clasificacion;
	char linea[BUFFER_SIZE];
	int num_part = 0;

	clasificacion = fopen("clasificacion.txt", "r");
	if (clasificacion == NULL) {
		printf("Error al abrir 'clasificacion.txt'.\n");
		return 0;
	}

	// Leer cada línea y extraer los nombres de las parejas
	while (fgets(linea, sizeof(linea), clasificacion) != NULL && num_part < MAX_PAREJAS) {
		// Leer nombres de la pareja, ignorando los puntos y el formato [ x - y ]
		if (sscanf(linea, "%[^-] - %[^[]", participantes[num_part].nombre, participantes[num_part + 1].nombre) == 2) {
			// Limpiar espacios al final de los nombres
			participantes[num_part].nombre[strcspn(participantes[num_part].nombre, "\n")] = '\0';
			participantes[num_part + 1].nombre[strcspn(participantes[num_part + 1].nombre, "\n")] = '\0';
			participantes[num_part].puntos = 0;
			participantes[num_part].diferencia_juego = 0;
			participantes[num_part + 1].puntos = 0;
			participantes[num_part + 1].diferencia_juego = 0;
			num_part += 2;
		}
	}

	fclose(clasificacion);
	return num_part;
}

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
