#include "torneo_mus.h"

int main() {
	generar_puntuaciones();
	printf("Archivo 'puntuaciones.txt' generado correctamente. Ahora puedes editarlo manualmente.\n");
	return 0;
}

void generar_puntuaciones() {
	FILE *parejas, *puntuaciones;
	char linea[BUFFER_SIZE];

	// Abrir archivos
	parejas = fopen("data/parejas.txt", "r");
	puntuaciones = fopen("data/puntuaciones.txt", "w");
	if (parejas == NULL) {
		printf("Error al abrir 'parejas.txt'.\n");
		return;
	}
	if (puntuaciones == NULL) {
		printf("Error al crear 'puntuaciones.txt'.\n");
		fclose(parejas);
		return;
	}
	// Leer cada línea de parejas.txt y escribir en puntuaciones.txt
	while (fgets(linea, sizeof(linea), parejas) != NULL) {
		// Eliminar el salto de línea de la línea leída
		linea[strcspn(linea, "\n")] = '\0';

		// Escribir la línea original y añadir espacio para la clasificación
		fprintf(puntuaciones, "%s\t\t\t[  -  ]\n", linea);
	}
	fclose(parejas);
	fclose(puntuaciones);
}
