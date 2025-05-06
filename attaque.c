#include "principal.h"

float attaque(Champ *champatt, Champ *champdef){
    if(champatt == NULL || champdef == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    float degats = champatt->att - champdef->def; // calcul des dégats
    if (degats < 0) {
        degats = 0;
    }
    if (champatt->statut == 5) { // renvoie de dégats
        champatt->pvcourant -= degats / 4;
        if (champatt->pvcourant < 0) {
            champatt->pvcourant = 0;
        }
    }
    int alea=rand()%100;
    if(alea<champdef->agilite){ //esquive
        degats=0;
        printf("%s a esquive l'attaque de %s !\n", champdef->nom, champatt->nom);
    }
    champdef->pvcourant -= degats;
    return champdef->pvcourant;
}

void degatseffetStatut(Champ *champ){
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    if (champ->nbeffets == 0) {
        return;
    }
    else if (champ->nbeffets > 0) {
        for (int i = 0; i < champ->nbeffets; i++) {
            if (champ->effets[i].effet_statut == 1) {
                champ->pvcourant -= champ->pvmax * 0.05;
                break;
            }
            else if (champ->effets[i].effet_statut == 6) {
                if(champ->pvcourant <= champ->pvmax * 0.25) {
                    champ->pvcourant = 0;
                    champ->statut = 0; // mort
                }
                break;
            }
            champ->effets[i].duree--;
            if (champ->effets[i].duree == 0) {
                for (int j = i; j < champ->nbeffets-1; j++) {
                    champ->effets[j] = champ->effets[j + 1];
                }
                champ->nbeffets--;
                i--;
            }
        }
    }
}

void appeffetStatut(Champ *champ, EffetStatut effetstatut, int duree) {
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    int bool=0;
    for (int i=0; i<champ->nbeffets; i++){
        if(champ->effets[i].effet_statut==effetstatut){
            champ->effets[i].duree=duree;
            bool=1;
        }
    }
    if(bool==0){
        champ->effets[champ->nbeffets].effet_statut= effetstatut;
        champ->effets[champ->nbeffets].duree= duree;
    }
}

void appeffetStat(Champ *champ, EffetStat effetstat, float valeur) {
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
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
    if(e1 == NULL || e2 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    for(int i=0; i<6; i++){
        if(tab[i] == NULL){
            printf("Erreur : pointeur nul");
            exit(1);
        }
    }
    for (int i=0; i<3; i++) {
        tab[i]=&e1->membres[i];
        tab[i+3]=&e2->membres[i];
    }
    for (int i=0; i<5; i++) {
        for (int j=i+1; j<6; j++) {
            if (tab[i]->vitesse < tab[j]->vitesse) {
                Champ *temp=tab[i];
                tab[i]=tab[j];
                tab[j]=temp;
            }
        }
    }
}

int memeEquipe(Champ* champ, Equipe* e1) {
    if(champ == NULL || e1 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    for (int i=0; i<3; i++) {
        if (champ==&e1->membres[i]) {
            return 1;
        }
    }
    return 0;
}

Champ* choixCible(Champ* attaquant, Equipe* e1, Equipe* e2) {
    if(attaquant == NULL || e1 == NULL || e2 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    int index=3;
    int verif;
    printf("Equipe adverse: \n");
    for (int i=0; i<3; i++) {
        if (e2->membres[i].pvcourant>0) {
            printf("%d- %s (PV: %f) \n", i, e2->membres[i].nom, e2->membres[i].pvcourant);
        } else {
            printf("%s KO \n", e2->membres[i].nom);
        }
    }
    for(int j=0; j<3; j++){
        for(int k=0; k<e2->membres[j].nbeffets; k++){
            if(e2->membres[j].effets[k].effet_statut==3){
                printf("%s est provoqué par %s !\n",attaquant->nom, e2->membres[j].nom);
                return &e2->membres[j];
            }
        }
    }
    do{
        do{
            printf("Choisissez votre cible (0,1 ou 2): ");
            verif=scanf("%d",&index);
            if(index<0 || index>2){
                printf("Index invalide");
            }
            vide_buffer();
        } while (index<0 || index>2 || verif!=1);
        if(e2->membres[index].pvcourant<=0){
            printf("Cible KO. Veuillez en chosir une nouvelle\n");
            index=3;
        }
    } while (index==3);
    return &e2->membres[index];
}

void tour (Equipe* e1, Equipe* e2){
    affichageCombat(e1,e2);
    if(e1 == NULL || e2 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    Champ *tab[6];
    int verif;
    triParVit(e1,e2,tab);
    for (int i=0;i<6;i++){
        if(tab[i]->pvcourant<=0){
            printf("%s est KO.\n",tab[i]->nom);
        } else {
            printf("\nC'est au tour de %s !\n", tab[i]->nom);
            for (int j=0; j<tab[i]->nbeffets; j++){
                if (tab[i]->effets[j].duree>0){
                degatseffetStatut(tab[i]);
                }
            }
        }
        Equipe *joueur;
        Equipe *adversaire;
            if(memeEquipe(tab[i],e1)==0){
                joueur=e2;
                adversaire=e1;
            } else {
                joueur=e1;
                adversaire=e2;
            }
        Champ *cible=choixCible(tab[i], joueur, adversaire);
        float pvtemp=cible->pvcourant;
        if (tab[i]->jaugeactuelle==tab[i]->jaugemax){
            int choix;
            printf("Jauge pleine! Voulez-vous utiliser une technique spéciale? (1:oui, 0:non): ");
            do{
                verif=scanf("%d", &choix);
                if(choix>1 || choix<0){
                    printf("INDEX INVALIDE");
                }
                vide_buffer();
            }while(choix>1 || choix<0 || verif!=1); 
            if (choix==1){
                printf("%s utilise son attaque spéciale !\n", tab[i]->nom);
                //implementer fonctions techniques
            }
            else {
                printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                attaque(tab[i], cible);
        } 
        } else {
        printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
        attaque(tab[i],cible);
        }
        for(int j=0; j<cible->nbeffets; j++){ // suppression des degats si le statut est invincibilité
            if(cible->effets[0].effet_statut==4){
                cible->pvcourant=pvtemp;
            }
        }
        if (cible->pvcourant<0) {
            cible->pvcourant=0;
            cible->statut=0;
            printf("%s à tué %s !\n", tab[i]->nom, cible->nom);
            if(memeEquipe(cible,e1)==0){
                e1->nbchampvivant--;
            } else {
                e2->nbchampvivant--;
            }
        }
        if(e1->nbchampvivant==0){
            i=6;
        }
        if(e2->nbchampvivant==0){
            i=6;
        }
        tab[i]->jaugeactuelle+=1;
        if(tab[i]->jaugeactuelle>tab[i]->jaugemax){
            tab[i]->jaugeactuelle=tab[i]->jaugemax;
        }
    }
}

void touria(Equipe* e1, Equipe* e2, int difficulte){
    affichageCombat(e1,e2);
    if(e1 == NULL || e2 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    Champ *tab[6];
    int verif;
    triParVit(e1,e2,tab);
    for (int i=0;i<6;i++){
        if(tab[i]->pvcourant<=0){
            printf("%s est KO.\n",tab[i]->nom);
        } 
        else {
            printf("\nC'est au tour de %s !\n", tab[i]->nom);
            for (int j=0; j<tab[i]->nbeffets; j++){
                if (tab[i]->effets[j].duree>0){
                    degatseffetStatut(tab[i]);
                }
            }
        }
        Equipe *joueur;
        Equipe *adversaire;
        Champ* cible;
        if(memeEquipe(tab[i],e1)==0){
            joueur=e2;
            adversaire=e1;
            if(difficulte==1){
                *cible=e1->membres[rand()%3];
                attaque(tab[i], cible);
                printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
            }
            else if(difficulte==2){
                *cible=e1->membres[0];
                for(int j=1; j<3; j++){
                    if(e1->membres[j].pvcourant<cible->pvcourant){
                        *cible=e1->membres[j];
                    }
                }
            }
            else{
                *cible=e1->membres[0];
                for(int j=1; j<3; j++){
                    if(e1->membres[j].pvcourant<cible->pvcourant){
                        *cible=e1->membres[j];
                    }
                if(tab[i]->jaugeactuelle==tab[i]->jaugemax){}
                //insérer tech spé si jauge pleine
                }
            }
        } 
        else {
            joueur=e1;
            adversaire=e2;
            cible=choixCible(tab[i], joueur, adversaire);
            float pvtemp=cible->pvcourant;
            if (tab[i]->jaugeactuelle==tab[i]->jaugemax){
                int choix;
                printf("Jauge pleine! Voulez-vous utiliser une technique spéciale? (1:oui, 0:non): ");
                do{
                    verif=scanf("%d", &choix);
                    if(choix>1 || choix<0){
                    printf("INDEX INVALIDE");
                    }
                    vide_buffer();
                }while(choix>1 || choix<0 || verif!=1); 
                if (choix==1){
                    printf("%s utilise son attaque spéciale !\n", tab[i]->nom);
                    //implementer fonctions techniques
                }
                else {
                printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                attaque(tab[i], cible);
                } 
            } 
            else {
                printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                attaque(tab[i],cible);
            }
            for(int j=0; j<cible->nbeffets; j++){ // suppression des degats si le statut est invincibilité
                if(cible->effets[0].effet_statut==4){
                cible->pvcourant=pvtemp;
                }
            }
        }
        if (cible->pvcourant<0) {
            cible->pvcourant=0;
            cible->statut=0;
            printf("%s à tué %s !\n", tab[i]->nom, cible->nom);
            if(memeEquipe(cible,e1)==0){
                e1->nbchampvivant--;
            } else {
                e2->nbchampvivant--;
            }
        }
        if(e1->nbchampvivant==0){
            i=6;
        }
        if(e2->nbchampvivant==0){
            i=6;
        }
        tab[i]->jaugeactuelle+=1;
        if(tab[i]->jaugeactuelle>tab[i]->jaugemax){
            tab[i]->jaugeactuelle=tab[i]->jaugemax;
        }
    }
}