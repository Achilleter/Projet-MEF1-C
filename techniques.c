#include <stdio.h>
#include "structures.h"

void berserk(Champ xavier, Champ ennemi){
    xavier.tech.nom ="Berserk";  
    xavier.tech.nbtactifs = 1;
    xavier.tech.nbtrechargement = 3;
    if(xavier.jauge < 0){
        xavier.jauge = 0;
    }
    if(xavier.jauge >= 3){
        xavier.jauge -=3;
        xavier.att = 50;
        xavier.def += 15;
        attaque(xavier, ennemi);
    }
    if(xavier.tech.nbtactifs < 1){
        xavier.effets[0].effet_statut = 2;
        xavier.effets[0].duree = 1;
    }
}