#include <stdio.h>
#include "structures.h"

void berserk(Champ* xavier, Champ* ennemi){
    if(xavier->tech.nbtactifs == 0){
        xavier->tech.nbtactifs = 2;
        xavier->tech.nbtrechargement = 4;
        xavier->jauge -=3;
        printf("Xavier utilise Berserk !\n");
        appeffetStat(xavier,1,20);//augmente l'attaque de 20
        appeffetStat(xavier,2,10);//augmente la defense de 10
        appeffetStatut(xavier,5,1);//applique invincibilité pendant 1 tour
    }
    else if(xavier->tech.nbtactifs == 1){
        appeffetStatut(xavier,2,1);//s'immobilise
        appeffetStat(xavier,1,-20);//diminue l'attaque de 20
        appeffetStat(xavier,2,-10);//diminue la defense de 10
    }
}


void flashbacks(Champ* nathalie, Champ* allié1, Champ* allié2){
    int a=0, b=0, c=0;
    nathalie->tech.nbtrechargement = 4;
    nathalie->jauge -= 4;
    printf("Nathalie utilise Flashbacks !\n");
    appeffetStat(allié1,4,100);//soigne de 100
    appeffetStat(allié2,4,100);
    appeffetStat(nathalie,4,100);
    for(int i=0; i<10; i++){ // enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité et le renvoie de dégâts)
        if(allié1->effets[i].effet_statut != 5 || allié1->effets[i].effet_statut != 6){
            allié1->effets[i].effet_statut = 0;
            allié1->effets[i].duree = 0;
        }
        if(nathalie->effets[i].effet_statut != 5 || nathalie->effets[i].effet_statut != 6){
            nathalie->effets[i].effet_statut = 0;
            nathalie->effets[i].duree = 0;
        }
        if(allié2->effets[i].effet_statut != 5 || allié2->effets[i].effet_statut != 6){
            allié2->effets[i].effet_statut = 0;
            allié2->effets[i].duree = 0;
        }
    }
}

 void marqueduBourreau(Champ* zed, Champ* ennemi){
    printf("\n Zed utilise marque du bourreau ! \n");
    zed->jauge -= 4;
    ennemi->pvcourant -= ennemi->pvmax*0.1;
    appeffetStatut(ennemi,7,2);//applique l'effet bourreau pendant 2 tours
    zed->tech.nbtrechargement=3;
}