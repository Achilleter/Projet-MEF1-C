#include "principal.h"

int main(){
    Equipe equipe1, equipe2;
    printf("Bienvenue dans Cyberfight !\n");
    printf("Rentrez vos noms d'équipes ! (20 caractères au maximum)\n");
    printf("Équipe 1: ");// choix du nom de l'équipe 1 puis de l'équipe 2
    scanf("%s", equipe1.nom); 
    do{
        printf("Veuillez entrer un nom d'équipe valide (20 caractères maximum): ");
        scanf("%s", equipe1.nom);
    }while (strlen(equipe1.nom) > 20);
    printf("\n %s\n", equipe1.nom);
    printf("Équipe 2: ");
    scanf("%s", equipe2.nom);
    do{
        printf("Veuillez entrer un nom d'équipe valide (20 caractères maximum): ");
        scanf("%s", equipe2.nom);
    }while (strlen(equipe2.nom) > 20);
    printf("%s\n", equipe2.nom);
    printf("Choisissez vos champions afin de former votre équipe !\n");
    printf("Pour cela vous devez choisir 1 champion chacun votre tour jusqu'à ce que vous ayez 3 champions.\n");
    for(int i=0; i<3; i++){
        printf("Équipe 1, choisissez votre champion n°%d: ", i+1);
        choixChamp(&equipe1.membres[i]);
        printf("Équipe 2, choisissez votre champion n°%d: ", i+1);
        choixChamp(&equipe2.membres[i]);
    }
    printf("Vos équipes sont prêtes !\n");
    afficherEquipe(&equipe1);// Affiche l'équipe 1
    afficherEquipe(&equipe2);
    printf("Le combat commence !\n");
    tour(&equipe1, &equipe2);// Appelle la fonction tour pour chaque équipe
}