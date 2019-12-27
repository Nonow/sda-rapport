#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

void afficher(Tas_binaire t){ 		// Fonction d'affichage
	printf("Tableau :    ");
	for(int i=0;i<t.nb;i++){
		printf("|%i|",t.tab[i]);
	}
	printf("\nIndice du tableau : ");
	for(int i=0;i<t.nb;i++){
		printf("|%i|",i);
	}
	printf("\n\n");
}

int pere(int i){	// fonction pour trouver le père
	return (i-1)/2;
}

int gauche(int i){		// fonction pour trouver le fils gauche
	return ((2*i)+1);
}

int droite(int i){		// fonction pour trouver le fils droite
	return ((2*i)+2);
}

Tas_binaire entasser(Tas_binaire t, int i){			// fonction pour mettre en tas

	if(t.nb==100)
		fprintf(stderr, "tas plein");
	int g = gauche(i);
	int d = droite(i);
	int min=i;

	if ((g<= t.nb) && (t.tab[g] > t.tab[i])){			// si le fils gauche existe et est plus grand on le prend
		min = g;
	}

	if( (d<= t.nb) && (t.tab[d] > t.tab[i]) ){				// si le fils droite existe et est plus grande on le prend
		min = d;
	}

	if(min != i){			// si on a découvert un fils plus grand que le père on permute avec lui
		int stock = t.tab[i];
		t.tab[i] = t.tab[min];
		t.tab[min]=stock;
		t=entasser(t,min);		// on recommence la fonction jusqu'à qu'on ne trouve plus de plus grand père
	}
	afficher(t);
	return t;
}

Tas_binaire DiminuerCle(Tas_binaire t,int i, int k){ 		// permute une valeur du tas avec une nouvelle valeur plus petite
	if(k > t.tab[i])
		fprintf(stderr, "erreur nouvelle valeur plus grande que valeur actuelle");

	t.tab[i] = k;

	while(i>0 && t.tab[pere(i)]> t.tab[i]){
		int save = t.tab[i];
		t.tab[i] = t.tab[pere(i)];
		t.tab[pere(i)] = save;
		i= pere(i);
	}
	afficher(t);
	return t;
}

Tas_binaire ExtraireMin(Tas_binaire t){			// extrait la plus petite valeur
	if (t.nb < 1)
		fprintf(stderr,"Erreur file vide");
	int min = t.tab[0];
	t.nb = t.nb-1;
	t.tab[0] = t.tab[t.nb];

	entasser(t,1);
	printf("Extraire : %i \n",(int) min);
	afficher(t);
	return t;
}

Tas_binaire inserer(Tas_binaire t, int x){ 			// insère une nouvelle valeur
	t.tab[t.nb] = x;
	t=DiminuerCle(t,t.nb,x);
	t.nb= t.nb+1;

	afficher(t);
	return t;
}

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

	int i;
// Tableau dynamique.
// Analyse du temps pris par les opérations.
analyzer_t * time_analysis = analyzer_create();
// Analyse du nombre de copies faites par les opérations.
analyzer_t * copy_analysis = analyzer_create();
// Analyse de l'espace mémoire inutilisé.
analyzer_t * memory_analysis = analyzer_create();
// Mesure de la durée d'une opération.
struct timespec before, after;
clockid_t clk_id = CLOCK_REALTIME;
// utilisé comme booléen pour savoir si une allocation a été effectuée.
char memory_allocation;

for(i = 0; i < 1000000 ; i++){
	// Ajout d'un élément et mesure du temps pris par l'opération.
	clock_gettime(clk_id, &before);
	memory_allocation = arraylist_append(t, i);
	clock_gettime(clk_id, &after);


	// Enregistrement du temps pris par l'opération
	analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec);
	// Enregistrement du nombre de copies efféctuées par l'opération.
	// S'il y a eu réallocation de mémoire, il a fallu recopier tout le tableau.
	analyzer_append(copy_analysis, (memory_allocation)? i:1 );
	// Enregistrement de l'espace mémoire non-utilisé.
	analyzer_append(memory_analysis,arraylist_capacity(t)-arraylist_size(t));
}

// Affichage de quelques statistiques sur l'expérience.
fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis));
fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis));
fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis));
fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis));

// Sauvegarde les données de l'expérience.
save_values(time_analysis, "../plots/dynamic_array_time_c.plot");
save_values(copy_analysis, "../plots/dynamic_array_copy_c.plot");
save_values(memory_analysis, "../plots/dynamic_array_memory_c.plot");

// Nettoyage de la mémoire avant la sortie du programme
arraylist_destroy(t);
analyzer_destroy(time_analysis);
analyzer_destroy(copy_analysis);
analyzer_destroy(memory_analysis);
return EXIT_SUCCESS;

}
