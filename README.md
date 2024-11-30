# Planificador de CPU


## Descripción
Este código permite crear múltiples procesos hijos, asignarles diferentes políticas de planificación de CPU y configurar su afinidad a núcleos específicos. Los procesos calculan la suma de números primos menores a un valor dado y reportan el tiempo de ejecución al proceso padre mediante pipes. El objetivo es observar cómo las políticas de planificación y la afinidad de CPU afectan el rendimiento del programa.

## Explicación de las Políticas de Planificación

### FIFO (First-In, First-Out)
Esta política asigna la CPU a los procesos en el orden en que llegan, sin preempción. Los procesos con mayor prioridad se ejecutan primero, pero una vez que un proceso comienza, no puede ser interrumpido hasta que termine.

**Impacto en el tiempo de ejecución:** Asegura que los procesos se ejecuten en el orden en que se solicitan. Si un proceso de alta prioridad consume todos los recursos, puede bloquear a los demás, lo que afectaría el rendimiento en sistemas con alta concurrencia.

### RR (Round-Robin)
Los procesos de igual prioridad se ejecutan en ciclos cortos de tiempo (time slices), permitiendo que todos los procesos tengan una oportunidad de ejecutarse en la CPU antes de que se realice un cambio de contexto.

**Impacto en el tiempo de ejecución:** Es una política más equitativa que evita que los procesos de alta prioridad bloqueen a los demás. Sin embargo, puede introducir overhead debido al cambio constante de contexto entre procesos, lo que podría aumentar el tiempo total de ejecución si hay muchos procesos.

### SCHED_OTHER (Política normal de Linux)
Esta es la política predeterminada para procesos normales, basada en prioridades dinámicas. La CPU es asignada de acuerdo con el historial de uso del proceso, priorizando los que más tiempo llevan esperando o los que tienen menor uso de la CPU.

**Impacto en el tiempo de ejecución:** Es una política que balancea equitativamente el uso de la CPU entre los procesos, pero no siempre es la más eficiente para tareas de alto rendimiento o tareas computacionalmente intensivas. El sistema optimiza la ejecución de los procesos según su comportamiento.

### BATCH
Está optimizada para procesos que no requieren interacción directa con el usuario, como trabajos de largo tiempo o en segundo plano. Generalmente, es utilizada para cargas de trabajo pesadas y largas.

**Impacto en el tiempo de ejecución:** Es ideal para trabajos que no necesitan una respuesta inmediata, pero en algunos casos puede ser más lenta comparada con otras políticas cuando se ejecutan tareas que requieren una respuesta rápida o interactiva.
