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
    <<<<<<< HEAD
    tour(equipe1, equipe2);
=======
    int i=0;
    while(equipe1->nbchampvivant > 0 && equipe2->nbchampvivant > 0){ // tant que les deux equipes ont des champions vivants
    i++;
    tour(equipe1, equipe2);// Appelle la fonction tour pour chaque equipe
    printf("\n Fin du tour numéro %d\n", 1); // Affiche le numéro du tour
    printf("Appuyez sur une touche pour continuer...\n");
    getchar(); // Attend que l'utilisateur appuie sur une touche
    }
    if(equipe1->nbchampvivant == 0){
        printf("L'equipe %s a perdu bravo à l'equipe %s !\n", equipe1->nom, equipe2->nom);
    } else {
        printf("L'equipe %s a perdu bravo à l'equipe %s !\n", equipe2->nom, equipe1->nom);
    }
    printf("Fin du combat !\n");
>>>>>>> 87ecc0eacf6a277e30fda8b3f2027f3b9295cc36
    free(equipe1);
    free(equipe2);
    return 0;
}