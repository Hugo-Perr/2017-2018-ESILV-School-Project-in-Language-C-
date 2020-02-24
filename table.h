#ifndef VECTOR_H
#define VECTOR_H
#include <stdbool.h>



// Definition du type structure 'fonctionnaire'
typedef struct _fonctionnaire
{
    char * concatenation;   // concatenation de 6 charactères du nom et du prenom
    char * nom;
    char * prenom;
    int salaire;
} fonctionnaire ;



/*____________________________________________________________________________________________________________________________________________________*/
/*----------------------------------   PARTIE 0 : FONCTIONS PROPRES A L'UTILISATION DES VECTEURS   --------------------------------------------------*/


//  définition du type structuré 'vector'
typedef struct
{
	unsigned int logic_size;
	unsigned int physical_size;
	fonctionnaire  * content;
} vector;

/*
 * Fonction qui crée dynamiquement vecteur, dont le contenu est vide (i.e. sans élément).
 * Retour : un pointeur sur le vecteur créé
 */
vector * create_vector(); //


/*
 * Fonction qui teste si le vecteur est vide ou non
 * Paramètre p_vec : le (pointeur en accès en lecture seule sur le) vecteur à tester
 * Retour : true si ne contient pas d'élément ou si p_vec est NULL; false sinon
 */
bool is_null_or_empty(vector const * p_vec);


/*
 * Fonction qui ajoute un élément de type fonctionnaire à un vecteur
 * Paramètre element : l'élément à ajouter ATTENTION : n'est pas un pointeur ICI
 * Paramètre p_vec : le (pointeur sur le) vecteur dans lequel ajouter
 * Retour : true si l'ajout a pu se faire ; false sinon
 */
bool add(fonctionnaire element, vector * p_vec); // ATTENTION element n'est pas un pointeur ICI



/*____________________________________________________________________________________________________________________________________________________*/
/*----------------------------------   PARTIE 0 (BIS) FONCTIONS NECESSAIRES UTILISATION TABLE *  --------------------------------------------------*/

void  initialisation_base_taille(int*base,int*taille); // affecte les valeurs entrees par l'utiisateur aux entiers base et taille

void initialisation_table(vector table[], int taille);

void afficher_table(vector table[], int taille, int index_debut, int index_fin); // utilisée pour afficher la table entre 2 index

/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 1 INDEX   ----------------------------------------------------------------------*/

char * concatenation (char* nom, char*prenom); // concatene un nom et un prenom en une chaine de 6 characteres

long long int puissance(long long int x, int n);//renvoie x a la puissance n

long long int calcul_index(int base, int taille,char* s); // calcule l'index correspondant a la base, taille et concatenation du fonctionnaire

void fonctionnalite_index(int base, int taille) ; // gere les printf et renvoie l'index correspondant au nom/prenom donne par l'utilisateur (sans considerer la table)


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 2 AJOUTER   ----------------------------------------------------------------------*/

bool comparer_2_chaines_char (char * chaine_1, char* chaine_2); // true si chaines char identiques

fonctionnaire * creer_fonctionnaire(char*nom,char*prenom,int salaire); // cree 1 element structure a partir des informations recues

bool est_deja_present (vector table[],char * nom, char* prenom, long long int index); // true si fonctionnaire deja present dans la table

int nombre_character_max (char *chaine_1, char* chaine_2); // nbr de charactere maximum que l'on peut comparer entre les deux chaines

bool chaines_identiques (char * chaine_1,char * chaine_2, int taille); // taille etant le nombre de charactere ou l'on verifiera identique ou non

void mettre_fonct_au_rang(fonctionnaire  element, vector * p_vect, int rang); // range le fonctionnaire au bon endroit dans la table

void classer_fonctionnaire_alphab (vector table[], long long int index); // classe la table de fonctionnaire d'un certain vecteur

bool ajouter(vector table[],fonctionnaire fonctionnaire_a_ajouter, int base, int taille_table); // Ajoute le fonct a la fin de la table SANS LA TRIER !

void fonctionnalite_ajouter(int base, int taille_table, vector table[]); // Fonctionnalite finale avec les scanf ...


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------   PARTIE 3 : CHARGER    ----------------------------------------------------------------------*/

void lire_ligne_chargee(char chaine[], char * nom, char* prenom, int * deplacement_salaire); // separe le nom du prenom et du salaire d'une chaine de characteres

void fonctionnalite_charger(vector table[],int base, int taille); // fonctionnalite finale.


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------   PARTIE 4  : AFFICHER SALAIRE    ----------------------------------------------------------------------*/

void fonctionnalite_afficher_salaire(vector table[],int base,int taille); // recherche le fonctionnaire dans le tableau interne correspondant au vecteur de son index.


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 5 : AFFICHER ENTRE  ----------------------------------------------------------------------*/

void fonctionnalite_afficher_entre (vector table[],int taille); // appel la fonction afficher_table definie plus en haut

/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 7 : NOMBRE MOYEN D'ELEMENTS  ----------------------------------------------------------------------*/

void compteur_element_si_conflit(vector table[], int taille); // affiche le nombre d'element par index si conflit



/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 8 : SUPPRIMER  ----------------------------------------------------------------------*/

bool chaines_totalement_id (char* chaine_1,char* chaine_2); // true si chaines completement identiques

bool supprimer_fonctionnaire(vector table[], int taille,int base, char* nom, char* prenom, long long int index);

void fonctionnalite_supprimer_fonctionnaire(vector table[], int taille, int base);


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 9 : SUPPRIMER ENTRE ----------------------------------------------------------------------*/

void fonctionnalite_supprimer_entre(vector table[], int taille, int base);

/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 10 :  ----------------------------------------------------------------------*/

void quitter(vector table[], int taille, int base);


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------    MENU     ----------------------------------------------------------------------*/

void afficher_menu(int base, int taille, vector  table_de_vecteurs[]); // affichage du menu et des choix

void programme_complet(); // seul et unique fonction a lancer dans le main















//-------------------------------------PARTIE 1 : INDEX  --------------------------------------------------------------------------------------------------------





// Cette fonction concatenation associe a chaque NOM et PRENOM une chaine de 6 charactères, si possible contenant les 4 premiers characteres du NOM et 2 du PRENOM.
// La concatenation retournee est composee uniquement de characteres en minuscule.
char * concatenation (char* nom, char*prenom);



// Afin de calculer l'index, il faut la fonction puissance qui n'existe pas en C (en dehors de l'inclusion de certaines fonctions)..
long long int puissance(long long int x, int n);


//Calcul de l'index
long long int calcul_index(int base, int taille,char* s);


// Fonction qui renvoie l'index associe au NOM,PRENOM, du fonctionnaire et à la BASE et TAILLE de la table.
void fonctionnalite_index(int base, int taille);
fonctionnaire * creer_fonctionnaire(char*nom,char*prenom,int salaire);



void afficher_menu(int base, int taille, vector  table_de_vecteurs[]);















#endif
