CC = gcc            
CFLAGS = -Wall -O2  
SRC = $(wildcard tarea2_1.c) # Todos los archivos fuente Combinacion_i.c
OBJ = $(SRC:.c=.o)  
EXE = $(SRC:.c=)   

# Regla principalall: $(EXE)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)
