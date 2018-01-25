CXX=g++ $(CXXFLAGS)
CXXFLAGS=-std=c++11
OFILES=tsp-main.o tsp-ga.o Point.o
DEBUG=-Wall -g -DDEBUG

default: $(OFILES)
	$(CXX) $(OFILES) -o tsp-ga
	@echo "TSA-Genome Compilation Complete"

debug-mode: $(OFILES)
	$(CXX) $(DEBUG) $(OFILES) -o tsp-ga
	@echo "TSA-Genome Compilation Complete"

# -r means ignore errors if files don't exist that we are
# atttempting to delete.
clean:
	-rm -f *.o tsp-ga ./a.out