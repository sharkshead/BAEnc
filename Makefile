all: lib lib/BAEnc.o Pi/baenc

clean:
	rm -f lib/BAEnc.o Pi/baenc

lib:
	mkdir lib

lib/BAEnc.o: src/BAEnc.cpp src/BAEnc.h
	cd src; g++ -c -o ../lib/BAEnc.o BAEnc.cpp


Pi/baenc: Pi/baenc.cpp src/BAEnc.h
	cd Pi; g++ -o baenc baenc.cpp ../lib/BAEnc.o
