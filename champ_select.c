#include "principal.h"

void selection(Champ tous[], Equipe* e1, Equipe* e2){                                         
    int deja_pris[10]={0}; // Tableau pour savoir quels champions ont déjà été pris
    for (int i=0; i<3; i++) { // Debut de la boucle pour choisir les champions
        int choix;
        //debut du choix pour le joueur 1
        printf("%s, choisissez votre combattant %d :\n\n", e1->nom, i+1);
        afficherEquipeChamp(tous, deja_pris); // Appelle la fonction pour afficher les champions disponibles
        int verif;
        do { // Verification de la saisie
            choix=0;
            printf("\nVotre choix: ");
            verif=scanf("%d", &choix);
            vide_buffer();
            if(choix<1 || choix>10){
                printf("Index invalide\n");
            }
            else if(deja_pris[choix-1]==1){ // Si le champion a déjà été pris il ne peut pas être choisi
                printf("Ce champion a deja ete pris !\n");
            }
        }while (choix<1 || choix>10 || deja_pris[choix-1]==1 || verif!=1);
        e1->membres[i]=tous[choix-1];
        deja_pris[choix-1]=1; // On marque le champion comme pris
        printf("%s a selectionne %s\n\n", e1->nom, e1->membres[i].nom);
        //debut du choix pour le joueur 2
        printf("%s, choisissez votre combattant %d:\n\n", e2->nom, i+1);
        afficherEquipeChamp(tous, deja_pris);
        do { // Verification de la saisie
            choix=0;
            printf("\nVotre choix: ");
            verif=scanf("%d", &choix);
            vide_buffer();
            if(choix<1 || choix>10){
                printf("Index invalide\n");
            }
            else  if(deja_pris[choix-1]==1){ // Si le champion a déjà été pris il ne peut pas être choisi
                printf("Ce champion a deja ete pris !\n");
            }
        } while (choix<1 || choix>10 || deja_pris[choix-1]==1 || verif!=1);
        e2->membres[i]=tous[choix-1];
        deja_pris[choix-1]=1; // On marque le champion comme pris
        printf("%s a selectionne %s\n\n", e2->nom, e2->membres[i].nom);
    }
    // Fin de la boucle pour choisir les champions
    e1->nbchampvivant=3; // Initialisation du nombre de champions vivants pour chaque équipe
    e2->nbchampvivant=3;
    printf("\n\n");
}

void selectionia(Champ tous[], Equipe* e1, Equipe* e2){
    int deja_pris[10]={0}; // Tableau pour savoir quels champions ont déjà été pris
    for (int i=0; i<3; i++) { // Debut de la boucle pour choisir les champions
        int choix;
        //debut du choix pour le joueur 1
        printf("%s, choisissez votre combattant %d :\n\n", e1->nom, i+1);
        afficherEquipeChamp(tous, deja_pris); // Appelle la fonction pour afficher les champions disponibles
        int verif;
        do { // Verification de la saisie
            choix=0;
            printf("\nVotre choix: ");
            verif=scanf("%d", &choix);
            vide_buffer();
            if(choix<1 || choix>10){
                printf("Index invalide\n");
            }
            else if(deja_pris[choix-1]==1){ // Si le champion a déjà été pris il ne peut pas être choisi
                printf("Ce champion a deja ete pris !\n");
            }
        }while (choix<1 || choix>10 || deja_pris[choix-1]==1 || verif!=1);
        e1->membres[i]=tous[choix-1];
        deja_pris[choix-1]=1; // On marque le champion comme pris
        printf("%s a selectionne %s\n\n", e1->nom, e1->membres[i].nom);
        //debut du choix pour l'IA
        do{
            choix=rand()%10+1;
        }
        while(deja_pris[choix-1]==1); // On choisit un champion au hasard qui n'a pas encore été pris
        e2->membres[i]=tous[choix-1];
        deja_pris[choix-1]=1; // On marque le champion comme pris
        printf("%s a selectionne %s\n\n", e2->nom, e2->membres[i].nom);
    }
    // Fin de la boucle pour choisir les champions
    e1->nbchampvivant=3; // Initialisation du nombre de champions vivants pour chaque équipe
    e2->nbchampvivant=3;
    printf("\n\n");
}