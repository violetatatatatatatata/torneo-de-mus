#include "torneo_mus.h"

int main(void)
{
    FILE *f, *new_f;
    Pareja participantes[MAX_PAREJAS];
    int num_part = 0;

    // Abrir el archivo de participantes
    f = fopen("data/participantes.txt", "r");
    if (f == NULL) {
        printf("No me borres el fichero hijo mío.\n");
        return 1;
    }

    // Validar el archivo de participantes
    if (validar_archivo_participantes(f) != 0) {
        fclose(f);
        return 1;
    }

    // Leer los participantes
    if (leer_participantes(f, participantes, &num_part) == 0) {
        // Verificar si hay nombres duplicados
        if (verificar_duplicados(participantes, num_part) != 0) {
            fclose(f);
            return 1;
        }

        // Generar parejas aleatorias
        new_f = fopen("data/parejas.txt", "w");
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
 * Maneja nombres con espacios.
 */
int leer_participantes(FILE *f, Pareja participantes[], int *num_part)
{
    char linea[BUFFER_SIZE];

    // Leer los participantes
    while (fgets(linea, sizeof(linea), f) != NULL) {
        // Ignorar líneas vacías o comentarios (que empiezan con #)
        if (linea[0] == '\n' || linea[0] == '#') {
            continue;
        }

        if (*num_part >= MAX_PAREJAS) {
            printf("Error: Demasiados participantes.\n");
            return 1;
        }

        // Eliminar el salto de línea al final
        linea[strcspn(linea, "\n")] = '\0';

        // Copiar el nombre completo
        strncpy(participantes[*num_part].nombre, linea, MAX_NOMBRE - 1);
        participantes[*num_part].nombre[MAX_NOMBRE - 1] = '\0'; // Asegurar terminación nula
        participantes[*num_part].id = *num_part;
        participantes[*num_part].puntos = 0;
        participantes[*num_part].diferencia_juego = 0;
        participantes[*num_part].num_oponentes = 0;
        (*num_part)++;

        // Verificar si el número de participantes es impar
        if (*num_part % 2 != 0 && feof(f)) {
            printf("Error: Ha de ser un número par de participantes.\n");
            return 1;
        }
    }

    if (*num_part < 2) {
        printf("Error: Has de escribir los participantes.\n");
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
		fprintf(new_f, "%s\t-\t%s\n", participantes[indices[i]].nombre,
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

/**
 * Verifica que el archivo de participantes tenga un formato válido.
 * Devuelve 0 si es válido, 1 si no lo es.
 */
int validar_archivo_participantes(FILE *f) {
	char linea[BUFFER_SIZE];
	int lineas_validas = 0;

	// Verificar que haya al menos 2 participantes
	while (fgets(linea, sizeof(linea), f) != NULL) {
		if (strlen(linea) > 1) { // Línea no vacía
			lineas_validas++;
		}
	}
	if (lineas_validas < 2) {
		printf("Error: El archivo debe contener al menos 2 participantes.\n");
		return 1;
	}
	// Reiniciar el puntero del archivo al inicio
	rewind(f);
	return 0;
}

/**
 * Verifica si hay nombres duplicados en la lista de participantes.
 * Devuelve 0 si no hay duplicados, 1 si los hay.
 */
int verificar_duplicados(Pareja participantes[], int num_part) {
	for (int i = 0; i < num_part; i++) {
		for (int j = i + 1; j < num_part; j++) {
			if (strcmp(participantes[i].nombre, participantes[j].nombre) == 0) {
				printf("Error: Nombre duplicado encontrado: %s\n", participantes[i].nombre);
				return 1;
			}
		}
	}
	return 0;
}
