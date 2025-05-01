#include "principal.h"

// void afficherChamp(Equipe *equipe){
//     for(int i=0; i<3; i++){
//         if(equipe->membres[i].statut == 0){
//             printf("%s |✖|", equipe->membres[i].nom);
//         }
//         else{
//             printf("%s |%d|", equipe->membres[i].nom, i+1);
//         }
//         printf("\n");
//         if(equipe->membres[i].nbeffets != 0){
//             for(int j=0; j<equipe->membres[i].nbeffets; j++){
//                 switch (equipe->membres[i].effets[j]) {
//                     case 1:
//                         printf("(U+2620");




void afficherEquipeChamp(Champ tab[], int deja_pris[]){
    for (int i=0; i<10; i++) {
        if (deja_pris[i]==1){
            printf("%d - %s (PV:%d ATT:%d DEF:%d AGI:%d VIT:%d) (DEJA PRIS).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
        } else {
            printf("%d - %s (PV:%d ATT:%d DEF:%d AGI:%d VIT:%d).\n",  i + 1, tab[i].nom, tab[i].pvmax, tab[i].att, tab[i].def, tab[i].agilite, tab[i].vitesse);
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

