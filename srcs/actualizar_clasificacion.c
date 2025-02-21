#include "torneo_mus.h"

int main() {
	Pareja participantes[MAX_PAREJAS];
	Partido enfrentamientos[MAX_PAREJAS / 2];
	int num_part = leer_parejas(participantes);

	if (num_part == 0) {
		printf("No se encontraron parejas en 'clasificacion.txt'.\n");
		return 1;
	}

	// Actualizar puntuaciones y clasificación
	actualizar_puntuaciones(participantes, num_part);
	actualizar_clasificacion(participantes, num_part);

	// Generar enfrentamientos para la siguiente ronda
	int num_enfrentamientos = generar_enfrentamientos(participantes, num_part, enfrentamientos);

	// Guardar los enfrentamientos en un archivo
	guardar_enfrentamientos(enfrentamientos, num_enfrentamientos, participantes);

	// Actualizar el historial de enfrentamientos
	actualizar_historial(participantes, enfrentamientos, num_enfrentamientos);

	return 0;
}

/**
 * Lee las parejas desde el archivo 'clasificacion.txt'.
 * Devuelve el número de participantes leídos.
 */
int leer_parejas(Pareja participantes[]) {
	FILE *clasificacion;
	char linea[BUFFER_SIZE];
	int num_part = 0;

	clasificacion = fopen("data/clasificacion.txt", "r");

	if (clasificacion == NULL) {
		printf("Error al abrir 'clasificacion.txt'.\n");
		return 0;
	}

	while (fgets(linea, sizeof(linea), clasificacion) != NULL && num_part < MAX_PAREJAS) {
		char nombre1[MAX_NOMBRE], nombre2[MAX_NOMBRE];
		int puntos1, puntos2;

		if (sscanf(linea, " %[^-] - %[^[] [ %d - %d ]", nombre1, nombre2, &puntos1, &puntos2) == 4) {
			// Limpiar espacios al final de los nombres
			nombre1[strcspn(nombre1, " \n")] = '\0';
			nombre2[strcspn(nombre2, " \n")] = '\0';

			// Guardar las parejas en el array de participantes
			strncpy(participantes[num_part].nombre, nombre1, MAX_NOMBRE);
			participantes[num_part].id = num_part;
			participantes[num_part].puntos = 0;
			participantes[num_part].diferencia_juego = 0;
			participantes[num_part].num_oponentes = 0;
			num_part++;

			strncpy(participantes[num_part].nombre, nombre2, MAX_NOMBRE);
			participantes[num_part].id = num_part;
			participantes[num_part].puntos = 0;
			participantes[num_part].diferencia_juego = 0;
			participantes[num_part].num_oponentes = 0;
			num_part++;
		}
	}

	fclose(clasificacion);
	return num_part;
}

/**
 * Actualiza las puntuaciones de las parejas basándose en los resultados del archivo.
 */
void actualizar_puntuaciones(Pareja participantes[], int num_part) {
	FILE *clasificacion;
	char linea[BUFFER_SIZE];

	clasificacion = fopen("data/clasificacion.txt", "r");
	if (clasificacion == NULL) {
		printf("Error al abrir 'clasificacion.txt'.\n");
		return;
	}

	// Leer cada línea y actualizar puntuaciones
	while (fgets(linea, sizeof(linea), clasificacion) != NULL) {
		char nombre1[MAX_NOMBRE], nombre2[MAX_NOMBRE];
		int puntos1, puntos2;

		// Extraer nombres y puntuaciones
		if (sscanf(linea, " %[^-] - %[^[] [ %d - %d ]", nombre1, nombre2, &puntos1, &puntos2) == 4) {
			// Limpiar espacios al final de los nombres
			nombre1[strcspn(nombre1, " \n")] = '\0';
			nombre2[strcspn(nombre2, " \n")] = '\0';

			// Buscar las parejas y actualizar sus puntuaciones
			for (int i = 0; i < num_part; i++) {
				if (strcmp(participantes[i].nombre, nombre1) == 0) {
					participantes[i].puntos += (puntos1 > puntos2) ? 1 : 0;
					participantes[i].diferencia_juego += (puntos1 - puntos2);
				}
				if (strcmp(participantes[i].nombre, nombre2) == 0) {
					participantes[i].puntos += (puntos2 > puntos1) ? 1 : 0;
					participantes[i].diferencia_juego += (puntos2 - puntos1);
				}
			}
		}
	}

	fclose(clasificacion);
}

/**
 * Ordena las parejas por puntos y diferencia de juego.
 */
void ordenar_por_puntos(Pareja participantes[], int num_part) {
	Pareja temp;
	for (int i = 0; i < num_part - 1; i++) {
		for (int j = i + 1; j < num_part; j++) {
			if (participantes[j].puntos > participantes[i].puntos ||
					(participantes[j].puntos == participantes[i].puntos &&
					 participantes[j].diferencia_juego > participantes[i].diferencia_juego)) {
				// Intercambiar posiciones
				temp = participantes[i];
				participantes[i] = participantes[j];
				participantes[j] = temp;
			}
		}
	}
}

/**
 * Actualiza el archivo 'clasificacion.txt' con la nueva clasificación.
 */
void actualizar_clasificacion(Pareja participantes[], int num_part) {
	FILE *clasificacion;

	// Ordenar las parejas por puntos y diferencia de juego
	ordenar_por_puntos(participantes, num_part);

	// Abrir el archivo para escribir la nueva clasificación
	clasificacion = fopen("data/clasificacion.txt", "w");
	if (clasificacion == NULL) {
		printf("Error al abrir 'clasificacion.txt' para escribir.\n");
		return;
	}

	// Escribir la clasificación actualizada
	for (int i = 0; i < num_part; i++) {
		fprintf(clasificacion, "%s - Puntos: %d - Diferencia: %d\n",
				participantes[i].nombre, participantes[i].puntos, participantes[i].diferencia_juego);
	}

	fclose(clasificacion);
	printf("Clasificación actualizada correctamente en 'data/clasificacion.txt'.\n");
}

/**
 * Genera los enfrentamientos para la siguiente ronda.
 * Devuelve el número de enfrentamientos generados.
 */
int generar_enfrentamientos(Pareja participantes[], int num_part, Partido enfrentamientos[]) {
    int num_enfrentamientos = 0;

    // Ordenar las parejas por puntos y diferencia de juego
    ordenar_por_puntos(participantes, num_part);

    // Emparejar a las parejas
    for (int i = 0; i < num_part; i++) {
        if (participantes[i].num_oponentes == num_part - 1) {
            // Si una pareja ya ha jugado contra todas las demás, no se puede emparejar
            continue;
        }

        for (int j = i + 1; j < num_part; j++) {
            // Verificar si las parejas ya se han enfrentado
            if (!ya_se_enfrentaron(participantes[i], participantes[j])) {
                enfrentamientos[num_enfrentamientos].pareja1 = i;
                enfrentamientos[num_enfrentamientos].pareja2 = j;
                num_enfrentamientos++;

                // Actualizar el historial de enfrentamientos
                participantes[i].oponentes[participantes[i].num_oponentes++] = j;
                participantes[j].oponentes[participantes[j].num_oponentes++] = i;
                break; // Salir del bucle interno después de encontrar un emparejamiento válido
            }
        }
    }

    return num_enfrentamientos;
}

/**
 * Guarda los enfrentamientos en un archivo.
 */
void guardar_enfrentamientos(Partido enfrentamientos[], int num_enfrentamientos, Pareja participantes[]) {
	FILE *f = fopen("data/enfrentamientos.txt", "w");
	if (f == NULL) {
		printf("Error al crear el archivo de enfrentamientos.\n");
		return;
	}

	for (int i = 0; i < num_enfrentamientos; i++) {
		fprintf(f, "%s vs %s\n",
				participantes[enfrentamientos[i].pareja1].nombre,
				participantes[enfrentamientos[i].pareja2].nombre);
	}
	fclose(f);
	printf("Enfrentamientos guardados en 'data/enfrentamientos.txt'.\n");
}

/**
 * Actualiza el historial de enfrentamientos de las parejas.
 */
void actualizar_historial(Pareja participantes[], Partido enfrentamientos[], int num_enfrentamientos) {
	for (int i = 0; i < num_enfrentamientos; i++) {
		int id1 = enfrentamientos[i].pareja1;
		int id2 = enfrentamientos[i].pareja2;

		// Agregar a la lista de oponentes
		participantes[id1].oponentes[participantes[id1].num_oponentes++] = id2;
		participantes[id2].oponentes[participantes[id2].num_oponentes++] = id1;
	}
}

/**
 * Verifica si dos parejas ya se han enfrentado.
 * Devuelve 1 si ya se enfrentaron, 0 en caso contrario.
 */
int ya_se_enfrentaron(Pareja pareja1, Pareja pareja2) {
    for (int i = 0; i < pareja1.num_oponentes; i++) {
        if (pareja1.oponentes[i] == pareja2.id) {
            return 1; // Ya se enfrentaron
        }
    }
    return 0; // No se han enfrentado
}
