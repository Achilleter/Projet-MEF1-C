#include "principal.h"

void berserk(Champ* xavier, Equipe* allie){
    if(xavier==NULL||allie==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(1);
    }
    //technique comnbinee avec steve
    for(int i=0; i<3; i++){ // vérifie si la technique combinée est possible
        if(strcmp(allie->membres[i].tech.nom, "cadeau_empoisonne")==0){
            int choix=0;
            if(allie->boolia==0){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // Demande à l'utilisateur s'il veut utiliser la technique combinée
                    printf("Voulez vous utiliser la technique combinée avec %s (1:oui, 0:non)\n", allie->membres[i].nom);
                    int verif;
                    do{
                        verif=scanf("%d", &choix);
                        if (choix<0 || choix>1) {
                            printf("Index invalide\n");
                        }
                        vide_buffer();
                    }
                    while(choix<0 || choix>1 || verif!=1);
                }
            }
            else if(allie->boolia==1){// L'IA choisit toujours de combiner la technique
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // L'IA choisit de combiner la technique toujours
                    choix=1;
                    printf("L'IA a choisi de combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
            if (choix==1){
                sacrifice_fraternel(xavier, &allie->membres[i]);
                return;
            }
            else{
                printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
            }
        }
    }
    //technique de xavier
    // augmente l'attaque de 20 pendant 1 tour et ce soigne de 50, applique l'invincibilité pendant 1 tour puis s'immobilise pendant 1 tour
    if(xavier->tech.nbtactifs == 0){
        xavier->tech.nbtactifs = 2;
        xavier->jaugeactuelle =0;
        printf("Xavier utilise Berserk !\n");
        appeffetStat(xavier,1,20);//augmente l'attaque de 20
        appeffetStat(xavier,4,50);//Ce soigne de 50
        appeffetStatut(xavier,4,2);//applique invincibilité pendant 1 tour
    }
    else if(xavier->tech.nbtactifs != 0){// Diminution des tours de la technique si elle est déjà active
        xavier->tech.nbtactifs--;
        if(xavier->tech.nbtactifs == 0){
            printf("Xavier est fatigue il se stun et perd ses bonus !\n"); // à la fin de la technique, il perd ses bonus et se stun
            xavier->tech.nbtactifs = 0;
            appeffetStatut(xavier,2,2);//s'immobilise
            appeffetStat(xavier,1,-20);//diminue l'attaque de 20
        }   
    }
}

void flashbacks(Champ* nathalie, Champ* allie1, Champ* allie2){
    if(nathalie==NULL||allie1==NULL||allie2==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(10);
    }
    //soigne de 60 tous les alliés et leur enlève tous les effets statuts négatifs (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
    nathalie->jaugeactuelle = 0;
    printf("Nathalie utilise Flashbacks !\n");
    appeffetStat(allie1,4,60);//soigne de 6O tous les alliés
    appeffetStat(allie2,4,60);
    appeffetStat(nathalie,4,60);
    int booltemp=0;
    // enlève tous les effets statuts négatifs pour chaque allie (sauf les effets comme l'invincibilité, le renvoie de dégâts et la provocation)
    for(int i=0; i<allie1->nbeffets; i++){
        if(booltemp==1){// Verification si un effet a été supprimé alors decrementer le compteur
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
    if(zed==NULL||ennemi==NULL||allie==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(11);
    }
    //technique comnbinee avec annesophie
    int choix=0;
    int verif;
    for(int i=0; i<3; i++){ // vérifie si la technique combinée est possible
        if(strcmp(allie->membres[i].tech.nom, "scierculaire")==0){
            if(allie->boolia==0){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // Demande à l'utilisateur s'il veut utiliser la technique combinée
                    printf("Voulez vous utiliser la technique combinee avec %s (1:oui, 0:non)\n", allie->membres[i].nom);
                    do{
                        verif=scanf("%d", &choix);
                        if (choix<0 || choix>1) {
                            printf("Index invalide\n");
                        }
                        vide_buffer();
                    }
                    while(choix<0 || choix>1 || verif!=1);
                }
            }
            else if(allie->boolia==1){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // L'IA choisit toujours de combiner la technique
                    choix=1;
                    printf("L'IA a choisi de combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
            if (choix==1){
                extermination(&allie->membres[i], zed, ennemi);
                return;
            }
            else{
                printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
            }
        }
    }
    //technique de zed
    verif=0;
    choix=0;
    if(allie->boolia==0){// si le joueur joue alors on lui demande de choisir une cible
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
    }
    else if(allie->boolia==1){// Si l'IA joue alors elle choisit une cible au hasard
        choix=rand()%3+1;
        while(ennemi->membres[choix-1].statut==0){
            choix=rand()%3+1;
        }
        printf("L'IA a choisi de viser %s\n", ennemi->membres[choix-1].nom);
    }
    // applique l'effet bourreau sur un ennemi pendant 2 tours
    printf("Zed utilise marque du bourreau !\n");
    zed->jaugeactuelle = 0;
    ennemi->membres[choix-1].pvcourant -= ennemi->membres[choix-1].pvmax*0.1; // inflige 10% des pvmax en degats
    appeffetStatut(&ennemi->membres[choix-1],6,1);//applique l'effet bourreau pendant 1 tour
}

void muraille(Champ* smasheur){
    if(smasheur==NULL){
        printf("Erreur: pointeur nul.");
        exit(100);
    }
    //provoque les ennemis, augmente sa défense de 30 et renvoie les dégats pendant 1 tour
    if(smasheur->tech.nbtactifs == 0){
        smasheur->tech.nbtactifs = 2;
        printf("Smasheur utilise muraille!\n");
        smasheur->jaugeactuelle = 0;
        appeffetStatut(smasheur,5,2);//applique l'effet renvoie de dégâts pendant 1 tour
        appeffetStatut(smasheur,3,2);//applique l'effet provocation pendant 1 tour
        appeffetStat(smasheur,2,30);//augmente la défense de 30
    }
    else if(smasheur->tech.nbtactifs != 0){ // Diminution des tours de la technique si elle est déjà active
        smasheur->tech.nbtactifs--;
        if(smasheur->tech.nbtactifs == 0){
            printf("Smasheur est fatigue et perd ses bonus !\n");
            smasheur->tech.nbtactifs = 0;
            appeffetStat(smasheur,2,-30);
        }
    }
}

void cadeau_empoisonne(Champ* steve, Equipe* ennemi, Equipe* allie){
    if(steve==NULL||ennemi==NULL||allie==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(101);
    }
    //technique comnbinee avec xavier
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "berserk")==0){ // vérifie si la technique combinée est possible
            int choix=0;
            if(allie->boolia==0){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // Demande à l'utilisateur s'il veut utiliser la technique combinée
                    printf("Voulez vous utiliser la technique combinee avec %s (1:oui, 0:non)\n", allie->membres[i].nom);
                    int verif;
                    do{
                        verif=scanf("%d", &choix);
                        if (choix<0 || choix>1) {
                            printf("Index invalide\n");
                        }
                        vide_buffer();
                    }
                    while(choix<0 || choix>1 || verif!=1);
                }
            }
            else if(allie->boolia==1){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // L'IA choisit toujours de combiner la technique
                    choix=1;
                    printf("L'IA a choisi de combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
           if (choix==1){
                sacrifice_fraternel(&allie->membres[i], steve);
                return;
            }
            else{
                printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
            }
        }
    }
    //technique de steve
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
        printf("Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[alea].nom);
        printf("Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[alea2].nom);
    }
    else if(ennemi->nbchampvivant==2){// Si il n'y a que 2 ennemis vivants, on applique l'effet poison sur les deux
        for(int i=0; i<3; i++){
            if(ennemi->membres[i].statut==1){
                appeffetStatut(&ennemi->membres[i],1,2);//applique l'effet poison pendant 2 tours
                printf("Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[i].nom);
            }
        }
    }
    else {
        for(int i=0; i<3; i++){ // Si il n'y a qu'un ennemi vivant
            if(ennemi->membres[i].statut==1){
                appeffetStatut(&ennemi->membres[i],1,2);// applique l'effet poison pendant 2 tours
                printf("Steve utilise Cadeau empoisonne sur %s ! \n",ennemi->membres[i].nom);
            }
        }
    }
}

void fossoyeur_des_mondes(Champ* booga){
    if(booga==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(110);
    }
    // augmente l'attaque de 5 a l'infini, la défense de 10 et se soigne de 25 PV à chaque tour pendant 2 tours
    appeffetStat(booga, 4, 10); // Se soigne de 20 PV à chaque tour
    if(booga->tech.nbtactifs == 0){
        booga->tech.nbtactifs = 3; // Applique l'effet pendant 2 tours
        printf("Booga utilise Fossoyeur des Mondes !\n");
        booga->jaugeactuelle = 0;
        appeffetStat(booga, 1, 5); // Augmente l'attaque de 5
        appeffetStat(booga, 2, 10); // Augmente la défense de 10
    }
    else if(booga->tech.nbtactifs == 1){
        appeffetStat(booga, 2, -10); // Diminue la défense de 10
        printf("\nBooga redevient comme avant et perd ses bonus !\n");
    }
    booga->tech.nbtactifs--;
}

void cryogenese(Champ* sandrine, Equipe* ennemi){
    if(sandrine==NULL||ennemi==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(111);
    }
    // inflige 30 de dégats à tous les ennemis et stun pendant 1 tour
    printf("Sandrine utilise Exploglace !\n");
        sandrine->jaugeactuelle = 0;
        for(int i=0; i<3; i++){
            if(ennemi->membres[i].statut==1){
                ennemi->membres[i].pvcourant -= 30;
                appeffetStatut(&ennemi->membres[i], 2, 1) ;//applique l'effet stun pendant 1 tour
            }
        }
}

void scierculaire(Champ* annesophie, Equipe* ennemi, Equipe* allie){
    if(annesophie==NULL||ennemi==NULL||allie==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(1000);
    }
    //technique comnbinee avec zed
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "bourreau")==0){ // vérifie si la technique combinée est possible
            int choix=0;
            if(allie->boolia==0){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // Demande à l'utilisateur s'il veut utiliser la technique combinée
                    printf("\nVoulez vous utiliser la technique combinée avec %s (1:oui, 0:non)\n", allie->membres[i].nom);
                    int verif;
                    do{
                        verif=scanf("%d", &choix);
                        if (choix<0 || choix>1) {
                            printf("Index invalide\n");
                        }
                        vide_buffer();
                    }
                    while(choix<0 || choix>1 || verif!=1);
                }
            }
            else if(allie->boolia==1){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // L'IA choisit toujours de combiner la technique
                    choix=1;
                    printf("L'IA a choisi de combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
            if (choix==1){
                extermination(annesophie, &allie->membres[i], ennemi);
                return;
            }
            else{
                printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
            }
        }
    }
    //technique de annesophie
    //inflige 50 dégats à tous les ennemis et applique l'effet poison pendant 1 tour
    printf("Annesophie utilise Scierculaire !\n");
    annesophie->jaugeactuelle = 0;
    for(int i=0; i<3; i++){
        if(ennemi->membres[i].statut==1){
            ennemi->membres[i].pvcourant -= 50;
            appeffetStatut(&ennemi->membres[i],1,1); 
        }
    }
}

void cicatrices_eternels(Champ* gaby, Equipe* ennemi, Equipe* allie){
    if(gaby==NULL||ennemi==NULL||allie==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(1001);
    }
    //technique comnbinee avec clara
    for(int i=0; i<3; i++){
        if(strcmp(allie->membres[i].tech.nom, "reinitialisation")==0){ // vérifie si la technique combinée est possible
            int choix=0;
            if(allie->boolia==0){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // Demande à l'utilisateur s'il veut utiliser la technique combinée
                    printf("Voulez vous utiliser la technique combinee avec %s (1:oui, 0:non)\n", allie->membres[i].nom);
                    int verif;
                    do{
                        verif=scanf("%d", &choix);
                        if (choix<0 || choix>1) {
                            printf("Index invalide\n");
                        }
                        vide_buffer();
                    }
                    while(choix<0 || choix>1 || verif!=1);
                }
            }
            else if(allie->boolia==1){
                if(allie->membres[i].jaugeactuelle==allie->membres[i].jaugemax && allie->membres[i].statut==1){
                    // L'IA choisit de combiner la technique toujours
                    choix=1;
                    printf("L'IA a choisi de combiner la technique avec %s\n", allie->membres[i].nom);
                }
            }
            if (choix==1){
                retour_a_la_haine(gaby, &allie->membres[i], ennemi, allie);
                return;
            }
            else{
                printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allie->membres[i].nom);
            }
        }
    }
    //technique de gaby
    // inflige 125 de dégats à tous les ennemis
    printf("Gaby utilise Cicatrices Eternels !\n");
    gaby->jaugeactuelle = 0;
    for(int i=0; i<3; i++){
        if(ennemi->membres[i].statut==1){
            ennemi->membres[i].pvcourant -= 100;
        }
    }
}

void reinitialisation(Champ* clara, Champ* allie1, Champ* allie2, Equipe* allies, Equipe* ennemi){
    if(clara==NULL||allie1==NULL||allie2==NULL||ennemi==NULL||allies==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(1010);
    }
    //technique comnbinee avec gaby
    int choix=0;
    int verif;
    for(int i=0; i<3; i++){
        if(strcmp(allies->membres[i].tech.nom, "cicatrices_eternels")==0){ // vérifie si la technique combinée est possible
            int choix=0;
            if(allies->boolia==0){
                if(allies->membres[i].jaugeactuelle==allies->membres[i].jaugemax && allie1->statut==1){
                    // Demande à l'utilisateur s'il veut utiliser la technique combinée
                    printf("Voulez vous utiliser la technique combinee avec %s (1:oui, 0:non)\n", allies->membres[i].nom);
                    int verif;
                    do{
                        verif=scanf("%d", &choix);
                        if (choix<0 || choix>1) {
                            printf("Index invalide\n");
                        }
                        vide_buffer();
                    }
                    while(choix<0 || choix>1 || verif!=1);
                }
            }
            else if(allies->boolia==1){
                if(allies->membres[i].jaugeactuelle==allies->membres[i].jaugemax && allie1->statut==1){
                    // L'IA choisit de combiner la technique toujours
                    choix=1;
                    printf("L'IA a choisi de combiner la technique avec %s\n", allies->membres[i].nom);
                }
            }
            if (choix==1){
                retour_a_la_haine(&allies->membres[i], clara, ennemi, allies);
                return;
            }
            else{
                printf("Vous avez choisi de ne pas combiner la technique avec %s\n", allies->membres[i].nom);
            }
        }
    }
    //technique de clara
    // Ressucite un allié avec la moitié de ses points de vies
    verif=0;
    if (allie1->statut==1 && allie2->statut==1) { // Si les deux alliés sont vivants
        printf("Aucun de vos alliés n'est mort !\n");
        return;
    }
    else if (allie1->statut==0 && allie2->statut==0) { // Si les deux alliés sont morts
        choix=0;
        printf("Choississez un allie à ressusciter (1=%s, 2=%s) :\n", allie1->nom, allie2->nom);
        do {
            verif=scanf("%d", &choix);
            if (choix<1 || choix>2) {
                printf("Index invalide\n");
            }
            vide_buffer();
        }while (choix<1 || choix>2 || verif!=1);
        printf("Clara utilise Reinitialisation !\n");
        clara->jaugeactuelle = 0;
        // ressuscite l'allié choisi
        if (choix==1) {
            printf("Vous ressuscitez %s !\n", allie1->nom);
            allie1->pvcourant = allie1->pvmax / 2;
            allie1->statut = 1;
        }
        else {
            printf("Vous ressuscitez %s !\n", allie2->nom);
            allie2->pvcourant = allie2->pvmax / 2;
            allie2->statut = 1;
        }
        allies->nbchampvivant++;
    }
    else { // Si un seul allié est mort
        printf("Clara utilise Reinitialisation !\n");
        clara->jaugeactuelle = 0;
        if (allie1->statut==0) {
            printf("Vous ressuscitez %s !\n", allie1->nom);
            allie1->pvcourant = allie1->pvmax / 2;
            allie1->statut = 1;
        }
        else if (allie2->statut==0) {
            printf("Vous ressuscitez %s !\n", allie2->nom);
            allie2->pvcourant = allie2->pvmax / 2;
            allie2->statut = 1;
        }
        allies->nbchampvivant++;
    }
}

void extermination(Champ* annesophie, Champ* zed, Equipe* adversaires){
    if(annesophie==NULL||zed==NULL||adversaires==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(10000);
    }
    // Les personnages combinent leurs techniques pour infliger 60 de dégats à tous les ennemis et applique l'effet bourreau pendant 1 tour
    printf("Annesophie et zed se combinent pour utiliser extermination !\n");
    annesophie->jaugeactuelle = 0;
    zed->jaugeactuelle = 0;
    for(int i=0; i<3; i++){
        if(adversaires->membres[i].statut==1){
            adversaires->membres[i].pvcourant -= 60;
            appeffetStatut(&adversaires->membres[i],6,1); //applique l'effet bourreau à tous les ennemis pendant 1 tour
        }
    }
}

void sacrifice_fraternel(Champ* xavier, Champ* steve){
    if(xavier==NULL||steve==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(10001);
    }
    // Steve donne la moitié de ses stats à Xavier
    printf("Xavier et Steve se combinent pour utiliser Sacrifice Fraternel !\n");
    xavier->jaugeactuelle = 0;
    steve->jaugeactuelle = 0;
    appeffetStat(xavier, 1, (steve->att)/2); // augmente l'attaque de xavier selon celle de steve...
    appeffetStat(xavier, 2, (steve->def)/2);
    appeffetStat(xavier, 5, (steve->pvcourant)/2);
    appeffetStat(steve, 1, -(steve->att)/2); // diminue l'attaque de steve de moitie...
    appeffetStat(steve, 2, -(steve->def)/2);
    appeffetStat(steve, 5, -(steve->pvcourant)/2);
}

void retour_a_la_haine(Champ* gaby, Champ* clara, Equipe* adversaires, Equipe* allie){
    if(gaby==NULL||clara==NULL||adversaires==NULL||allie==NULL){ //verification des pointeurs
        printf("Erreur: pointeur nul.");
        exit(10002);
    }
    // Gaby et Clara suppriment un ennemi
    printf("Gaby attire Clara dans les tenebres pour l'aider à supprimer un ennemi!\n");
    gaby->jaugeactuelle = 0;
    clara->jaugeactuelle = 0;
    int choix=0;
    int verif;
    if(allie->boolia==0){// si le joueur joue alors on lui demande de choisir une cible
        do{
            printf("Choisissez un ennemi à supprimer (1=%s, 2=%s, 3=%s) :\n", adversaires->membres[0].nom, adversaires->membres[1].nom, adversaires->membres[2].nom);
            verif=scanf("%d", &choix);
            if (choix<1 || choix>3) {
                printf("Index invalide\n");
            }
            vide_buffer();
        } while (choix<1 || choix>3 || verif!=1);
    }
    else if(allie->boolia==1){// Si l'IA joue alors elle choisit une cible au hasard
        choix=rand()%3+1;
    }
    adversaires->membres[choix-1].pvcourant = 0;
    printf("Gaby et Clara ont supprimes %s !\n", adversaires->membres[choix].nom);
}