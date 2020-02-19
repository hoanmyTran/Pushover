PRGNAME = PushOver
main : $(PRGNAME)
MANIPULATION_FONCTIONS = partie1.o partie2.o partie3.o partie4.o principal.o


principal.o : principal.c fonctions.h terminalCouleur.h
	gcc -g -Wall -c principal.c
partie1.o : partie1.c fonctions.h terminalCouleur.h
	gcc -g -Wall -c partie1.c
partie2.o : partie1.c fonctions.h terminalCouleur.h
	gcc -g -Wall -c partie2.c
partie3.o : partie1.c fonctions.h terminalCouleur.h
	gcc -g -Wall -c partie3.c
partie4.o : partie1.c fonctions.h terminalCouleur.h
	gcc -g -Wall -c partie4.c

all : $(PRGNAME) run clean
$(PRGNAME): $(MANIPULATION_FONCTIONS)
	$(CC) $(MANIPULATION_FONCTIONS) -o $(PRGNAME)

run : $(PRGNAME)
	./$(PRGNAME)

clean :
	rm -f $(PRGNAME) ./*.o ./*~
