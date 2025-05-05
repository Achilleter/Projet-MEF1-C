#include "principal.h"

void afficherChamp(Equipe *equipe1, Equipe *equipe2){
    printf("%s%*s%s\n\n", equipe1->nom, 40+strlen(equipe1->nom),"", equipe2->nom);
    for(int i=0; i<3; i++){
        if(equipe1->membres[i].statut == 0){
             printf("%s |✖|%*s%s |%d|", equipe1->membres[i].nom, 40+strlen(equipe1->nom)-strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        else if(equipe2->membres[i].statut == 0){
            printf("%s |%d|%*s%s |✖|", equipe1->membres[i].nom, i+1, 40+strlen(equipe1->nom)-strlen(equipe1->membres[i].nom), "",equipe2->membres[i].nom);
        }
        else{
            printf("%s |%d|%*s%s |%d|", equipe1->membres[i].nom, i+1, 40+strlen(equipe1->nom)-strlen(equipe1->membres[i].nom), "", equipe2->membres[i].nom, i+1);
        }
        printf("\n");
        int nbeffets1=equipe1->membres[i].nbeffets;
        int nbeffets2=equipe2->membres[i].nbeffets;
        while(nbeffets1!=0 || nbeffets2!=0){
            for(int j=0; j<equipe1->membres[i].nbeffets; j++){
                switch(equipe1->membres[i].effets[j].effet_statut){
                    case 1:
                        printf("(poison) ");
                        break;
                    case 2:
                        printf("(stun) ");
                        break;
                    case 3:
                        printf("(provocation) ");
                        break;
                    case 4:
                        printf("(invincibilite) ");
                        break;
                    case 5:
                        printf("(renvoie_degats) ");
                        break;
                    case 6:
                        printf("(bourreau) ");
                        break;
                    default:
                        break;
               }
            }
                nbeffets1--;
            if(nbeffets1<0){
                nbeffets1=0;
            }
            printf("%*s", 40+strlen(equipe1->nom)-strlen(equipe1->membres[i].nom), "");
            for(int j=0; j<equipe2->membres[i].nbeffets; j++){
                switch(equipe2->membres[i].effets[j].effet_statut){
                    case 1:
                        printf("(poison) ");
                        break;
                    case 2:
                        printf("(stun) ");
                        break;
                    case 3:
                        printf("(provocation) ");
                        break;
                    case 4:
                        printf("(invincibilite) ");
                        break;
                    case 5:
                        printf("(renvoie_degats) ");
                        break;
                    case 6:
                        printf("(bourreau) ");
                        break;
                    default:
                        break;
                }
            }
            nbeffets2--;
            if(nbeffets2<0){
                nbeffets2=0;
            }
        }
        printf(" \n");
        // Affichage des PV sous les membres de l'équipe 1
        int pvactuel1=equipe1->membres[i].pvcourant/20;
        printf("("); 
        while(pvactuel1>0){
            printf("#");
            pvactuel1--;
        }
        printf(")");
        // Affichage des PV sous les membres de l'équipe 2
        int pvactuel2 = equipe2->membres[i].pvcourant/20;
        printf("%*s(", 40+strlen(equipe1->nom)-strlen(equipe1->membres[i].nom), "");
        while (pvactuel2>0){
            printf("#");
            pvactuel2--;
        }
        printf(")\n");
    }
}





void afficherEquipeChamp(Champ tab[], int deja_pris[]){
    for (int i=0; i<10; i++) {
        if (deja_pris[i]==1){
            printf("%d - %s (PV:%.2f ATT:%.2f DEF:%.2f AGI:%.2f VIT:%.2f) (DEJA PRIS).\n\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        } else {
            printf("%d - %s (PV:%.2f ATT:%.2f DEF:%.2f AGI:%.2f VIT:%.2f).\n\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        }
    }
}






// //Base pour affichage:
// //void afficherChamp(const Champ *c, int index, int prochain) {
//     // 1. Nom + numéro + statut
//     printf("%-12s |%d|", c->nom, index + 1);
//     if (c->statut == 0)
//         printf(" ✖");
//     else
//         printf("   "); // pour garder l’alignement même si vivant
//     if (prochain)
//         printf(" <"); // marqueur du prochain tour
//     printf("\n");

//     // 2. Effets spéciaux alignés
//     printf(" %-12s(", "");  // 12 espaces d'alignement
//     for (int i = 0; i < c->nbeffets; i++) {
//         printf("%s", effetStatutToEmoji(c->effets[i].effet_statut));
//     }
//     printf(")\n");

//     // 3. Barre de vie
//     printf(" %-12s", "");
//     printBarreVie(c->pvcourant, c->pvmax);
//     printf("\n");

//     // 4. Barre d'effets
//     printf(" %-12s", "");
//     printBarreEffets();
//     printf("\n\n");
// }


// void afficherEquipeChamp(Champ tab[], int deja_pris[]){
//     for (int i=0; i<10; i++) {
//         if (deja_pris[i]==1){
//             printf("%d - %s (PV:%d ATT:%d DEF:%d AGI:%d VIT:%d) (DEJA PRIS).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
//         } else {
//             printf("%d - %s (PV:%d ATT:%d DEF:%d AGI:%d VIT:%d).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
//         }
//     }
// }

