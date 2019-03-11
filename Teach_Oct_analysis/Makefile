CXXFLAGS=-g -std=c++0x -m64 -O2 -Wall
ROOTFLAGS=$(shell root-config --libs --cflags --glibs)

makePlots: main.o makePlots.o
	g++ $^ -o makePlots $(CXXFLAGS) $(ROOTFLAGS)
	mv *.o obj_file

main.o: main.cc makePlots.h
	g++ -c $(CXXFLAGS) $(ROOTFLAGS) $< -o $@

makePlots.o:makePlots.cc makePlots.h
	g++ -c $(CXXFLAGS) $(ROOTFLAGS) $< -o $@

clean:
	rm -f makePlots obj_file/*.o ./*~
