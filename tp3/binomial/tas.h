struct Tas_binaire {
    int* tab;
    int nb;

};typedef struct Tas_binaire Tas_binaire;

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
	//afficher(t);
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
	//afficher(t);
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


Tas_binaire fusion(Tas_binaire t, Tas_binaire r){
	if (t.nb > r.nb){ 			// on ajoute le tas le plus petit dans le plus grand
		for(int i=0;i<r.nb;i++){
			t=inserer(t,r.tab[i]);	// on insere les clefs
			t=entasser(t,r.tab[i]); 		// on met en tas
		}
	}
	else{
		Tas_binaire stock= t;
		t=r;
		r=stock;
		for(int i=0;i<r.nb;i++){
			t=inserer(t,r.tab[i]);
			t=entasser(t,r.tab[i]);
		}
	}
	return t;
}
