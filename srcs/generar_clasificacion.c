#include "torneo_mus.h"

int main() {
	generar_clasificacion();
	return 0;
}

void generar_clasificacion() {
	FILE *parejas, *clasificacion;
	char linea[BUFFER_SIZE];

	// Abrir archivos
	parejas = fopen("data/parejas.txt", "r");
	clasificacion = fopen("data/clasificacion.txt", "w");

	if (parejas == NULL) {
		printf("Error al abrir 'parejas.txt'.\n");
		return;
	}
	if (clasificacion == NULL) {
		printf("Error al crear 'clasificacion.txt'.\n");
		fclose(parejas);
		return;
	}

	// Leer cada línea de parejas.txt y escribir en clasificacion.txt con espacio para clasificación
	while (fgets(linea, sizeof(linea), parejas) != NULL) {
		// Eliminar el salto de línea de la línea leída
		linea[strcspn(linea, "\n")] = '\0';

		// Escribir la línea original y añadir espacio para la clasificación
		fprintf(clasificacion, "%s [  -  ]\n", linea);
	}

	// Cerrar archivos
	fclose(parejas);
	fclose(clasificacion);

	printf("Archivo 'clasificacion.txt' generado correctamente. Ahora puedes editarlo manualmente.\n");
}
