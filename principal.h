#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    boost_att = 1,
    boost_def,
    boost_vitesse,
    soin
} EffetStat;

typedef enum {
    poison = 1,
    stun,
    provocation,
    invincibilite,
    renvoie_degats,
    bourreau,
} EffetStatut;

typedef struct {
    EffetStatut effet_statut;
    int duree;
} EffetActif;

typedef struct {
    char nom[100];                                    
    char description[1000];
    int nbtactifs;                          
} Techniquespe;

typedef struct {
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

typedef struct {
    char nom[20];
    Champ membres[3];
} Equipe;

float attaque(Champ *champatt, Champ *champdef);
void degatseffetStatut(Champ *champ);
void appeffetStatut(Champ *champ, EffetStatut effetstatut, int duree);
void appeffetStat(Champ *champ, EffetStat effetstat, float valeur);
void triParVit(Equipe *e1, Equipe *e2, Champ *tab[6]);
int memeEquipe(Champ* champ, Equipe* e1);
Champ *choixCible(Champ* att, Equipe* e1, Equipe* e2);
void tour (Equipe* e1, Equipe* e2);
void berserk(Champ* xavier);
void flashbacks(Champ* nathalie, Champ* allie1, Champ* allie2);
void marqueduBourreau(Champ* zed, Champ* ennemi);
void murailleInfinie(Champ* smasheur);
void motivation(Champ* steve, Champ* allie1, Champ* allie2);
void fossoyeurdesMondes(Champ* booga);
void cryogenese(Champ* sandrine, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3);
void scierculaire(Champ* annesophie, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3);
void cicatricesEternels(Champ* gaby, Champ* ennemi1, Champ* ennemi2, Champ* ennemi3);
void reinitialisation(Champ* clara, Champ* allie1, Champ* allie2);
void getchamp(Champ tab[]);
void vide_buffer();
void selection(Champ tous[], Equipe* e1, Equipe* e2);
void afficherEquipeChamp(Champ tab[], int deja_pris[]);
void afficherChamp(Equipe *equipe);
void nettoyerNom(char* nom);