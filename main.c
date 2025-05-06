#include "principal.h"

int main(){
    srand(time(NULL)); // Initialisation de la fonction rand()
    Equipe* equipe1 = malloc(sizeof(Equipe));
    Equipe* equipe2 = malloc(sizeof(Equipe));
    printf("Bienvenue dans Cyberfight !\n");
    int nbjoueurs;
    // choix du nombre de joueurs
    do{
        printf("Voulez vous jouer a 1 ou 2 personnes ? (tapez 1 ou 2) !\n");
        scanf("%d", &nbjoueurs);
        if (nbjoueurs != 1 && nbjoueurs != 2){
            printf("Veuillez entrer une valeur valide (1 ou 2): ");
        }
    }while (nbjoueurs != 1 && nbjoueurs != 2);
    if(nbjoueurs == 1){
        printf("Vous avez choisi de jouer seul !\n");
        int difficulte;
        do{
            printf("Choisissez le niveau de difficulte de l'IA ! (1:noob, 2:facile ou 3:moyen)\n");
            scanf("%d", &difficulte);
            if (difficulte<1 || difficulte>3){
                printf("Veuillez entrer une valeur valide (1, 2 ou 3): ");
            }
        }
        while (difficulte<1 || difficulte>3);
        if(difficulte == 1){
            printf("Vous avez choisi le niveau de difficulte noob !\n");
        }
        else if(difficulte == 2){
            printf("Vous avez choisi le niveau de difficulte facile !\n");
        }
        else{
            printf("Vous avez choisi le niveau de difficulte moyen (bon courage !) !\n");
        }
        do{
            printf("Rentrez votre nom d'equipe ! (20 caracteres au maximum)\n");
            scanf("%s", equipe1->nom);
            if(strlen(equipe1->nom) > 20){
                printf("Veuillez entrer un nom d'equipe valide (20 caracteres maximum): ");
            }
        }
        while (strlen(equipe1->nom) > 20);
        printf("Bonjour %s\n", equipe1->nom);
        strcpy(equipe2->nom, "IA"); // Initialise le nom de l'IA
        printf("Choisissez vos champions afin de former votre equipe !\n");
        printf("Pour cela vous devez choisir 1 champion chacun votre tour jusqu'a ce que vous ayez 3 champions.\n");
        Champ liste[10];
        getchamp(liste);
        selectionia(liste, equipe1, equipe2);
        printf("Vos equipes sont pretes !\n");
        printf("Le combat commence !\n");
        int i=0;
        while(equipe1->nbchampvivant > 0 && equipe2->nbchampvivant > 0){ // tant que les deux equipes ont des champions vivants
        i++;
        touria(equipe1, equipe2, difficulte);// Appelle la fonction touria pour chaque equipe
        printf("\n Fin du tour numero %d\n", 1); // Affiche le numéro du tour
        printf("Appuyez sur une touche pour continuer...\n");
        getchar(); // Attend que l'utilisateur appuie sur une touche
        }
        if(equipe1->nbchampvivant == 0){
            printf("L'equipe %s a perdu bravo à l'equipe %s !\n", equipe1->nom, equipe2->nom);
        } else {
            printf("L'equipe %s a perdu bravo à l'equipe %s !\n", equipe2->nom, equipe1->nom);
        }
    }
    else{
        printf("Vous avez choisi de jouer a deux !\n");
        // choix du nom de l'équipe 1 puis de l'équipe 2
        printf("Rentrez vos noms d'equipes ! (20 caracteres au maximum)\n");
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
    }
    printf("Fin du combat !\n");
        free(equipe1);
        free(equipe2);
        return 0;
}