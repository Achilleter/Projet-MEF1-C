#include "principal.h"

int main(){
    Equipe* equipe1 = malloc(sizeof(Equipe));
    Equipe* equipe2 = malloc(sizeof(Equipe));
    printf("Bienvenue dans Cyberfight !\n");
    printf("Rentrez vos noms d'equipes ! (20 caracteres au maximum)\n");
    // choix du nom de l'équipe 1 puis de l'équipe 2
    do{
        printf("Equipe 1: ");
        scanf("%s", equipe1->nom);
        if(strlen(equipe1->nom) > 20){
            printf("Veuillez entrer un nom d'equipe valide (20 caracteres maximum): ");
        }
    }while (strlen(equipe1->nom) > 20);
    printf("Bonjour %s\n", equipe1->nom);
    do{
        printf("Equipe 2: ");
        scanf("%s", equipe2->nom);
        if(strlen(equipe2->nom) > 20){
            printf("Veuillez entrer un nom d'equipe valide (20 caracteres maximum): ");
        }
        else if((strcmp(equipe1->nom, equipe2->nom) == 0)){
            printf("Veuillez entrer un nom d'equipe different de %s: ", equipe1->nom);
        }
    }while ((strlen(equipe2->nom) > 20) || (strcmp(equipe1->nom, equipe2->nom) == 0));
    printf("Bonjour %s\n", equipe2->nom);
    printf("Choisissez vos champions afin de former votre equipe !\n");
    printf("Pour cela vous devez choisir 1 champion chacun votre tour jusqu'a ce que vous ayez 3 champions.\n");
    Champ liste[10];
    getchamp(liste);
    selection(liste, equipe1, equipe2);
    printf("Vos equipes sont pretes !\n");
    printf("Le combat commence !\n");
    tour(equipe1, equipe2);
    free(equipe1);
    free(equipe2);
    return 0;
}