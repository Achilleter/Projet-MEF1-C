#include "principal.h"

Champ getchamp(char nom[20],Champ champ){
    FILE* fp=fopen("combattants.txt", "r");
    char string[100];
    if(fp!= NULL){
        while(fgets(string, 99, fp)!=NULL){
            if(strcmp(string, nom) == 0){
                strcpy(champ.nom, string);
                fgets(string, 99, fp);
                champ.pvmax=atoi(string);
                fgets(string, 99, fp);
                champ.att=atoi(string);
                fgets(string, 99, fp);
                champ.def=atoi(string);
                fgets(string, 99, fp);
                champ.agilite=atoi(string);
                fgets(string, 99, fp);
                champ.vitesse=atoi(string);
                fgets(string, 99, fp);
                champ.tech.nom=string;
                fgets(string, 99, fp);
                champ.tech.nom=string;
                champ.pvcourant=champ.pvmax;
                champ.jauge=0;
                champ.nbeffets=0;
                champ.statut=1; // vivant
            }
        }
        fclose(fp);
    }
    else{
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    return champ;
}