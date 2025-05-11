#include "principal.h"

float attaque(Champ *champatt, Champ *champdef){
    if(champatt == NULL || champdef == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    float degats = champatt->att * (100/(100+champdef->def)); // calcul des dégats
    for(int i=0; i<10; i++){
        if (degats < 0) {
            degats = 0;
        }
        if (champdef->effets[i].effet_statut == 5) { // renvoie de dégats
            printf("%s renvoi les degats de %s\n",champdef->nom, champatt->nom);
            champatt->pvcourant -= degats / 4;
            if (champatt->pvcourant < 0) {
                champatt->pvcourant = 0;
            }
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
    //verification des pointeurs
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    float pvtemp=champ->pvcourant;
    if (champ->nbeffets == 0) {
        return;
    }
    else if (champ->nbeffets > 0) {
        for (int i = 0; i < champ->nbeffets; i++) {
            if (champ->effets[i].effet_statut == 1 && champ->effets[i].duree>0) { // application poison
                champ->pvcourant -= champ->pvmax * 0.05;
                printf("%s subit des degats de poison !\n", champ->nom);
            }
            else if (champ->effets[i].effet_statut == 6 && champ->effets[i].duree>0) { // application bourreau
                if(champ->pvcourant <= champ->pvmax * 0.25) {
                    champ->pvcourant = 0;
                    printf("%s a ete execute par bourreau !\n", champ->nom);
                }
            }
            else if(champ->effets[i].effet_statut == 4 && champ->effets[i].duree>0) { // application invincibilité
                champ->pvcourant = pvtemp;
            }
        }
    }
}

void appeffetStatut(Champ *champ, EffetStatut effetstatut, int duree) {
    // Verification des pointeurs
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    int bool=0;
    for (int i=0; i<champ->nbeffets; i++){ // si champ déjà touché rallongement de l'effet
        if(champ->effets[i].effet_statut==effetstatut){
            champ->effets[i].duree=duree;
            bool=1;
        }
    }
    if(bool==0){ // sinon ajout de l'effet
        champ->nbeffets++;
        champ->effets[champ->nbeffets-1].effet_statut= effetstatut;
        champ->effets[champ->nbeffets-1].duree= duree;
    }
}

void appeffetStat(Champ *champ, EffetStat effetstat, float valeur) {
    // Verification des pointeurs
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    switch (effetstat){
            case 1:// change attaque
                champ->att += valeur;
                break;
            case 2: // change défense
                champ->def += valeur;
                break;
            case 3: // change vitesse
                champ->vitesse += valeur;
                break;
            case 4: // soin
                if(champ->statut==1){
                    champ->pvcourant += valeur;
                    if (champ->pvcourant > champ->pvmax) {
                        champ->pvcourant = champ->pvmax;
                    }
                }
                break;
            case 5: // changement pvmax
                champ->pvmax+=valeur;
                champ->pvcourant+=valeur;
                break;
        }
}

void suppressionEffetStatut(Champ *champ, int numeffet) {
    // Verification des pointeurs
    if(champ == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
   if (numeffet != champ->nbeffets - 1) {
        champ->effets[numeffet] = champ->effets[champ->nbeffets - 1];
    }
    champ->effets[champ->nbeffets - 1].effet_statut = 0;
    champ->effets[champ->nbeffets - 1].duree = 0;
    champ->nbeffets--;
}

void triParVit(Equipe* e1, Equipe* e2, Champ* tab[6]) {
    if(e1 == NULL || e2 == NULL){       // Vérification des pointeurs e1 et e2
        printf("Erreur : pointeur nul");
        exit(1);
    }
    for (int i=0; i<3; i++) {          // Regroupement des 2 équipes dans un seul tableau
        tab[i]=&e1->membres[i];
        tab[i+3]=&e2->membres[i];
    }
    for (int i=0; i<5; i++) {          // Tri à bulle
        for (int j=i+1; j<6; j++) {
            if (tab[i]->vitesse < tab[j]->vitesse) {
                Champ* temp=tab[i];
                tab[i]=tab[j];
                tab[j]=temp;
            }
        }
    }
}


int memeEquipe(Champ* champ, Equipe* e1) {
    if(champ == NULL || e1 == NULL) {    // Vérification des pointeurs champ et e1
        printf("Erreur : pointeur nul");
        exit(1);
    }
    for (int i=0; i<3; i++) {            // Boucle qui detérmine si le champion appartient à l'équipe 
        if (champ==&e1->membres[i]) {
            return 1;                    // Retourne 1 si le champion est dans la même équipe, 0 sinon
        }
    }
    return 0;
}

Champ* choixCible(Champ* attaquant, Equipe* e1, Equipe* e2) {
    if(attaquant == NULL || e1 == NULL || e2 == NULL){    // Vérification des pointeurs attaquant, e1 et e2
        printf("Erreur : pointeur nul");
        exit(1);
    }
    int index=3; // Met l'index initial à 3 (en dehors du tableau)
    int verif;
    for(int j=0; j<3; j++){ // Si un ennemi provocateur est présent, il est la cible par défaut
        for(int k=0; k<e2->membres[j].nbeffets; k++){
            if(e2->membres[j].effets[k].effet_statut==3){
                if(e2->membres[j].effets[k].duree>0){  
                    printf("%s est provoque par %s !\n",attaquant->nom, e2->membres[j].nom);
                    printf("Appuyez sur entree pour continuer...\n");
                    getchar();
                    return &e2->membres[j];
                }
            }
        }
    }
    do{
        do{ // Demande à l'utilisateur de choisir une cible
            printf("Choisissez votre cible (1,2 ou 3):\n");
            verif=scanf("%d",&index);
            if(index<1 || index>3){
                printf("Index invalide\n");
            }
            vide_buffer();
        } while (index<1 || index>3 || verif!=1);
        if(e2->membres[index-1].pvcourant<=0){ // Si la cible est KO, on redemande une cible
            printf("Cible KO. Veuillez en chosir une nouvelle\n");
            index=4;
        }
    } while (index==4);
    return &e2->membres[index-1];
}

void tour (Equipe* e1, Equipe* e2){ // fonction représentant un tour.
    if(e1 == NULL || e2 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    Champ *tab[6];
    int verif;
    triParVit(e1,e2,tab); // Appel de la fonction de tri par vitesse pour définir un ordre de passage.
    for (int i=0;i<6;i++){ // Parcourt du tableau pour faire jouer les 6 champions. 
        int verifstun=0; // Vérifie si le champion est stun.
        for(int j=0; j<10; j++){ 
            if(tab[i]->effets[j].effet_statut==2){
                verifstun=1;
            }
        }
        if (tab[i]->pvcourant<=0){ // Vérifie si le champion est mort.
            printf("%s est KO, il ne peut pas attaquer\n",tab[i]->nom);
        }
        else { 
            affichageCombat(e1,e2, tab[i]);
            Equipe *joueur;
            Equipe *adversaire;
            Champ *cible;
            float pvtemp=0; // Mise en place de statistiques temporaires dans le cadre d'un stun.
            int joueurinvincibletemp=0;
            int equipetemp=0;
            for(int j=0; j<3; j++){
                for(int k=0; k<e1->membres[j].nbeffets; k++){
                    if (e1->membres[j].effets[k].effet_statut==4){
                        pvtemp=e1->membres[j].pvcourant;
                        joueurinvincibletemp=j;
                        equipetemp=1;
                    }
                }
                for(int k=0; k<e2->membres[j].nbeffets; k++){
                    if (e2->membres[j].effets[k].effet_statut==4){
                        pvtemp=e2->membres[j].pvcourant;
                        joueurinvincibletemp=j;
                        equipetemp=2;
                    }
                }
            }
            if(verifstun==1){
                printf("%s est stun !\n", tab[i]->nom);
            }   
            else {
                if(memeEquipe(tab[i],e1)==0){ //Vérifie l'équipe du champion actuel.
                    joueur=e2;
                    adversaire=e1;
                } 
                else {
                    joueur=e1;
                    adversaire=e2;
                }
                if (tab[i]->jaugeactuelle==tab[i]->jaugemax){ //Vérifie si la jauge est à son maximum.
                    int choix;
                    printf("Jauge pleine! Voulez-vous utiliser une technique speciale? \n1:oui \n0:non \n");
                    printf("Description de la technique speciale: \n"); //Affiche la description des techniques spéciales en comprant le nom de la technique du champion actuelle aux noms des techniques préalablement définis.
                    if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                        printf("Berserk : Insere une cle piratee en lui : devient immunise a toutes les attaques pendant 1 tour et attaque+30 pendant 1 tour, puis s'immobilise le prochain tour\n");
                    } 
                    else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                        printf("Flashbacks : Repare ses coequipiers : PVcourants+=60 pour toute la team et purge ses allies de tous les effets negatifs\n");
                    }
                    else if (strcmp(tab[i]->tech.nom, "bourreau")==0){
                        printf("Bourreau : Place un traceur sur un ennemi : si ce dernier possede 25 pourcent ou moins de ses pvmax, il est execute sans pitie et pvcourant-(pvmax/10)\n");
                    } 
                    else if (strcmp(tab[i]->tech.nom, "muraille")==0){
                        printf("Muraille : Se place devant son equipe et provoque l'equipe adverse : applique provocation et renvoi de degats sur lui même et defense+30\n");
                    } 
                    else if (strcmp(tab[i]->tech.nom, "cadeau_empoisonne")==0){
                        printf("Cadeau empoisonne : Il court circuite ses ennemis : applique poison a 2 ennemis aleatoires et vitesse-2\n");
                    }
                    else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0){
                        printf("Fossoyeur des mondes : Une anomalie dans le systeme provoque un desequilibre chez Booga : pv+30 et defense+30 pendant 2 tours +10attaque\n");
                    }
                    else if (strcmp(tab[i]->tech.nom, "cryogenese")==0){
                        printf("Cryogenese : Sa glaciere integree explose et gel les adversaires : Inflige 30 degats a tous les ennemis et les stuns pendant 1 tour\n");
                    }
                    else if (strcmp(tab[i]->tech.nom, "scierculaire")==0){
                        printf("Scierculaire : Tourne sur elle même et tire sur tous ce qu'elle voit : Inflige 50 degats a tous les adversaires et leur applique poison\n");
                    }
                    else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                        printf("Cicatrices eternels : Relache toute sa timidite et laisse ses demons prendre le controle : Inflige 100 degats a tous les ennemis\n");
                    }
                    else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0){
                        printf("Reinitialisation : Reinitialise les donnes d'un allie : Ramene un allie a la vie\n");
                    }
                    do{ // Demande au joueur s'il souhaite utiliser sa technique spéciale
                        verif=scanf("%d", &choix);
                        if(choix>1 || choix<0){
                            printf("Index invalide");
                        }
                        vide_buffer();
                    } 
                    while(choix>1 || choix<0 || verif!=1); 
                    if (choix==1){
                        // Vérfication de la technique en comparant le noms des techniques au nom de la technique du personnage situé dans tab[i].
                        if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                            berserk(tab[i], joueur);
                        }
                        else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                            if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                                flashbacks(tab[i], &joueur->membres[1], &joueur->membres[2]);
                            }
                            else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) {
                                flashbacks(tab[i], &joueur->membres[0], &joueur->membres[2]);
                            }
                            else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) { 
                                flashbacks(tab[i], &joueur->membres[0], &joueur->membres[1]);
                            }
                        }
                        else if (strcmp(tab[i]->tech.nom, "bourreau")==0) {
                            bourreau(tab[i], adversaire, joueur);
                        }
                        else if (strcmp(tab[i]->tech.nom, "muraille")==0) {
                            muraille(tab[i]);
                        }
                        else if (strcmp(tab[i]->tech.nom, "cadeau_empoisonne")==0) {
                            cadeau_empoisonne(tab[i], adversaire, joueur);
                        }
                        else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0) {
                            fossoyeur_des_mondes(tab[i]);
                        }
                        else if (strcmp(tab[i]->tech.nom, "cryogenese")==0) { 
                            cryogenese(tab[i], adversaire);
                        }
                        else if (strcmp(tab[i]->tech.nom, "scierculaire")==0) {
                            scierculaire(tab[i], adversaire, joueur);
                        }
                        else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                            cicatrices_eternels(tab[i], adversaire, joueur);
                        }
                        else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0) {
                            if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                                reinitialisation(tab[i], &joueur->membres[1], &joueur->membres[2], joueur, adversaire);
                            }
                            else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) { 
                                reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[2], joueur, adversaire);
                            }
                            else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) {
                                reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[1], joueur, adversaire);
                            }
                        }
                    }
                    else {
                        cible=choixCible(tab[i], joueur, adversaire); //Appel de la fonction choixCible pour assurer la validité de la cible choisie.
                        printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                        attaque(tab[i], cible);
                    }
                }
                else {
                cible=choixCible(tab[i], joueur, adversaire);
                printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                attaque(tab[i],cible);
                }
            }
            if (tab[i]->tech.nbtactifs != 0) {
                // vérfication de la technique avec le nom de la technique du champion.
                if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                    berserk(tab[i], joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                    if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                        flashbacks(tab[i], &joueur->membres[1], &joueur->membres[2]);
                    }
                    else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) {
                        flashbacks(tab[i], &joueur->membres[0], &joueur->membres[2]);
                    } 
                    else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) { 
                        flashbacks(tab[i], &joueur->membres[0], &joueur->membres[1]);
                    }
                } 
                else if (strcmp(tab[i]->tech.nom, "bourreau")==0) {
                    bourreau(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "muraille")==0) {
                    muraille(tab[i]);
                }
                else if (strcmp(tab[i]->tech.nom, "motivation")==0) {
                    cadeau_empoisonne(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0) {
                    fossoyeur_des_mondes(tab[i]);
                }
                else if (strcmp(tab[i]->tech.nom, "cryogenese")==0) { 
                    cryogenese(tab[i], adversaire);
                }
                else if (strcmp(tab[i]->tech.nom, "scierculaire")==0) {
                    scierculaire(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                    cicatrices_eternels(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0) {
                    if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                        reinitialisation(tab[i], &joueur->membres[1], &joueur->membres[2], joueur, adversaire);
                    } else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) { 
                        reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[2], joueur, adversaire);
                    } else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) {
                        reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[1], joueur, adversaire);
                    }
                }
            }
            if (tab[i]->nbeffets>0){
                degatseffetStatut(tab[i]); // Application des dégâts d'effets.
            }
            if(equipetemp == 1 && pvtemp>e1->membres[joueurinvincibletemp].pvcourant){ // Vérifie si le champion est dans l'équipe 1 et si son pv est supérieur à celui de l'équipe 1.
                e1->membres[joueurinvincibletemp].pvcourant=pvtemp;
                printf("%s a bloque tous les degats !\n", e1->membres[joueurinvincibletemp].nom);
            }
            else if(equipetemp == 2 && pvtemp>e2->membres[joueurinvincibletemp].pvcourant){
                e2->membres[joueurinvincibletemp].pvcourant=pvtemp;
                printf("%s a bloque tous les degats !\n", e2->membres[joueurinvincibletemp].nom);
            }
            for(int j=0; j<3; j++){ // Gere la mort des champions.
                if(adversaire->membres[j].pvcourant<=0 && adversaire->membres[j].statut==1){ // Mis à jour du statut du champion.
                    adversaire->membres[j].pvcourant=0;
                    adversaire->membres[j].statut=0;
                    printf("%s est mort(e) !\n", adversaire->membres[j].nom);
                    for(int m=0; j<adversaire->membres[j].nbeffets; m++){
                        adversaire->membres[j].effets[m].duree=0; // Suppression de l'effet si le champion est mort.
                        adversaire->membres[j].effets[m].effet_statut=0;
                    }
                    adversaire->membres[j].nbeffets=0; // Réinitialisation du nombre d'effets.
                    if(memeEquipe(&adversaire->membres[j],e1)==0){
                        e2->nbchampvivant--; //Baisse le nombre de champions vivants dans l'équipe.
                    } 
                    else {
                        e1->nbchampvivant--;
                    }
                }
            }
            for(int j=0; j<3; j++){
                if(joueur->membres[j].pvcourant<=0 && joueur->membres[j].statut==1){
                    joueur->membres[j].pvcourant=0;
                    joueur->membres[j].statut=0;
                    printf("%s est mort(e) !\n", joueur->membres[j].nom);
                    for(int n=0; n<joueur->membres[j].nbeffets; n++){
                        joueur->membres[j].effets[n].duree=0; // Suppression de l'effet si le champion est mort.
                        joueur->membres[j].effets[n].effet_statut=0;
                    }
                    joueur->membres[j].nbeffets=0;
                    if(memeEquipe(&joueur->membres[j],e1)==0){
                        e2->nbchampvivant--;
                    } else {
                        e1->nbchampvivant--;
                    }
                }
            }
            if(e1->nbchampvivant==0 || (e1->membres[0].pvcourant==0 && e1->membres[0].pvcourant==0 && e1->membres[0].pvcourant==0)){ //Arrête le programme dès que tous les champions de l'équipe sont morts.
                break;
            }
            if(e2->nbchampvivant==0|| (e2->membres[0].pvcourant==0 && e2->membres[0].pvcourant==0 && e2->membres[0].pvcourant==0)){
                break;
            }
            tab[i]->jaugeactuelle+=1; // Augmente la barre de jauge de 1 à chaque fin de tour.
            if(tab[i]->jaugeactuelle>tab[i]->jaugemax){ // Met la barre de jauge au maximum si cette dernière est atteinte.
                tab[i]->jaugeactuelle=tab[i]->jaugemax;
            }
            int booltemp = 0;
            while (booltemp < tab[i]->nbeffets) {
                if (tab[i]->effets[booltemp].effet_statut != 0) {
                    tab[i]->effets[booltemp].duree--; // Baisse la durée des effets
                }
                if (tab[i]->effets[booltemp].duree <= 0) { // Supprime l'effet si ça dure est inférieure ou égale à 0.
                    suppressionEffetStatut(tab[i], booltemp);
                }
                else {
                    booltemp++;
                }
            }
        }
    }
}

void touria (Equipe* e1, Equipe* e2, int difficulte){ // fonction représentant un tour
    if(e1 == NULL || e2 == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    Champ *tab[6];
    int verif;
    triParVit(e1,e2,tab); // Appel de la fonction de tri par vitesse pour définir un ordre de passage
    for (int i=0;i<6;i++){ // Parcourt du tableau pour faire jouer les 6 champions 
        int verifstun=0;
        for(int j=0; j<10; j++){ 
            if(tab[i]->effets[j].effet_statut==2){
                verifstun=1;
            }
        }
        if (tab[i]->pvcourant<=0){
            printf("%s est KO, il ne peut pas attaquer\n",tab[i]->nom);
        }
        else {
            affichageCombat(e1,e2, tab[i]);
            Equipe *joueur;
            Equipe *adversaire;
            Champ *cible;
            float pvtemp=0;
            int joueurinvincibletemp=0;
            int equipetemp=0;
            for(int j=0; j<3; j++){
                for(int k=0; k<e1->membres[j].nbeffets; k++){
                    if (e1->membres[j].effets[k].effet_statut==4){
                        pvtemp=e1->membres[j].pvcourant;
                        joueurinvincibletemp=j;
                        equipetemp=1;
                    }
                }
                for(int k=0; k<e2->membres[j].nbeffets; k++){
                    if (e2->membres[j].effets[k].effet_statut==4){
                        pvtemp=e2->membres[j].pvcourant;
                        joueurinvincibletemp=j;
                        equipetemp=2;
                    }
                }
            }
            if(verifstun==1){
                printf("%s est stun !\n", tab[i]->nom);
            }
            else {
                if(memeEquipe(tab[i],e1)==0){
                    joueur=e2;
                    adversaire=e1;
                    if(difficulte==1){ // Difficulté "noob" de l'IA
                        do{
                            cible=&adversaire->membres[rand()%3]; // Choisit aléatoirement les cibles
                        }
                        while(cible->pvcourant<=0);
                        attaque(tab[i], cible);
                        printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                        printf("Appuyez sur entree pour continuer...\n");
                        getchar();
                    }
                    else if(difficulte==2){ // Difficulté "facile" de l'IA
                    cible=&adversaire->membres[0]; // Le premier membre de l'équipe adverse est pris comme cible par défaut
                    for(int k=1; k<3; k++){
                        if(adversaire->membres[k].pvcourant<cible->pvcourant && adversaire->membres[k].pvcourant>0){ // Prends comme cible le membre de l'équipe adverse ayant le moins de PV
                            cible=&adversaire->membres[k];
                        }
                    }
                    attaque(tab[i], cible);
                    printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                    printf("Appuyez sur entree pour continuer...\n");
                    getchar();
                    }
                    else{ // Difficulté "moyenne" de l'IA
                        if(tab[i]->jaugeactuelle==tab[i]->jaugemax){
                            // vérfication de la technique en comparant le noms des techniques au nom de la technique du personnage situé dans tab[i]
                            if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                                berserk(tab[i], joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                                if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                                    flashbacks(tab[i], &joueur->membres[1], &joueur->membres[2]);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) {
                                    flashbacks(tab[i], &joueur->membres[0], &joueur->membres[2]);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) { 
                                    flashbacks(tab[i], &joueur->membres[0], &joueur->membres[1]);
                                }
                            }
                            else if (strcmp(tab[i]->tech.nom, "bourreau")==0) {
                                bourreau(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "muraille")==0) {
                                muraille(tab[i]);
                            }
                            else if (strcmp(tab[i]->tech.nom, "cadeau_empoisonne")==0) {
                                cadeau_empoisonne(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0) {
                                fossoyeur_des_mondes(tab[i]);
                            }
                            else if (strcmp(tab[i]->tech.nom, "cryogenese")==0) { 
                                cryogenese(tab[i], adversaire);
                            }
                            else if (strcmp(tab[i]->tech.nom, "scierculaire")==0) {
                                scierculaire(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                                cicatrices_eternels(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0) {
                                if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                                    reinitialisation(tab[i], &joueur->membres[1], &joueur->membres[2], joueur, adversaire);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) { 
                                    reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[2], joueur, adversaire);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) {
                                    reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[1], joueur, adversaire);
                                }
                            }
                            printf("Appuyez sur entree pour continuer...\n");
                            getchar();
                        }
                        else{
                            cible=&e1->membres[0];
                            for(int k=1; k<3; k++){
                                if(e1->membres[k].pvcourant<cible->pvcourant && e1->membres[k].pvcourant>0){
                                    cible=&e1->membres[k];
                                }
                            }
                            attaque(tab[i], cible);
                            printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                            printf("Appuyez sur entree pour continuer...\n");
                            getchar();
                        }
                    }
                }
                else {
                    joueur=e1;
                    adversaire=e2;
                    if (tab[i]->jaugeactuelle==tab[i]->jaugemax){   
                        int choix;
                        printf("Jauge pleine! Voulez-vous utiliser une technique speciale? \n1:oui \n0:non \n");
                        printf("Description de la technique speciale: \n");
                        if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                            printf("Berserk : Insere une cle piratee en lui : devient immunise a toutes les attaques pendant 1 tour et attaque+30 pendant 1 tour, puis s'immobilise le prochain tour\n");
                        } 
                        else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                            printf("Flashbacks : Repare ses coequipiers : PVcourants+=60 pour toute la team et purge ses allies de tous les effets negatifs\n");
                        }
                        else if (strcmp(tab[i]->tech.nom, "bourreau")==0){
                            printf("Bourreau : Place un traceur sur un ennemi : si ce dernier possede 25 pourcent ou moins de ses pvmax, il est execute sans pitie et pvcourant-(pvmax/10)\n");
                        } 
                        else if (strcmp(tab[i]->tech.nom, "muraille")==0){
                            printf("Muraille : Se place devant son equipe et provoque l'equipe adverse : applique provocation et renvoi de degats sur lui même et defense+30\n");
                        } 
                        else if (strcmp(tab[i]->tech.nom, "cadeau_empoisonne")==0){
                            printf("Cadeau empoisonne : Il court circuite ses ennemis : applique poison a 2 ennemis aleatoires et vitesse-2\n");
                        }
                        else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0){
                            printf("Fossoyeur des mondes : Une anomalie dans le systeme provoque un desequilibre chez Booga : pv+30 et defense+30 pendant 2 tours +10attaque\n");
                        }
                        else if (strcmp(tab[i]->tech.nom, "cryogenese")==0){
                            printf("Cryogenese : Sa glaciere integree explose et gel les adversaires : Inflige 30 degâts a tous les ennemis et les stuns pendant 1 tour\n");
                        }
                        else if (strcmp(tab[i]->tech.nom, "scierculaire")==0){
                            printf("Scierculaire : Tourne sur elle même et tire sur tous ce qu'elle voit : Inflige 50 degats a tous les adversaires et leur applique poison\n");
                        }
                        else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                            printf("Cicatrices eternels : Relache toute sa timidite et laisse ses demons prendre le controle : Inflige 100 degats a tous les ennemis\n");
                        }
                        else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0){
                            printf("Reinitialisation : Reinitialise les donnes d'un allie : Ramene un allie a la vie\n");
                        }
                        do{
                            verif=scanf("%d", &choix);
                            if(choix>1 || choix<0){
                                printf("Index invalide");
                            }
                            vide_buffer();
                        } 
                        while(choix>1 || choix<0 || verif!=1); 
                        if (choix==1){
                            // vérfication de la technique en comporant le noms des techniques eau nom de la technique du personnage situé dans tab[i]
                            if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                                berserk(tab[i], joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                                if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                                    flashbacks(tab[i], &joueur->membres[1], &joueur->membres[2]);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) {
                                    flashbacks(tab[i], &joueur->membres[0], &joueur->membres[2]);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) { 
                                    flashbacks(tab[i], &joueur->membres[0], &joueur->membres[1]);
                                }
                            }
                            else if (strcmp(tab[i]->tech.nom, "bourreau")==0) {
                                bourreau(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "muraille")==0) {
                                muraille(tab[i]);
                            }
                            else if (strcmp(tab[i]->tech.nom, "cadeau_empoisonne")==0) {
                                cadeau_empoisonne(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0) {
                                fossoyeur_des_mondes(tab[i]);
                            }
                            else if (strcmp(tab[i]->tech.nom, "cryogenese")==0) { 
                                cryogenese(tab[i], adversaire);
                            }
                            else if (strcmp(tab[i]->tech.nom, "scierculaire")==0) {
                                scierculaire(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                                cicatrices_eternels(tab[i], adversaire, joueur);
                            }
                            else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0) {
                                if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                                    reinitialisation(tab[i], &joueur->membres[1], &joueur->membres[2], joueur, adversaire);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) { 
                                    reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[2], joueur, adversaire);
                                }
                                else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) {
                                    reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[1], joueur, adversaire);
                                }
                            }
                        }
                        else {
                            cible=choixCible(tab[i], joueur, adversaire);
                            printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                            attaque(tab[i], cible);
                        }
                    }
                    else {
                        cible=choixCible(tab[i], joueur, adversaire);
                        printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                        attaque(tab[i],cible);
                    }
                }
            }
            if (tab[i]->tech.nbtactifs != 0) {
                // vérfication de la technique
                if (strcmp(tab[i]->tech.nom, "berserk")==0) {
                    berserk(tab[i], joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "flashbacks")==0) {
                    if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                        flashbacks(tab[i], &joueur->membres[1], &joueur->membres[2]);
                    }
                    else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) {
                        flashbacks(tab[i], &joueur->membres[0], &joueur->membres[2]);
                    } 
                    else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) { 
                        flashbacks(tab[i], &joueur->membres[0], &joueur->membres[1]);
                    }
                } 
                else if (strcmp(tab[i]->tech.nom, "bourreau")==0) {
                    bourreau(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "muraille")==0) {
                    muraille(tab[i]);
                }
                else if (strcmp(tab[i]->tech.nom, "motivation")==0) {
                    cadeau_empoisonne(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "fossoyeur_des_mondes")==0) {
                    fossoyeur_des_mondes(tab[i]);
                }
                else if (strcmp(tab[i]->tech.nom, "cryogenese")==0) { 
                    cryogenese(tab[i], adversaire);
                }
                else if (strcmp(tab[i]->tech.nom, "scierculaire")==0) {
                    scierculaire(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "cicatrices_eternels")==0){
                    cicatrices_eternels(tab[i], adversaire, joueur);
                }
                else if (strcmp(tab[i]->tech.nom, "reinitialisation")==0) {
                    if(strcmp(tab[i]->nom, joueur->membres[0].nom)==0) {
                        reinitialisation(tab[i], &joueur->membres[1], &joueur->membres[2], joueur, adversaire);
                    } else if (strcmp(tab[i]->nom, joueur->membres[1].nom)==0) { 
                        reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[2], joueur, adversaire);
                    } else if (strcmp(tab[i]->nom, joueur->membres[2].nom)==0) {
                        reinitialisation(tab[i], &joueur->membres[0], &joueur->membres[1], joueur, adversaire);
                    }
                }
            }
            if (tab[i]->nbeffets>0){
                degatseffetStatut(tab[i]);
            }
            if(equipetemp == 1 && pvtemp>e1->membres[joueurinvincibletemp].pvcourant){
                e1->membres[joueurinvincibletemp].pvcourant=pvtemp;
                printf("%s a bloque tous les degats !\n", e1->membres[joueurinvincibletemp].nom);
            }
            else if(equipetemp == 2 && pvtemp>e2->membres[joueurinvincibletemp].pvcourant){
                e2->membres[joueurinvincibletemp].pvcourant=pvtemp;
                printf("%s a bloque tous les degats !\n", e2->membres[joueurinvincibletemp].nom);
            }
            for(int j=0; j<3; j++){
                if(adversaire->membres[j].pvcourant<=0 && adversaire->membres[j].statut==1){
                    adversaire->membres[j].pvcourant=0;
                    adversaire->membres[j].statut=0;
                    printf("%s est mort(e) !\n", adversaire->membres[j].nom);
                    for(int v=0; v<adversaire->membres[j].nbeffets; v++){
                        adversaire->membres[j].effets[v].duree=0; // Suppression de l'effet si le champion est mort.
                        adversaire->membres[j].effets[v].effet_statut=0;
                    }
                    adversaire->membres[j].nbeffets=0;
                    if(memeEquipe(&adversaire->membres[j],e1)==0){
                        e2->nbchampvivant--;
                    } 
                    else {
                        e1->nbchampvivant--;
                    }
                }
            }
            for(int j=0; j<3; j++){
                if(joueur->membres[j].pvcourant<=0 && joueur->membres[j].statut==1){
                    joueur->membres[j].pvcourant=0;
                    joueur->membres[j].statut=0;
                    printf("%s est mort(e) !\n", joueur->membres[j].nom);
                    for(int s=0; s<joueur->membres[j].nbeffets; s++){
                        joueur->membres[j].effets[s].duree=0; // Suppression de l'effet si le champion est mort.
                        joueur->membres[j].effets[s].effet_statut=0;
                    }
                    joueur->membres[j].nbeffets=0;
                    if(memeEquipe(&joueur->membres[j],e1)==0){
                        e2->nbchampvivant--;
                    } else {
                        e1->nbchampvivant--;
                    }
                }
            }
            if(e1->nbchampvivant==0){
                break;
            }
            if(e2->nbchampvivant==0){
                break;
            }
            tab[i]->jaugeactuelle+=1;
            if(tab[i]->jaugeactuelle>tab[i]->jaugemax){
                tab[i]->jaugeactuelle=tab[i]->jaugemax;
            }
            int booltemp = 0;
            while (booltemp < tab[i]->nbeffets) {
                if (tab[i]->effets[booltemp].effet_statut != 0) {
                    tab[i]->effets[booltemp].duree--;
                }
                if (tab[i]->effets[booltemp].duree <= 0) {
                    suppressionEffetStatut(tab[i], booltemp);
                }
                else {
                    booltemp++;
                }
            }
        }
    }
}
