#pragma once
#include"Peca.h"
#include"Tela.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
#include<Windows.h>

typedef struct{

	int score;
	char name[6]; //name tem 5 caracteres e null

} highScore;

void inicializa(int sx, int sy);
bool moveupeca();
void finaliza(void);
bool defeat();
bool quit();
void keystroke();
void executajogo();
void imprimejogo();
void pecatela();
void descepeca();
void descerapido();
void transferetela();
void verlinha();
void removelinha(int l);
void vercolisao();
void mostrascores();
void gravascores();
void perdeu();
void novorecord();
void ordenascores();
void trocapontos(int i, int j);
void lerscores();
void telainicial();
Tela* inicializatela(int sx, int sy);