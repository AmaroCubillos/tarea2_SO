#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

long long primos(int limite) {
    long long suma = 0;
    for (int i = 2; i <= limite; i++) {
        int prim = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prim = 0;
            }
        }
        if (prim == 1) {
            suma += i;
        }
    }
    return suma;
}

void afinidad(int cpu) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        perror("error al asignar la afinidad de CPU");
        exit(EXIT_FAILURE);
    }
}

void planificador(int politica, int prioridad) {
    struct sched_param parametro;
    parametro.sched_priority = prioridad;
    if (sched_setscheduler(0, politica, &parametro) == -1) {
        perror("error al seleccionar la politica del planificador");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int limite = 1000000;
    int politicas[4] = {SCHED_FIFO, SCHED_RR, SCHED_OTHER, SCHED_BATCH};
    const char *nombrespoliticas[4] = {"FIFO", "RR", "LINUX", "BATCH"};

    for (int i = 0; i < 4; i++) {
        printf("Resultados para la política %s:\n", nombrespoliticas[i]);
        
        int num = 8;
        int cpu = 0;

        while (cpu < num) {
            pid_t pid = fork();
            
            if (pid == 0) {
                afinidad(cpu);

                if (politicas[i] == SCHED_FIFO || politicas[i] == SCHED_RR) {
                    planificador(politicas[i], 10);
                } else {
                    planificador(politicas[i], 0);
                }

                struct timespec inicio, fin;
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                long long resultado = primos(limite);
                clock_gettime(CLOCK_MONOTONIC, &fin);

                double tiempo = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

                printf(" Núcleo %d: suma = %lld, tiempo = %.5f s\n", cpu, resultado, tiempo);
                exit(0);
            } else if (pid < 0) {
                perror("fallo al hacer fork");
                exit(EXIT_FAILURE);
            }

            waitpid(pid, NULL, 0);
            cpu++;
        }
    }

    return 0;
}
