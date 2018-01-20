CPP=g++ -std=c++11
OFILES=tsp-main.o tsp-ga.o Point.o
DEBUG=-Wall -g -DDEBUG

.SUFFIXES: .o .cpp

default: $(OFILES)
	$(CPP) $(OFILES) -o tsp
	@echo "TSA-Genome Compilation Complete"

debug-mode: $(OFILES)
	$(CPP) $(DEBUG) $(OFILES) -o tsp
	@echo "TSA-Genome Compilation Complete"

# -r means ignore errors if files don't exist that we are
# atttempting to delete.
clean:
	-rm -f *.o tsp ./a.out