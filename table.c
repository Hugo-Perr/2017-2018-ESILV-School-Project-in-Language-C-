#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 4 seules extensions autorisees (l'autre est #include <stdbool.h> )
#include "table.h"

/*____________________________________________________________________________________________________________________________________________________*/
/*----------------------------------   PARTIE 0 : FONCTIONS PROPRES A L'UTILISATION DES VECTEURS   --------------------------------------------------*/

vector* create_vector() //creation du vecteur
{
	vector* new_vector = (vector*) malloc( sizeof(vector) );

	if( new_vector != NULL )
	{
		new_vector->logic_size = 0;
		new_vector->physical_size = 0;
		new_vector->content = NULL;
	}

	return new_vector;
}

bool is_null_or_empty(vector const * p_vec)
{
	bool vide = true;
	if( (p_vec != NULL) && (p_vec->logic_size != 0) )  // <=> (p_vec->logic_size > 0) car de type unsigned int
	{
		// éventuellement vérifier que p_vec-> content != NULL..
		// mais normalement la fonction add a bien fait son job ;)

		vide = false;
	}
	return vide;
}


bool add(fonctionnaire element, vector * p_vec)
{
	bool ajout_ok = false;

	if(p_vec != NULL)
	{
		if(p_vec->logic_size < p_vec->physical_size ) // il reste de la place physique dans contenu
		{
			p_vec->content[p_vec->logic_size] = element; // rappel : les index dans intervalle [0, taille[
			p_vec->logic_size++;
		}
		else // il faut créer un tableau interne plus grand (d'une case)
		{
			fonctionnaire* new_tab = (fonctionnaire*) malloc( (p_vec->logic_size +1) * sizeof(fonctionnaire) );

			if( new_tab != NULL ) // malloc OK
			{
				// copie des élements contenus dans p_vec dans new_vector
				unsigned int i;
				for(i = 0 ; i < p_vec->logic_size ; i++)
				{
					new_tab[i] = p_vec->content[i];
				}

				// ajout du nouvel élement
				new_tab[i] = element;  // ici, i == p_vec->logic_size
				// Mise à jour du vecteur
				p_vec->logic_size++;
				p_vec->physical_size++;
				free(p_vec->content);     // libération mémoire de l'ancien tableau interne
				p_vec->content = new_tab; // association du tableau comme contenu du vecteur
				ajout_ok=true;
			}
		}
	}

	return ajout_ok;
}


/*____________________________________________________________________________________________________________________________________________________*/
/*----------------------------------   PARTIE 0 (BIS) FONCTIONS NECESSAIRES UTILISATION TABLE *  --------------------------------------------------*/

void  initialisation_base_taille(int*base,int*taille)
{
    printf("Quelle est la taille  ? : ");
    scanf("%d",taille);
    printf("Quelle est la base ? : ");
    scanf("%d",base);

}

void initialisation_table(vector table[], int taille)
{
    for (int i=0; i<taille; i++)
    {
        table[i].logic_size=0;
        table[i].physical_size=0;
        table[i].content=NULL;
    }
}


void afficher_table(vector table[], int taille, int index_debut, int index_fin)
{
    for (int i=index_debut; i<(index_fin+1) ; i++)
    {
        printf("________________________________________________________________________________________");
        printf("INDEX %d \n",i);
        printf("Logic size = %d    ;    Physic size = %d \n ",   table[i].logic_size ,    table[i].physical_size);

        int compteur_fonctionnaire = 0;
        for( compteur_fonctionnaire = 0 ; compteur_fonctionnaire < table[i].logic_size ; compteur_fonctionnaire++)
        {
            //fonctionnaire * point_tab = table[i].content ;
            printf("Fonctionnaire %d\n",compteur_fonctionnaire);

            if (is_null_or_empty(&(table[i])) == false) // si le vecteur correspondant à l'index n'est pas null ou vide : on peut afficher les fonctionnaires
            {
                char * nom_conc = table[i].content[compteur_fonctionnaire].concatenation;
                char * nom_ = table[i].content[compteur_fonctionnaire].nom;
                char * prenom_ = table[i].content[compteur_fonctionnaire].prenom;
                int salaire_ = table[i].content[compteur_fonctionnaire].salaire;
                printf("NOM CONCAT : %s\nNOM : %s\nPRENOM : %s\nSALAIRE : %d \n \n",  nom_conc  , nom_ , prenom_ , salaire_ );
            }
            else
            {
                printf("vecteur NULL ou vide \n");
            }
        }

        if (compteur_fonctionnaire==0)// ie si le vecteur table[i] est vide
        {
            printf("vecteur NULL ou vide. \n ");
        }
    }
    printf("\n \n \n \n");
}



/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 1 INDEX   ----------------------------------------------------------------------*/

char * concatenation (char* nom, char*prenom)
{
    char* concatenation = (char*) malloc (7*sizeof(char));
    int taille_nom = strlen(nom);

    if (concatenation!=NULL)
    {
        int i=0;
        while (i<7)
        {
            if (taille_nom<4) // cas ou le nom est trop court pour obtenir 4 lettres du nom et 2 du prenom
            {
                if (i<taille_nom)
                {
                    *(concatenation+i)=*(nom+i);
                }
                if(i>=taille_nom)
                {
                    *(concatenation+i)=*(prenom+i-taille_nom);
                }
            }

            if (taille_nom>=4) // cas ou le nom est assez long
            {
                if (i<4)
                {
                    *(concatenation+i)=*(nom+i);
                }
                if(i>=4)
                {
                    *(concatenation+i)=*(prenom+i-4);
                }
            }
            i+=1;
        }

        *(concatenation+6)='\0'; // on ferme la chaine de caractères
        return (concatenation);


    }
}

long long int puissance(long long int x, int n)
{
    if (n==0)
    {
        return 1;
    }
    else
    {
        long long int resultat = (x*puissance(x,n-1));
        return resultat;
    }
}

long long int calcul_index(int base, int taille,char* s)
{
    long long int index = 0;
    for (int i=0; i<6 ; i++)
    {
        long long int ajout_index =   *(s+i) * (puissance(base,i));
        index+= ajout_index;
    }
    return  index %(taille);
}

void fonctionnalite_index(int base, int taille)
{
    char * nom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    char * prenom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    printf("Quel Nom ? : ");
    scanf("%s",nom);
    printf("Quel Prenom ? : ");
    scanf("%s",prenom);

    char * s = concatenation(nom,prenom);
    long long int index = calcul_index(base,taille,s);

    printf("L'index correspondant est : %ld\n",index);
    printf("\n");
    printf("\n");
}



/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 2 AJOUTER   ----------------------------------------------------------------------*/

bool comparer_2_chaines_char (char * chaine_1, char* chaine_2) // true si chaines char identiques
{
    bool resultat_comparaison = false;
    if ( strlen(chaine_1) == strlen(chaine_2))
    {
        int taille = strlen(chaine_1);
        int i =0;
        while(*(chaine_1+i)==*(chaine_2+i)  && i<taille)
        {
            i++;
        }
        if (i == taille)
        {
            resultat_comparaison = true ;
        }
    }

    return resultat_comparaison;
}

fonctionnaire * creer_fonctionnaire(char*nom,char*prenom,int salaire) // cree 1 element structure a partir des informations recues
{
    fonctionnaire * new_fonct = (fonctionnaire*) malloc (sizeof(fonctionnaire));
    if (new_fonct!=NULL)
    {
        new_fonct->concatenation=concatenation(nom,prenom);
        new_fonct->nom=nom;
        new_fonct->prenom=prenom;
        new_fonct->salaire=salaire;

        return new_fonct;
    }
}

bool est_deja_present (vector table[],char * nom, char* prenom, long long int index) // true si fonctionnaire deja present dans la table
{
    bool resultat_recherche = false;
    char * nom_concat = concatenation(nom,prenom);

    vector * vecteur_index = &table[index];

    for (int i=0 ; i< table[index].logic_size ; i++)
    {
        if ( comparer_2_chaines_char( table[index].content[i].concatenation,   nom_concat )   ==   true)
        {
            resultat_recherche = true ;
        }
    }
    return resultat_recherche ;
}


int nombre_character_max (char *chaine_1, char* chaine_2) // nbr de charactere maximum que l'on peut comparer entre les deux chaines
{
    int resultat = strlen(chaine_1);
    if (strlen(chaine_2)<resultat)
    {
        resultat = strlen(chaine_2);
    }
    return resultat;
}

bool chaines_identiques (char * chaine_1,char * chaine_2, int taille) // taille etant le nombre de charactere ou l'on verifiera identique ou non
{
    bool identique = false ;
    int nbr_char_identiques = 0;
    for (int
         i=0; i<taille ; i++)
    {
        if (chaine_1[i]==chaine_2[i])
        {
            nbr_char_identiques ++;
        }
    }
    if (nbr_char_identiques==taille)
    {
        identique=true;
    }
    return identique ;
}


void mettre_fonct_au_rang(fonctionnaire  element, vector * p_vect, int rang) // range le fonctionnaire au bon endroit dans la table
{
    for (int i=rang ; i<p_vect->logic_size ; i++)
    {
        fonctionnaire fonct_temp = p_vect->content[i];
        p_vect->content[i] = element;
        element=fonct_temp;
    }
}


void classer_fonctionnaire_alphab (vector table[], long long int index) // classe la table de fonctionnaire d'un certain vecteur
{


    if (table[index].logic_size -1 >0) // dans le cas contraire, il est inutile de classer les fonctionnaires car il y en a 1 seul
    {
        char* nom_fonct_a_classer   =   table[index].content[table[index].logic_size - 1].nom ; // nom a range placé de maniere random en fin de tableau de fonctionnaire
        int nb_char_max ;
        char * nom_analyse ;
        int i = 0;
        bool est_a_gauche_dans_table = false ;


        while ( i<  (table[index].logic_size -1) && est_a_gauche_dans_table==false ) // i<logicsize-1 car le fonctionnaire a ranger est a la fin de la table ;
        {
            nom_analyse   =   table[index].content[i].nom ;
            nb_char_max =   nombre_character_max(nom_fonct_a_classer,  nom_analyse); // nbr de charactere maximum que l'on peut comparer entre les deux chaines
            int parcourir_nom   =   0;

            /* TEST si noms analyses sont identiques : cas particulier */
            bool nom_i_et_nom_a_classer_sont_identiques = chaines_identiques(nom_fonct_a_classer,nom_analyse,nb_char_max);
            if (nom_i_et_nom_a_classer_sont_identiques == true )
            {
                est_a_gauche_dans_table = true ; // par defaut on place le nom identique a gauche ; ca permet aussi de sortir de la boucle while immediatement
            }

            /* Parcourir le nom analyser et le comparer avec le nom du fonctionnaire a ranger */
            else
            {
                for (int k=0 ; k<nb_char_max ; k++ )
                {
                    if ((int) nom_analyse[k] > (int) nom_fonct_a_classer[k])
                    {
                        est_a_gauche_dans_table = true ;
                        k=nb_char_max;// permet de sortir de la boucle for immediatement
                    }

                    if ((int) nom_analyse[k] < (int) nom_fonct_a_classer[k])
                    {
                        i= i+1; // le mot analysé est avant celui que l'on veut ranger, on passe au mot suivant dans le tableau de fonctionnaires du vecteur
                        k=nb_char_max; // on sort de la bouvle for immediatement
                    }
                    // si aucuns des if n'est verifier c'est que les k premiers characteres sont identiques ; on passe au suivant
                }
            }
        }

    if (est_a_gauche_dans_table == true ) // alors le fonctionnaire devrait etre au ième rang de la table
    {
        mettre_fonct_au_rang(table[index].content[table[index].logic_size - 1],&table[index],i); // i car c'est a ce rang que le booleen est devenu true
    }
    // Dans le cas contraire  est_a_gauche_dans_table == false  : donc le fonctionnaire a range reste a droite de la table, a sa position initiale
}
}

bool ajouter(vector table[],fonctionnaire fonctionnaire_a_ajouter, int base, int taille_table) // Ajoute le fonct a la fin de la table SANS LA TRIER !
{
    bool ajout_reussi = false ;
    long long int  index = calcul_index(base,taille_table,fonctionnaire_a_ajouter.concatenation);
    bool present_dans_table = est_deja_present(table,fonctionnaire_a_ajouter.nom,fonctionnaire_a_ajouter.prenom,index);
    if(present_dans_table == false)
    {
        vector * vecteur_ou_ajouter = &(table[index]);
        bool reussi_add = add(fonctionnaire_a_ajouter,vecteur_ou_ajouter);
        if (reussi_add==true)
        {
            ajout_reussi = true ;
        }
    }
    return ajout_reussi ;
}

void fonctionnalite_ajouter(int base, int taille_table, vector table[]) // Fonctionnalite avec les scanf ...
{
    char * nom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    char * prenom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    int salaire =0 ;

    printf("Quel nom ? : ");
    scanf("%s",nom);
    printf("Quel prenom ? : ");
    scanf("%s",prenom);
    printf("Quel salaire ? : ");
    scanf("%d",&salaire);

    fonctionnaire fonctionnaire_a_ajouter = *creer_fonctionnaire(nom,prenom,salaire);
    bool ajout_reussi = ajouter(table,fonctionnaire_a_ajouter,base,taille_table);

    if ( ajout_reussi == true )
    {
        printf("Reussite de l'ajout\n");
        classer_fonctionnaire_alphab(table,calcul_index(base,taille_table,fonctionnaire_a_ajouter.concatenation)); // on range le dernier element ajoute dans la table
    }

    else
    {
        printf("Echec de l'ajout.\n");
    }
}



/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------   PARTIE 3 : CHARGER    ----------------------------------------------------------------------*/

void lire_ligne_chargee(char chaine[], char * nom, char* prenom, int * deplacement_salaire)
{
    int salaire;
    char  char_analyse = chaine[0];
    int compteur = 0;

    /*  Lecture du NOM  */
    while (char_analyse!=' ')
    {
        nom[compteur] = char_analyse ;
        compteur++;
        char_analyse=chaine[compteur];
    }
    nom[compteur]='\0';
    compteur++; // passage au 1er char du prenom
    char_analyse=chaine[compteur];

    /*  Lecture du PRENOM  */
    while (char_analyse!=' ')
    {
        prenom[compteur-strlen(nom)-1]=char_analyse;
        compteur++;
        char_analyse=chaine[compteur];
    }
    prenom[compteur-strlen(nom)-1]='\0';

    /*  Lecture du SALAIRE  */
    compteur++; // on rajoute 1 a cause de l'espace entre le prenom et le salaire
    int taille_salaire = strlen(chaine)-compteur-1;
    for(int i=0; i<taille_salaire; i++)
    {
        *deplacement_salaire = (*deplacement_salaire) * 10 + ( chaine[compteur+i] - '0' );// convertion decimal en nombre
	}
}


void fonctionnalite_charger(vector table[],int base, int taille)
{
    FILE* fichier_chicago = NULL; // initialisation du pointeur à NULL
    int nombre_fonctionnaires_max = 0;
    int nombre_fonctionnaires_a_charger = 0;
    fonctionnaire element_a_charger ;

    fichier_chicago = fopen("Chicago.txt","r"); // ouverture du fichier txt en lecture seule
    if (fichier_chicago!=NULL)
    {
        fscanf(fichier_chicago,"%d",&nombre_fonctionnaires_max);
        while (nombre_fonctionnaires_a_charger<=0 || nombre_fonctionnaires_a_charger>nombre_fonctionnaires_max) // boucle qui permet de s'assurer que le nbr de fonct a charger est correct
        {
            printf("Combien de fonctionnaires voulez-vous charger dans la table ? :");
            scanf("%d",&nombre_fonctionnaires_a_charger);
        }

        int salaire_chargee;
        bool est_present = false ;
        char chaine_chargee[50]; // chaine assez volumineuse pour contenir nom, prenom et salaire du fonctionnaire
        fgets(chaine_chargee,50,fichier_chicago);// le charactere suivant etant un espace ceci permet de le depasser et de lire les elements fonctionnaires


        for (int i=0; i<nombre_fonctionnaires_a_charger ; i++) // permet d'effectuer le chargement de fonctionnaires = au nombre desiré
        {
            fgets(chaine_chargee,50,fichier_chicago);
            char * nom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
            char * prenom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
            int salaire =0;
            lire_ligne_chargee(chaine_chargee,nom,prenom,&salaire);
            fonctionnaire * fonct_a_rajouter = creer_fonctionnaire(nom,prenom,salaire);
            long long int index_fonct = calcul_index(base,taille,fonct_a_rajouter->concatenation);
            bool ajout_ok ;
            if( est_deja_present(table,nom,prenom,index_fonct) == false ) // s'il est deja present on ne l'ajoute pas
            {
                ajout_ok = ajouter(table,*fonct_a_rajouter,base,taille);
                classer_fonctionnaire_alphab(table,index_fonct);
            }
        }
        printf("  - Chargement termine -   \n \n");
    }
}



/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------   PARTIE 4  : AFFICHER SALAIRE    ----------------------------------------------------------------------*/
void fonctionnalite_afficher_salaire(vector table[],int base,int taille)
{
    int salaire_a_afficher = -1 ;
    char * nom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    char * prenom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum

    printf("Quel nom ? : ");
    scanf("%s",nom);
    printf("Quel prenom ? : ");
    scanf("%s",prenom);
    char * nom_concat = concatenation(nom,prenom);
    long long int index_fonct = calcul_index(base,taille,nom_concat);
    bool est_present = est_deja_present(table, nom,prenom,index_fonct);

    if (est_present==true)
    {
        vector * vecteur_index = &table[index_fonct];
        for (int i=0 ; i< table[index_fonct].logic_size ; i++)
        {
            if ( comparer_2_chaines_char( table[index_fonct].content[i].concatenation,   nom_concat )   ==   true );
            {
                salaire_a_afficher= table[index_fonct].content[i].salaire ;
            }
        }
    }

    printf("Le salaire de %s %s est : %d.\n \n",nom,prenom,salaire_a_afficher);
}




/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 5 : AFFICHER ENTRE  ----------------------------------------------------------------------*/
void fonctionnalite_afficher_entre (vector table[],int taille)
{
    int index_debut=-1;
    int index_fin=-1;
    while (index_debut<0 || index_debut>=taille)
    {
        printf("Index de debut ? : ");
        scanf("%d",&index_debut);
    }

    while (index_fin<0 || index_fin<index_debut || index_fin>=taille)
    {
        printf("Index de fin ? : ");
        scanf("%d",&index_fin);
    }

    afficher_table(table,taille,index_debut,index_fin);
}




/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 6 : COMPTEUR DE CONFLITS ----------------------------------------------------------------------*/
void compteur_de_conflits(vector table[],int taille)
{
    int compt_conflits = 0;
    for (int i=0; i<taille ; i++)
    {
         if (table[i].logic_size>1) // si il y a plus d'un fonctionnaire par vecteur : conflit
         {
             compt_conflits+= (table[i].logic_size -1);
         }
    }
    printf("Il y a %d conflits dans la table.\n \n",compt_conflits);
}




/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 7 : NOMBRE MOYEN D'ELEMENTS  ----------------------------------------------------------------------*/

void compteur_element_si_conflit(vector table[], int taille)
{
    for (int i=0; i<taille ; i++)
    {
         if (table[i].logic_size>1)
         {
             printf("Index %d : il y a %d elements.\n",i,table[i].logic_size);
         }
         else
         {
             printf("Index %d : pas de conflits.\n",i);
         }
    }
    printf("\n\n");
}



/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 8 : SUPPRIMER  ----------------------------------------------------------------------*/

bool chaines_totalement_id (char* chaine_1,char* chaine_2)
{
    bool resultat = false;
    int nombre_char_comparer = nombre_character_max(chaine_1,chaine_2);
    if (strlen(chaine_1)==strlen(chaine_2) && chaines_identiques(chaine_1,chaine_2,nombre_char_comparer)==true)
    {
       resultat =true;
    }
    return resultat;
}


bool supprimer_fonctionnaire(vector table[], int taille,int base, char* nom, char* prenom, long long int index)
{
    bool supr_ok = false ;
    if (table[index].logic_size>1)
    {
        fonctionnaire * new_tab = (fonctionnaire*) malloc( (table[index].logic_size-1) * sizeof(fonctionnaire) ); // creation d'un nouveau tableau de fonctionnaire
        if( new_tab != NULL ) // malloc OK
			{
				// copie des élements contenus dans p_vec dans new_vector
				int h = 0; // cet element passera a 1 lorsqu'on trouvera l'element a enlever afin de continuer a remplir correctement la table
				for(int i = 0 ; i < (table[index].logic_size ) ; i++)
				{
				    if (chaines_totalement_id(table[index].content[i].nom,nom)==true && chaines_totalement_id(table[index].content[i].prenom,prenom)==true)
                    {
                        // on ne copie pas ce terme dans le newtab
                        h=1;
                    }
                    else
                    {
                        new_tab[i-h] = table[index].content[i];
                    }
				}
				// Mise à jour du vecteur
				table[index].logic_size --;
				table[index].physical_size--;
				free(table[index].content);     // libération mémoire de l'ancien tableau interne
				table[index].content = new_tab; // association du tableau comme contenu du vecteur
				supr_ok = true ;
			}
    }
    else
    {
        table[index].logic_size --;
        table[index].physical_size--;
        table[index].content = NULL ;
        supr_ok =true ;
    }
    return supr_ok ;

}

void fonctionnalite_supprimer_fonctionnaire(vector table[], int taille, int base)
{
    char * nom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    char * prenom = ( char *) malloc ((25+1) * sizeof ( char )); // 25 caract è res maximum
    printf("Quel nom ? : ");
    scanf("%s",nom);
    printf("Quel prenom ? : ");
    scanf("%s",prenom);
    long long int index = calcul_index(base,taille,concatenation(nom,prenom));
    bool supr_ok = false ;

    if (est_deja_present(table,nom,prenom,index)==true)
    {
        supr_ok = supprimer_fonctionnaire(table,taille, base,nom,prenom,index);
    }

    if (supr_ok==true)
    {
        printf("Fonctionnaire supprime. \n \n ");
    }
    else
    {
        printf("Echec de la suppression. \n \n");
    }
}


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 9 : SUPPRIMER ENTRE ----------------------------------------------------------------------*/


void fonctionnalite_supprimer_entre(vector table[], int taille, int base)
{
    int index_debut=-1;
    int index_fin=-1;
    while (index_debut<0 || index_debut>=taille)
    {
        printf("Index de debut ? : ");
        scanf("%d",&index_debut);
    }

    while (index_fin<0 || index_fin<index_debut || index_fin>=taille)
    {
        printf("Index de fin ? : ");
        scanf("%d",&index_fin);
    }
    for (int i=index_debut ; i<(index_fin+1) ; i++)
    {
        free(table[i].content);
        table[i].content = NULL ;
        table[i].logic_size=0;
        table[i].physical_size=0;
    }

}

/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------  PARTIE 10 :  ----------------------------------------------------------------------*/

void quitter(vector table[], int taille, int base)
{
    for (int i=0 ; i<taille ; i++)
    {
        free(table[i].content);
        table[i].content = NULL ;
        table[i].logic_size=0;
        table[i].physical_size=0;
    }

    exit(0) ;

}


/*____________________________________________________________________________________________________________________________________________________*/
/*-----------------------------------------------------------    MENU     ----------------------------------------------------------------------*/

void afficher_menu(int base, int taille, vector  table_de_vecteurs[]) // affichage du menu et des choix
{
    printf(" - MENU -  \n \n1. index  \n2. ajouter  \n3. charger  \n4. afficher salaire  \n5. afficher entre  \n6. Compteur de conflits  \n");
    printf("7. Compteur d'elements par conflits  \n8. Supprimer un fonctionnaire  \n9. Supprimer entre \n10.Quitter \n");
    printf(" \n \nQuel est votre choix ? : ");
    int choix;
    scanf("%d",&choix);

    if (choix==1)
    {
        fonctionnalite_index(base,taille);
    }

    if (choix==2)
    {
        fonctionnalite_ajouter(base,taille,table_de_vecteurs);
    }

    if (choix==3)
    {
        fonctionnalite_charger(table_de_vecteurs,base,taille);
    }

    if (choix==4)
    {
        fonctionnalite_afficher_salaire(table_de_vecteurs,base,taille);
    }

    if (choix==5)
    {
        fonctionnalite_afficher_entre(table_de_vecteurs,taille);
    }
    if (choix==6)
    {
        compteur_de_conflits(table_de_vecteurs,taille);
    }
     if (choix==7)
    {
        compteur_element_si_conflit(table_de_vecteurs,taille);
    }
    if (choix == 8)
    {
        fonctionnalite_supprimer_fonctionnaire(table_de_vecteurs,taille,base);
        afficher_table(table_de_vecteurs,taille,0,(taille-1));
    }
    if (choix == 9)
    {
        fonctionnalite_supprimer_entre(table_de_vecteurs,taille,base);
    }
    if (choix == 10)
    {
        quitter(table_de_vecteurs,taille,base);
    }
    afficher_menu(base,taille,table_de_vecteurs);
}

void programme_complet() // seul et unique fonction a lancer dans le main
{
    /* INITIALISATION DES PARAMETRES DE LA TABLE */
    int base=0;
    int taille=0;
    initialisation_base_taille(&base,&taille); // affecte valeurs donnes par l'utilisateur a la base et a la taille
    vector table[taille]; // le tableau de vecteur
    initialisation_table(table,taille); // initialisation du tableau

    /* MENU */
    afficher_menu(base,taille,table);
}
