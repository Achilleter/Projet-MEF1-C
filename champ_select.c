#include "principal.h"

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
                    equipe1->membres[champ1] = Champions[choix - 1]; 
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
                    equipe2->membres[champ2] = Champions[choix - 1]; 
                    getchamp(Champions[choix - 1], equipe2->membres[champ2]);
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