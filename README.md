# Torneo de Mus - Sistema Suizo

Este es un programa en C que implementa un sistema de torneo de Mus basado en el formato suizo. Permite gestionar las rondas, clasificaciones y emparejamientos de los participantes.

## 📂 Estructura del Proyecto
```
├── srcs/                     # Código fuente
│   ├── generar_parejas.c     # Genera las parejas iniciales aleatorias
│   ├── generar_clasificacion.c # Crea la clasificación inicial
│   ├── actualizar_clasificacion.c # Actualiza la clasificación tras cada ronda
│   ├── torneo_mus.h          # Archivo de cabecera con estructuras y funciones
├── data/                     # Archivos de datos
│   ├── participantes.txt     # Lista de participantes
│   ├── parejas.txt           # Archivo generado con las parejas
│   ├── clasificacion.txt     # Archivo con la clasificación actualizada
│   ├── enfrentamientos.txt   # Archivo con los emparejamientos de cada ronda
├── Makefile                  # Archivo para compilar el proyecto
├── README.md                 # Este archivo
```

## Cómo Usar
###  Compilación del Proyecto
Para compilar todos los archivos, ejecuta:
```sh
make
```
Esto generará los ejecutables en el directorio `bin/`.

###  Uso del Programa
#### **Generar parejas**
```sh
./bin/generar_parejas
```
Genera parejas aleatorias a partir de `data/participantes.txt`.

#### **Generar clasificación inicial**
```sh
./bin/generar_clasificacion
```
Crea `data/clasificacion.txt` con la lista de parejas sin puntuación inicial.

#### **Actualizar clasificación tras una ronda**
```sh
./bin/actualizar_clasificacion
```
Actualiza la clasificación según los resultados de la última ronda y genera nuevos emparejamientos.

##  Notas Importantes
- **El archivo `data/participantes.txt` debe contener un número par de participantes.**
- **Los archivos generados (`parejas.txt`, `clasificacion.txt`, `enfrentamientos.txt`) se sobrescriben en cada ejecución.**
- **Si se usa el suizo condicionado, se debe modificar el código para evitar enfrentamientos repetidos.**

## Mejoras Futuras
- Implementar una interfaz gráfica para la gestión del torneo.
- Incluir una opción para hacer suizo condicionado automáticamente.

## ALGORITMO DEL PROGRAMA ! 

Generación de parejas:
	Se leen los participantes desde un archivo y se asignan parejas aleatoriamente.
	Se aseguran de que haya un número par de participantes.
	Se almacenan las parejas en un archivo.

Clasificación:
	Se genera una clasificación inicial con espacio para los puntos.
	Se actualizan los puntos después de cada ronda.
	Se ordenan las parejas por puntos y diferencia de juego.
	Se guarda la clasificación en un archivo.

Enfrentamientos:
	Se ordenan las parejas por puntos.
	Se emparejan para la siguiente ronda según su clasificación.
	Se evita que jueguen contra el mismo rival si ya se enfrentaron.
	Se guardan los enfrentamientos en un archivo.
