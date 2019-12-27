#include <stdio.h>
#include <stdlib.h>
#include "tas.h"



int main( int argc, char** argv ){
	Tas_binaire t;
	int num=0;
	int insert=0;
	int x=0;
	t.nb=0;
	for(int i=0;i<10;i++){
		t.tab[t.nb]=i;
		t.nb++;
	}
	do{
		printf("1=insertion\n2=extrairemin\n3=entasser\nChoix option : ");
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

	}while(num != 0);

}
