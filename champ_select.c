#include "principal.h"

void selection(Champ tous[], Champ e1[3], Champ e2[3]){
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
    for (int i=0; i<3; i++) {
        int choix;
        printf("%s, choisissez votre combattant %d :\n", nom_e1, i+1);
        afficherEquipeChamp(tous, deja_pris);
        do {
            printf("Votre choix : ");
            scanf("%d", &choix);
        } while (choix<1 || choix>10 || deja_pris[choix-1]=1);
        e1[i]=tous[choix-1];
        deja_pris[choix-1]=1;
        printf("%s sélectionné !\n\n", e1[i].nom);
        printf("%s, choisissez votre combattant %d :\n", nom_e2, i+1);
        afficherEquipeChamp(tous, deja_pris);
        do {
            printf("Votre choix : ");
            scanf("%d", &choix);
        } while (choix<1 || choix>10 || deja_pris[choix-1]=1);
        e2[i]=tous[choix-1];
        deja_pris[choix-1]=1;
        printf("%s sélectionné !\n\n", e2[i].nom);
    }

    printf("\nComposition des équipes:\n");
    printf("%s :\n", nom_e1);
    for (int i=0; i<3; i++){
        printf("- %s\n", e1[i].nom);
    }
    printf("%s :\n", nom_e2);
    for (int i = 0; i < 3; i++){
        printf("- %s\n", e2[i].nom);
    }
}























// Fonction de Rémi (A revoir car quelques incohérences) 

void choixChamp(Equipe* equipe1, Equipe* equipe2, int deja_pris[10]) {
    int choix = 0;
    int champ1 = 0, champ2 = 0; 
    char Champions[10]={"Xavier", "Nathalie", "Zed", "Smasheur", "Sandrine", "Anne-Sophie", "Gaby", "Clara", "Steve", "Booga"};
    for(int i=0; i<10; i++){
        deja_pris[i] = 0; 
    }
    for(int tour = 0; tour < 6; tour++){ // 6 tours au total (3 champions par équipe)
        printf("Tour %d: ", tour + 1);
        if(tour < 0){
            tour = 0;
        }
        else{
            if(tour % 2 == 0){ // Premier tour pour l'équipe 1 => L'équipe 1 choisit son champion lorsque tour est pair et pour l'équipe 2 lorsque tour est impair
                printf("Equipe 1, choisissez votre champion (1 à 10): \n");
                //une fonction qui affiche tous les champions disponibles
                //afficherEquipeChamp();
                do{
                    scanf("%d", &choix);
                    if(choix < 1 || choix > 10){
                        printf("Index invalide\n");
                    }
                }while (choix < 1 || choix > 10);
                if(deja_pris[choix - 1] == 0){
                    //faut assigner le bon champ à equipe1->membres[champ1]
                    getchamp(Champions[choix - 1], equipe1->membres[champ1]);
                    deja_pris[choix - 1] = 1;
                    champ1++;
                } 
                else{
                    printf("Champion déjà pris !\n");
                    tour--; 
                }
            } 
            else{ // Tour de l'équipe 2
                printf("Equipe 2, choisissez votre champion (1 à 10): \n");
                //afficherEquipeChamp();
                do{
                    scanf("%d", &choix);
                    if(choix < 1 || choix > 10){
                        printf("Index invalide\n");
                    }
                }while (choix < 1 || choix > 10);
                if(deja_pris[choix - 1] == 0){
                    getchamp(Champions[choix - 1], equipe2->membres[champ2]);
                    //faut assigner le bon champ à equipe2->membres[champ2]
                    deja_pris[choix - 1] = 1;
                    champ2++;
                    
                } 
                else{
                    printf("Champion déjà pris !\n");
                    tour--; 
                }
            }
        }
    }
    //afficherEquipe(); pour l'équipe 1
    //afficherEquipe(); pour l'équipe 2
}
