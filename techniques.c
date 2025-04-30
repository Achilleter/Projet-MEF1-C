#include "principal.h"

void berserk(Champ* xavier){
    if(xavier==NULL){
        printf("Erreur: pointeur nul.");
        exit(1);
    }
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


void flashbacks(Champ* nathalie, Champ* allie1, Champ* allie2){
    if(nathalie==NULL||allie1==NULL||allie2==NULL){
        printf("Erreur: pointeur nul.");
        exit(10);
    }
    //soigne de 100 tous les alliés et leur enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
    nathalie->tech.nbtrechargement = 4;
    nathalie->jauge -= 4;
    printf("Nathalie utilise Flashbacks !\n");
    appeffetStat(allie1,4,100);//soigne de 100
    appeffetStat(allie2,4,100);
    appeffetStat(nathalie,4,100);
    for(int i=0; i<6; i++){ // enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
        if((allie1->effets[i].effet_statut != 5 || allie1->effets[i].effet_statut != 4) || allie1->effets[i].effet_statut != 3){
            allie1->effets[i].effet_statut = 0;
            allie1->effets[i].duree = 0;
        }
        if((allie1->effets[i].effet_statut != 5 || allie1->effets[i].effet_statut != 4) || allie1->effets[i].effet_statut != 3){
            nathalie->effets[i].effet_statut = 0;
            nathalie->effets[i].duree = 0;
        }
        if((allie1->effets[i].effet_statut != 5 || allie1->effets[i].effet_statut != 4) || allie1->effets[i].effet_statut != 3){
            allie2->effets[i].effet_statut = 0;
            allie2->effets[i].duree = 0;
        }
    }
}

 void marqueduBourreau(Champ* zed, Champ* ennemi){
    if(zed==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(11);
    }
    // applique l'effet bourreau sur un ennemi pendant 2 tours
    printf("\n Zed utilise marque du bourreau ! \n");
    zed->jauge -= 4;
    ennemi->pvcourant -= ennemi->pvmax*0.1;
    appeffetStatut(ennemi,6,2);//applique l'effet bourreau pendant 2 tours
    zed->tech.nbtrechargement=3;
}

void murailleInfinie(Champ* smasheur){
    if(smasheur==NULL){
        printf("Erreur: pointeur nul.");
        exit(100);
    }
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

void motivation(Champ* steve, Champ* allie1, Champ* allie2){
    if(steve==NULL||allie1==NULL||allie2==NULL){
        printf("Erreur: pointeur nul.");
        exit(101);
    }
    //augmentation de la vitesse d'un allié ou de soi même de 25
    int verif;
    printf("\n Steve utilise Motivation ! \n");
    steve->tech.nbtrechargement = 4;
    steve->jauge -= 4;
    int choix=0;
    printf("\n Qui voulez-vous motiver ? (0=vous, 1=%s, 2=%s) \n", allie1->nom, allie2->nom);
    do{// vérification du choix
        verif=scanf("%d",&choix);
        if(choix<0 || choix>2){
            printf("Index invalide\n");
        }
        vide_buffer();
    } while (choix<0 || choix>2 || verif!=1);
    switch (choix){
        case 0:
            printf("\n Vous vous motivez ! \n");
            appeffetStat(steve,3,25);//augmente la vitesse de 25
            break;
        case 1:
            printf("\n Vous motivez %s ! \n", allie1->nom);
            appeffetStat(allie1,3,25);
            break;
        case 2: 
            printf("\n Vous motivez %s ! \n", allie2->nom);
            appeffetStat(allie2,3,25);
            break;
    }
}

void fossoyeurdesMondes(Champ* booga){
    if(booga==NULL){
        printf("Erreur: pointeur nul.");
        exit(110);
    }
    if(booga->tech.nbtactifs == 0){
        booga->tech.nbtactifs = 2;
        booga->tech.nbtrechargement = 3;
        printf("\n Booga utilise Fossoyeur des Mondes ! \n");
        booga->jauge -= 4;
        appeffetStat(booga, 4, 25); // Se soigne de 25 PV à chaque tour
        appeffetStat(booga, 1, 10); // Augmente l'attaque de 10
        appeffetStat(booga, 2, 10); // Augmente la défense de 10
    }
}

void cryogenese(Champ* sandrine, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3){
    if(sandrine==NULL||ennemi1==NULL||ennemi2==NULL||ennemi3=NULL){
        printf("Erreur: pointeur nul.");
        exit(111);
    }
    // inflige 30 de dégats à tous les ennemis et diminue leur vitesse de 15
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
    if(annesophie==NULL||ennemi1==NULL||ennemi2==NULL||ennemi3=NULL){
        printf("Erreur: pointeur nul.");
        exit(1000);
    }
    //inflige 50 dégats à tous les ennemis et réduit leur défense de 5
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
    if(gaby==NULL||ennemi1==NULL||ennemi2==NULL||ennemi3=NULL){
        printf("Erreur: pointeur nul.");
        exit(1001);
    }
    // inflige 100 de dégats à tous les ennemis
    printf("\n Gaby utilise Cicatrices Eternels ! \n");
    gaby->tech.nbtrechargement = 6;
    gaby->jauge -= 4;
    ennemi1->pvcourant -= 100;
    ennemi2->pvcourant -= 100;
    ennemi3->pvcourant -= 100;
}

void reinitialisation(Champ* clara, Champ* allie1, Champ* allie2){
    if(clara==NULL||allie1==NULL||allie2==NULL){
        printf("Erreur: pointeur nul.");
        exit(1010);
    }
    // Ressucite un allié avec la moitié de ses points de vies
    int verif;
    if (allie1->statut==1||allie2->statut==1) {
        printf("\n Aucun de vos alliés n'est mort ! \n");
        return;
    }
    else if (allie1->statut==0 && allie2->statut==0) {
        int choix=0;
        printf("\n Choississez un allié à ressusciter (1=%s, 2=%s) : \n", allie1->nom, allie2->nom);
        do {
            verif=scanf("%d", &choix);
            if (choix<1 || choix>2) {
                printf("Index invalide\n");
            }
            vide_buffer();
        }while (choix<1 || choix>2 || verif!=1);
        printf("\n Clara utilise Réinitialisation ! \n");
        clara->tech.nbtrechargement = 6;
        clara->jauge -= 4;
        if (choix==1) {
            printf("\n Vous ressuscitez %s ! \n", allie1->nom);
            allie1->pvcourant = allie1->pvmax / 2;
            allie1->statut = 1;
        }
        else {
            printf("\n Vous ressuscitez %s ! \n", allie2->nom);
            allie2->pvcourant = allie2->pvmax / 2;
            allie2->statut = 1;
        }
    }
    else {
        printf("\n Clara utilise Réinitialisation ! \n");
        clara->tech.nbtrechargement = 6;
        clara->jauge -= 4;
        if (allie1->statut==0) {
            printf("\n Vous ressuscitez %s ! \n", allie1->nom);
            allie1->pvcourant = allie1->pvmax / 2;
            allie1->statut = 1;
        }
        else {
            printf("\n Vous ressuscitez %s ! \n", allie2->nom);
            allie2->pvcourant = allie2->pvmax / 2;
            allie2->statut = 1;
        }
    }
}
