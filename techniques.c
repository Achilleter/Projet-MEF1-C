#include "principal.h"

void berserk(Champ* xavier, Equipe* allie){
    if(xavier==NULL){
        printf("Erreur: pointeur nul.");
        exit(1);
    }
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "cadeau_empoisonne")==0){
            if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax){
                printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)", allie->membres[i].nom);
                int verif;
                int choix=0;
                do{
                    verif=scanf("%d", &choix);
                    if (choix<0 || choix>1) {
                        printf("Index invalide\n");
                    }
                    vide_buffer();
                }
                while(choix<0 || choix>1 || verif!=1);
                if (choix==1){
                    sacrifice_fraternel(xavier, &allie->membres[i]);
                    return;
                }
                else{
                    printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
        }
    }
    // augmente l'attaque de 20 et la défense de 10, applique l'invincibilité pendant 1 tour puis s'immobilise pendant 1 tour
    if(xavier->tech.nbtactifs == 0){
        xavier->tech.nbtactifs = 2;
        xavier->jaugeactuelle =0;
        printf("Xavier utilise Berserk !\n");
        appeffetStat(xavier,1,20);//augmente l'attaque de 20
        appeffetStat(xavier,2,10);//augmente la defense de 10
        appeffetStatut(xavier,4,2);//applique invincibilité pendant 1 tour
    }
    else if(xavier->tech.nbtactifs != 0){
        xavier->tech.nbtactifs--;
        if(xavier->tech.nbtactifs == 0){
            printf("Xavier est fatigué il s'immobilise !\n");
            xavier->tech.nbtactifs = 0;
            appeffetStatut(xavier,2,2);//s'immobilise
            appeffetStat(xavier,1,-20);//diminue l'attaque de 20
            appeffetStat(xavier,2,-10);//diminue la defense de 10
        }   
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
    int booltemp=0;
    // enlève tous les effets statuts négatifs pour chaque allie (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
    for(int i=0; i<allie1->nbeffets; i++){
        if(booltemp==1){
            i--;
        }
        booltemp=0;
        if(allie1->effets[i].effet_statut != 5 && allie1->effets[i].effet_statut != 4 && allie1->effets[i].effet_statut != 3){
            suppressionEffetStatut(allie1, i);
            booltemp=1;
        }
    }
    booltemp=0;
    for(int i=0; i<allie2->nbeffets; i++){
        if(booltemp==1){
            i--;
        }
        booltemp=0;
        if(allie2->effets[i].effet_statut != 5 && allie2->effets[i].effet_statut != 4 && allie2->effets[i].effet_statut != 3){
            suppressionEffetStatut(allie2, i);
            booltemp=1;
        }
    }
    booltemp=0;
    for(int i=0; i<nathalie->nbeffets; i++){
        if(booltemp==1){
            i--;
        }
        booltemp=0;
        if(nathalie->effets[i].effet_statut != 5 && nathalie->effets[i].effet_statut != 4 && nathalie->effets[i].effet_statut != 3){
            suppressionEffetStatut(nathalie, i);
            booltemp=1;
        }
    }
}

 void bourreau(Champ* zed, Equipe* ennemi, Equipe* allie){
    if(zed==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(11);
    }
    int choix=0;
    int verif;
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "scierculaire")==0){
            if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax){
                printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)", allie->membres[i].nom);
                do{
                    verif=scanf("%d", &choix);
                    if (choix<0 || choix>1) {
                        printf("Index invalide\n");
                    }
                    vide_buffer();
                }
                while(choix<0 || choix>1 || verif!=1);
                if (choix==1){
                    extermination(zed, &allie->membres[i], ennemi);
                    return;
                }
                else{
                    printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
        }
    }
    verif=0;
    choix=0;
    do{
    printf("Choisissez un ennemi à viser (1=%s, 2=%s, 3=%s) : \n", ennemi->membres[0].nom, ennemi->membres[1].nom, ennemi->membres[2].nom);
        verif=scanf("%d", &choix);
        if (choix<1 || choix>3) {
            printf("Index invalide\n");
        }
        if(ennemi->membres[choix-1].statut==0){ // Si la cible est KO, on redemande une cible
            printf("Cible KO. Veuillez en chosir une nouvelle\n");
            choix=0;
        }
        vide_buffer();
    } while (choix<1 || choix>3 || verif!=1);
    // applique l'effet bourreau sur un ennemi pendant 2 tours
    printf("\n Zed utilise marque du bourreau ! \n");
    zed->jaugeactuelle = 0;
    ennemi->membres[choix-1].pvcourant -= ennemi->membres[choix-1].pvmax*0.1;
    appeffetStatut(&ennemi->membres[choix-1],6,2);//applique l'effet bourreau pendant 2 tours
}

void muraille(Champ* smasheur){
    if(smasheur==NULL){
        printf("Erreur: pointeur nul.");
        exit(100);
    }
    //provoque les ennemis, augmente sa défense de 20 et renvoie les dégats pendant 1 tour
    if(smasheur->tech.nbtactifs == 0){
        smasheur->tech.nbtactifs = 2;
        printf("\n Smasheur utilise muraille! \n");
        smasheur->jaugeactuelle = 0;
        appeffetStatut(smasheur,5,2);//applique l'effet renvoie de dégâts pendant 1 tour
        appeffetStatut(smasheur,3,2);//applique l'effet provocation pendant 1 tour
        appeffetStat(smasheur,3,20);//augmente la défense de 20
    }
    else if(smasheur->tech.nbtactifs != 0){
        printf("def reduite !\n");
        appeffetStat(smasheur,3,-20);//diminue la défense de 20
    }
    smasheur->tech.nbtactifs--;
}

void cadeau_empoisonne(Champ* steve, Equipe* ennemi, Equipe* allie){
    if(steve==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(101);
    }
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "berserk")==0){
            if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax){
                printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)", allie->membres[i].nom);
                int choix=0;
                int verif;
                do{
                    verif=scanf("%d", &choix);
                    if (choix<0 || choix>1) {
                        printf("Index invalide\n");
                    }
                    vide_buffer();
                }
                while(choix<0 || choix>1 || verif!=1);
                if (choix==1){
                    sacrifice_fraternel(steve, &allie->membres[i]);
                    return;
                }
                else{
                    printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
        }
    }
    steve->jaugeactuelle = 0;
    // applique l'effet poison sur 2 ennemi au hasard
    if(ennemi->nbchampvivant==3){
        int alea=rand()%3;
        int alea2=rand()%3;
        while(alea==alea2){
            alea2=rand()%3;
        }
        appeffetStatut(&ennemi->membres[alea],1,2);//applique l'effet poison pendant 2 tours
        appeffetStatut(&ennemi->membres[alea2],1,2);//applique l'effet poison pendant 2 tours
        appeffetStat(&ennemi->membres[alea], 3, -2); // diminue la vitesse de 2
        appeffetStat(&ennemi->membres[alea2], 3, -2); // diminue la vitesse de 2
        printf("\n Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[alea].nom);
        printf("\n Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[alea2].nom);
    }
    else if(ennemi->nbchampvivant==2){
        for(int i=0; i<3; i++){
            if(ennemi->membres[i].statut==1){
                appeffetStatut(&ennemi->membres[i],1,2);//applique l'effet poison pendant 2 tours
                appeffetStat(&ennemi->membres[i], 3, -2); // diminue la vitesse de 2
                printf("\n Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[i].nom);
            }
        }
    }
    else {
        for(int i=0; i<3; i++){
            if(ennemi->membres[i].statut==1){
                appeffetStatut(&ennemi->membres[i],1,2);// applique l'effet poison pendant 2 tours
                appeffetStat(&ennemi->membres[i], 3, -50); // diminue la vitesse de 50
                printf("\n Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[i].nom);
            }
        }
    }
}

void fossoyeur_des_mondes(Champ* booga){
    if(booga==NULL){
        printf("Erreur: pointeur nul.");
        exit(110);
    }
    appeffetStat(booga, 4, 25); // Se soigne de 25 PV à chaque tour
    if(booga->tech.nbtactifs == 0){
        booga->tech.nbtactifs = 4; // Applique l'effet pendant 4 tours
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
    booga->tech.nbtactifs--;
}

void cryogenese(Champ* sandrine, Equipe* ennemi){
    if(sandrine==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(111);
    }
    // inflige 30 de dégats à tous les ennemis et diminue les stuns pendant 1 tour
    printf("\n Sandrine utilise Exploglace ! \n");
        sandrine->jaugeactuelle = 0;
        for(int i=0; i<3; i++){
            if(ennemi->membres[i].statut==1){
                ennemi->membres[i].pvcourant -= 30;
                appeffetStatut(&ennemi->membres[i], 2, 1) ;//applique l'effet stun pendant 1 tour
            }
        }
}

void scierculaire(Champ* annesophie, Equipe* ennemi, Equipe* allie){
    if(annesophie==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(1000);
    }
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "bourreau")==0){
            if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax){
                printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)", allie->membres[i].nom);
                int choix=0;
                int verif;
                do{
                    verif=scanf("%d", &choix);
                    if (choix<0 || choix>1) {
                        printf("Index invalide\n");
                    }
                    vide_buffer();
                }
                while(choix<0 || choix>1 || verif!=1);
                if (choix==1){
                    extermination(annesophie, &allie->membres[i], ennemi);
                    return;
                }
                else{
                    printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
        }
    }
    //inflige 50 dégats à tous les ennemis et applique l'effet poison pendant 2 tours
    printf("\n Annesophie utilise Scierculaire ! \n");
    annesophie->jaugeactuelle = 0;
    for(int i=0; i<3; i++){
        if(ennemi->membres[i].statut==1){
            ennemi->membres[i].pvcourant -= 50;
            appeffetStatut(&ennemi->membres[i],1,2); 
        }
    }
}

void cicatrices_eternels(Champ* gaby, Equipe* ennemi, Equipe* allie){
    if(gaby==NULL||ennemi==NULL){
        printf("Erreur: pointeur nul.");
        exit(1001);
    }
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "reinitialisation")==0){
            if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax){
                printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)", allie->membres[i].nom);
                int choix=0;
                int verif;
                do{
                    verif=scanf("%d", &choix);
                    if (choix<0 || choix>1) {
                        printf("Index invalide\n");
                    }
                    vide_buffer(); 
                }
                while(choix<0 || choix>1 || verif!=1);
                if (choix==1){
                    retour_a_la_haine(gaby, &allie->membres[i], ennemi);
                    return;
                }
                else{
                    printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
        }
    }
    // inflige 100 de dégats à tous les ennemis
    printf("\n Gaby utilise Cicatrices Eternels ! \n");
    gaby->jaugeactuelle = 0;
    for(int i=0; i<3; i++){
        if(ennemi->membres[i].statut==1){
            ennemi->membres[i].pvcourant -= 100;
        }
    }
}

void reinitialisation(Champ* clara, Champ* allie1, Champ* allie2, Equipe* allies, Equipe* ennemi){
    if(clara==NULL||allie1==NULL||allie2==NULL){
        printf("Erreur: pointeur nul.");
        exit(1010);
    }
    int choix=0;
    int verif;
    for(int i=0; i<3; i++){
        if(strcmp(allies->membres[i].tech.nom, "cicatrices_eternels")==0){
            if(allies->membres[i].jaugeactuelle==allies->membres[i].jaugemax){
                printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)", allies->membres[i].nom);
                do{
                    verif=scanf("%d", &choix);
                    if (choix<0 || choix>1) {
                        printf("Index invalide\n");
                    }
                    vide_buffer();
                }
                while(choix<0 || choix>1 || verif!=1);
                if (choix==1){
                        retour_a_la_haine(clara, &allies->membres[i], ennemi);
                    return;
                }
                else{
                    printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allies->membres[i].nom);
                }
            }
        }
    }
    // Ressucite un allié avec la moitié de ses points de vies
    verif=0;
    if (allie1->statut==1 && allie2->statut==1) {
        printf("\n Aucun de vos alliés n'est mort ! \n");
        return;
    }
    else if (allie1->statut==0 && allie2->statut==0) {
        choix=0;
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
        allies->nbchampvivant++;
    }
    else {
        printf("\n Clara utilise Réinitialisation ! \n");
        clara->jaugeactuelle = 0;
        if (allie1->statut==0) {
            printf("\n Vous ressuscitez %s ! \n", allie1->nom);
            allie1->pvcourant = allie1->pvmax / 2;
            allie1->statut = 1;
        }
        else if (allie2->statut==0) {
            printf("\n Vous ressuscitez %s ! \n", allie2->nom);
            allie2->pvcourant = allie2->pvmax / 2;
            allie2->statut = 1;
        }
        allies->nbchampvivant++;
    }
}

void extermination(Champ* annesophie, Champ* zed, Equipe* adversaires){
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
