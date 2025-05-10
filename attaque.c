#include "principal.h"

float attaque(Champ *champatt, Champ *champdef){
    if(champatt == NULL || champdef == NULL){
        printf("Erreur : pointeur nul");
        exit(1);
    }
    float degats = champatt->att * (100/(100+champdef->def)); // calcul des dégats
    if (degats < 0) {
        degats = 0;
    }
    if (champdef->statut == 5) { // renvoie de dégats
        printf("%s renvoi les degats de %s",champdef->nom, champatt->nom);
        champatt->pvcourant -= degats / 4;
        if (champatt->pvcourant < 0) {
            champatt->pvcourant = 0;
        }
    }
    if (champdef->statut == 4) { // invincibilité
        degats=0;
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
                    champ->statut = 0; // mort
                    printf("%s a ete execute par bourreau !\n", champ->nom);
                }
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
    champ->effets[numeffet].effet_statut=0;
    champ->effets[numeffet].duree=0;
    champ->effets[numeffet].effet_statut=champ->effets[champ->nbeffets].effet_statut;
    champ->effets[numeffet].duree=champ->effets[champ->nbeffets].duree;
    champ->effets[champ->nbeffets].effet_statut=0;
    champ->effets[champ->nbeffets].duree=0;
    champ->nbeffets--;
}

// Fonction partition. Tri rapide
int partition(Champ *A[], int debut, int fin) {
    int inf=debut+1;
    int sup=fin;
    Champ *pivot=A[debut];
    Champ *tmp;
    if (pivot == NULL){
        printf("Erreur. Pointeur nul.");
    }
    while (inf<=sup) {
        while (sup>=inf && A[sup]->vitesse<pivot->vitesse) {
            sup=sup-1;
        }
        while (inf<=fin && A[inf]->vitesse>pivot->vitesse) {
            inf=inf+1;
        }
        if (inf<sup) {
            tmp=A[inf];
            A[inf]=A[sup];
            A[sup]=tmp;
        }
    }

    tmp=A[debut];
    A[debut]=A[sup];
    A[sup]=tmp;
    return sup;
}

// Fonction récursive de tri rapide
void triRapideRec(Champ *A[], int debut, int fin) {
    if (debut<fin) {
        int pivot=partition(A, debut, fin);
        triRapideRec(A, debut, pivot - 1);
        triRapideRec(A, pivot + 1, fin);
    }
    for (int i=0; i<6; i++){
        if (A[i]==NULL){
            printf("Erreur. Pointeur nul.");
        }
    }
}

// Fonction principale du tri rapide
void triRapide(Champ *A[], int n) {
    triRapideRec(A, 0, n-1);
}

// Fonction de tri par vitesse de deux équipes
void triParVit(Equipe *e1, Equipe *e2, Champ *tab[6]) {
    if (e1==NULL || e2==NULL) {
        printf("Erreur : pointeur nul\n");
        exit(1);
    }
    for (int i=0; i<3; i++) {
        tab[i]=&e1->membres[i];
        tab[i+3]=&e2->membres[i];
    }
    triRapide(tab, 6);
    for (int i=0; i<6; i++) {
        if (tab[i] == NULL) {
            printf("Erreur : pointeur nul.");
            exit(10);
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
                    printf("%s est provoqué par %s !\n",attaquant->nom, e2->membres[j].nom);
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

void tour (Equipe* e1, Equipe* e2){ // fonction représentant un tour
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
        if (verifstun==1){
            printf("%s est stun !\n", tab[i]->nom);
        }
        if (tab[i]->pvcourant<=0){
            printf("%s est KO.\n",tab[i]->nom);
        }
        else {
            affichageCombat(e1,e2, tab[i]);
            Equipe *joueur;
            Equipe *adversaire;
            if(verifstun==1){
                printf("%s est stun !\n", tab[i]->nom);
            }   
            else {
                if(memeEquipe(tab[i],e1)==0){
                    joueur=e2;
                    adversaire=e1;
                } 
                else {
                    joueur=e1;
                    adversaire=e2;
                }
                if (tab[i]->jaugeactuelle==tab[i]->jaugemax){
                    int choix;
                    printf("Jauge pleine! Voulez-vous utiliser une technique speciale? \n1:oui \n0:non \n");
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
                        Champ *cible=choixCible(tab[i], joueur, adversaire);
                        printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                        attaque(tab[i], cible);
                    }
                }
                else {
                Champ *cible=choixCible(tab[i], joueur, adversaire);
                printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
                attaque(tab[i],cible);
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
            for(int j=0; j<3; j++){
                if(adversaire->membres[j].pvcourant<=0 && adversaire->membres[j].statut==1){
                    adversaire->membres[j].pvcourant=0;
                    adversaire->membres[j].statut=0;
                    printf("%s à tué %s !\n", tab[i]->nom, adversaire->membres[j].nom);
                    int booltemp=0;
                    for(int k=0; k<adversaire->membres[j].nbeffets; k++){
                        if(booltemp==1){
                            k--;
                        }
                        booltemp=0;
                        if(adversaire->membres[j].effets[k].effet_statut!=0 && adversaire->membres[j].effets[k].duree>0){
                            suppressionEffetStatut(&adversaire->membres[j], k);
                            booltemp=1;
                        }
                    }
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
                    printf("%s à tué %s !\n", tab[i]->nom, joueur->membres[j].nom);
                    for(int k=0; k<joueur->membres[j].nbeffets; k++){
                        if(joueur->membres[j].effets[k].effet_statut!=0 && joueur->membres[j].effets[k].duree>0){
                            suppressionEffetStatut(&joueur->membres[j], k);
                            k--;
                        }
                    }
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
            int booltemp=0;
            for(int j=0; j<tab[i]->nbeffets; j++){
                if(booltemp==1){
                    j--;
                }
                booltemp=0;
                if(tab[i]->effets[j].effet_statut!=0){
                    tab[i]->effets[j].duree--;
                }
                if(tab[i]->effets[j].duree==0){
                    suppressionEffetStatut(tab[i], j);
                    booltemp=1;
                }
            }
        }
    }
}


//  void touria(Equipe* e1, Equipe* e2, int difficulte){
//      if(e1 == NULL || e2 == NULL){
//          printf("Erreur : pointeur nul");
//          exit(1);
//      }
//      Champ *tab[6];
//      int verif;
//      triParVit(e1,e2,tab);
//      for (int i=0;i<6;i++){
//          if(tab[i]->pvcourant<=0){
//              printf("%s est KO.\n",tab[i]->nom);
//          }
//          else {
//              affichageCombat(e1,e2, tab[i]);
//              for (int j=0; j<tab[i]->nbeffets; j++){
//                  if (tab[i]->effets[j].duree>0){
//                      degatseffetStatut(tab[i]);
//                  }
//              }
//              Equipe *joueur;
//              Equipe *adversaire;
//              Champ* cible;
//              if(memeEquipe(tab[i],e1)==0){
//                  cible=0;
//                 joueur=e2;
//                  adversaire=e1;
//                  if(difficulte==1){
//                      cible=&adversaire->membres[rand()%3];
//                      attaque(tab[i], cible);
//                      printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
//                  }
//                  else if(difficulte==2){
//                      cible=&adversaire->membres[0];
//                      for(int k=1; k<3; k++){
//                          if(adversaire->membres[k].pvcourant<cible->pvcourant){
//                              cible=&adversaire->membres[k];
//                              }
//                     }
//                     attaque(tab[i], cible);
//                     printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
//                  }
//                  else{
//                      if(tab[i]->jaugeactuelle==tab[i]->jaugemax){
//                          //insérer tech spé si jauge pleine
//                      }
//                      else{
//                          cible=&e1->membres[0];
//                          for(int k=1; k<3; k++){
//                              if(e1->membres[k].pvcourant<cible->pvcourant){
//                                  cible=&e1->membres[k];
//                              }
//                          }
//                          attaque(tab[i], cible);
//                          printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
//                      }
//                  }
//              }
//              else {
//                  cible=0;
//                  joueur=e1;
//                  adversaire=e2;
//                  cible=choixCible(tab[i], joueur, adversaire);
//                  float pvtemp=cible->pvcourant;
//                  if (tab[i]->jaugeactuelle==tab[i]->jaugemax){
//                      int choix;
//                      printf("Jauge pleine! Voulez-vous utiliser une technique spéciale? (1:oui, 0:non): ");
//                      do{
//                          verif=scanf("%d", &choix);
//                          if(choix>1 || choix<0){
//                          printf("INDEX INVALIDE");
//                          }
//                          vide_buffer();
//                      }while(choix>1 || choix<0 || verif!=1); 
//                      if (choix==1){
//                          printf("%s utilise son attaque spéciale !\n", tab[i]->nom);
//                          //implementer fonctions techniques
//                      }
//                      else {
//                      printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
//                      attaque(tab[i], cible);
//                      } 
//                  } 
//                  else {
//                      printf("%s attaque %s.\n", tab[i]->nom, cible->nom);
//                      attaque(tab[i],cible);
//                  }
//                  for(int j=0; j<cible->nbeffets; j++){ // suppression des degats si le statut est invincibilité
//                      if(cible->effets[0].effet_statut==4){
//                      cible->pvcourant=pvtemp;
//                      }
//                  }
//          }
//         if (cible->pvcourant<0) {
//             cible->pvcourant=0;
//             cible->statut=0;
//             printf("%s à tué %s !\n", tab[i]->nom, cible->nom);
//             if(memeEquipe(cible,e1)==0){
//                 e1->nbchampvivant--;
//             } else {
//                 e2->nbchampvivant--;
//             }
//         }
//         if(e1->nbchampvivant==0){
//             i=6;
//         }
//         if(e2->nbchampvivant==0){
//             i=6;
//         }
//         tab[i]->jaugeactuelle+=1;
//         if(tab[i]->jaugeactuelle>tab[i]->jaugemax){
//             tab[i]->jaugeactuelle=tab[i]->jaugemax;
//         }
//      }
//  }
//  }
