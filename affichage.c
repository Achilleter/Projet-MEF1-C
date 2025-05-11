#include "principal.h"

void affichageCombat(Equipe *equipe1, Equipe *equipe2, Champ* joueur){
    printf("\n%s%*s%s\n\n", equipe1->nom, 70-(int)strlen(equipe1->nom),"", equipe2->nom);
    for(int i=0; i<3; i++){
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
        int nbeffets1=equipe1->membres[i].nbeffets;
        int nbeffets2=equipe2->membres[i].nbeffets;
        int effetmax=3;
        int effetduree=0;
        int nbtotaleffet=nbeffets1*5;
        if(nbeffets1 == 0 && nbeffets2 == 0){
            printf("(Chill Guy)%*s(Chill Guy)", 59, "");
        }
        else if(nbeffets1 == 0 && nbeffets2 != 0){
            printf("(Chill Guy)%*s", 59, "");
        }
        if(nbeffets1 != 0){
            for(int j=0; j<nbeffets1; j++){
                int effetdureemax=equipe1->membres[i].effets[j].duree;
                switch(equipe1->membres[i].effets[j].effet_statut){
                    case 1:
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🐍");
                            effetduree--;
                        }
                        while(effetmax-effetdureemax>0){
                            printf("_");
                            effetdureemax++;
                        }
                        printf(")");
                        break;
                    case 2:
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
                    case 3:
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
                    case 4:
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
                    case 5:
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
                    case 6:
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
                    default:
                        break;
                }
            }
        }
        if(nbeffets1 != 0 && nbeffets2 != 0){
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
        int pvactuel1=equipe1->membres[i].pvcourant/20; // variable pour afficher la barre de vie
        int pvmax1=equipe1->membres[i].pvmax/20;
        int pvvide1=pvmax1-pvactuel1; // variable pour remplir le vide de la barre de vie
        int pvaffichage1=0;
        if(equipe1->membres[i].pvcourant >=10.00 && equipe1->membres[i].pvcourant < 100.00){
            pvaffichage1=2;
        }
        else if(equipe1->membres[i].pvcourant >=0.00 && equipe1->membres[i].pvcourant < 10.00){
            pvaffichage1=1;
        }
        printf("("); 
        while(pvactuel1>0){
            printf("❤");
            pvactuel1--;
        }
        while(pvvide1>0){
            printf("_");
            pvvide1--;
        }
        printf(")(");
        if(pvaffichage1 == 2){
            printf("0");
        }
        else if(pvaffichage1 == 1){
            printf("00");
        }
        printf("%.2f)%*s", equipe1->membres[i].pvcourant, 60-(pvmax1), "");
        // Affichage des PV sous les membres de l'équipe 2
        int pvactuel2=equipe2->membres[i].pvcourant/20;
        int pvmax2=equipe2->membres[i].pvmax/20;
        int pvvide2=pvmax2-pvactuel2; // variable pour remplir le vide de la barre de vie
        int pvaffichage2=0;
        if(equipe2->membres[i].pvcourant >=10.00 && equipe2->membres[i].pvcourant < 100.00){
            pvaffichage2=2;
        }
        else if(equipe2->membres[i].pvcourant >=0.00 && equipe2->membres[i].pvcourant < 10.00){
            pvaffichage2=1;
        }
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
        if(pvaffichage2 == 2){
            printf("0");
        }
        else if(pvaffichage2 == 1){
            printf("00");
        }
        printf("%.2f)\n", equipe2->membres[i].pvcourant);
        // afficher la jauge de chaque champion
        int jaugeactuel1=equipe1->membres[i].jaugeactuelle; // variable pour afficher la jauge de vie
        int jaugemax1=equipe1->membres[i].jaugemax;
        int jaugevide1=jaugemax1-jaugeactuel1; // variable pour remplir le vide de la jauge de vie
        printf("(");
        while(jaugeactuel1>0){
            printf("🗲");
            jaugeactuel1--;
        }
        while(jaugevide1>0){
            printf("_");
            jaugevide1--;
        }
        printf(")%*s", 68-jaugemax1, "");
        // afficher la jauge de chaque champion de l'équipe 2
        int jaugeactuel2=equipe2->membres[i].jaugeactuelle; // variable pour afficher la jauge de vie
        int jaugemax2=equipe2->membres[i].jaugemax;
        int jaugevide2=jaugemax2-jaugeactuel2; // variable pour remplir le vide de la jauge de vie  
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


void afficherEquipeChamp(Champ tab[], int deja_pris[]){  // affichage des champions pour la selection
    int alligne = 0; // variable temporelle pour l'alignement
    for (int i=0; i<10; i++) { 
        if(i+1<10){
            alligne = 11;
        }
        else if(i+1==10){
            alligne = 10;
        }
        if(deja_pris[i] == 1){                         
            printf("%d - %s %*s(PV:%.2f | ATT:%.2f | DEF:%.2f | AGI:%.2f | VIT:%.2f) [DEJA PRIS]\n",  i + 1, tab[i].nom, alligne-(int)strlen(tab[i].nom), "", tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        } else {
            printf("%d - %s %*s(PV:%.2f | ATT:%.2f | DEF:%.2f | AGI:%.2f | VIT:%.2f)\n",  i + 1, tab[i].nom, alligne-(int)strlen(tab[i].nom), "", tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        }
    }
}
