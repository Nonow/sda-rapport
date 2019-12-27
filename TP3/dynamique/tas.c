#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

int main( int argc, char** argv ){
	Tas_binaire t;
	int num=0;
	int insert=0;
	int x=0;
	t.nb=0;

	printf("Nombre d'élément du tableau :  ");
	scanf("%d", &t.nb);
	if(t.nb>0){
		printf("\nCréation du tableau \n");
		t.tab = malloc(t.nb * sizeof(int));
		if(t.tab == NULL){
				exit(0);
		}
		do{
			printf("1=insertion\n2=extrairemin\n3=entasser\n4=afficher\nChoix option : ");
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

		}while(num != 0);


	}


}
