#include "Tela.h"



void imprimetela(Tela* tela) {						//função para imprimir matriz da tela

	printf("\n%c", 201);								//imprime quina ╔		

	for (int i = 0; i < tela->sizex; i++){			//imprime limites do teto ═
		printf("%c", 205);							
	}

	printf("%c\n", 187);							//imprime quina ╗

	for (int i = 0; i < tela->sizey; i++) {
		for (int j = 0; j < tela->sizex; j++) {
			if (j == 0)	printf("%c", 186);			//imprime paredes a esquerda ║
			printf("%c", tela->table[j][i]);		//imprime dados da matriz tela
			if (j == tela->sizex-1)	printf("%c", 186);	//imprime paredes a direita ║
		}
		printf("\n");								//pula linha
	}

	printf("%c", 200);								//imprime quina ╚

	for (int i = 0; i < tela->sizex; i++){
		printf("%c", 205);							//imprime chão ═
	}
	
	printf("%c\n", 188);							//imprime quina ╝
}
