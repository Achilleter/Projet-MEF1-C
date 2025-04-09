#include <stdio.h>

float attaque(Champ champatt, Champ champdef){
    float degats = champatt.attaque - champdef.defense;
    if (degats < 0) {
        degats = 0;
    }
    champdef.pvcourant -= degats;
    return champdef.pvcourant;
}

Champ techspé(Champ champatt, Champ champdef){
    
}