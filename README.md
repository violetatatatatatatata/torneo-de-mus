# Torneo de Mus - Sistema Suizo

Este es un programa en C que implementa un sistema de torneo de Mus basado en el formato suizo. Permite gestionar las rondas, clasificaciones y emparejamientos de los participantes.

## 📂 Estructura del Proyecto
```
├── srcs/                     # Código fuente
│   ├── generar_parejas.c     # Genera las parejas iniciales aleatorias
│   ├── generar_puntuaciones.c # Genera la puntuación de los participantes
│   ├── actualizar_clasificacion.c # Actualiza la clasificación tras cada ronda
│   ├── torneo_mus.h          # Archivo de cabecera con estructuras y funciones
├── data/                     # Archivos de datos
│   ├── participantes.txt     # Lista de participantes
│   ├── parejas.txt           # Archivo generado con las parejas
│   ├── clasificacion.txt     # Archivo con la clasificación actualizada
│   ├── enfrentamientos.txt   # Archivo con los emparejamientos de cada ronda
│   ├── puntuaciones.txt      # Archivo con las puntuaciones de cada pareja
│   ├── ranking.txt           # Archivo con el ranking general
├── bin/                      # Directorio donde se generan los ejecutables
├── Makefile                  # Archivo para compilar el proyecto
├── README.md                 # Este archivo
```

##  Cómo Usar

###  Compilación del Proyecto
Para compilar todos los archivos, ejecuta:
```sh
make
```
Esto generará los ejecutables en el directorio `bin/`.

###  Uso del Programa
####  **Generar parejas**
```sh
./bin/generar_parejas
```
Genera parejas aleatorias a partir de `data/participantes.txt`.

####  **Generar puntuaciones iniciales**
```sh
./bin/generar_puntuaciones
```
Genera el archivo `data/puntuaciones.txt` con la estructura de puntuación vacía.

####  **Actualizar clasificación tras una ronda**
```sh
./bin/actualizar_clasificacion
```
Actualiza la clasificación según los resultados de la última ronda y genera nuevos emparejamientos.

##  Notas Importantes
- **El archivo `data/participantes.txt` debe contener un número par de participantes.**
- **Los archivos generados (`parejas.txt`, `clasificacion.txt`, `enfrentamientos.txt`, `puntuaciones.txt`, `ranking.txt`) se sobrescriben en cada ejecución.**

## Mejoras Futuras
- Implementar una interfaz gráfica para la gestión del torneo.
- Generar reportes detallados con el historial de partidas y estadísticas de cada jugador.

##  Algoritmo del Programa

###  Generación de parejas:
1. Se leen los participantes desde un archivo y se asignan parejas aleatoriamente.
2. Se aseguran de que haya un número par de participantes.
3. Se almacenan las parejas en un archivo.

###  Puntuaciones y Clasificación:
1. Se genera un archivo de puntuaciones inicial vacío.
2. Se actualizan los puntos después de cada ronda.
3. Se ordenan las parejas por puntos y diferencia de juego.
4. Se guarda la clasificación en un archivo.

###  Enfrentamientos:
1. Se ordenan las parejas por puntos.
2. Se emparejan para la siguiente ronda según su clasificación.
3. Se evita que jueguen contra el mismo rival si ya se enfrentaron.
4. Se guardan los enfrentamientos en un archivo.
