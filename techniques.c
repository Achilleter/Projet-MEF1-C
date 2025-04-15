#include <stdio.h>
#include "structures.h"

void berserk(Champ xavier, Champ ennemi){
    xavier.tech.nom ="Berserk";  
    xavier.tech.nbtactifs = 1;
    xavier.tech.nbtrechargement = 3;
    if(xavier.jauge >= 3){
        xavier.jauge -=3;
        xavier.att = 50;
        xavier.def += 15;
        attaque(xavier, ennemi);
    }
    else if(xavier.jauge < 0){
        xavier.jauge = 0;
    }
    if(xavier.tech.nbtactifs < 1){
        xavier.effets[0].effet_statut = 2;
        xavier.effets[0].duree = 1;
    }
}

void flashbacks(Champ nathalie, Champ allié1, Champ allié2, Champ ennemi){
    nathalie.tech.nom = "Flashbacks";  
    nathalie.tech.nbtactifs = 1;
    nathalie.tech.nbtrechargement = 4;
    if(nathalie.jauge >= 4){
        nathalie.jauge -= 4;
        allié1.pvcourant += 100;
        allié2.pvcourant += 100;
        nathalie.pvcourant += 100;
        for(int i=0; i<4; i++){
            nathalie.effets[i].effet_statut = 0;
            nathalie.effets[i].duree = 0;
            nathalie.effets[i].valeur = 0;
            nathalie.effets[i].effet_stat = 0;
            allié1.effets[i].effet_statut = 0;
            allié1.effets[i].duree = 0;
            allié1.effets[i].valeur = 0;
            allié1.effets[i].effet_stat = 0;
            allié2.effets[i].effet_statut = 0;
            allié2.effets[i].duree = 0;
            allié2.effets[i].valeur = 0;
            allié2.effets[i].effet_stat = 0;
            }
        }
    else if(nathalie.jauge < 0){
        nathalie.jauge = 0;
    }
    if(nathalie.tech.nbtactifs < 1){
        nathalie.effets[0].effet_statut = 2;
        nathalie.effets[0].duree = 1;
    }
 }