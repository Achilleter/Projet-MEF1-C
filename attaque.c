#include <stdio.h>

float attaque(Champ champatt, Champ champdef){
    float degats = champatt.attaque - champdef.defense;
    if (degats < 0) {
        degats = 0;
    }
    champdef.pvcourant -= degats;
    return champdef.pvcourant;
}

Champ techspé(Champ champatt, Champ champdef, int* nbtactifs, int* nbtrechargment){
    if(champatt.tech.nbtactifs>1){
        *nbtactifs=champatt.tech.nbtactifs;
    }
    if(champatt.tech.nbtrechargement>1){
        *nbtrechargment=champatt.tech.nbtrechargement;
    }
    if(champatt.effet_statut!=0){
        champdef.statut=champatt.tech.effet_statut;
    }
    if(champatt.effet_stat!=0){
        champdef.stat=champatt.tech.effet_stat;
    }
}

void appeffet_Statut(Champ champ){
        switch(champ.statut){
            case 1:
                champ.pvcourant-=champ.pvmax*0.05;
                break;
            case 3:
                champ.vitesse-=champ.vitesse*0.5;
                break;
            default:
                break;
}