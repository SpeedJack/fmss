CC=gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
all:
	gcc -fPIC -Wall -c fmu.c
	gcc -fPIC -Wall -c skeleton.c
	gcc -fPIC -Wall -c misraC/Attack_fmu.c
	gcc -shared -o Attack_fmu.so skeleton.o fmu.o Attack_fmu.o 
	rm -rf sources
	rm -rf binaries
	mkdir sources
	mkdir  binaries
	mkdir binaries/linux64
	cp fmu.h sources
	cp FmuGUID.h sources
	cp fmu.c sources
	cp skeleton.c sources
	rm -f misraC/main.c
	cp -r misraC sources
	cp -r fmi sources
	mv Attack_fmu.so binaries/linux64/
	zip -r Attack_fmu.fmu modelDescription.xml binaries/ resources/ sources/
	rm -rf sources
	rm -rf binaries

run:
	./fmuCheck.linux64 -h 1E-01 Attack_fmu.fmu
run1:
	./fmuCheck.linux64 -h 1E-02 Attack_fmu.fmu

clean:
	rm -rf  Attack_fmu.o fmu.o skeleton.o
