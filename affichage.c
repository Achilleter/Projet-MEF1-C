#include "principal.h"

void affichageCombat(Equipe *equipe1, Equipe *equipe2, Champ* joueur){
    printf("%s%*s%s\n\n", equipe1->nom, 70-(int)strlen(equipe1->nom),"", equipe2->nom);
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
        if(nbeffets1==0 && nbeffets2==0){
            printf("(Chill Guy)%*s(Chill Guy)", 59, "");
        }
        else if(nbeffets1==0 && nbeffets2!=0){
            printf("(Chill Guy)%*s", 59, "");
        }
        else if(nbeffets1!=0 || nbeffets2!=0){
            for(int j=0; j<nbeffets1; j++){
                int effetdureemax=equipe1->membres[i].effets[j].duree;
                switch(equipe1->membres[i].effets[j].effet_statut){
                    case 1:
                        effetduree=equipe1->membres[i].effets[j].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🦠");
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
            if(nbeffets1!=0){
                printf("%*s", 70-(int)(5*nbeffets1), "");
            }
            for(int k=0; k<nbeffets2; k++){
                int effetdureemax2=equipe2->membres[i].effets[k].duree;
                switch(equipe2->membres[i].effets[k].effet_statut){
                    case 1:
                        effetduree=equipe2->membres[i].effets[k].duree;
                        printf("(");
                        while(effetduree>0){
                            printf("🦠");
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
            if(nbeffets1!=0 && nbeffets2==0){
                printf("%*s(Chill Guy)", 65, "");
            }
        }
        printf("\n");
        // Affichage des PV sous les membres de l'équipe 1
        int pvactuel1=equipe1->membres[i].pvcourant/20; // variable pour afficher la barre de vie
        int pvmax=20;
        int pvvide1=pvmax-pvactuel1; // variable pour remplir le vide de la barre de vie
        printf("("); 
        while(pvactuel1>0){
            printf("❤");
            pvactuel1--;
        }
        while(pvvide1>0){
            printf("_");
            pvvide1--;
        }
        printf(")(%.2f)%*s", equipe1->membres[i].pvcourant, 20, "");
        // Affichage des PV sous les membres de l'équipe 2
        int pvactuel2=equipe2->membres[i].pvcourant/20;
        int pvvide2=pvmax-pvactuel2; // variable pour remplir le vide de la barre de vie
        printf("("); 
        while(pvactuel2>0){
            printf("❤");
            pvactuel2--;
        }
        while(pvvide2>0){
            printf("_");
            pvvide2--;
        }
        printf(")(%.2f)\n", equipe2->membres[i].pvcourant);
        // afficher la jauge de chaque champion
        int jaugeactuel1=equipe1->membres[i].jaugeactuelle; // variable pour afficher la jauge de vie
        int jaugemax1=equipe1->membres[i].jaugemax;;
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
        printf(")%*s", 40, "");
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
        printf(")\n"); 
    }
}





void afficherEquipeChamp(Champ tab[], int deja_pris[]){  // Affichage des champions pour la selection
    for (int i=0; i<10; i++) { 
        if (deja_pris[i]==1){                           // Vérifie si le champion é déjà été choisir pour proposer un affichage différent en conséquence
            printf("%d - %s (PV:%.2f ATT:%.2f DEF:%.2f AGI:%.2f VIT:%.2f) (DEJA PRIS).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        } else {
            printf("%d - %s (PV:%.2f ATT:%.2f DEF:%.2f AGI:%.2f VIT:%.2f).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        }
    }
}
