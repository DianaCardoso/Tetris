/*Peca.h*/

#pragma once
#include"Peca.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>

typedef struct Bloco {

	int x, y;

}Bloco;

typedef enum Tipopeca {

	I, J, L, O, S, T, Z

}Tipopeca;

typedef struct Peca {

	bool moveu, colesq, coldir, colbaixo;
	char** map;
	int sx, sy;
	Bloco pos;
	Tipopeca tipo;

}Peca;

void inicializapeca(Peca* peca);			//inicializa a pe�a
void alocapeca(Peca* peca);					//aloca matriz que representa a pe�a
void tipopeca(Peca* peca);					//gera tipo aleatorio de pe�a
void girapeca(Peca* peca);					// rataciona a pe�a
void movepeca(Peca* peca, int x, int y);	//movimenta a pe�a
void posicaopeca(Peca* peca, int x, int y);