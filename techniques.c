#include <stdio.h>
#include "structures.h"

void berserk(Champ* xavier, Champ* ennemi){
    // augmente l'attaque de 20 et la défense de 10, applique l'invincibilité pendant 1 tour puis s'immobilise pendant 1 tour
    if(xavier->tech.nbtactifs == 0){
        xavier->tech.nbtactifs = 2;
        xavier->tech.nbtrechargement = 4;
        xavier->jauge -=3;
        printf("Xavier utilise Berserk !\n");
        appeffetStat(xavier,1,20);//augmente l'attaque de 20
        appeffetStat(xavier,2,10);//augmente la defense de 10
        appeffetStatut(xavier,4,1);//applique invincibilité pendant 1 tour
    }
    else if(xavier->tech.nbtactifs == 1){
        xavier->tech.nbtactifs = 0;
        appeffetStatut(xavier,2,1);//s'immobilise
        appeffetStat(xavier,1,-20);//diminue l'attaque de 20
        appeffetStat(xavier,2,-10);//diminue la defense de 10
    }
}


void flashbacks(Champ* nathalie, Champ* allié1, Champ* allié2){
    //soigne de 100 tous les alliés et leur enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
    int a=0, b=0, c=0;
    nathalie->tech.nbtrechargement = 4;
    nathalie->jauge -= 4;
    printf("Nathalie utilise Flashbacks !\n");
    appeffetStat(allié1,4,100);//soigne de 100
    appeffetStat(allié2,4,100);
    appeffetStat(nathalie,4,100);
    for(int i=0; i<6; i++){ // enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
        if((allié1->effets[i].effet_statut != 5 || allié1->effets[i].effet_statut != 6) || allié1->effets[i].effet_statut != 3){
            allié1->effets[i].effet_statut = 0;
            allié1->effets[i].duree = 0;
        }
        if((allié1->effets[i].effet_statut != 5 || allié1->effets[i].effet_statut != 6) || allié1->effets[i].effet_statut != 3){
            nathalie->effets[i].effet_statut = 0;
            nathalie->effets[i].duree = 0;
        }
        if((allié1->effets[i].effet_statut != 5 || allié1->effets[i].effet_statut != 6) || allié1->effets[i].effet_statut != 3){
            allié2->effets[i].effet_statut = 0;
            allié2->effets[i].duree = 0;
        }
    }
}

 void marqueduBourreau(Champ* zed, Champ* ennemi){
    // applique l'effet bourreau sur un ennemi pendant 2 tours
    printf("\n Zed utilise marque du bourreau ! \n");
    zed->jauge -= 4;
    ennemi->pvcourant -= ennemi->pvmax*0.1;
    appeffetStatut(ennemi,6,2);//applique l'effet bourreau pendant 2 tours
    zed->tech.nbtrechargement=3;
}

void murailleInfinie(Champ* smasheur){
    //provoque les ennemis, augmente sa défense de 20 et renvoie les dégats pendant 1 tour
    if(smasheur->tech.nbtactifs == 0){
        smasheur->tech.nbtactifs = 2;
        smasheur->tech.nbtrechargement = 4;
        printf("\n Smasheur utilise Muraille Infinie ! \n");
        smasheur->jauge -= 4;
        appeffetStatut(smasheur,5,1);//applique l'effet renvoie de dégâts pendant 1 tour
        appeffetStatut(smasheur,3,1);//applique l'effet provocation pendant 1 tour
        appeffetStat(smasheur,3,20);//augmente la défense de 20
    }
    else if(smasheur->tech.nbtactifs == 1){
        smasheur->tech.nbtactifs = 0;
        appeffetStat(smasheur,3,-20);//diminue la défense de 20
    }
}

void motivation(Champ* steve, Champ* allié1, Champ* allié2){
    //augmentation de la vitesse d'un allié ou de soi même de 25
    printf("\n Steve utilise Motivation ! \n");
    steve->tech.nbtrechargement = 4;
    steve->jauge -= 4;
    int choix=0;
    printf("\n Qui voulez-vous motiver ? (0=vous, 1=%s, 2=%s) \n", allié1->nom, allié2->nom);
    do{// vérification du choix
    scanf("%d",&choix);
    if(choix<0 || choix>2){
        printf("Index invalide\n");
    }
    } while (choix<0 || choix>2);
    switch (choix){
        case 0:
            printf("\n Vous vous motivez ! \n");
            appeffetStat(steve,3,25);//augmente la vitesse de 25
            break;
        case 1:
            printf("\n Vous motivez %s ! \n", allié1->nom);
            appeffetStat(allié1,3,25);
            break;
        case 2: 
            printf("\n Vous motivez %s ! \n", allié2->nom);
            appeffetStat(allié2,3,25);
            break;
    }
}

void fossoyeurdesMondes(Champ* booga){
    
}

void Exploglace(Champ* sandrine, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3){
    // inflige 50 de dégats à tous les ennemis et diminue leur vitesse de 15
    printf("\n Sandrine utilise Exploglace ! \n");
    sandrine->tech.nbtrechargement = 4;
    sandrine->jauge -= 4;
    ennemi1->pvcourant -= 30;
    ennemi2->pvcourant -= 30;
    ennemi3->pvcourant -= 30;
    appeffetStat(ennemi1,3,15);//diminue la vitesse de 15
    appeffetStat(ennemi2,3,15);
    appeffetStat(ennemi3,3,15);
}

void scierculaire(Champ* annesophie, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3){
    //inflige 70 dégats à tous les ennemis et réduit leur défense de 5
    printf("\n Annesophie utilise Scierculaire ! \n");
    annesophie->tech.nbtrechargement = 4;
    annesophie->jauge -= 4;
    ennemi1->pvcourant -= 50;
    ennemi2->pvcourant -= 50;
    ennemi3->pvcourant -= 50;
    appeffetStat(ennemi1,2,-5);//diminue la défense de 5
    appeffetStat(ennemi2,2,-5);
    appeffetStat(ennemi3,2,-5);
}

void cicatricesEternels(Champ* gaby, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3){
    // inflige 100 de dégats à tous les ennemis
    printf("\n Gaby utilise Cicatrices Eternels ! \n");
    gaby->tech.nbtrechargement = 6;
    gaby->jauge -= 4;
    ennemi1->pvcourant -= 100;
    ennemi2->pvcourant -= 100;
    ennemi3->pvcourant -= 100;
}

void reinitialisation(Champ* clara, Champ* allié1, Champ* allié2){
    // Ressucite un allié avec la moitié de ses points de vies
    if (allié1->statut==1||allié2->statut==1) {
        printf("\n Aucun de vos alliés n'est mort ! \n");
        return;
    }
    else if (allié1->statut==0 && allié2->statut==0) {
        int choix=0;
        printf("\n Choississez un allié à ressusciter (1=%s, 2=%s) : \n", allié1->nom, allié2->nom);
        do {
            scanf("%d", &choix);
            if (choix<1 || choix>2) {
                printf("Index invalide\n");
            }
        }
        while (choix<1 || choix>2);
        printf("\n Clara utilise Réinitialisation ! \n");
        clara->tech.nbtrechargement = 6;
        clara->jauge -= 4;
        if (choix==1) {
            printf("\n Vous ressuscitez %s ! \n", allié1->nom);
            allié1->pvcourant = allié1->pvmax / 2;
            allié1->statut = 1;
        }
        else {
            printf("\n Vous ressuscitez %s ! \n", allié2->nom);
            allié2->pvcourant = allié2->pvmax / 2;
            allié2->statut = 1;
        }
    }
    else {
        printf("\n Clara utilise Réinitialisation ! \n");
        clara->tech.nbtrechargement = 6;
        clara->jauge -= 4;
        if (allié1->statut==0) {
            printf("\n Vous ressuscitez %s ! \n", allié1->nom);
            allié1->pvcourant = allié1->pvmax / 2;
            allié1->statut = 1;
        }
        else {
            printf("\n Vous ressuscitez %s ! \n", allié2->nom);
            allié2->pvcourant = allié2->pvmax / 2;
            allié2->statut = 1;
        }
    }
}