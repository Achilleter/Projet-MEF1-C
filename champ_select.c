#include "principal.h"

void selection(Champ tous[], Equipe* e1, Equipe* e2){                                         
    // char *nom_e1;
    // char *nom_e2;
    // int verif;
    // printf("Nom de l'équipe 1: ");
    // do{
    //     printf("Combien de caractères composent le nom de votre équipe (espaces compris)? ");
    //     verif=scanf("%d", &n1);
    //     vide_buffer();
    // } while (n1<0 || verif!=1);
    // nom_e1=malloc(n1*sizeof(char));
    // printf("Entrez le nom de votre équipe: ");
    // do{
    //     verif=scanf("%s", nom_e1);
    //     vide_buffer();
    // }while(verif!=1);
    // printf("Nom de l'équipe 2: ");
    // do{
    //     printf("Combien de caractères composent le nom de votre équipe (espaces compris)? ");
    //     verif=scanf("%d", &n2);
    //     vide_buffer();
    // } while (n2<0 || verif!=1);
    // nom_e2=malloc(n2*sizeof(char));
    // printf("Entrez le nom de votre équipe: ");
    // do{
    //     verif=scanf("%s", nom_e2);
    //     vide_buffer();
    // }while(verif!=1);
    int deja_pris[10]={0};
    for (int i=0; i<3; i++) {
        int choix;
        printf("%s, choisissez votre combattant %d :\n\n", e1->nom, i+1);
        afficherEquipeChamp(tous, deja_pris);
        int verif;
        do {
            choix=0;
            printf("Votre choix: ");
            verif=scanf("%d", &choix);
            vide_buffer();
            if(choix<1 || choix>10){
                printf("Index invalide\n");
            }
            else if(deja_pris[choix-1]==1){
                printf("Ce champion a deja ete pris !\n");
            }
        }while (choix<1 || choix>10 || deja_pris[choix-1]==1 || verif!=1);
        e1->membres[i]=tous[choix-1];
        deja_pris[choix-1]=1;
        printf("%s a selectionne %s\n", e1->nom, e1->membres[i].nom);
        printf("%s, choisissez votre combattant %d:\n\n", e2->nom, i+1);
        afficherEquipeChamp(tous, deja_pris);
        do {
            choix=0;
            printf("Votre choix: ");
            verif=scanf("%d", &choix);
            vide_buffer();
            if(choix<1 || choix>10){
                printf("Index invalide\n");
            }
            else  if(deja_pris[choix-1]==1){
                printf("Ce champion a deja ete pris !\n");
            }
        } while (choix<1 || choix>10 || deja_pris[choix-1]==1 || verif!=1);
        e2->membres[i]=tous[choix-1];
        deja_pris[choix-1]=1;
        printf("%s a selectionne %s\n", e2->nom, e2->membres[i].nom);
    }
    e1->nbchampvivant=3; // Initialisation du nombre de champions vivants pour chaque équipe
    e2->nbchampvivant=3;
    printf("\n\n");
}

// void selectionia(Champ tous[], Equipe* e1, Equipe* e2){
//     int deja_pris[10]={0};
//     for (int i=0; i<3; i++) {
//         int choix;
//         printf("%s, choisissez votre combattant %d :\n\n", e1->nom, i+1);
//         afficherEquipeChamp(tous, deja_pris);
//         int verif;
//         do {
//             choix=0;
//             printf("Votre choix: ");
//             verif=scanf("%d", &choix);
//             vide_buffer();
//             if(choix<1 || choix>10){
//                 printf("Index invalide\n");
//             }
//             else if(deja_pris[choix-1]==1){
//                 printf("Ce champion a deja ete pris !\n");
//             }
//         }while (choix<1 || choix>10 || deja_pris[choix-1]==1 || verif!=1);
//         e1->membres[i]=tous[choix-1];
//         deja_pris[choix-1]=1;
//         printf("%s a selectionne %s\n", e1->nom, e1->membres[i].nom);
//         do{
//             choix=rand()%10+1;
//         }
//         while(deja_pris[choix-1]==1); // On choisit un champion au hasard qui n'a pas encore été pris
//         e2->membres[i]=tous[choix-1];
//         deja_pris[choix-1]=1;
//         printf("%s a selectionne %s\n", e2->nom, e2->membres[i].nom);
//     }
//     e1->nbchampvivant=3; // Initialisation du nombre de champions vivants pour chaque équipe
//     e2->nbchampvivant=3;
//     printf("\n\n");
// }