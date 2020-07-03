#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Forca.h"

int errosTotais = 0;
char letraAtual;

void abertura () {

	printf(" _______________\n");
	printf("|               |\n");
	printf("| JOGO DA FORCA |\n");
	printf("|_______________|\n\n");
	printf("  _ _ _ _\n");
	printf(" |       |\n");
	printf(" |		\n");
	printf(" |		\n");
	printf(" |		\n");
	printf("_|_		\n\n");

}

void imagemVitoria () {
	printf("\nBOA!\n");
	printf("  _ _ _ _\n");
	printf(" |       |            Obrigado!\n");
	printf(" |               (_) /\n");
	printf(" |              --|--\n");
	printf(" |               |-|\n");
	printf("_|_\n\n");
}

void contaErros ( int* chutesdados, char* palavra, char* chutes ) {

	int existe = 0;

	for ( int i = 0; i < strlen(palavra); i++ ) {

		if ( letraAtual == palavra[i] ) {
			existe = 1;
			break;
		}
	}
	if ( !existe ) {
		errosTotais++;
	}
}

void desenhaForca ( int* chutesdados, char* palavra, char* chutes ) {

	if ( errosTotais == 0 ) {
		printf("  _ _ _ _\n");
		printf(" |       |\n");
		printf(" |		\n");
		printf(" |		\n");
		printf(" |		\n");
		printf("_|_		\n");
	}
	else if ( errosTotais == 1 ) {
		printf("  _ _ _ _\n");
		printf(" |       |\n");
		printf(" |      (_)\n");
		printf(" |		\n");
		printf(" |		\n");
		printf("_|_		\n");
	}
	else if ( errosTotais == 2 ) {
		printf("  _ _ _ _\n");
		printf(" |       |\n");
		printf(" |      (_)\n");
		printf(" |       |\n");
		printf(" |		\n");
		printf("_|_		\n");
	}
	else if ( errosTotais == 3 ) {
		printf("  _ _ _ _\n");
		printf(" |       |\n");
		printf(" |      (_)\n");
		printf(" |     --|\n");
		printf(" |		\n");
		printf("_|_		\n");
	}
	else if ( errosTotais == 4 ) {
		printf("  _ _ _ _\n");
		printf(" |       |\n");
		printf(" |      (_)\n");
		printf(" |     --|--\n");
		printf(" |		\n");
		printf("_|_		\n");
	}
	else if ( errosTotais == 5 ) {
		printf("\n  _ _ _ _   MORRI!\n");
		printf(" |       | /\n");
		printf(" |      (_)\n");
		printf(" |     --|--\n");
		printf(" |      |-|\n");
		printf("_|_		\n");
		printf("     GAMEOVER\n");
	}
}

void errofopen ( FILE* f ) {
	if ( f == 0 ) {
		printf("Erro no banco de dados.\n");
		exit(1);
	}
}

/*Compara as letras com os chutes*/
int compara ( char letra, char* chutes, int chutesdados ) {

	int achou = 0;

	for( int j = 0; j < chutesdados; j++ ) {
                if ( chutes[j] == letra ) {
                	achou = 1;
                        break;
        	}
	}
	return achou;
}

/*Verifica se acertou todas as letras*/
int ganhou ( char* palavra, char* chutes, int chutesdados ) {

	for ( int i = 0; i < strlen(palavra); i++ ) {
		if ( !compara(palavra[i], chutes, chutesdados) ) {
			return 0;
		}
	}
	return 1;
}

/*Imprime a letra(se acertou) ou um traço(se errou)*/
void imprimeEspacos ( char* palavra, char* chutes, int chutesdados ) {

        for ( int i = 0; i < strlen(palavra); i++ ) {
                if ( compara( palavra[i], chutes, chutesdados ) ) {
                        printf("%c ", palavra[i]);
                }
                else {
                        printf("_ ");
                }
        }
        printf("\n");
}

/*Recebe a letra do chute*/
void chuta ( char chutes[26], int* chutesdados ) {

	char chute;
        printf("Qual letra? ");
        scanf(" %c", &chute);
        chutes[*chutesdados] = chute;
		letraAtual = chute;
        (*chutesdados)++;

}

/*Recebe a palavra secreta*/
void palavrasecreta ( char* palavra ) {

	FILE* f;
	f = fopen("Palavras.txt", "r");

	errofopen( f );

	int qtdpalavras;
	fscanf(f, "%d", &qtdpalavras);

	srand( time(0) );
	int randomico = rand() % qtdpalavras;

	for ( int i = 0; i <= randomico; i++ ) {
		fscanf(f, "%s", palavra);
	}
	fclose(f);
}

/*Verifica se errou o máximo de tentativas(foi enforcado)*/
int enforcou ( int* chutesdados, char* palavra, char* chutes ) {

	int erros = 0;

	for ( int i = 0; i < *chutesdados; i++ ) {

		int existe = 0;

		for ( int j = 0; j < strlen(palavra); j++ ) {

			if ( chutes[i] == palavra[j] ) {
				existe = 1;
				break;
			}
		}
		if ( !existe ) {
			erros++;
		}
	}

	if ( erros >= 5 ) {
		printf("\nA palavra secreta era: %s\n", palavra);
	}

	return erros >= 5;
}

void adicionapalavra () {
	char quer;

	printf("\nQuer adicionar uma palavra no jogo (S/N)?\nResposta: ");
	scanf(" %c", &quer);

	if ( quer == 'S' || quer == 's' ) {

		char novapalavra[60];

		printf("Digite a palavra: ");
		scanf("%s", novapalavra);
		
		FILE* f;
		f = fopen("Palavras.txt", "r+");

		errofopen( f );	

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		printf("OK!\n");

		fclose(f);
	}
}

int main () {

	char palavra[26];
	char chutes[26];

	int chutesdados = 0;

	abertura();
	palavrasecreta(palavra);

	do {

		imprimeEspacos( palavra, chutes, chutesdados );
		chuta( chutes, &chutesdados );
		contaErros(&chutesdados, palavra, chutes);
		desenhaForca(&chutesdados, palavra, chutes);
	
		printf("%d\n", errosTotais);

		if ( ganhou(palavra, chutes, chutesdados) ) {
			imagemVitoria();
		}

	}while( !ganhou(palavra, chutes, chutesdados) && !enforcou( &chutesdados, palavra, chutes ) );

	adicionapalavra();

	return 0;
}
