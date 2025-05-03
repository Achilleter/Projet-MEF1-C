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
        printf("%s, choisissez votre combattant %d :\n", e1->nom, i+1);
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
        printf("%s a selectionne %s\n\n", e1->nom, e1->membres[i].nom);
        printf("%s, choisissez votre combattant %d:\n", e2->nom, i+1);
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
    printf("Composition des equipes:\n");
    printf("%s:\n", e1->nom);
    for (int i=0; i<3; i++){
        printf("- %s\n", e1->membres[i].nom);
    }
    printf("%s:\n", e2->nom);
    for (int i=0; i<3; i++){
        printf("- %s\n", e2->membres[i].nom);
    }
}























// Fonction de Rémi (A revoir car quelques incohérences) 

//void choixChamp(Equipe* equipe1, Equipe* equipe2, int deja_pris[10]) {
//     int choix = 0;
//     int champ1 = 0, champ2 = 0; 
//     char Champions[10]={"Xavier", "Nathalie", "Zed", "Smasheur", "Sandrine", "Anne-Sophie", "Gaby", "Clara", "Steve", "Booga"};
//     for(int i=0; i<10; i++){
//         deja_pris[i] = 0; 
//     }
//     for(int tour = 0; tour < 6; tour++){ // 6 tours au total (3 champions par équipe)
//         printf("Tour %d: ", tour + 1);
//         if(tour < 0){
//             tour = 0;
//         }
//         else{
//             if(tour % 2 == 0){ // Premier tour pour l'équipe 1 => L'équipe 1 choisit son champion lorsque tour est pair et pour l'équipe 2 lorsque tour est impair
//                 printf("Equipe 1, choisissez votre champion (1 à 10): \n");
//                 //une fonction qui affiche tous les champions disponibles
//                 //afficherEquipeChamp();
//                 do{
//                     scanf("%d", &choix);
//                     if(choix < 1 || choix > 10){
//                         printf("Index invalide\n");
//                     }
//                 }while (choix < 1 || choix > 10);
//                 if(deja_pris[choix - 1] == 0){
//                     //faut assigner le bon champ à equipe1->membres[champ1]
//                     getchamp(Champions[choix - 1], equipe1->membres[champ1]);
//                     deja_pris[choix - 1] = 1;
//                     champ1++;
//                 } 
//                 else{
//                     printf("Champion déjà pris !\n");
//                     tour--; 
//                 }
//             } 
//             else{ // Tour de l'équipe 2
//                 printf("Equipe 2, choisissez votre champion (1 à 10): \n");
//                 //afficherEquipeChamp();
//                 do{
//                     scanf("%d", &choix);
//                     if(choix < 1 || choix > 10){
//                         printf("Index invalide\n");
//                     }
//                 }while (choix < 1 || choix > 10);
//                 if(deja_pris[choix - 1] == 0){
//                     getchamp(Champions[choix - 1], equipe2->membres[champ2]);
//                     //faut assigner le bon champ à equipe2->membres[champ2]
//                     deja_pris[choix - 1] = 1;
//                     champ2++;
                    
//                 } 
//                 else{
//                     printf("Champion déjà pris !\n");
//                     tour--; 
//                 }
//             }
//         }
//     }
//     //afficherEquipe(); pour l'équipe 1
//     //afficherEquipe(); pour l'équipe 2
// }
