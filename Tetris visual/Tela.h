#pragma once
#include<locale.h>
#include<stdio.h>

typedef struct Tela {

	char** table;
	int sizex, sizey;
	
}Tela;

void imprimetela(Tela*);