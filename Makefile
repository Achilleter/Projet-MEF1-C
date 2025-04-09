Prog = PROJET-MEF1-C

# Sources
SRC=main.c fonction.c affichage.c

# Règle par défaut : compile et exécute 
all: $(PROG)
./$(PROG)

# Compilation du programme
$(PROG): $(SRC) fichier.h
	gcc -Wall -o $(PROG) $(SRC)

# Nettoyage
clean:
	rm -f $(PROG)
