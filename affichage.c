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

void afficherEquipeChamp(Champ tab[], int deja_pris[]){
    for (int i=0; i<10; i++) {
        if (deja_pris[i]==1){
            printf("%d - %s (PV:%d ATT:%d DEF:%d AGI:%d VIT:%d) (DEJA PRIS).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        } else {
            printf("%d - %s (PV:%d ATT:%d DEF:%d AGI:%d VIT:%d).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        }
    }
}

void nomEquipe(Champ tous[], Champ e1[3], Champ e2[3]){
    int deja_pris[10] = {0};
    char *nom_e1;
    char *nom_e2;
    int n1, n2;
    printf("Nom de l'équipe 1 : ");
    do{
        printf("Combien de caractères composent le nom de votre équipe (espaces compris)? ");
        scanf("%d", &n1);
    } while (n1<0);
    nom_e1=malloc(n1*sizeof(char));
    printf("Entrez le nom de votre équipe: ");
    scanf("%s", nom_e1);
    printf("Nom de l'équipe 2 : ");
    do{
        printf("Combien de caractères composent le nom de votre équipe (espaces compris)? ");
        scanf("%d", &n2);
    } while (n2<0);
    nom_e2=malloc(n2*sizeof(char));
    printf("Entrez le nom de votre équipe: ");
    scanf("%s", nom_e2);


