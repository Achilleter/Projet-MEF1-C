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

void triParVit(Equipe *e1, Equipe *e2, Champ *tab[6]) {
    for (int i = 0; i < 3; i++) {
        tab[i] = &e1->membres[i];
        tab[i + 3] = &e2->membres[i];
    }
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (tab[i]->vitesse < tab[j]->vitesse) {
                Champ *temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

void tour (Equipe e1, Equipe e2){
    Champ *tab[6];
    triParVit(e1,e2,tab);
    for (int i=0;i<6:i++){
        Champ *a=tab[i];
        if(a->pvcourants<=0){
            printf("%s est ko.\n",a->nom);
            continue;
        }
        printf("\nC'est au tour de %s !\n", c->nom);
        for (int j=0; j<a->nbeffets; j++){
            if(a->effets[j].duree==0){
                continue;
            } else if (a->effets[j].duree>0){
                appeffet_Statut(a);
            }
        }
        if (a->jauge=5) {
            int choix;
            printf("Jauge pleine! Voulez-vous utiliser une technique spéciale? (1:oui, 0:non): ");
            scanf("%d", &choix);
            if (choix==1){
                // Travailler fonction technique
            }
        // Travailler fonction cible
    }
    a->jauge+=(a->vitesse/40);
    if(a->jauge>5){
        a->jauge=5;
    }

