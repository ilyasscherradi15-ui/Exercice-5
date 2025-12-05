#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure d'un nœud de l'arbre binaire
typedef struct Abnoeud {
    char nom[50];               // Nom de l'employé
    int idemploye;              // Identifiant unique de l'employé (clé de tri)
    char poste[50];             // Poste occupé par l'employé
    struct Abnoeud* filsg;      // Pointeur vers le fils gauche (valeurs < id)
    struct Abnoeud* filsd;      // Pointeur vers le fils droit (valeurs > id)
} Abnoeud;

// Définition de la structure de l'arbre binaire
typedef struct AbArbre {
    Abnoeud* racine;            // Pointeur vers la racine de l'arbre
} AbArbre;

// Fonction pour créer un nouveau nœud
Abnoeud* creer_noeud(char *nom, int idemploye, char *poste, Abnoeud* filsg, Abnoeud* filsd) {
    Abnoeud* n = (Abnoeud*) malloc(sizeof(Abnoeud));
    if(n == NULL) {
        printf("Erreur d'allocation de mémoire pour le nœud de l'arbre\n");
        exit(EXIT_FAILURE);
    }
    strcpy(n->nom, nom);        // Copie du nom
    n->idemploye = idemploye;   // Attribution de l'ID
    strcpy(n->poste, poste);    // Copie du poste
    n->filsg = filsg;           // Initialisation du fils gauche
    n->filsd = filsd;           // Initialisation du fils droit
    return n;
}

// Fonction pour créer un arbre vide
AbArbre* creer_abarbre() {
    AbArbre* a = (AbArbre*) malloc(sizeof(AbArbre));
    a->racine = NULL;           // L'arbre est initialement vide
    return a;
}

// Fonction pour créer une feuille vide
Abnoeud* CreerFeuille() {
    Abnoeud* fe = (Abnoeud*) malloc(sizeof(Abnoeud));
    fe->filsg = NULL;           // Pas de fils gauche
    fe->filsd = NULL;           // Pas de fils droit
    strcpy(fe->nom, "");        // Nom vide
    fe->idemploye = 0;          // ID nul
    strcpy(fe->poste, "");      // Poste vide
    return fe;
}

// Fonction pour ajouter un nœud dans l'arbre (version retournant la racine)
Abnoeud* ajouterNoeud(Abnoeud* racine, char *nom, int idemploye, char *poste) {
    if (racine == NULL) {
        // Cas de base : position trouvée, création du nouveau nœud
        return creer_noeud(nom, idemploye, poste, NULL, NULL);
    } else {
        if (idemploye < racine->idemploye) {
            // L'ID est inférieur, insertion dans le sous-arbre gauche
            racine->filsg = ajouterNoeud(racine->filsg, nom, idemploye, poste);
        } else if (idemploye > racine->idemploye) {
            // L'ID est supérieur, insertion dans le sous-arbre droit
            racine->filsd = ajouterNoeud(racine->filsd, nom, idemploye, poste);
        } else {
            // L'ID existe déjà (doublon)
            printf("L'employé avec l'ID %d existe déjà dans l'arbre.\n", idemploye);
        }
        return racine;
    }
}

// Parcours préfixe (Racine - Gauche - Droite)
void Prefixe(Abnoeud* racine) {
    if(racine != NULL) {
        // Traitement de la racine d'abord
        printf("Nom: %s, ID: %d, Poste: %s\n", racine->nom, racine->idemploye, racine->poste);
        Prefixe(racine->filsg);  // Parcours du sous-arbre gauche
        Prefixe(racine->filsd);  // Parcours du sous-arbre droit
    }
}

// Parcours infixe (Gauche - Racine - Droite) → donne les éléments triés par ID
void Infixe(Abnoeud* racine) {
    if(racine != NULL) {
        Infixe(racine->filsg);  // Parcours du sous-arbre gauche d'abord
        // Traitement de la racine après le sous-arbre gauche
        printf("Nom: %s, ID: %d, Poste: %s\n", racine->nom, racine->idemploye, racine->poste);
        Infixe(racine->filsd);  // Parcours du sous-arbre droit après
    }
}

// Parcours postfixe (Gauche - Droite - Racine)
void Postfixe(Abnoeud* racine) {
    if(racine != NULL) {
        Postfixe(racine->filsg);  // Parcours du sous-arbre gauche
        Postfixe(racine->filsd);  // Parcours du sous-arbre droit
        // Traitement de la racine en dernier
        printf("Nom: %s, ID: %d, Poste: %s\n", racine->nom, racine->idemploye, racine->poste);
    }
}

// Recherche d'un employé par son ID
Abnoeud* rechercherEmploye(Abnoeud* racine, int idemploye) {
    if(racine == NULL) {
        return NULL;  // Arbre vide ou élément non trouvé
    }
    if(idemploye == racine->idemploye) {
        // Employé trouvé
        printf("Employé trouvé: Nom: %s, ID: %d, Poste: %s\n", racine->nom, racine->idemploye, racine->poste);
        return racine;
    }
    else if(idemploye < racine->idemploye) {
        // Recherche dans le sous-arbre gauche
        return rechercherEmploye(racine->filsg, idemploye);
    } else {
        // Recherche dans le sous-arbre droit
        return rechercherEmploye(racine->filsd, idemploye);
    }
}

// Suppression d'un nœud de l'arbre
Abnoeud* SupprimerNoeud(Abnoeud* racine, int idemploye) {
    if(racine == NULL) {
        return NULL;  // Arbre vide
    }
    
    // Recherche du nœud à supprimer
    if(idemploye < racine->idemploye) {
        racine->filsg = SupprimerNoeud(racine->filsg, idemploye);
    } else if(idemploye > racine->idemploye) {
        racine->filsd = SupprimerNoeud(racine->filsd, idemploye);
    } else {
        // Nœud trouvé (3 cas possibles)
        
        // Cas 1: Nœud avec 0 ou 1 enfant à droite
        if(racine->filsg == NULL) {
            Abnoeud* temp = racine->filsd;
            free(racine);
            return temp;
        }
        // Cas 2: Nœud avec 0 ou 1 enfant à gauche
        else if(racine->filsd == NULL) {
            Abnoeud* temp = racine->filsg;
            free(racine);
            return temp;
        }
        // Cas 3: Nœud avec 2 enfants
        else {
            // Trouver le successeur (plus petit élément du sous-arbre droit)
            Abnoeud* successeur = racine->filsd;
            while(successeur->filsg != NULL) {
                successeur = successeur->filsg;
            }
            
            // Copier les données du successeur dans le nœud courant
            racine->idemploye = successeur->idemploye;
            strcpy(racine->nom, successeur->nom);
            strcpy(racine->poste, successeur->poste);
            
            // Supprimer le successeur
            racine->filsd = SupprimerNoeud(racine->filsd, successeur->idemploye);
        }
    }
    return racine;
}

// Calcul de la taille de l'arbre (nombre de nœuds)
int tailleArbre(Abnoeud* racine) {
    if(racine == NULL) {
        return 0;  // Arbre vide
    } else {
        // 1 (nœud courant) + taille gauche + taille droite
        return 1 + tailleArbre(racine->filsg) + tailleArbre(racine->filsd);
    }
}

// Calcul de la hauteur de l'arbre (nombre de niveaux)
int hauteurArbre(Abnoeud* racine) {
    if(racine == NULL) {
        return 0;  // Arbre vide
    } else {
        // Calcul récursif des hauteurs des sous-arbres
        int hauteurGauche = hauteurArbre(racine->filsg);
        int hauteurDroite = hauteurArbre(racine->filsd);
        
        // La hauteur est le maximum des deux sous-arbres + 1 (niveau courant)
        return (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite) + 1;
    }
}

// Programme principal de test
int main() {
    // Création d'un arbre vide
    AbArbre* arbre = creer_abarbre();
    
    // Ajout d'employés (les assignations sont nécessaires car ajouterNoeud retourne la racine)
    arbre->racine = ajouterNoeud(arbre->racine, "ILYASS", 1001, "Manager");
    arbre->racine = ajouterNoeud(arbre->racine, "REDA", 1002, "Developer");
    arbre->racine = ajouterNoeud(arbre->racine, "SAMIRA", 1003, "Designer");
     arbre->racine = ajouterNoeud(arbre->racine, "ILYASS", 1004, "Analyst");
     arbre->racine = ajouterNoeud(arbre->racine, "OMAR", 1005, "Intern");
     
    
    // Affichage des différents parcours
    printf("Parcours Préfixe (Racine-Gauche-Droite):\n");
    Prefixe(arbre->racine);
    
    printf("\nParcours Infixe (Gauche-Racine-Droite - Trié par ID):\n");
    Infixe(arbre->racine);
    
    printf("\nParcours Postfixe (Gauche-Droite-Racine):\n");
    Postfixe(arbre->racine);
    
    // Recherche d'un employé
    int idRecherche = 1002;
    printf("\nRecherche de l'employé avec ID %d:\n", idRecherche);
    Abnoeud* employeTrouve = rechercherEmploye(arbre->racine, idRecherche);
    if (employeTrouve == NULL) {
        printf("Employé avec l'ID %d non trouvé.\n", idRecherche);
    }
    
    // Suppression d'un employé
    printf("\nSuppression de l'employé avec l'ID 1001:\n");
    arbre->racine = SupprimerNoeud(arbre->racine, 1001);
    printf("État de l'arbre après suppression (parcours infixe):\n");
    Infixe(arbre->racine);
    
    // Statistiques de l'arbre
    printf("\n=== Statistiques de l'arbre ===\n");
    printf("Taille de l'arbre (nombre d'employés): %d\n", tailleArbre(arbre->racine));
    printf("Hauteur de l'arbre (nombre de niveaux): %d\n", hauteurArbre(arbre->racine));
    
    return 0;
}