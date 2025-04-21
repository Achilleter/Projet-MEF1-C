# Nom de l'exécutable
PROG = PROJET-MEF1-C

# Fichiers sources
SRC = main.c attaque.c utilitaire.c techniques.c

# Options de compilation
CFLAGS = -Wall -Wextra -g
LDFLAGS = 

# Règle par défaut : compile puis exécute
all: $(PROG)
	./$(PROG)

# Compilation de l'exécutable
$(PROG): $(SRC) principal.h
	gcc $(CFLAGS) -o $(PROG) $(SRC) $(LDFLAGS)

# Nettoyage des fichiers générés
clean:
	rm -f $(PROG)
