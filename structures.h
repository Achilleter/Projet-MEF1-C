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
    char *nom;                     
    float valeur;                 
    char description[1000];
    int nbtactifs;                
    int nbtrechargement;          
    EffetStat effet_stat;         
    EffetStatut effet_statut;     
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
    float jauge;
    int statut; //mort ou vivant
    char nom[100];
} Champ;

typedef struct {
    char *nom;
    Champ membres[3];
} Equipe;

