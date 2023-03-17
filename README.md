# Laboratorio 2 - Transformación de lazos, optimización del compilador y jerarquía de memoria
### EL4314 - Arquitectura de Computadoras I
### Escuela de Ingeniería Electrónica
### Tecnológico de Costa Rica

<br/><br/>

## Preámbulo
Ene ste segundo laboratorio, usted experimentará el efecto que tienen la transformación de lazos, las optimizaciones del compilador y la jerarquía de memoria en el rendimiento de un procesador. Para la experimentación se usará un conjunto de aplicaciones de prueba, que incluye un arreglo de dos dimensiones, y otras cinco aplicaciones: _matrix multiplication_}, _Fast Fourier Transform_ (FFT), _Adaptive Differential Pulse Code Modulation_ (ADPCM), _Advanced Encryption Standard_ (AES) y JPEG, las cuales provienen del _benchmark CHStone_ [1].

Para este laboratorio se utilizará el simulador SimpleScalar, el cual es
una plataforma modular para la investigación de la arquitectura de
sistemas computacionales.

Para esta experimentación se utilizará el simulador (algo antiguo) llamado *SimpleScalar*, el cual es "una plataforma modular para la investigación de la arquitectura de sistemas computacionales". *SimpleScalar* permite realizar exploraciones del espacio de diseño de procesadores superscalares y entre los parámetros que se pueden explorar están la configuración de la memoria caché y del predictor de saltos. *Wattch* es una plataforma basada en *SimpleScalar* que permite la exploración y análisis de consumo de energía para un software en particular. Dicho simulador se encuentra disponible en una máquina virtual, la cual podrá descargar de [aquí](https://tecnube1-my.sharepoint.com/:f:/g/personal/jocastro_itcr_ac_cr/Et2j-bTKL4JFjir2rtHyKZwBde69Je0A8aKH2xubgCNBcw?e=95nDK0), y que ha sido preparada para este laboratorio 2 (usuario: _arquitectura_, contraseña: _ARQUI_)

[1] Yuko Hara, Hiroyuki Tomiyama, Shinya Honda, Hiroaki Takada and Katsuya Ishii, "CHStone: A benchmark program suite for practical C-based high-level synthesis," 2008 IEEE International Symposium on Circuits and Systems (ISCAS), Seattle, WA, USA, 2008, pp. 1192-1195, doi: 10.1109/ISCAS.2008.4541637.


## Uso del simulador

Para el uso del simulador es necesario:

-   Compilar el código fuente mediante un _toolchain_ de gcc específico para la arquitectura que utiliza el simulador.
-   Definir la configuración deseada con las caracteristicas de la caché
    de la simulación.

### Compilar el código fuente

Para compilar el código fuente utilice.

`sslittle-na-sstrix-gcc -O0 hello.c -o hello`

El `-O0` indica que se utiliza el nivel de optimización 0, hay 4 niveles
lo cuales tendrá que variar durante las pruebas `O0`, `O1`, `O2` y `O3`.

o en caso de errores puede intentar:

`sslittle-na-sstrix-gcc -x c++ hello.c -o hello`

Este toolchain se encuentra en la máquina virtual en la siguiente
dirección: `$HOME/simplescalar/bin`

Recomendación: exporte al PATH los directorios mencionados
anteriormente de forma permanente en el archivo `.bashrc`
([guía](https://phoenixnap.com/kb/linux-add-to-path))

    export PATH=$HOME/wattch/sim-wattch-1.02d:$PATH
    export PATH=$HOME/simplescalar/bin:$PATH

### Configuración de la caché

La configuración base que usted utilizará en este laboratorio es:

|                     | L1 Inst | L1 Data | L2 Unified |
|---------------------|---------|---------|------------|
| Tamaño (KB)         | 8       | 8       | 128        |
| Número de conjuntos | 256     | 256     | 4096       |
| Asociatividad       | 1       | 1       | 1          |
| Línea de cache (B)  | 32      | 32      | 32         |

La configuración anterior se configura en el simulador de la siguiente
forma.

`sim-outorder -cache:dl1 dl1:256:32:1:l -cache:il1 il1:256:32:1:l  -cache:il2 dl2 -cache:dl2 dl2:4096:32:1:l <binary>`

Esta versión de sim-outorder se encuentra en la máquina vitual en la
siguiente dirección: `$HOME/wattch/sim-wattch-1.02d`

## Parte 1: Arreglo 2D

Usted empleará un pequeño programa en C que llenará una matriz de dos
dimensiones, el mismo se realiza con dos lazos. Para asignar los datos a
la matriz, se utiliza la suma del índice del lazo interno y externo
actual, i.e., `A[i][j]=i+j;`

```c
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            A[i][j] = i + j;
```

En esta sección del laboratorio, usted analizará el rendimiento y el consumo de potencia, de este sencillo programa, esto desde dos puntos de vista de:

-   El efecto de las transformaciones de lazo.
-   El efecto de la optmizacion del compilador.

### Transformación de lazos

Usted realizará la transformación de lazos al código de arreglo 2D,
utilizando distintas dimensiones para la variable `SIZE`: 16x16, 32x23,
64x64, 128x128. Para este experimento utilice la configuración de la
caché presentada anteriomente.

La siguiente lista presenta posibles [transformaciones de lazo] a
realizar(https://tecnube1-my.sharepoint.com/:b:/g/personal/jocastro_itcr_ac_cr/EcnKvkGM_XdFmy0fuHxgxecBVO4s_YqyxplXeqCuH0X5JA?e=88hV0w). 

-   Loop permutation
-   Loop unrrolling
-   Loop tiling
-   
Note que se pueden implementar y analizar las transformaciones
de manera independente o bien combinadas para cada tamaño del arreglo,
además algunas transformaciones, como loop tiling, sólo tienen sentido para tamaños especificos.

Reporte y analice brevemente para cada uno de los tipos de trasformación utilizados.

### Niveles de optimización del compilador

En esta sección se desea medir el efecto de los niveles de
optimizacion del compilador. Para en el que el arreglo tiene dimensión
32x32, reporte y analice brevemente para los siguientes niveles de optimización: `O0`, `O1`, `O2`, `O3`.

## Parte 2: _Benchmark_

### Optimización del compilador 
Usted ejecutará las 5 aplicaciones con las diferentes nivels de optimización del compilador y la configuración de la caché base descrita. Reporte y discuta brevemente el efecto de las diferentes optimizaciones.


### Configuración de la caché
Considere además el efecto de modificar la jerarquía de memoria, particularmente el nivel L1 de datos. Proponga al menos 5 diferentes escenarios para esta memoria caché en donde varíe el nivel de asociatividad (y por lo tanto la cantidad de conjuntos), el tamaño de la línea de caché y la estrategia de reemplazo de bloque (LRU, FIFO, random). En todo caso, el tamaño de esta memoria no debe cambiar y el nivel de optimización en la compilación debe ser `O0`.

Reporte y discuta brevemente los resultados obtenidos para los diferentes escenarios y para las 5 aplicaciones. Utilice la media geométrica para determinar cuál es la mejor configuración tomando en cuenta el rendimiento de la caché y el tiempo de ejecución.

## Mediciones y análisis

Para todas las experimentaciones que realizará en este laboratorio, extraiga los siguientes datos de los reportes generados por el simulador:

-   Potencia consumida por el software.
-   Número de instrucciones ejecutadas y tiempo de ejecución.
-   Rendimiento de caché.


## Evaluación
Este laboratorio se evaluará con la siguiente rúbrica


| Rubro | % | C | EP | D | NP |
|-------|---|---|----|---|----|
|Transformaciones manuales| 50|   |    |   |    |
|Optimización del compilador| 10|   |    |   |    |
|Experimentación con _benchmark_| 20|   |    |   |    |
|Uso de repositorio|20|   |    |   |    |

C: Completo,
EP: En progreso ($\times 0,8$),
D: Deficiente ($\times 0,5$),
NP: No presenta ($\times 0$)

- El uso del repositorio implica que existan contribuciones de todos los miembros del equipo. El último _commit_ debe registrarte antes de las 23:59 del viernes 24 de marzo de 2023.