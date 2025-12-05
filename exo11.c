#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Produit
{
    char nom[50];
    int prix;
    int quantite;
    struct Produit *suivant;
} Produit;
typedef struct ListeRepere
{
    Produit *tete;
    Produit *queue;
    int account;
} Liste;
Liste *creer_liste()
{
    Liste *l = (Liste *)malloc(sizeof(Liste));
    l->tete = NULL;
    l->queue = NULL;
    l->account = 0;
    return l;
}
Produit *creer_produit(char nom[], int prix, int quantite)
{
    Produit *p = (Produit *)malloc(sizeof(Produit));
    strcpy(p->nom, nom);
    p->prix = prix;
    p->quantite = quantite;
    p->suivant = NULL;
    return p;
}
// fct pour saisir un produit
Produit *saisir_produit()
{
    char nom[50];
    int prix;
    int quantite;
    Produit *p = creer_produit(nom, prix, quantite);
    printf("Entrer le nom du produit: ");
    scanf("%s", nom);
    printf("Entrer le prix du produit: ");
    scanf("%d", &prix);
    printf("Entrer la quantite du produit: ");
    scanf("%d", &quantite);
    return creer_produit(nom, prix, quantite);
}
void ajouter_produit_liste_fin(Liste *l, char _nom[], int _prix, int _quantite)
{
    Produit *p = saisir_produit();
    if (l == NULL || p == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (l->tete == NULL)
    {
        l->tete = p;
        l->queue = p;
    }
    else
    {
        l->queue->suivant = p;
        l->queue = p;
    }
    l->account++;
}
void ajouter_produit_liste_debut(Liste *l, char _nom[], int _prix, int _quantite)
{
    Produit *p = saisir_produit();
    if (l == NULL || p == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (l->tete == NULL)
    {
        l->tete = p;
        l->queue = p;
    }
    else
    {
        p->suivant = l->tete;
        l->tete = p;
    }
    l->account++;
}
void ajouter_produit_liste_milieu(Liste *l, char _nom[], int _prix, int _quantite)
{
    int milieu = l->account / 2;
    Produit *p = saisir_produit();
    if (l == NULL || p == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (l->tete == NULL)
    {
        ajouter_produit_liste_debut(l, _nom, _prix, _quantite);
        return;
    }

    Produit *temp = l->tete;
    for (int i = 0; i < milieu - 1; i++)
    {
        if (temp->suivant == NULL)
        {
            break;
        }
        temp = temp->suivant;
    }
    p->suivant = temp->suivant;
    temp->suivant = p;
    if (p->suivant == NULL)
    {
        l->queue = p;
    }
    l->account++;
    return;
}
void afficher_liste_produits(Liste *l)
{
    if (l == NULL)
    {
        printf("La liste est vide\n");
        return;
    }
    Produit *temp = l->tete;
    while (temp != NULL)
    {
        printf("Nom: %s, Prix: %d, Quantite: %d\n", temp->nom, temp->prix, temp->quantite);
        temp = temp->suivant;
    }
}
void enregistrer_liste_produits(Liste *l)
{
    FILE *file = fopen("produits.txt", "w");
    if (file == NULL)
    {
        perror("Erreur d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }
    Produit *temp = l->tete;
    while (temp != NULL)
    {
        fprintf(file, "%s %d %d\n", temp->nom, temp->prix, temp->quantite);
        temp = temp->suivant;
    }
    fclose(file);
}
void enregistrer_liste_produit(Liste *l)
{
    FILE *file = fopen("produits.txt", "r");
    if (file == NULL)
    {
        perror("Erreur d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }
    if (l == NULL)
    {
        printf("Erreur: Liste non initialisée\n");
        return;
    }
    int compteur = 0;
    char nom[50];
    int prix;
    int quantite;

    while (fscanf(file, "%s %d %d\n", nom, &prix, &quantite) == 3)
    {
        Produit *nouveau = creer_produit(nom, prix, quantite);
        if (nouveau == NULL)
        {
            printf("Erreur de création de produit\n");
            continue; // ou gérer l'erreur comme approprié
        }
        if (l->tete == NULL)
        {
            l->tete = nouveau;
            l->queue = nouveau;
        }
        else
        {
            l->queue->suivant = nouveau;
            l->queue = nouveau;
            l->account++;
        }
        compteur++;
        printf("Produit lu: %s (%d MAD, %d unités)\n", nom, prix, quantite);
    }

    fclose(file);
    if (compteur == 0)
    {
        printf("Aucun produit trouvé dans le fichier\n");
    }
    else
    {
        printf("%d produits chargés depuis le fichier\n", compteur);
    }
}
void trier_liste_produits(Liste *l)
{
    if (l == NULL || l->tete == NULL)
    {
        printf("La liste est vide ou non initialisée\n");
        return;
    }
    Produit *trie = NULL;
    Produit *courant = l->tete;
    while (courant != NULL)
    {
        Produit *suivant = courant->suivant;
        if (trie == NULL || courant->prix < trie->prix)
        {
            courant->suivant = trie;
            trie = courant;
        }
        else
        {
            Produit *temp = trie;
            while (temp->suivant != NULL && temp->suivant->prix < courant->prix)
            {
                temp = temp->suivant;
            }
            courant->suivant = temp->suivant;
            temp->suivant = courant;
        }
        courant = suivant;
    }
    l->tete = trie;
    Produit *temp = trie;
    while (temp != NULL && temp->suivant != NULL)
    {
        temp = temp->suivant;
    }
    l->queue = temp;
}
Produit *trouver_produit_cher(Liste *l)
{
    if (l == NULL || l->tete == NULL)
    {
        printf("la liste est vide ou nom initialisee\n");
        return NULL;
    }
    Produit *courant = l->tete;
    Produit *produit_cher = courant;
    int prix_max = courant->prix;
    while (courant != NULL)
    {
        if (courant->prix > prix_max)
        {
            prix_max = courant->prix;
            produit_cher = courant;
        }
        courant = courant->suivant;
    }
    return produit_cher;
}
void liberer_liste(Liste *l)
{
    if (l == NULL)
        return;

    Produit *courant = l->tete;
    while (courant != NULL)
    {
        Produit *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    free(l);
}

int main()
{
    Liste *maListe = NULL;
    int choix;
    char nom[50];
    int prix, quantite;

    printf("=== GESTIONNAIRE DE PRODUITS ===\n");

    do
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Creer une nouvelle liste\n");
        printf("2. Ajouter un produit au debut\n");
        printf("3. Ajouter un produit a la fin\n");
        printf("4. Ajouter un produit au milieu\n");
        printf("5. Afficher tous les produits\n");
        printf("6. Trier la liste par prix\n");
        printf("7. Trouver le produit le plus cher\n");
        printf("8. Enregistrer la liste dans un fichier\n");
        printf("9. Charger la liste depuis un fichier\n");
        printf("10. Liberer la memoire\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            if (maListe != NULL)
            {
                liberer_liste(maListe);
            }
            maListe = creer_liste();
            printf("Liste creee avec succes!\n");
            break;

        case 2:
            if (maListe == NULL)
            {
                printf("Veuillez d'abord creer une liste (option 1)\n");
            }
            else
            {
                printf("Ajout d'un produit au debut...\n");
                // Note: Les paramètres sont ignorés dans votre fonction
                ajouter_produit_liste_debut(maListe, "", 0, 0);
                printf("Produit ajoute au debut!\n");
            }
            break;

        case 3:
            if (maListe == NULL)
            {
                printf("Veuillez d'abord creer une liste (option 1)\n");
            }
            else
            {
                printf("Ajout d'un produit a la fin...\n");
                // Note: Les paramètres sont ignorés dans votre fonction
                ajouter_produit_liste_fin(maListe, "", 0, 0);
                printf("Produit ajoute a la fin!\n");
            }
            break;

        case 4:
            if (maListe == NULL)
            {
                printf("Veuillez d'abord creer une liste (option 1)\n");
            }
            else
            {
                printf("Ajout d'un produit au milieu...\n");
                // Note: Les paramètres sont ignorés dans votre fonction
                ajouter_produit_liste_milieu(maListe, "", 0, 0);
                printf("Produit ajoute au milieu!\n");
            }
            break;

        case 5:
            if (maListe == NULL)
            {
                printf("Aucune liste existante. Veuillez creer une liste d'abord.\n");
            }
            else
            {
                printf("\n=== LISTE DES PRODUITS ===\n");
                afficher_liste_produits(maListe);
                printf("Total de produits : %d\n", maListe->account);
            }
            break;

        case 6:
            if (maListe == NULL)
            {
                printf("Aucune liste existante. Veuillez creer une liste d'abord.\n");
            }
            else
            {
                printf("Tri de la liste par prix...\n");
                trier_liste_produits(maListe);
                printf("Liste triee avec succes!\n");
            }
            break;

        case 7:
            if (maListe == NULL)
            {
                printf("Aucune liste existante. Veuillez creer une liste d'abord.\n");
            }
            else
            {
                Produit *cher = trouver_produit_cher(maListe);
                if (cher != NULL)
                {
                    printf("\n=== PRODUIT LE PLUS CHER ===\n");
                    printf("Nom: %s, Prix: %d, Quantite: %d\n",
                           cher->nom, cher->prix, cher->quantite);
                }
            }
            break;

        case 8:
            if (maListe == NULL)
            {
                printf("Aucune liste existante. Veuillez creer une liste d'abord.\n");
            }
            else
            {
                printf("Enregistrement de la liste dans le fichier...\n");
                enregistrer_liste_produits(maListe);
                printf("Liste enregistree dans 'produits.txt'\n");
            }
            break;

        case 9:
            if (maListe == NULL)
            {
                printf("Veuillez d'abord creer une liste (option 1)\n");
            }
            else
            {
                printf("Chargement de la liste depuis le fichier...\n");
                // Note: Votre fonction s'appelle enregistrer_liste_produit mais elle charge!
                enregistrer_liste_produit(maListe);
            }
            break;

        case 10:
            if (maListe != NULL)
            {
                liberer_liste(maListe);
                maListe = NULL;
                printf("Memoire liberee!\n");
            }
            else
            {
                printf("Aucune liste a liberer.\n");
            }
            break;

        case 0:
            if (maListe != NULL)
            {
                liberer_liste(maListe);
            }
            printf("Au revoir!\n");
            break;

        default:
            printf("Choix invalide! Veuillez choisir entre 0 et 10.\n");
            break;
        }

    } while (choix != 0);

    return 0;
}