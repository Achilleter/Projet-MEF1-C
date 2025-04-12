#include <stdio.h>

void berserk(Champ xavier, Champ ennemi, Techniquespe technique){
    technique.nom ="Berserk";  
    technique.nbtactifs = 1;
    technique.nbtrechargement = 3;
    if(xavier.jauge < 0){
        xavier.jauge = 0;
    }
    if(xavier.jauge >= 3){
        xavier.jauge -=3;
        xavier.att = 50;
        xavier.def += 15;
        attaque(xavier, ennemi);
    }
    xavier.effets.effet_statut = 2;
    xavier.effets.duree = 2;
}