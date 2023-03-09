# Laboratorio 2

Para este laboratorio se utilizará el simulador SimpleScalar, el cual es una plataforma modular para la investigación de la arquitectura de sistemas computacionales. 

## Máquina virtual a utilizar

Para el laboratorio es necesario utilizar una máquina virtual...

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

Para compilar el código fuente puede utilice.

`sslittle-na-sstrix-gcc`

Este toolchain se encuentra en la máquina virtual en la siguiente dirección: `$HOME/simplescalar/bin`


### Arreglo 2D

Se implementará un programa en C que llenará una matriz de dos dimensiones, el mismo se reliza con dos lazos, para asignar los datos a la matriz, se utiliza la suma del índice del lazo interno y externo actual, osea `A[i][j]=i+j;`


```
for (i = 0; i < SIZE; i++)
	for (j = 0; j < SIZE; j++)
		A[i][j] = i + j;
```
#### Transformación de lazos

....

#### Niveles de optimización del compilador 

....

#### Mediciónes y análisis

....



