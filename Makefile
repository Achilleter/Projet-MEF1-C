PROG = PROJET-MEF1-C

# Sources
SRC=main.c attaque.c utilitaire.c techniques.c

# Règle par défaut : compile et exécute 
all: $(PROG)
	./$(PROG)

# Compilation du programme
$(PROG): $(SRC) principal.h
	# Compilation avec les options de débogage et d'optimisation
	gcc -Wall -Wl,--verbose -o $(PROG) $(SRC)

# Nettoyage
clean:
	rm -f $(PROG)
