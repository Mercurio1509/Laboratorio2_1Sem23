# Laboratorio 2

Para este laboratorio se utilizará el simulador SimpleScalar, el cual es una plataforma modular para la investigación de la arquitectura de sistemas computacionales. 

## Máquina virtual a utilizar

Para el laboratorio es necesario utilizar una máquina virtual, la podrá descargar [aquí]()

## Uso del simulador

Para el uso del simulador es necesario:

* Definir la configuración deseada con las caracteristicas de la cache de la simulación.


* Compilar el código fuente mediante un toolchain de gcc.


### Configuración de la caché
|    | L1 Inst | L2 Data | L3 Unified |
|----|----|----|----|
|Tamaño (KB) | 8|8|128|
|Número de conjuntos | 256|256 | 4096|
|Asociatividad |1 |1 |1|
|Línea de cache (B)| 32| 32| 32|


La configuración anterior se configura en el simulador de la siguiente forma.

`sim-outorder -cache:dl1 dl1:256:32:1:l -cache:il1 il1:256:32:1:l 
-cache:il2 dl2 -cache:dl2 dl2:4096:32:1:l <binary>`

Esta versión de sim-outorder se encuentra en la máquina vitual en la siguiente dirección: `$HOME/wattch/sim-wattch-1.02d`

### Compiar el código fuente

Para compilar el código fuente utilice.

`sslittle-na-sstrix-gcc`

Este toolchain se encuentra en la máquina virtual en la siguiente dirección: `$HOME/simplescalar/bin`


## Arreglo 2D

Se implementará un programa en C que llenará una matriz de dos dimensiones, el mismo se reliza con dos lazos, para asignar los datos a la matriz, se utiliza la suma del índice del lazo interno y externo actual, osea `A[i][j]=i+j;`


```
for (i = 0; i < SIZE; i++)
	for (j = 0; j < SIZE; j++)
		A[i][j] = i + j;
```
Se analizaŕá el rendimiento y el consumo de potencia, de este sencillo programa, esto desde dos puntos de vista:

* El efecto de las transformaciones de lazo.
* El efecto de la optmizacion del compilador.


#### Transformación de lazos

Usted realizará la transformación de lazos al código de arreglo 2D, utilizando distintas dimensiones para la variable `SIZE`: 16x16, 32x23, 64x64, 128x128. Para este experimento utilice la configuración de la caché presentada anteriomente.

La siguiente lista presenta posibles transformaciones de lazo a realizar. Note que se pueden implementar y analizar las transformaciones de manera independente o bien combinadas para cada tamaño del arreglo, además algunas transformacioes sólo tienen sentido para tamaños especificos.

* Loop permutatin
* Loop unrrolling
* Loop tiling

#### Niveles de optimización del compilador 

En esta secciones se desea medir el efecto de los niveles de optimizacion del compilador. Para en el que el arreglo tiene dimensión 32x32, analice para los siguientes niveles de optimización: 00, 01, 02, 03.

## Aplicaciones

Usted modificará tres aplicaciones tratando de hacer su ejecución lo más eficiente posible. Para
ello, utilice las transformaciones de lazos y la optimización del compilador ya probadas. Usted es
libre de determinar dónde aplicar las transformaciones en el código, pero tenga en cuenta que las
transformaciones que introduzca no deben alterar los resultados producidos por la aplicación. Se
proporciona el código para estas aplicaciones:
* Multiplicación de matrices
* FFT 
* ADPCM

Considere además el efecto de los diferentes niveles de optimización y varíe:
* La configuración de la jerarquía de memoria, particularmente el nivel L1 de datos y reporte sobre el efecto en el
rendimiento.

Deberá brindar, como parte de la entrega de este proyecto, las versiones finales para las aplicacionescon las que logró obtener el mejor rendimiento.

## Mediciónes y análisis

Para las transformaciones aplicadas, así como para los diferentes niveles de optimización probados y modificaciones a la configuración de la caché, extraiga los siguientes datos de los reportes generados por el simulador:

* Potencia consumida por el software.
* Número de instrucciones ejecutadas y tiempo deejecución.
* Rendimiento de caché.

Realice un análisis al respecto de los resultados obtenidos. Para la ejecución de los diferentes escenarios de prueba, así como para la extracción de la información relevante proveniente del reporte de ejecución del simulador, usted deberá desarrollar un script de Python que le permita automatizar el proceso.