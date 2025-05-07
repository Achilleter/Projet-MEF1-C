#include "principal.h"

void affichageCombat(Equipe *equipe1, Equipe *equipe2){
    printf("%s%*s%s\n\n", equipe1->nom, 50-(int)strlen(equipe1->nom),"", equipe2->nom);
    for(int i=0; i<3; i++){
        if(equipe1->membres[i].statut == 0){
             printf("%s |✖|%*s%s |%d|", equipe1->membres[i].nom, 46-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        else if(equipe2->membres[i].statut == 0){
            printf("%s |%d|%*s%s |✖|", equipe1->membres[i].nom, i+1, 46-(int)strlen(equipe1->membres[i].nom), "",equipe2->membres[i].nom);
        }
        else{
            printf("%s |%d|%*s%s |%d|", equipe1->membres[i].nom, i+1, 46-(int)strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        printf("\n");
        int nbeffets1=equipe1->membres[i].nbeffets;
        int nbeffets2=equipe2->membres[i].nbeffets;
        int effetduree=0;
        if(nbeffets1==0){
            printf("(Chill Guy)");
        }
        if(nbeffets2==0){
            printf("%*s(Chill Guy)", 39, "");
        }
        while(nbeffets1!=0 || nbeffets2!=0){
            switch(equipe1->membres[i].effets[nbeffets1-1].effet_statut){
                case 1:
                    effetduree=equipe1->membres[i].effets[nbeffets1-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("poison");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 2:
                    effetduree=equipe1->membres[i].effets[nbeffets1-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("stun");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 3:
                    effetduree=equipe1->membres[i].effets[nbeffets1-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("provocation");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 4:
                    effetduree=equipe1->membres[i].effets[nbeffets1-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("invincibilite");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 5:
                    effetduree=equipe1->membres[i].effets[nbeffets1-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("renvoie_degats");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 6:
                    effetduree=equipe1->membres[i].effets[nbeffets1-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("bourreau");
                        effetduree--;
                    }
                    printf(")");
                    break;
                default:
                    break;
            }
            printf("%*s", 46-(int)strlen(equipe1->membres[i].nom), "");
            switch(equipe2->membres[i].effets[nbeffets2].effet_statut){
                case 1:
                    effetduree=equipe2->membres[i].effets[nbeffets2-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("poison");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 2:
                    effetduree=equipe2->membres[i].effets[nbeffets2-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("stun");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 3:
                    effetduree=equipe2->membres[i].effets[nbeffets2-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("provocation");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 4:
                    effetduree=equipe2->membres[i].effets[nbeffets2-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("invincibilite");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 5:
                    effetduree=equipe2->membres[i].effets[nbeffets2-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("renvoie_degats");
                        effetduree--;
                    }
                    printf(")");
                    break;
                case 6:
                    effetduree=equipe2->membres[i].effets[nbeffets2-1].duree;
                    printf("(");
                    while(effetduree>0){
                        printf("bourreau");
                        effetduree--;
                    }
                    printf(")");
                    break;
                default:
                    break;
            }
                nbeffets1--;
            if(nbeffets1<0){
                nbeffets1=0;
            }
            nbeffets2--;
            if(nbeffets2<0){
                nbeffets2=0;
            }
        }
        printf("\n");
        // Affichage des PV sous les membres de l'équipe 1
        int pvactuel1=equipe1->membres[i].pvcourant/20; // variable pour afficher la barre de vie
        int pvmax=20;
        int pvvide1=pvmax-pvactuel1; // variable pour remplir le vide de la barre de vie
        printf("("); 
        while(pvactuel1>0){
            printf("#");
            pvactuel1--;
        }
        while(pvvide1>0){
            printf(" ");
            pvvide1--;
        }
        printf(")(%.2f)%*s", equipe1->membres[i].pvcourant, 20, "");
        // Affichage des PV sous les membres de l'équipe 2
        int pvactuel2=equipe2->membres[i].pvcourant/20;
        int pvvide2=pvmax-pvactuel2; // variable pour remplir le vide de la barre de vie
        printf("("); 
        while(pvactuel2>0){
            printf("#");
            pvactuel2--;
        }
        while(pvvide2>0){
            printf(" ");
            pvvide2--;
        }
        printf(")(%.2f)\n", equipe2->membres[i].pvcourant);
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
