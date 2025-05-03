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
                strcpy(tab[i].tech.nom, string);
                tab[i].pvcourant=tab[i].pvmax;
                tab[i].jauge=0;
                tab[i].nbeffets=0;
                tab[i].statut=1; // vivant
                int j=0;
                while(j==0){
                    if(*(fgets(string, 1, fp))=='\n'){
                        j=1;
                    }
                }
            }
            fclose(fp);
        }
    else{
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
}

void vide_buffer(){
    while (getchar()!='\n'){
    }
}