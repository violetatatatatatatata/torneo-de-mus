#include "mus.h"

int main() {
	generar_clasificacion();
	return 0;
}

void generar_clasificacion() {
	FILE *parejas, *clasificacion;
	char linea[BUFFER_SIZE];

	// Abrir archivos
	parejas = fopen("parejas.txt", "r");
	clasificacion = fopen("clasificacion.txt", "w");

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
		// Escribir la línea original y añadir espacio para la clasificación
		fprintf(clasificacion, "%s [  -  ]\n", linea);
	}

	// Cerrar archivos
	fclose(parejas);
	fclose(clasificacion);

	printf("Archivo 'clasificacion.txt' generado correctamente. Ahora puedes editarlo manualmente.\n");
}
