#include "principal.h"

// Fonction qui affiche le combat entre les deux équipes
void affichageCombat(Equipe *equipe1, Equipe *equipe2, Champ* joueur){
    if(equipe1 == NULL || equipe2 == NULL || joueur == NULL){ // Vérification si les équipes ou le joueur sont nuls
        printf("Erreur: pointeur nul");
        exit(1);
    }
    printf("\n%s%*s%s\n\n", equipe1->nom, 70-(int)strlen(equipe1->nom),"", equipe2->nom); // Affichage des noms des équipes sur une ligne
    for(int i=0; i<3; i++){ // Boucle pour afficher les membres de chaque équipe avec leur statut et le membre qui doit jouer, le tout sur une ligne
        if(equipe1->membres[i].statut == 0 && equipe2->membres[i].statut == 1 && equipe1->membres[i].nom != joueur->nom && equipe2->membres[i].nom != joueur->nom){
            printf("%s |☠|%*s%s |%d|", equipe1->membres[i].nom, 66-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        if(equipe1->membres[i].statut == 1 && equipe2->membres[i].statut == 0 && equipe1->membres[i].nom != joueur->nom && equipe2->membres[i].nom != joueur->nom){
            printf("%s |%d|%*s%s |☠|", equipe1->membres[i].nom, i+1, 66-(int)strlen(equipe1->membres[i].nom), "",equipe2->membres[i].nom);
        }
        else if(equipe1->membres[i].statut == 0 && equipe2->membres[i].statut == 0){
            printf("%s |☠|%*s%s |☠|", equipe1->membres[i].nom, 66-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom);
        }
        if(equipe1->membres[i].statut == 1 && equipe2->membres[i].statut == 1 && equipe1->membres[i].nom != joueur->nom && equipe2->membres[i].nom != joueur->nom){
            printf("%s |%d|%*s%s |%d|", equipe1->membres[i].nom, i+1, 66-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        if(equipe1->membres[i].nom == joueur->nom && equipe2->membres[i].nom != joueur->nom && equipe1->membres[i].statut == 1 && equipe2->membres[i].statut == 1){
            printf(")>%s<( |%d|%*s%s |%d|", equipe1->membres[i].nom, i+1, 62-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        else if(equipe1->membres[i].nom != joueur->nom && equipe2->membres[i].nom == joueur->nom && equipe1->membres[i].statut == 1 && equipe2->membres[i].statut == 1){
            printf("%s |%d|%*s)>%s<( |%d|", equipe1->membres[i].nom, i+1, 66-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        else if(equipe1->membres[i].statut == 0 && equipe2->membres[i].statut == 1 && equipe2->membres[i].nom == joueur->nom && equipe1->membres[i].nom != joueur->nom){
            printf("%s |☠|%*s)>%s<( |%d|", equipe1->membres[i].nom, 66-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        else if(equipe1->membres[i].statut == 1 && equipe2->membres[i].statut == 0 && equipe1->membres[i].nom == joueur->nom && equipe2->membres[i].nom != joueur->nom){
            printf(")>%s<( |%d|%*s%s |☠|", equipe1->membres[i].nom, i+1, 62-(int)strlen(equipe1->membres[i].nom), "",equipe2->membres[i].nom);
        }
        printf("\n");
        // Affichage des effets de chaque membre de l'équipe 1 et 2, ligne suivante
        int nbeffets1=equipe1->membres[i].nbeffets; // Nombre d'effets de l'équipe 1
        int nbeffets2=equipe2->membres[i].nbeffets; 
        int effetmax=3; // Varitable temporaire pour afficher les effets même avec le vide
        int effetduree=0; // Variable pour afficher un effet
        int nbtotaleffet=nbeffets1*5; // Variable temporaire pour connaître le nombre d'effets (*5 car chaque effet est affiché par 5 caractères)
        if(nbeffets1 == 0 && nbeffets2 == 0){ // Si les deux équipes n'ont pas d'effets
            printf("(Chill Guy)%*s(Chill Guy)", 59, "");
        }
        else if(nbeffets1 == 0 && nbeffets2 != 0){
            printf("(Chill Guy)%*s", 59, "");
        }
        if(nbeffets1 != 0){ // Si l'équipe 1 a des effets
            for(int j=0; j<nbeffets1; j++){ // Boucle pour afficher tous les effets d'un membre de l'équipe 1
                int effetdureemax=equipe1->membres[i].effets[j].duree; // Variable temporaire qui va permettre de remplir le vide de la barre d'effets
                switch(equipe1->membres[i].effets[j].effet_statut){ // Switch pour afficher les effets en se basant sur les énumérations
                    case 1: // Poison
                        effetduree=equipe1->membres[i].effets[j].duree; // Variable temporaire pour afficher un nombre de fois l'effet selon sa durée
                        printf("(");
                        while(effetduree>0){ // Boucle while pour afficher l'effet selon sa durée
                            printf("🐍");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){ // Boucle while pour afficher le vide de la barre d'effets
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    case 2: // Stun
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🌀");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    case 3: // Provocation
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("💢");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    case 4: // Invincibilité
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🛡");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    case 5: // Renvoie de dégâts
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🦔");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    case 6: // Execute
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🗡");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    default: // Si l'effet n'est pas reconnu
                        break;
                }
            }
        }
        if(nbeffets1 != 0 && nbeffets2 != 0){ // Si les deux équipes ont des effets, on affiche un espace entre les deux
            	printf("%*s", 68-(nbtotaleffet), ""); 
        }
        else if(nbeffets1 != 0 && nbeffets2 == 0){
            printf("%*s(Chill Guy)", 68-(nbtotaleffet), "");
        }
        if(nbeffets2 != 0){
            for(int k=0; k<nbeffets2; k++){
                int effetdureemax2=equipe2->membres[i].effets[k].duree;
                switch(equipe2->membres[i].effets[k].effet_statut){
                    case 1:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🐍");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax2>0){
                            printf("_");
                            effetdureemax2++;
                        }
                        printf(")");
                        break;
                    case 2:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🌀");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax2>0){
                            printf("_");
                            effetdureemax2++;
                        }
                        printf(")");
                        break;
                    case 3:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("💢");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax2>0){
                            printf("_");
                            effetdureemax2++;
                        }
                        printf(")");
                        break;
                    case 4:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🛡");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax2>0){
                            printf("_");
                            effetdureemax2++;
                        }
                        printf(")");
                        break;
                    case 5:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🦔");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax2>0){
                            printf("_");
                            effetdureemax2++;
                        }
                        printf(")");
                        break;
                    case 6:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🗡");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax2>0){
                            printf("_");
                            effetdureemax2++;
                        }
                        printf(")");
                        break;
                    default:
                        break;
                }
            }
        }
        printf("\n");
        // Affichage des PV sous les membres de l'équipe 1
        int pvactuel1=equipe1->membres[i].pvcourant/20; // Variable temporaire pour afficher la barre de vie
        int pvmax1=equipe1->membres[i].pvmax/20; // Variable temporaire pour affiche la barre de vie même avec le vide
        int pvvide1=pvmax1-pvactuel1; // variable pour remplir le vide de la barre de vie
        printf("("); 
        while(pvactuel1>0){ // Boucle while pour afficher la barre de vie selon ses PV courants
            printf("❤");
            pvactuel1--;
        }
        while(pvvide1>0){ // Boucle while pour afficher le vide de la barre de vie avec le vide qu'il y a entre les PV courants et les PV max
            printf("_");
            pvvide1--;
        }
        printf(")(");
        if(equipe1->membres[i].pvcourant >=100.00){ // Si le PV est supérieur ou égal à 100, on affiche un 3 chiffres suivi d'un . puis 2 chiffres
        }
        else if(equipe1->membres[i].pvcourant >=10.00 && equipe1->membres[i].pvcourant < 100.00){ // Si le PV est supérieur ou égal à 10, on affiche un 0 puis de 2 chiffres suivi d'un . puis 2 chiffres
            printf("0");
        }
        else if(equipe1->membres[i].pvcourant >=0.00 && equipe1->membres[i].pvcourant < 10.00){ // Si le PV est supérieur ou égal à 0, on affiche deux 0 puis de 2 chiffres suivi d'un . puis 2 chiffres
            printf("00");
        }
        printf("%.2f)%*s", equipe1->membres[i].pvcourant, 60-(pvmax1), ""); // Affichage des PV courants en float
        // Affichage des PV sous les membres de l'équipe 2
        int pvactuel2=equipe2->membres[i].pvcourant/20;
        int pvmax2=equipe2->membres[i].pvmax/20;
        int pvvide2=pvmax2-pvactuel2;
        printf("("); 
        while(pvactuel2>0){
            printf("❤");
            pvactuel2--;
        }
        while(pvvide2>0){
            printf("_");
            pvvide2--;
        }
        printf(")(");
        if(equipe2->membres[i].pvcourant >=100.00){
        }
        else if(equipe2->membres[i].pvcourant >=10.00 && equipe2->membres[i].pvcourant < 100.00){
            printf("0");
        }
        else if(equipe2->membres[i].pvcourant >=0.00 && equipe2->membres[i].pvcourant < 10.00){
            printf("00");
        }
        printf("%.2f)\n", equipe2->membres[i].pvcourant);
        // Afficher la jauge de chaque champion
        int jaugeactuel1=equipe1->membres[i].jaugeactuelle; // Variable temporaire pour afficher la jauge courante
        int jaugemax1=equipe1->membres[i].jaugemax; // Variable pour afficher la jauge max avec le vide
        int jaugevide1=jaugemax1-jaugeactuel1; // variable pour remplir le vide de la jauge
        printf("(");
        while(jaugeactuel1>0){ // Boucle while pour afficher la jauge selon sa jauge courante
            printf("🗲");
            jaugeactuel1--;
        }
        while(jaugevide1>0){ // Boucle while pour afficher le vide de la jauge avec le vide qu'il y a entre la jauge courante et la jauge max
            printf("_");
            jaugevide1--;
        }
        printf(")%*s", 68-jaugemax1, "");
        // Afficher la jauge de chaque champion de l'équipe 2
        int jaugeactuel2=equipe2->membres[i].jaugeactuelle;
        int jaugemax2=equipe2->membres[i].jaugemax;
        int jaugevide2=jaugemax2-jaugeactuel2;
        printf("(");
        while(jaugeactuel2>0){
            printf("🗲");
            jaugeactuel2--;
        }
        while(jaugevide2>0){
            printf("_");
            jaugevide2--;
        }
        printf(")\n\n"); 
    }
}

// Affichage des champions pour la selection
void afficherEquipeChamp(Champ tab[], int deja_pris[]){
    int alligne = 0; // Variable temporelle pour l'alignement
    for (int i=0; i<10; i++) { 
        if(i+1<10){
            alligne = 11; // Si le nombre de champions est inférieur à 10, on affiche un espace de 11 caractères
        }
        else if(i+1==10){
            alligne = 10; // Si le nombre de champions est égal à 10, on affiche un espace de 10 caractères vu que 10 est un nombre à deux caractères
        }
        if(deja_pris[i] == 1){ // Si le champion est déjà pris, on affiche un message après avoir affiché ses stats et son nom                 
            printf("%d - %s %*s(PV:%.2f | ATT:%.2f | DEF:%.2f | AGI:%.2f | VIT:%.2f) [DEJA PRIS]\n",  i + 1, tab[i].nom, alligne-(int)strlen(tab[i].nom), "", tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        } else { 
            printf("%d - %s %*s(PV:%.2f | ATT:%.2f | DEF:%.2f | AGI:%.2f | VIT:%.2f)\n",  i + 1, tab[i].nom, alligne-(int)strlen(tab[i].nom), "", tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        }
    }
}
