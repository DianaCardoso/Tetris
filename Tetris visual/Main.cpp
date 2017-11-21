#include "Tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//kbhit();
//Sleep(milis);

int main() {

	srand(time(NULL));

	inicializa(20,20);				//inicializa o jogo, informando as dimensões da tela
	telainicial();

	while (!quit()) {
		executajogo();				//função que executa o jogo
		
		//Sleep(rand() % rand()%rand()%10);		//tentativa de forçar relogio do sistema para evitar padrões ao gerar peças
	}
	return 0;
}