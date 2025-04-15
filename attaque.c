#include <stdio.h>
#include "structures.h"

float attaque(Champ champatt, Champ champdef){
    float degats = champatt.att - champdef.def;
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
    if(champatt.tech.effet_statut!=0){
        champdef.statut=champatt.tech.effet_statut;
    }
    if(champatt.tech.effet_stat!=0){
        champdef.stat=champatt.tech.effet_stat;
    }
}

void degatseffetStatut(Champ *champ){
    if (champ->nbeffets == 0) {
        return;
    }
    else if (champ->nbeffets > 0) {
        for (int i = 0; i < champ->nbeffets; i++) {
            switch (champ->effets[i].effet_statut) {
                case 1:
                champ->pvcourant -= champ->pvmax * 0.05;
                break;
                case 6:
                if(champ->pvcourant <= champ->pvmax * 0.25) {
                    champ->pvcourant = 0;
                    champ->statut = 0; // mort
                }
                break;
            }
            champ->effets[i].duree--;
            if (champ->effets[i].duree = 0) {
                for (int j = i; j < champ->nbeffets-1; j++) {
                    champ->effets[j] = champ->effets[j + 1];
                }
                champ->nbeffets--;
                i--;
            }
        }
    }
}

void appeffetStatut(Champ *champ, EffetStatut effetstatut, int durée) {
        champ->effets[champ->nbeffets].effet_statut= effetstatut;
        champ->effets[champ->nbeffets].duree= durée;
}

void appeffetstat(Champ *champ, EffetStat effetstat, float valeur) {
        switch (effetstat){
            case 1:
                champ->att += valeur;
                break;
            case 2:
                champ->def += valeur;
                break;
            case 3:
                champ->vitesse += valeur;
                break;
            case 4:
                champ->pvcourant += valeur;
                if (champ->pvcourant > champ->pvmax) {
                    champ->pvcourant = champ->pvmax;
                }
                break;
        }
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

int memeEquipe(Champ* champ, Equipe* e1) {
    for (int i=0; i<3; i++) {
        if (champ==&e1->membres[i]) {
            return 1;
        }
    }
    return 0;
}

Champ* cible(Champ* att, Equipe* e1, Equipe* e2) {
    int index=3;
    printf("Equipe adverse: \n");
    for (int i=0; i<3; i++) {
        if (e2->membres[i].pvcourant>0) {
            printf("%d - %s (PV: %f) \n", i, e2->membres[i].nom, e2->membres[i].pvcourant);
        } else {
            printf("%s KO \n", e2->membres[i].nom);
        }
    }
    do{
        do{
            printf("Choisissez votre cible (0,1 ou 2): ");
            scanf("%d",&index);
            if(index<0 || index>2){
                printf("Index invalide");
            }
        } while (index<0 || index>2);
        if(e2->membres[index]->pvcourant<=0){
            printf("Cible KO. Veuillez en chosir une nouvelle\n");
            index=3;
        }
    } while (index==3);
    return e2->membres[index];
}

void tour (Equipe* e1, Equipe* e2){
    Champ *tab[6];
    triParVit(e1,e2,tab);
    for (int i=0;i<6;i++){
        Champ *a=tab[i];
        if(a->pvcourant<=0){
            printf("%s est ko.\n",a->nom);
            continue;
        }
        printf("\nC'est au tour de %s !\n", c->nom);
        for (int j=0; j<a->nbeffets; j++){
            if(a->effets[j].duree==0){
                continue;
            } else if (a->effets[j].duree>0){
                appeffet(a);
            }
        }
        if (a->jauge=5) {
            int choix;
            printf("Jauge pleine! Voulez-vous utiliser une technique spéciale? (1:oui, 0:non): ");
            scanf("%d", &choix);
            if (choix==1){
                // Travailler fonction technique
            }
            else {
        // Travailler fonction cible
            }
            a->jauge+=(a->vitesse/40);
            if(a->jauge>5){
                a->jauge=5;
            }
        }
    }
}
