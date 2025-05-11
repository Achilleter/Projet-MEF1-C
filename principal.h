#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { // Effets de statistiques possibles
    boost_att = 1,
    boost_def,
    boost_vitesse,
    soin,
    renforcement
} EffetStat;

typedef enum { // Effets de statut possibles
    poison = 1,
    stun,
    provocation,
    invincibilite,
    renvoie_degats,
    execute
} EffetStatut;

typedef struct { // Effets de statut actifs sur un champion
    EffetStatut effet_statut;
    int duree;
} EffetActif;

typedef struct { // Techniques spéciales
    char nom[100];                                    
    int nbtactifs;                          
} Techniquespe;

typedef struct { // Caractéristiques d'un champion
    float pvcourant;
    float pvmax;
    float att;
    float def;
    float agilite;
    float vitesse;
    EffetActif effets[10];
    int nbeffets;
    Techniquespe tech;
    float jaugeactuelle;
    float jaugemax;
    int statut; //mort ou vivant
    char nom[100];
} Champ;

typedef struct { // Caractéristiques d'une équipe
    char nom[20];
    Champ membres[3];
    int nbchampvivant; //nombre de champions vivants dans l'équipe
    int boolia; // 1 si IA, 0 si joueur
} Equipe;
// fonctions de notre programme
float attaque(Champ *champatt, Champ *champdef);
void degatseffetStatut(Champ *champ);
void appeffetStatut(Champ *champ, EffetStatut effetstatut, int duree);
void appeffetStat(Champ *champ, EffetStat effetstat, float valeur);
void triParVit(Equipe *e1, Equipe *e2, Champ *tab[6]);
int memeEquipe(Champ* champ, Equipe* e1);
Champ *choixCible(Champ* att, Equipe* e1, Equipe* e2);
void tour (Equipe* e1, Equipe* e2);
void berserk(Champ* xavier, Equipe* allie);
void flashbacks(Champ* nathalie, Champ* allie1, Champ* allie2);
void bourreau(Champ* zed, Equipe* ennemi, Equipe* allie);
void muraille(Champ* smasheur);
void cadeau_empoisonne(Champ* steve, Equipe* ennemi, Equipe* allie);
void fossoyeur_des_mondes(Champ* booga);
void cryogenese(Champ* sandrine, Equipe* ennemi);
void scierculaire(Champ* annesophie, Equipe* ennemi, Equipe* allie);
void cicatrices_eternels(Champ* gaby, Equipe* ennemi, Equipe* allie);
void reinitialisation(Champ* clara, Champ* allie1, Champ* allie2, Equipe* allies, Equipe* ennemi);
void getchamp(Champ tab[]);
void vide_buffer();
void selection(Champ tous[], Equipe* e1, Equipe* e2);
void afficherEquipeChamp(Champ tab[], int deja_pris[]);
void affichageCombat(Equipe *equipe, Equipe *equipe2, Champ* joueur);
void nettoyerNom(char* nom);
void selectionia(Champ tous[], Equipe* e1, Equipe* e2);
void touria(Equipe* e1, Equipe* e2, int difficulte);
void extermination(Champ* annesophie,Champ* zed, Equipe* adversaires);
void sacrifice_fraternel(Champ* xavier, Champ* steve);
void retour_a_la_haine(Champ* gaby, Champ* clara, Equipe* adversaires, Equipe* allie);
void suppressionEffetStatut(Champ* champ, int numeffet);