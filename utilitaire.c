#include "principal.h"

void getchamp(Champ tab[]){
    // recupere les champions depuis le fichier champions.txt et les stocke dans le tableau tab
    FILE* fp=fopen("champions.txt", "r"); // Ouvre le fichier champions.txt en mode lecture
    if(fp!= NULL){
        char string[99]; // tableau de char pour stocker les lignes du fichier
        for(int i=0; i<10; i++){
            // on recupere les informations de chaque champion lignes par lignes
            fgets(string, 99, fp); // lit une ligne du fichier
            strcpy(tab[i].nom, string);
            fgets(string, 99, fp);
            tab[i].pvmax=atoi(string);
            fgets(string, 99, fp);
            tab[i].att=atoi(string);
            fgets(string, 99, fp);
            tab[i].def=atoi(string);
            fgets(string, 99, fp);
            tab[i].agilite=atoi(string);
            fgets(string, 99, fp);
            tab[i].vitesse=atoi(string);
            fgets(string, 99, fp);
            tab[i].jaugemax=atoi(string);
            fgets(string, 99, fp);
            strcpy(tab[i].tech.nom, string);
            tab[i].pvcourant=tab[i].pvmax;
            tab[i].jaugeactuelle=0;
            tab[i].nbeffets=0;
            tab[i].tech.nbtactifs=0;
            for(int j=0; j<10; j++){
                tab[i].effets[j].duree=0;
                tab[i].effets[j].effet_statut=0;
            }
            tab[i].statut=1; // initialise à vivant
        }
        fclose(fp);
    }
    else{
        // si le fichier n'existe pas ou ne peut pas être ouvert, on affiche un message d'erreur et on quitte le programme
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    for (int i = 0; i < 10; i++) {
        // Nettoyage des noms de champions pour enlever les retours à la ligne
        nettoyerNom(tab[i].nom);
        nettoyerNom(tab[i].tech.nom);
    }
}

void vide_buffer(){
    // vide le buffer d'entrée pour éviter les erreurs de lecture
    while (getchar()!='\n'){
    }
}

void nettoyerNom(char* nom) {
    // Enlève le retour à la ligne
    int len = strlen(nom);
    if (len > 0 && nom[len - 1] == '\n') {
        nom[len - 1] = '\0';
    }
    while (len > 0 && nom[len - 1] == ' ') {
        nom[len - 1] = '\0';
        len--;
    }
}