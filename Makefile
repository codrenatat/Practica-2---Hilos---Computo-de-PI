CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm
PTHREAD_FLAGS = -pthread

# Nombres de los ejecutables
SERIAL = serial
PARALELO = threads

# Archivos fuente
SERIAL_SRC = serial.c
PARALELO_SRC = threads.c

all: $(SERIAL) $(PARALELO)

$(SERIAL): $(SERIAL_SRC)
        $(CC) $(CFLAGS) -o $(SERIAL) $(SERIAL_SRC) $(LDFLAGS)

$(PARALELO): $(PARALELO_SRC)
        $(CC) $(CFLAGS) $(PTHREAD_FLAGS) -o $(PARALELO) $(PARALELO_SRC) $(LDFLAGS)

run_serial: $(SERIAL)
        ./$(SERIAL)

run_paralelo: $(PARALELO)
        ./$(PARALELO)

clean:
        rm -f $(SERIAL) $(PARALELO)