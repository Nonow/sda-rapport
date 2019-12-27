#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

int main( int argc, char** argv ){
	Tas_binaire t;
	int num=0;
	int insert=0;
	int x=0;
	t.nb=0;

	Tas_binaire r;

	printf("Nombre d'élément du tableau 1 :  ");
	scanf("%d", &t.nb);
	if(t.nb>0){
		printf("\nCréation du tableau \n");
		t.tab = malloc(t.nb * sizeof(int));
		if(t.tab == NULL){
				exit(0);
		}
	}

	printf("Nombre d'élément du tableau 2 :  ");
	scanf("%d", &r.nb);
	if(r.nb>0){
		printf("\nCréation du tableau \n");
		r.tab = malloc(r.nb * sizeof(int));
		if(r.tab == NULL){
				exit(0);
		}
	}

		do{
			printf("Tableau 1\n-------------\n1=insertion\n2=extrairemin\n3=entasser\n4=afficher\n-------------\nTableau 2\n-------------\n5=insertion\n6=extrairemin\n7=entasser\n8=afficher\n9=fusion\nChoix option : ");
			scanf("%d", &num);

			if(num==1){
				printf("Choix insertion: ");
				scanf("%d", &insert);
				t=inserer(t,insert);
			}
			else if(num==2){
				t=ExtraireMin(t);
			}
			else if(num==3){
				printf("Choix entasser: ");
				scanf("%d", &x);
				t=entasser(t,x);
			}
			else if(num==4){
				afficher(t);
			}


			else if(num==5){
				printf("Choix insertion: ");
				scanf("%d", &insert);
				r=inserer(r,insert);
			}
			else if(num==6){
				r=ExtraireMin(r);
			}
			else if(num==7){
				printf("Choix entasser: ");
				scanf("%d", &x);
				r=entasser(r,x);
			}
			else if(num==8){
				afficher(r);
			}

			else if(num==9){
				t=fusion(t,r);
			}

		}while(num != 0);
}
