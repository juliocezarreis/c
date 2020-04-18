#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define valido1 0
#define valido2 99

int main( void ) {

	// imprime cabecalho do nosso jogo
	printf("********************\n");
	printf("*Jogo de Advinhacao*\n");
	printf("********************\n");
	//gerar o numero
	int segundos = time(0);
	srand(segundos);
	int n = rand();
	int numerosecreto = n % 100;

	int chute;
	int tentativas;
	tentativas = 1;

	while(1) {
		printf("\nTentativa %d\n", tentativas);
		printf("Qual é o seu chute? ");
		scanf("%d", &chute);

		if(chute < valido1 || chute > valido2) {
			printf("Chute invalido!\n");
			continue;
		}
		int acertou = (chute == numerosecreto);
		int maior = chute > numerosecreto;

		if(acertou) {
			printf("\nBEM NA MOSCA! Em %d tentativas\n" , tentativas);
        		printf("Fim de jogo!\n");
			printf("Jogar novamente?\n1 - yeep\n0 - noop\n");
			printf("Resposta: ");
			int jogar;
			scanf("%d", &jogar);
			if(jogar == 1) {
				srand(time(0));
				numerosecreto = rand() % 100;
				tentativas = 1;
				continue;
			}
			else {
			break;
			}
		}
		else if(maior) {
			printf("Seu chute foi maior ;)\n");
		}
		else {
			printf("Seu chute foi menor ;)\n");
		}
	tentativas++;
	}
}
