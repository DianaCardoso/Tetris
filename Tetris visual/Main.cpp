#include "Tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//kbhit();
//Sleep(milis);

int main() {

	srand(time(NULL));

	inicializa(20,20);				//inicializa o jogo, informando as dimens�es da tela
	telainicial();

	while (!quit()) {
		executajogo();				//fun��o que executa o jogo
		
		//Sleep(rand() % rand()%rand()%10);		//tentativa de for�ar relogio do sistema para evitar padr�es ao gerar pe�as
	}
	return 0;
}