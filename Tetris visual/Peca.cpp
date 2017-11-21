/*Peça.c*/

#include "peca.h"

void alocapeca(Peca* peca) {					//aloca peça e zera a sua matriz

	peca->map = (char**)malloc(sizeof(char*)*peca->sx);

	for (int i = 0; i < peca->sx; i++) {
		peca->map[i] = (char*)malloc(sizeof(char)*peca->sy);
		for (int j = 0; j < peca->sy; j++){
			peca->map[i][j] = ' ';
		}
	}
}

void desalocapeca(Peca* peca) {		//libera a memoria que foi utilizada pela peça

	free (peca);

}

void desalocapecamap(Peca* peca) {

	for (int i = 0; i < peca->sx; i++){
		free(peca->map[i]);
	}

	free(peca->map);
}

void tipopeca(Peca* peca) {		//define o tipo de peça de acordo com valor aleatorio

	srand(time(NULL));

	switch (rand()%7) {		//7 tipos de peças -> 7 valores possiveis, incluindo 0
	case 0: //I
		peca->tipo = I;
		break;
	case 1: //J
		peca->tipo = J;
		break;
	case 2: //L
		peca->tipo = L;
		break;
	case 3: //T
		peca->tipo = T;
		break;
	case 4: //S
		peca->tipo = S;
		break;
	case 5: //Z
		peca->tipo = Z;
		break;
	case 6: //O
		peca->tipo = O;
		break;
	}
}

void inicializapeca(Peca* peca) {			//inicializa a peça

	tipopeca(peca);							//define o tipo aleatorio da peça

	peca->moveu = true;
	peca->colesq = peca->coldir = peca->colbaixo = false;

	switch (peca->tipo){					//de acordo com o tipo, gera a matriz para a peça
	case I:
		peca->sx = 1;						//define tamanho da matriz, de acordo com a necessidade da peça
		peca->sy = 4;						//
		alocapeca(peca);					//aloca a matriz para a peça, com os tamanhos definicos
		peca->map[0][0] = 'I';				//1
		peca->map[0][1] = 'I';				//2
		peca->map[0][2] = 'I';				//3
		peca->map[0][3] = 'I';				//4 - linhas 1,2,3,4 definem a posição dos 4 blocos que formam a peça
		break;								//codigo se repete para as outras peças

	case J:
		peca->sx = 2;
		peca->sy = 3;
		alocapeca(peca);
		peca->map[1][0] = 'J';
		peca->map[1][1] = 'J';
		peca->map[1][2] = 'J';
		peca->map[0][2] = 'J';
		break;

	case L:
		peca->sx = 2;
		peca->sy = 3;
		alocapeca(peca);
		peca->map[0][0] = 'L';
		peca->map[0][1] = 'L';
		peca->map[0][2] = 'L';
		peca->map[1][2] = 'L';
		break;

	case T:
		peca->sx = 3;
		peca->sy = 2;
		alocapeca(peca);
		peca->map[0][1] = 'T';
		peca->map[1][1] = 'T';
		peca->map[2][1] = 'T';
		peca->map[1][0] = 'T';
		break;

	case O:
		peca->sx = 2;
		peca->sy = 2;
		alocapeca(peca);
		peca->map[0][0] = 'O';
		peca->map[0][1] = 'O';
		peca->map[1][0] = 'O';
		peca->map[1][1] = 'O';
		break;

	case S:
		peca->sx = 3;
		peca->sy = 2;
		alocapeca(peca);
		peca->map[0][1] = 'S';
		peca->map[1][1] = 'S';
		peca->map[1][0] = 'S';
		peca->map[2][0] = 'S';
		break;

	case Z:
		peca->sx = 3;
		peca->sy = 2;
		alocapeca(peca);
		peca->map[0][0] = 'Z';
		peca->map[1][0] = 'Z';
		peca->map[1][1] = 'Z';
		peca->map[2][1] = 'Z';
		break;
	}

}


void girapeca(Peca* peca) {		//codigo para girar a peça - BUG - precisa revisão

	Peca* tmp;								//gera peça temporaria "peca2"

	tmp = (Peca*)malloc(sizeof(Peca));		//aloca a memoria necessaria pela peca2
	tmp->sx = peca->sy;
	tmp->sy = peca->sx;
	tmp->pos = peca->pos;

	alocapeca(tmp);							//aloca matriz da peca2

	for (int i = 0; i < tmp->sx; i++){
		for (int j = 0; j < tmp->sy; j++){
			tmp->map[i][j] = peca->map[tmp->sy-1-j][i];	//iguala peças, com rotação - precisa revisão
		}
	}

	peca->pos.y = peca->pos.y - tmp->sy + peca->sy;

	desalocapecamap(peca);

	peca->sy = tmp->sy;
	peca->sx = tmp->sx;

	alocapeca(peca);

	peca->map = tmp->map;

	desalocapeca(tmp);

	peca->moveu = true;
}

void posicaopeca(Peca* peca, int x, int y) {		//define posição da peça

	peca->pos.x = x;
	peca->pos.y = y;
	peca->moveu = true;
}

void movepeca(Peca* peca, int x, int y) {		//realiza movimentação da peça através da soma nos valores ja existentes
	
	peca->pos.x += x;
	peca->pos.y += y;
	peca->moveu = true;
}