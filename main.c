#include "principal.h"

int main(){
    srand(time(NULL)); // Initialisation de la fonction rand()
    //Initialisation des pointeurs de l'équipe 1 et 2
    Equipe* equipe1 = malloc(sizeof(Equipe));
    Equipe* equipe2 = malloc(sizeof(Equipe));
    if(!equipe1 || !equipe2){ // Vérification de l'allocation mémoire
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    printf("Bienvenue dans Cyberfight !\n");
    // int nbjoueurs;
    // // choix du nombre de joueurs
    // int verif, verif1;
    // do{
    //     printf("Voulez vous jouer a 1 ou 2 personnes ? (tapez 1 ou 2) !\n");
    //     verif=scanf("%d", &nbjoueurs);
    //     if (nbjoueurs != 1 && nbjoueurs != 2){
    //         printf("Veuillez entrer une valeur valide (1 ou 2): ");
    //     }
    //     vide_buffer();
    // }while ((nbjoueurs != 1 && nbjoueurs != 2) || verif!=1); // vérifie que le nombre de joueurs est valide
    //début du jeu à 1 joueur
    // if(nbjoueurs == 1){
    //     printf("Vous avez choisi de jouer seul !\n");
    //     int difficulte;
    //     // choix de la difficulté de l'IA
    //     do{
    //         printf("Choisissez le niveau de difficulte de l'IA ! (1:noob, 2:facile ou 3:moyen)\n");
    //         verif1=scanf("%d", &difficulte);
    //         if (difficulte<1 || difficulte>3){
    //             printf("Veuillez entrer une valeur valide (1, 2 ou 3): ");
    //         }
    //         vide_buffer();
    //     } while (difficulte<1 || difficulte>3 || verif1!=1);
    //     if(difficulte == 1){
    //         printf("Vous avez choisi le niveau de difficulte noob !\n");
    //     }
    //     else if(difficulte == 2){
    //         printf("Vous avez choisi le niveau de difficulte facile !\n");
    //     }
    //     else{
    //         printf("Vous avez choisi le niveau de difficulte moyen (bon courage !) !\n");
    //     }
    //     //demande le nom de l'équipe
    //     do{
    //         printf("Rentrez votre nom d'equipe ! (20 caracteres au maximum)\n");
    //         scanf("%s", equipe1->nom);
    //         if(strlen(equipe1->nom) > 20){
    //             printf("Veuillez entrer un nom d'equipe valide (20 caracteres maximum): ");
    //         }
    //     }
    //     while (strlen(equipe1->nom) > 20); //verifie que le nom de l'équipe est valide
    //     printf("Bonjour %s\n", equipe1->nom);
    //     strcpy(equipe2->nom, "IA"); // Initialise le nom de l'IA
    //     printf("Choisissez vos champions afin de former votre equipe !\n");
    //     printf("Pour cela vous devez choisir 1 champion chacun votre tour jusqu'a ce que vous ayez 3 champions.\n");
    //     Champ liste[10];
    //     getchamp(liste); //récupère la liste des champions depuis le fichier champions.txt
    //     selectionia(liste, equipe1, equipe2); // Appelle la fonction pour choisir les champions
    //     printf("Vos equipes sont pretes !\n");
    //     printf("Le combat commence !\n");
    //     // Debut du combat
    //     int i=0;
    //     while(equipe1->nbchampvivant > 0 && equipe2->nbchampvivant > 0){ // tant que les deux equipes ont des champions vivants le jeu continue
    //     i++;
    //     touria(equipe1, equipe2, difficulte);// Appelle la fonction touria pour chaque equipe
    //     printf("\n Fin du tour numero %d\n", i); // Affiche le numéro du tour
    //     printf("Appuyez sur la touche entree pour continuer...\n");
    //     getchar(); // Attend que l'utilisateur appuie sur entrée
    //    }//verification de fin de combat
    //     if(equipe1->nbchampvivant == 0){
    //         printf("L'equipe %s a perdu bravo à l'equipe %s !\n", equipe1->nom, equipe2->nom);
    //     } else {
    //         printf("L'equipe %s a perdu bravo à l'equipe %s !\n", equipe2->nom, equipe1->nom);
    //     }
    //     //fin du combat
    // }
    // //début du jeu à 2 joueurs
    // else{
        // choix du nom de l'équipe 1 puis de l'équipe 2
        printf("Vous avez choisi de jouer a deux !\n");
        printf("Rentrez vos noms d'equipes ! (20 caracteres au maximum)\n");
        do{
            printf("Equipe 1: ");
            scanf("%s", equipe1->nom);
            if(strlen(equipe1->nom) > 20){
                printf("Veuillez entrer un nom d'equipe valide (20 caracteres maximum): ");
            }
        }while (strlen(equipe1->nom) > 20); //verifie que le nom de l'équipe est assez court
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
        }while ((strlen(equipe2->nom) > 20) || (strcmp(equipe1->nom, equipe2->nom) == 0)); //verifie que le nom de l'équipe est assez court et différent de l'équipe 1
        printf("Bonjour %s\n", equipe2->nom);
        printf("Choisissez vos champions afin de former votre equipe !\n");
        printf("Pour cela vous devez choisir 1 champion chacun votre tour jusqu'a ce que vous ayez 3 champions.\n");
        Champ liste[10];
        getchamp(liste); //récupère la liste des champions depuis le fichier champions.txt
        selection(liste, equipe1, equipe2); // Appelle la fonction pour choisir les champions
        printf("Vos equipes sont pretes !\n");
        printf("Le combat commence !\n");
        int i=0;
        while(equipe1->nbchampvivant > 0 && equipe2->nbchampvivant > 0){ // tant que les deux equipes ont des champions vivants
        i++;
        tour(equipe1, equipe2);// Appelle la fonction tour pour chaque equipe
        printf("\n Fin du tour numero %d\n", i); // Affiche le numéro du tour
        printf("Appuyez sur entree pour continuer...\n");
        getchar(); // Attend que l'utilisateur appuie sur entrée
        }//verification de fin de combat
        if(equipe1->nbchampvivant == 0){
            printf("L'equipe %s a perdu bravo a l'equipe %s !\n", equipe1->nom, equipe2->nom);
        } 
        else if(equipe2->nbchampvivant == 0){
            printf("L'equipe %s a perdu bravo a l'equipe %s !\n", equipe2->nom, equipe1->nom);
        }
    // }
    printf("Fin du combat !\n");
    printf("Merci d'avoir joue a Cyberfight !\n");
    // libération de la mémoire
    free(equipe1);
    free(equipe2);
    return 0;
}