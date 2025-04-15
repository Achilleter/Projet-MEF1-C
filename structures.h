typedef enum {
    boost_att = 1,
    boost_def,
    boost_vitesse,
    soin
} EffetStat;

typedef enum {
    poison = 1,
    stun,
    silence,
    gel,
    invincibilite,
    renvoie_degats
} EffetStatut;

typedef struct {
    EffetStat effet_stat;
    EffetStatut effet_statut;
    int duree;
    float valeur;
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

