#include "principal.h"

void berserk(Champ* xavier){
    if(xavier==NULL){
        printf("Erreur: pointeur nul.");
        exit(1);
    }
    // augmente l'attaque de 20 et la défense de 10, applique l'invincibilité pendant 1 tour puis s'immobilise pendant 1 tour
    if(xavier->tech.nbtactifs == 0){
        xavier->tech.nbtactifs = 2;
        xavier->jaugeactuelle =0;
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
    nathalie->jaugeactuelle = 0;
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

 void bourreau(Champ* zed, Equipe* ennemi){
    if(zed==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(11);
    }
    int verif;
    int choix=0;
    do{
    printf("Choisissez un ennemi à viser (1=%s, 2=%s, 3=%s) : \n", ennemi->membres[0].nom, ennemi->membres[1].nom, ennemi->membres[2].nom);
        verif=scanf("%d", &choix);
        if (choix<1 || choix>3) {
            printf("Index invalide\n");
        }
        vide_buffer();
    } while (choix<1 || choix>3 || verif!=1);
    // applique l'effet bourreau sur un ennemi pendant 2 tours
    printf("\n Zed utilise marque du bourreau ! \n");
    zed->jaugeactuelle = 0;
    ennemi->membres[choix].pvcourant -= ennemi->membres[choix].pvmax*0.1;
    appeffetStatut(&ennemi->membres[choix],6,2);//applique l'effet bourreau pendant 2 tours
}

void muraille(Champ* smasheur){
    if(smasheur==NULL){
        printf("Erreur: pointeur nul.");
        exit(100);
    }
    //provoque les ennemis, augmente sa défense de 20 et renvoie les dégats pendant 1 tour
    if(smasheur->tech.nbtactifs == 0){
        smasheur->tech.nbtactifs = 2;
        printf("\n Smasheur utilise Muraille Infinie ! \n");
        smasheur->jaugeactuelle = 0;
        appeffetStatut(smasheur,5,2);//applique l'effet renvoie de dégâts pendant 1 tour
        appeffetStatut(smasheur,3,2);//applique l'effet provocation pendant 1 tour
        appeffetStat(smasheur,3,20);//augmente la défense de 20
    }
    else if(smasheur->tech.nbtactifs == 1){
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
    steve->jaugeactuelle = 0;
    int choix=0;
    do{// vérification du choix
        printf("\n Qui voulez-vous motiver ? (0=vous, 1=%s, 2=%s) \n", allie1->nom, allie2->nom);
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

void fossoyeur_des_mondes(Champ* booga){
    if(booga==NULL){
        printf("Erreur: pointeur nul.");
        exit(110);
    }
    appeffetStat(booga, 4, 25); // Se soigne de 25 PV à chaque tour
    if(booga->tech.nbtactifs == 0){
        booga->tech.nbtactifs = 2;
        printf("\n Booga utilise Fossoyeur des Mondes ! \n");
        booga->jaugeactuelle = 0;
        appeffetStat(booga, 1, 10); // Augmente l'attaque de 10
        appeffetStat(booga, 2, 10); // Augmente la défense de 10
    }
    else if(booga->tech.nbtactifs == 1){
        appeffetStat(booga, 1, -10); // Diminue l'attaque de 10
        appeffetStat(booga, 2, -10); // Diminue la défense de 10
        printf("\n Booga redevient comme avant ! \n");
    }
}

void cryogenese(Champ* sandrine, Equipe* ennemi){
    if(sandrine==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(111);
    }
    // inflige 30 de dégats à tous les ennemis et diminue leur vitesse de 15
    printf("\n Sandrine utilise Exploglace ! \n");
    sandrine->jaugeactuelle = 0;
    ennemi->membres[0].pvcourant -= 30;
    ennemi->membres[1].pvcourant -= 30;
    ennemi->membres[2].pvcourant -= 30;
    appeffetStat(&ennemi->membres[0],3,15);//diminue la vitesse de 15
    appeffetStat(&ennemi->membres[1],3,15);
    appeffetStat(&ennemi->membres[2],3,15);
}

void scierculaire(Champ* annesophie, Equipe* ennemi){
    if(annesophie==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(1000);
    }
    //inflige 50 dégats à tous les ennemis et réduit leur défense de 5
    printf("\n Annesophie utilise Scierculaire ! \n");
    annesophie->jaugeactuelle = 0;
    ennemi->membres[0].pvcourant -= 50;
    ennemi->membres[1].pvcourant -= 50;
    ennemi->membres[2].pvcourant -= 50;
    appeffetStatut(&ennemi->membres[0],1,2);//applique l'effet poison pendant 2 tours
    appeffetStatut(&ennemi->membres[1],1,2);
    appeffetStatut(&ennemi->membres[2],1,2);
}

void cicatrices_eternels(Champ* gaby, Equipe* ennemi){
    if(gaby==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(1001);
    }
    // inflige 100 de dégats à tous les ennemis
    printf("\n Gaby utilise Cicatrices Eternels ! \n");
    gaby->jaugeactuelle = 0;
    ennemi->membres[0].pvcourant -= 100;
    ennemi->membres[1].pvcourant -= 100;
    ennemi->membres[2].pvcourant -= 100;
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
        clara->jaugeactuelle = 0;
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
        clara->jaugeactuelle = 0;
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

void nomtechsamirazed(Champ* annesophie, Champ* zed, Equipe* adversaires){
    if(annesophie==NULL||zed==NULL||adversaires==NULL){
        printf("Erreur: pointeur nul.");
        exit(10000);
    }
    // Les personnages combinent leurs techniques pour infliger 60 de dégats à tous les ennemis, diminue leur défense de 5 et applique l'effet bourreau pendant 1 tour
   printf("\n Annesophie et zed se combine pour utilise Nomtechsamirazed ! \n");
   annesophie->jaugeactuelle = 0;
    zed->jaugeactuelle = 0;
    for(int i=0; i<3; i++){
        adversaires->membres[i].pvcourant -= 60;
        appeffetStat(&adversaires->membres[i],2,-5); //diminue la défense de tous les ennemis de 5
        appeffetStatut(&adversaires->membres[i],6,1); //applique l'effet bourreau à tous les ennemis pendant 1 tour
    }
}

void sacrifice_fraternel(Champ* xavier, Champ* steve){
    if(xavier==NULL||steve==NULL){
        printf("Erreur: pointeur nul.");
        exit(10001);
    }
    // Steve donne la moitié de ses stats à Xavier
    printf("\n Xavier et Steve se combine pour utilise Sacrifice Fraternel ! \n");
    xavier->jaugeactuelle = 0;
    steve->jaugeactuelle = 0;
    appeffetStat(xavier, 1, (steve->att)/2); // augmente l'attaque de xavier selon celle de steve
    appeffetStat(xavier, 2, (steve->def)/2); // augmente la défense de xavier selon celle de steve
    appeffetStat(xavier, 3, (steve->vitesse)/2); // augmente la vitesse de xavier selon celle de steve
    appeffetStat(xavier, 5, (steve->pvcourant)/2); // augmente les pvmax de xavier selon ceux de steve
    appeffetStat(steve, 1, -(steve->att)/2); // diminue l'attaque de steve de moitie
    appeffetStat(steve, 2, -(steve->def)/2);
    appeffetStat(steve, 3, -(steve->vitesse)/2);
    appeffetStat(steve, 5, -(steve->pvcourant)/2);
}

void retour_a_la_haine(Champ* gaby, Champ* clara, Equipe* adversaires){
    if(gaby==NULL||clara==NULL){
        printf("Erreur: pointeur nul.");
        exit(10002);
    }
    // Gaby et Clara suppriment un ennemi
    printf("\n Gaby et Clara se combine pour utilise Retour à la haine ! \n");
    gaby->jaugeactuelle = 0;
    clara->jaugeactuelle = 0;
    int choix=0;
    int verif;
    do{
        printf("Choisissez un ennemi à supprimer (1=%s, 2=%s, 3=%s) : \n", adversaires->membres[0].nom, adversaires->membres[1].nom, adversaires->membres[2].nom);
        verif=scanf("%d", &choix);
        if (choix<1 || choix>3) {
            printf("Index invalide\n");
        }
        vide_buffer();
    } while (choix<1 || choix>3 || verif!=1);
    adversaires->membres[choix].pvcourant = 0;
    adversaires->membres[choix].statut = 0;
    printf("\n Vous avez supprimé %s ! \n", adversaires->membres[choix].nom);
}