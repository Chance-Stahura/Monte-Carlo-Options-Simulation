HEADERS = monteCarlo.h 

default: simulation

#compilation only
  #compiles .c into machine code, produces an object file NOT AN EXECUTABLE
simulation.o: monteCarlo.c $(HEADERS)
	gcc -c monteCarlo.c -o simulation.o

#linking
  #takes object file, links requred libs, produces final executable
simulation: simulation.o
	gcc -pthread -Wall -Wextra -O2 simulation.o -lm -o simulation
	@echo "to run the program: ./simulation"

clean:
	-rm -f simulation.o
	-rm -f simulation