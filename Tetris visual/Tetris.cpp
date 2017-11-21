#include "Tetris.h"


Tela *tela, *saidatela;  //tela: tela que mant√©m os blocos fixos do jogo	saidatela: tela que fara a jun√ß√£o dos blocos fixados e os ainda em movimento
bool defeated, quitgame; //defeat: indica se o jogo esta perdido	quitgame: define se foi escolhido para sair do jogo
int score, frame, estado;		//score: pontua√ß√£o		frame: contagem de atualiza√ß√µes da tela.
Peca* peca;				//variavel da pe√ßa. Ela ser√° reinicializada sempre que uma nova pe√ßa aparecer
FILE *highscores;
highScore *pontuacao; //10 posi√ßoes para as grava√ß√µes e 1 extra para pontua√ß√£o temporaria no sortting

void executajogo() {//fun√ß√£o de execu√ß√£o do jogo - √© aqui que todas as fun√ß√µes necessarias s√£o chamadas em seu tempo

	if (!defeated && !quitgame) {
		for (int counter = 0; (counter < 20) && !quitgame; counter++) {
			if (kbhit())
				keystroke();
			if (moveupeca()) { 
				imprimejogo(); vercolisao(); }
			Sleep(1);
		}
		descepeca();
	}
	else {
		if (defeated)
			perdeu();
	}
}

void telainicial() {

	int tmp=0;
	system("cls");
	printf("\n\n\t¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶¶  ¶¶¶¶¶¶   ¶¶  ¶¶¶¶¶¶¶\n\t   ¶¶    ¶¶          ¶¶     ¶¶    ¶¶  ¶¶ ¶¶\n\t   ¶¶    ¶¶¶¶¶¶      ¶¶     ¶¶¶¶¶¶    ¶¶  ¶¶¶¶¶¶\n\t   ¶¶    ¶¶          ¶¶     ¶¶   ¶¶   ¶¶       ¶¶\n\t   ¶¶    ¶¶¶¶¶¶¶¶    ¶¶     ¶¶    ¶¶  ¶¶ ¶¶¶¶¶¶¶\n");
	
	printf("\n\n\tPressione enter para jogar ou f4 para sair");
	printf("\n\n\nDurante o jogo: \n'P' - pausa o jogo\n^ - gira a peca\n> - move a peca para direita\n< - move a peca para esquerda\nv - desce a peca");

	do{
		tmp = getch();
	}while (tmp != 62 && tmp != 13);

	if (tmp == 62)
		quitgame = true;
}

//bool colideesq() {
//	for (int i = 0; i < peca->sx; i++)
//		for (int j = 0; j < peca->sy; j++)
//			if (peca->map[i][j] != ' ' && tela->table[peca->pos.x + i - 1][peca->pos.y + j] != ' ')
//				return true;
//	return false;
//}
//
//bool colidedir() {
//	for (int i = 0; i < peca->sx; i++)
//		for (int j = 0; j < peca->sy; j++)
//			if (peca->pos.x + peca->sx + i < tela->sizex)
//				if (peca->map[i][j] != ' ' && tela->table[peca->pos.x + peca->sx][peca->pos.y + j] != ' ')
//					return true;
//	return false;
//}

void vercolisao() {

	peca->colesq = peca->coldir = peca->colbaixo = false;

	if (peca->pos.x == 0)
		peca->colesq = true;

	//if (peca->pos.x<tela->sizex - peca->sx && !colidedir()

	if (!(peca->pos.x<tela->sizex - peca->sx))
		peca->coldir = true;

	for (int i = 0; i < peca->sx; i++)
		for (int j = 0; j < peca->sy; j++) {
			if (peca->map[i][j] != ' ')
				if ((peca->pos.y + j >= 0 && tela->table[peca->pos.x + i][peca->pos.y + j + 1] != ' ') || peca->pos.y + peca->sy >= tela->sizey)
					peca->colbaixo = true;
			//if (peca->map[i][j] != ' ' && (tela->table[peca->pos.x + i][peca->pos.y + peca->sy] != ' ') || peca->pos.y + peca->sy >= tela->sizey)
			//	peca->colbaixo = true;
			if (peca->pos.y + j >= 0)
				if (peca->map[i][j] != ' '&& peca->pos.x > 0 && peca->pos.x + peca->sx <= tela->sizex - 1) {
					if (tela->table[peca->pos.x + i - 1][peca->pos.y + j] != ' ')
						peca->colesq = true;
					if (tela->table[peca->pos.x + i + 1][peca->pos.y + j] != ' ')
						peca->coldir = true;
				}
		}
}

void perdeu() {

	char opt;
	system("cls");

	printf("\tVoce perdeu!");

	lerscores();

	if (score > pontuacao[9].score)
		novorecord();
	mostrascores();

	printf("\n\n Deseja Jogar Novamente? (s/n)");

	do{
		opt = getch();
	}while (opt != 'n' && opt != 'N' && opt != 's' && opt != 'S');

	printf("\n");

	if (opt == 'n' || opt == 'N')
		quitgame = true;
	else
		inicializa(tela->sizex, tela->sizey);
}

void lerscores() {

	pontuacao = (highScore*)malloc(sizeof(highScore) * 11);

	int i;

	highscores = fopen("highscores.ttr", "r");

	for (i = 0; i < 10; i++) {
		strcpy(pontuacao[i].name, "DEVEL");
		pontuacao[i].score = 0;
		if (highscores != NULL)
			if(!feof(highscores))
			fscanf(highscores, "%s %d ", &pontuacao[i].name, &pontuacao[i].score);
	}

	if (highscores==NULL){
		gravascores();
	}	
}

void gravascores() {

	highscores = fopen("highscores.ttr", "w");

	for (int i = 0; i < 10; i++){
		fprintf(highscores, "%s %d\n", pontuacao[i].name, pontuacao[i].score);
	}

	fclose(highscores);
}

void novorecord(){

	char tmpnome[6];

	printf("\n\n\tNovo Record!\n\t%d", score);

	printf("\n\tNome: ");
	scanf("%s", &tmpnome);

	strcpy(pontuacao[9].name, tmpnome);

	pontuacao[9].score = score;

	ordenascores();
	gravascores();
}

void ordenascores() {

	for (int i = 0; i < 10; i++){
		for (int j = i; j < 10; j++){
			if (pontuacao[i].score < pontuacao[j].score){
				trocapontos(i, j);
			}
		}
	}
}

void trocapontos(int i, int j) {

	pontuacao[10] = pontuacao[i];
	pontuacao[i] = pontuacao[j];
	pontuacao[j] = pontuacao[10];
}

void mostrascores() {

	system("cls");

	printf("\tVoce perdeu!");
	printf("\n\n  Melhores pontuacoes: \n");
	printf("posicao\tnome \tpontos\n");

	for (int i = 0; i < 10; i++){
		printf("%d      \t%s\t%d\n", i+1, pontuacao[i].name, pontuacao[i].score);
	}
}

//void executajogo() {//fun√ß√£o de execu√ß√£o do jogo - √© aqui que todas as fun√ß√µes necessarias s√£o chamadas em seu tempo
//	if (kbhit())
//		keystroke();
//	if (!defeated) {
//		frame++;								//adiciona 1 no contador de frames
//		if(moveupeca())
//			imprimejogo();
//	if (frame == 60) {						//define a cada quantos frames a pe√ßa se move. Pode ser trocado por variavel de dificuldade
//			descepeca();
//			frame = 0;						//reseta variavel de frames
//		}
//	}
//	else {
//		printf("perdeu!");
//		scanf("%d", &frame);
//		quitgame = true;
//	}
//}

bool moveupeca() {

	if (!peca->moveu)
		return false;

	peca->moveu = false;

	return true;
}

//bool moveupeca() {
//	bool saida=true;
//	if(peca->pos.y+peca->sy>0)
//	for (int i = 0; i < peca->sx && saida; i++)
//		for (int j = 0; j < peca->sy && saida; j++)
//			if (saidatela->table[peca->pos.x+i][peca->pos.y + peca->sy-1] != peca->map[i][peca->sy-1])
//				saida = true;
//			else saida = false;
//	else return false;
//	return saida;
//}



//fun√ß√£o responsavel por inicializar as variaveis do jogo
void inicializa(int sx, int sy) {

	srand(time(NULL));

	peca = (Peca*)malloc(sizeof(Peca));	//aloca√ß√£o da variavel pe√ßa.
	tela = inicializatela(sx, sy);			// \/
	saidatela = inicializatela( sx, sy);	// chamada das fun√ß√µes que inicializam as telas

	score = frame = 0;						//zera score e frame
	defeated = quitgame = false;			//seta variaveis defeated e quitgame

	//imprimetela(tela);						//debug

	inicializapeca(peca); //debug			//inicializa a variavel pe√ßa. Sempre que for gerar uma nova pe√ßa essa fun√ß√£o √© chamada
	posicaopeca(peca, tela->sizex / 2, -peca->sy);				//seta a posi√ß√£o da pe√ßa gerada para o centro da tela

	//imprimejogo();
}

Tela* inicializatela(int sx, int sy) {

	Tela *telai;						//tela temporaria que ser√° retornada
	telai = (Tela*)malloc(sizeof(Tela)); //armazena a tela com blocos ja fixados

	telai->sizex = sx; //define tamanho da tela
	telai->sizey = sy;

	telai->table = (char**)malloc(sizeof(char*)*telai->sizex); //inicializa a tela como espa√ßo em branco

	for (int i = 0; i < telai->sizex; i++) {
		telai->table[i] = (char*)malloc(sizeof(char)*telai->sizey);//alloca√ß√£o da matriz da tela
		for (int j = 0; j < telai->sizey; j++){
			telai->table[i][j] = ' ';
		}
	}
	return telai;//retorna o ponteiro para a tela criada
}

void finaliza(void) {						//libera a memoria alocada para gerar as telas

	for (int i = 0; i < tela->sizex; i++) {
		free(tela->table[i]);
		free(saidatela->table[i]);
	}

	fclose(highscores);

	free(saidatela->table);
	free(saidatela);
	free(tela->table);
	free(tela);
}

bool defeat(){			//retorna o valor da variavel defeated

	return defeated;
}

bool quit() {				//retorna o valor da variavel quitgame

	return quitgame;
}

void keystroke() {			//fun√ß√£o que trata o evento de teclas pressionadas

	int tecla;

	tecla = getch();

	if (tecla == 'p') {
		printf("pausa!");
		do{
			tecla = getch();
		}while (tecla != 'p' && tecla != 62);
	}

	if (tecla == 0 || tecla == 224){	//se forem teclas especiais, pega seu segundo valor
		tecla = getch();
	}
		
	if (tecla == 62){				//se for f4, sai do jogo
		quitgame = true;
	}

	switch (tecla){

	case 72:						//tecla para cima. Gira a pe√ßa
		girapeca(peca);
		if (peca->pos.x+peca->sx > tela->sizex)
			peca->pos.x = tela->sizex-peca->sx;
		break;

//	case 75:						//tecla para esquerda
//		if(peca->pos.x>0 && !colideesq())
//			movepeca(peca, -1, 0);
//		break;

	case 75:						//tecla para esquerda
		if (!peca->colesq)
			movepeca(peca, -1, 0);
		break;

	case 77:						//tecla para direita
		if (!peca->coldir)
			movepeca(peca, 1, 0);
		break;

	//case 77:						//tecla para direita
	//	if(peca->pos.x<tela->sizex-peca->sx && !colidedir())
	//		movepeca(peca, 1, 0);
	//	break;

	case 80:
		descerapido();
		break;

	default:
		break;
	}
}
//4\100+3*100
//3\100+2*100
//2\100+1*100
//1\100+0*100

void descerapido() {

	int linhas=0;

	//do{
		descepeca();
		vercolisao();
		pecatela();
	//}while (peca->pos.y>0);

	//movepeca(peca, 0, linhas);
}

/*void executajogo() {//fun√ß√£o de execu√ß√£o do jogo - √© aqui que todas as fun√ß√µes necessarias s√£o chamadas em seu tempo

	if (!defeated) {
		system("cls");							//apaga tela
		frame++;								//adiciona 1 no contador de frames
		pecatela();								//faz interpola√ß√£o da pe√ßa e da tela "saidatela"
		printf("score: %d", score);				//imprime score
		imprimetela(saidatela);					//imprime matriz da tela "saidatela"
		//imprimetela(tela);						//imprime a tela fixa -- DEBUG
		if (frame == 8) {						//define a cada quantos frames a pe√ßa se move. Pode ser trocado por variavel de dificuldade
			descepeca();
			frame = 0;						//reseta variavel de frames
		}
	}
	else {
		printf("perdeu!");
		scanf("%d", &frame);
		quitgame = true;
	}
}*/

void imprimejogo() {

	system("cls");								//apaga tela

	pecatela();									//faz interpola√ß√£o da pe√ßa e da tela "saidatela"

	printf("score: %d", score);					//imprime score

	imprimetela(saidatela);						//imprime matriz da tela "saidatela"
}

void pecatela() {				//fun√ß√£o que comuta tela e pe√ßa

	for (int i = 0; i < tela->sizey; i++)
		for (int j = 0; j < tela->sizex; j++) {
			if (i >= peca->pos.y && i < peca->pos.y + peca->sy && j >= peca->pos.x && j < peca->pos.x + peca->sx && peca->map[j-peca->pos.x][i-peca->pos.y]!=' ')
				saidatela->table[j][i] = peca->map[j-peca->pos.x][i-peca->pos.y];
			else
			saidatela->table[j][i] = tela->table[j][i];			//transfere a matris da tela para a saidatela
		}

	//for (int i = 0; i < peca->sy; i++)
		//for (int j = 0; j < peca->sx; j++)
			//saidatela->table[j + peca->pos.x][i + peca->pos.y] = peca->map[j][i];	//adiciona a pe√ßa em saidatela
}

void descepeca() {

	bool espacolivre = peca->colbaixo;

		/*true;
	for (int i = 0; i < peca->sx; i++)
		for (int j = -1; j < peca->sy; j++)
			if(espacolivre)
				if (peca->map[i][j] != ' ')
					if ((peca->pos.y + j>=0 && tela->table[peca->pos.x + i][peca->pos.y + j + 1] != ' ') || peca->pos.y + peca->sy >= tela->sizey)
						espacolivre = false;*/

	if (!espacolivre)
	movepeca(peca, 0, 1); 
	else {
		if(peca->pos.y+1 < 0)
			defeated = true;

		verlinha();
		transferetela();
		inicializapeca(peca);
		posicaopeca(peca, tela->sizex / 2, -peca->sy); //codigo para definir a posi√ß√£o da pe√ßa
	}
}

void transferetela() {

	for (int i = 0; i < tela->sizex; i++)
		for (int j = 0; j < tela->sizey; j++)
			tela->table[i][j] = saidatela->table[i][j];
}

void verlinha() {

	int count=0, combo=0;

	for (int j = 0; j < tela->sizey; j++) {
		for (int i = 0; i < tela->sizex; i++) {
			if (saidatela->table[i][j] == ' '){
				break;
			}
			count++;
		}
		if (count == tela->sizex) {
			combo++;
			removelinha(j);
			score += 100 + (combo-1) * 100;
		}
		count = 0;
	}
}

void removelinha(int l) {

	for (int i = 0; i < tela->sizex; i++){
		for (int j = l; j > 0; j--){
			saidatela->table[i][j] = saidatela->table[i][j - 1];
		}
	}

	if(l==0){
		for (int i = 0; i <tela->sizex; i++){
			saidatela->table[i][0] = ' ';
		}
	}
}
