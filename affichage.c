#include "principal.h"

void afficherChamp(const Champ *c, int index, int prochain) {
    // 1. Nom + numéro + statut
    printf("%-12s |%d|", c->nom, index + 1);
    if (c->statut == 0)
        printf(" ✖");
    else
        printf("   "); // pour garder l’alignement même si vivant
    if (prochain)
        printf(" <"); // marqueur du prochain tour
    printf("\n");

    // 2. Effets spéciaux alignés
    printf(" %-12s(", "");  // 12 espaces d'alignement
    for (int i = 0; i < c->nbeffets; i++) {
        printf("%s", effetStatutToEmoji(c->effets[i].effet_statut));
    }
    printf(")\n");

    // 3. Barre de vie
    printf(" %-12s", "");
    printBarreVie(c->pvcourant, c->pvmax);
    printf("\n");

    // 4. Barre d'effets
    printf(" %-12s", "");
    printBarreEffets();
    printf("\n\n");
}

void afficherEquipe(const Equipe* equipe, Champ *prochain) {
    printf("\n===[ %s ]===\n\n", equipe->nom);
    for (int i = 0; i < 3; i++) {
        int estProchain = (prochain == &(equipe->membres[i]));
        afficherChamp(&(equipe->membres[i]), i, estProchain);
    }
}