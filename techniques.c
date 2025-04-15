#include <stdio.h>
#include "structures.h"

void berserk(Champ xavier, Champ ennemi){
    xavier.tech.nom ="Berserk";  
    xavier.tech.nbtactifs = 1;
    xavier.tech.nbtrechargement = 3;
    if(xavier.jauge >= 3){
        xavier.jauge -=3;
        printf("Xavier s'insère une clé piratée en lui : devient immunisé à toutes les attaques pdt 1 tour + Att=50 + DEF+=10 pdt 1 tour et peut attaquer, à la fin il est STUN le prochain tour");
        printf("\nJauge actuelle : %.2f\n", xavier.jauge);
        for(int j=0; j<10; j++){ // permet de trouver la première case vide dans le tableau d'effets de Xavier
            if(xavier.effets[j].effet_statut == 0){
                xavier.effets[j].effet_statut = 5; 
                xavier.effets[j].duree = 1;
                break;
            }
        }
        for(int m=0; m<10; m++){
            if(xavier.effets[m].effet_stat == 0){
                xavier.effets[m].effet_stat = 1; 
                xavier.effets[m].valeur = 20;
                xavier.effets[m].duree = 1;
                break;
            }
        }
        for(int n=0; n<10; n++){
            if(xavier.effets[n].effet_stat == 0){
                xavier.effets[n].effet_stat = 2; 
                xavier.effets[n].valeur = 10;
                xavier.effets[n].duree = 1;
                break;
            }
        }
        attaque(xavier, ennemi);
    }
    else if(xavier.jauge < 0){
        xavier.jauge = 0;
    }
    else if(xavier.jauge < 3){
        printf("Pas assez de jauge pour utiliser cette technique.\n");
        printf("Jauge actuelle : %.2f\n", xavier.jauge);
        return;
    }
    for(int i=0; i<4; i++){
        if(xavier.tech.nbtactifs < 1){
            xavier.effets[i].effet_statut = 2;
            xavier.effets[i].duree = 1;
        }
    }
}



void flashbacks(Champ nathalie, Champ allié1, Champ allié2, Champ ennemi){
    int a=0, b=0, c=0;
    nathalie.tech.nom = "Flashbacks";  
    nathalie.tech.nbtactifs = 1;
    nathalie.tech.nbtrechargement = 4;
    if(nathalie.jauge >= 4){
        nathalie.jauge -= 4;
        printf("Nathalie remonte le temps : PVcourants+=100 pour toute la team + Purge la team de tous les effets négatifs/changement de stats");
        printf("\nJauge actuelle : %.2f\n", nathalie.jauge);
        for(int n=0; n<4; n++){ // permet de trouver la première case vide dans le tableau d'effets de chaque perso
            if(allié1.effets[n].effet_stat == 0){
                a=n;
                break;
            }
        }
        for(int j=0; j<4; j++){
            if(allié2.effets[j].effet_stat == 0){
                b=j;
                break;
            }
        }
        for(int m=0; m<4; m++){
            if(nathalie.effets[m].effet_stat == 0){
                c=m;
                break;
            }
        }
        allié1.effets[a].effet_stat = 4; 
        allié1.effets[a].valeur += 100;
        allié2.effets[b].effet_stat = 4;
        allié2.effets[b].valeur += 100;
        nathalie.effets[c].effet_stat = 4;
        nathalie.effets[c].valeur += 100;
        printf("PV courants de %s : %.2f\n", allié1.nom, allié1.pvcourant);
        printf("PV courants de %s : %.2f\n", allié2.nom, allié2.pvcourant);
        printf("PV courants de %s : %.2f\n", nathalie.nom, nathalie.pvcourant);
        for(int i=0; i<4; i++){ // enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité et le renvoie de dégâts)
            if(allié1.effets[i].effet_statut != 5 || allié1.effets[i].effet_statut != 6){
                allié1.effets[i].effet_statut = 0;
                allié1.effets[i].duree = 0;
                allié1.effets[i].valeur = 0;
            }
            if(nathalie.effets[i].effet_statut != 5 || nathalie.effets[i].effet_statut != 6){
                nathalie.effets[i].effet_statut = 0;
                nathalie.effets[i].duree = 0;
                nathalie.effets[i].valeur = 0;
            }
            if(allié2.effets[i].effet_statut != 5 || allié2.effets[i].effet_statut != 6){
                allié2.effets[i].effet_statut = 0;
                allié2.effets[i].duree = 0;
                allié2.effets[i].valeur = 0;
            }
        }
    }
    else if(nathalie.jauge < 0){
        nathalie.jauge = 0;
    }
    else if(nathalie.jauge < 4){
        printf("Pas assez de jauge pour utiliser cette technique.\n");
        printf("Jauge actuelle : %.2f\n", nathalie.jauge);
        return;
    }
    if(nathalie.tech.nbtactifs < 1){
        return;
    }
    else if(nathalie.tech.nbtactifs > 1){
        return;
    }
}

