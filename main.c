#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int Ref_prd;
    char Dez[20];
    float P_unit;
    int Q_stoxck;
    int Q_seuil;
}Produit;
void Creer_Produit(FILE*fj){
    fj=fopen("Produit","w");
    if(fj==NULL){
        perror("Erreur d'ouverture de fichier Produit\n");
        exit(EXIT_FAILURE);
    }
    fclose(fj);
}
void Lister_Produit(FILE*fj){
   Produit p;
   while(fscanf(fj,"%d %s %f %d %d",&p.Ref_prd,p.Dez,&p.P_unit,&p.Q_stoxck,&p.Q_seuil)==5){
    printf("Ref_prd=%d désignation=%s Prix_unitaire=%f Q-stock=%d Q-seuil=%d \n",p.Ref_prd,p.Dez,p.P_unit,p.Q_stoxck,p.Q_seuil);
   }
}
void  Rechercher_Produit(FILE*fj){
    int ref;
    Produit p1;
    
    printf("donner moi un Reference:");
    scanf("%d",&ref);
    while(fscanf(fj,"%d %s %f %d %d",&p1.Ref_prd,p1.Dez,&p1.P_unit,&p1.Q_stoxck,&p1.Q_seuil)==5){
        if(ref=p1.Ref_prd){
            printf("Ref_prd=%d désignation=%s Prix_unitaire=%f Q-stock=%d Q-seuil=%d\n",p1.Ref_prd,p1.Dez,p1.P_unit,p1.Q_stoxck,p1.Q_seuil);
        }
    }
}
void  Ajouter_Produit(FILE*fj){
    
}

int main()
{
    
    return 0;
}