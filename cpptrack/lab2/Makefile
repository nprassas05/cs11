CPP=g++ -std=c++11
OFILES=tsp.o Point.o
DEBUG=-Wall -g -DDEBUG

default: $(OFILES)
	$(CPP) $(OFILES) -o tsp

debug-mode: $(OFILES)
	$(CPP) $(DEBUG) $(OFILES) -o tsp

tsp.o: tsp.cc
	$(CPP) -c tsp.cc

Point.o: Point.cc Point.hh
	$(CPP) -c Point.cc

# -r means ignore errors if files don't exist that we are
# atttempting to delete.
clean:
	-rm -f *.o tsp ./a.out