#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Champ getchamp(char nom[20],Champ champ){
    FILE* fp=fopen("champion.txt", "r");
    char string[100];
    while(fgets(string, 20, fp)!=NULL){
        if(strcmp(string, nom) == 0){
            strcpy(champ.nom, string);
            fgets(string, 20, fp);
            champ.pvmax=atoi(string);
            fgets(string, 20, fp);
            champ.att=atoi(string);
            fgets(string, 20, fp);
            champ.def=atoi(string);
            fgets(string, 20, fp);
            champ.agilite=atoi(string);
            fgets(string, 20, fp);
            champ.vitesse=atoi(string);
            fgets(string, 20, fp);
            champ.tech.nom=string;
            fgets(string, 20, fp);
            champ.tech.nom=string;
            champ.pvcourant=champ.pvmax;
            champ.jauge=0;
            champ.nbeffets=0;
            champ.statut=1; // vivant
        }
    }
    fclose(fp);
    return champ;
}