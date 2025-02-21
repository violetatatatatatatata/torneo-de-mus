# Compilador
CC = gcc
# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c99 -I./srcs
# Directorio de los archivos fuente
SRC_DIR = srcs
# Directorio de los archivos objeto y ejecutables
BIN_DIR = bin
# Directorio de los archivos de datos
DATA_DIR = data

# Nombres de los ejecutables
TARGET_GENERAR_PAREJAS = generar_parejas
TARGET_GENERAR_CLASIFICACION = generar_clasificacion
TARGET_ACTUALIZAR_CLASIFICACION = actualizar_clasificacion

# Archivos fuente
SRC_GENERAR_PAREJAS = $(SRC_DIR)/generar_parejas.c
SRC_GENERAR_CLASIFICACION = $(SRC_DIR)/generar_clasificacion.c
SRC_ACTUALIZAR_CLASIFICACION = $(SRC_DIR)/actualizar_clasificacion.c

# Regla para compilar todo
all:	$(BIN_DIR)/$(TARGET_GENERAR_PAREJAS) \
	$(BIN_DIR)/$(TARGET_GENERAR_CLASIFICACION) \
	$(BIN_DIR)/$(TARGET_ACTUALIZAR_CLASIFICACION)

# Crear la carpeta bin y data si no existen
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)


# Regla para compilar generar_parejas
$(BIN_DIR)/$(TARGET_GENERAR_PAREJAS): $(SRC_GENERAR_PAREJAS) $(SRC_DIR)/torneo_mus.h | $(BIN_DIR) $(DATA_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_GENERAR_PAREJAS)

# Regla para compilar generar_clasificacion
$(BIN_DIR)/$(TARGET_GENERAR_CLASIFICACION): $(SRC_GENERAR_CLASIFICACION) $(SRC_DIR)/torneo_mus.h | $(BIN_DIR) $(DATA_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_GENERAR_CLASIFICACION)

# Regla para compilar actualizar_clasificacion
$(BIN_DIR)/$(TARGET_ACTUALIZAR_CLASIFICACION): $(SRC_ACTUALIZAR_CLASIFICACION) $(SRC_DIR)/torneo_mus.h | $(BIN_DIR) $(DATA_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_ACTUALIZAR_CLASIFICACION)

# Regla para limpiar los archivos compilados
clean:
	rm -rf $(BIN_DIR)/$(TARGET_GENERAR_PAREJAS) \
	$(BIN_DIR)/$(TARGET_GENERAR_CLASIFICACION) \
	$(BIN_DIR)/$(TARGET_ACTUALIZAR_CLASIFICACION)
