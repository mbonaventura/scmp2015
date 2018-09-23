LDFLAGS=-L/home/simulations/qss-solver/src/libs
LIBRARIES=-lqssc
OUT_SRC = /home/simulations/qss-solver/build/adr/adr.c
OUT = /home/simulations/qss-solver/build/adr/adr
INCLUDES = -I/home/simulations/qss-solver/src/engine/ -I/home/simulations/qss-solver/usr/include
CFLAGS= -Wall -msse2 -mfpmath=sse -O2 $(LDFLAGS) $(LIBRARIES)
# Compiler.
CC = gcc
default: $(OUT)
$(OUT):
	$(CC) $(INCLUDES) $(OUT_SRC) $(CFLAGS) -o $@ -lm -lgsl -lconfig -lgslcblas -lrt
.PHONY: clean
clean:
	rm -f $(OUT) *.dat *.log
