CC=gcc
CFLAGS=-I.
FMUNAME = max_speed_attack_fmu
DESTDIR = ../../../into-cps/FMUs
DESTFILES = max_speed_attack_fmu_1.fmu max_speed_attack_fmu_2.fmu

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
all:
	gcc -fPIC -Wall -c fmu.c
	gcc -fPIC -Wall -c skeleton.c
	gcc -fPIC -Wall -c misraC/$(FMUNAME).c
	gcc -shared -o $(FMUNAME).so skeleton.o fmu.o $(FMUNAME).o
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
	mv $(FMUNAME).so binaries/linux64/
	zip -r $(FMUNAME).fmu modelDescription.xml binaries/ resources/ sources/
	rm -rf sources
	rm -rf binaries
	$(foreach dest,$(DESTFILES),cp -b $(FMUNAME).fmu $(DESTDIR)/$(dest);)

run:
	./fmuCheck.linux64 -h 1E-01 $(FMUNAME).fmu
run1:
	./fmuCheck.linux64 -h 1E-02 $(FMUNAME).fmu

clean:
	rm -f *.o *.fmu
