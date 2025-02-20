#include "mus.h"

int main(void)
{
	FILE *f, *new_f;
	Pareja participantes[MAX_PAREJAS];
	int num_part = 0;

	f = fopen("participantes.txt", "r+");
	if (f == NULL) {
		printf("No me borres el fichero hijo mío.\n");
		return 1;
	}
	if (leer_participantes(f, participantes, &num_part) == 0) {
		new_f = fopen("parejas.txt", "w");
		if (new_f == NULL) {
			printf("Error al crear el archivo de parejas.\n");
			fclose(f);
			return 1;
		}
		generar_parejas(participantes, new_f, num_part);
		printf("Parejas generadas! Abra el fichero para verlas :)\n");
		fclose(new_f);
	} else {
		printf("Error al leer los participantes. Modifique el fichero.\n");
	}
	fclose(f);
	return 0;
}

/**
 * Lee los participantes desde el archivo y los almacena en un array.
 */
int leer_participantes(FILE *f, Pareja participantes[], int *num_part)
{
	int count;
	char linea[BUFFER_SIZE];

	// Saltar las primeras 3 líneas
	for (count = 0; count < 3; count++) {
		if (fgets(linea, sizeof(linea), f) == NULL) {
			printf("No me modifiques el fichero, coño.\n");
			return 1;
		}
	}
	// Leer los participantes
	while (fgets(linea, sizeof(linea), f) != NULL) {
		if (*num_part >= MAX_PAREJAS) {
			printf("Error: Demasiados participantes.\n");
			return 1;
		}
		// Guardar el nombre sin el salto de línea usando sscanf()
		sscanf(linea, "%[^\n]", participantes[*num_part].nombre);
		participantes[*num_part].id = *num_part;
		participantes[*num_part].puntos = 0;
		participantes[*num_part].diferencia_juego = 0;
		participantes[*num_part].num_oponentes = 0;
		(*num_part)++;
		// Verificar si el número de participantes es impar
		if (*num_part % 2 != 0 && feof(f)) {
			printf("Ha de ser un número par de participantes.\n");
			return 1;
		}
	}
	if (*num_part < 2) {
		printf("Has de escribir los participantes.\n");
		return 1;
	}
	return 0;
}
/**
 * Genera parejas aleatorias y las guarda.
 */
void generar_parejas(Pareja participantes[], FILE *new_f, int num_part)
{
	int indices[MAX_PAREJAS];

	mezclar_indices(indices, num_part);
	for (int i = 0; i < num_part; i += 2) {
		fprintf(new_f, "%s - %s\n", participantes[indices[i]].nombre,
				participantes[indices[i + 1]].nombre);
	}
}

/**
 * Mezcla los índices de los participantes usando el algoritmo Fisher-Yates Shuffle.
 */
void mezclar_indices(int indices[], int num_part)
{
	srand(time(NULL));

	// Inicializar los índices
	for (int i = 0; i < num_part; i++)
		indices[i] = i;
	// Fisher-Yates Shuffle
	for (int i = num_part - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = indices[i];
		indices[i] = indices[j];
		indices[j] = temp;
	}
}
