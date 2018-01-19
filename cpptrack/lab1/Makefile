CPP=g++ -std=c++11
OFILES=lab1.o Point.o
DEBUG=-Wall -g

default: $(OFILES)
	$(CPP) $(OFILES) -o lab1

debug-mode: $(OFILES)
	$(CPP) $(OFILES) -o lab1 -DDEBUG

lab1.o: lab1.cc
	$(CPP) -c lab1.cc

Point.o: Point.cc Point.hh
	$(CPP) -c Point.cc

# -r means ignore errors if files don't exist that we are
# atttempting to delete.
clean:
	-rm -f *.o lab1 ./a.out