# aed2-dyv
Practica de divide y vencerás AED2

## Archivos

 - main.cpp: Implementación principal
 - proyecto-cpp: Ejecutable de main.cpp
 - main\_presentable.cpp: Archivo simplificado solo con divide y vencerás para inclusión en la memoria
 - main\_experiments.cpp: Pruebas
 - proyecto-cpp_exp: Ejecutable de main\_experiments.cpp
 - main.c: Reimplementación en C mas rapida
 - proyecto-c: Ejecutable de main.c
 - generador.cpp: Generador de casos de prueba
 - generador: Ejecutable de generador.cpp
 - validate.sh: Script de validación automatica de divide y venceras contra directo
 - measure.sh: Script de medición de tiempo automatico
 - plot.sh: Script para automatizar producir plots de los datos de measure.sh
 - Makefile: makefile
 - memoria.txt: Memoria
 - memoria.pdf: Memoria en PDF generada de memoria.txt
 - \*.csv: Salidas de measure.sh
 - massif.out.\*: Salidas de valgrind --tool=massif

Nota: los ejecutables incluidos han sido compilados para Debian 12.10 GNU/Linux x86\_64

Todas las implementaciones leen la cadena de stdin.

### proyecto-cpp

`./proyecto-cpp [-dyv|-dir]`

### proyecto-cpp_exp

`./proyecto-cpp_exp [-dyv|-dir|-dyndyv|-dyndir]`

### proyecto-c

`./proyecto-c [-dyv|-dir]`

### generador

Genera una cadena de n caracteres del set "abcd"

`./generador n [modo: best|worst|normal]`

### validate.sh

Compara las salidas de `./proyecto-cpp` con `-dyv` y `-dir` incrementando n en 1
hasta el infinito

`./validate.sh [n inicial]`

### measure.sh

Genera casos y llama a `./proyecto-cpp` y mide el tiempo de usuario con `-dyv` y `-dir`, y saca un CSV por stdout

`./measure.sh [n inicial] [# muestras] [modo incremento] [modo generador]`

 - modo incremento
    - lin1: incrementa en 1 cada muestra
    - linn: incrementa en n inicial cada muestra
    - exp: incrementa al doble cada muestra

 - modo generador:
    - best
    - worst
    - normal

### plot.sh

Toma un archivo CSV generador por `measure.sh` y genera un grafico en texto plano usando GNU Plot

`./plot <archivo CSV>`

## Compilacion

```
make
```

## Ejecución

Test manual

```
time ./generador 1000000 > ./proyecto-cpp
```

Tests automaticos

```
./validate.sh
(<C-c>)
make measurelinn
make plotlinn
```

