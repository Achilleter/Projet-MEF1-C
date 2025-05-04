#include "principal.h"

void getchamp(Champ tab[]){
    FILE* fp=fopen("champions.txt", "r");
    if(fp!= NULL){
        char string[99];
        for(int i=0; i<10; i++){
            fgets(string, 99, fp);
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
            for(int j=0; j<10; j++){
                tab[i].effets[j].duree=0;
                tab[i].effets[j].effet_statut=0;
            }
            tab[i].statut=1; // vivant
        }
        fclose(fp);
    }
    else{
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    for (int i = 0; i < 10; i++) {
        nettoyerNom(tab[i].nom);
    }
}

void vide_buffer(){
    while (getchar()!='\n'){
    }
}

void nettoyerNom(char* nom) {
    size_t len = strlen(nom);
    if (len > 0 && nom[len - 1] == '\n') {
        nom[len - 1] = '\0';
    }
}