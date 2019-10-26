#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

// Assinaturas de metodos.
void limparConteudoString(char palavra[]);
int isQuebraLinha(int ascii);
int isCondicaoParada(int ascii);
int isPalavraReservada(char *palavra);
void exibirError(char *palavra, int tipoError, int nuLinha);
void apresentarMemoriaConsumida();
void calcularMemoria(int tipo, int valor);

char palavraReservada[12][11] = {"funcao", "principal", "retorno", "ler", "escrever", "testar", "falso", "verdadeiro", "repetir", "inteiro", "caracter", "real"};
int MEMORIA_CONSUMIDA = 0;
int MEMORIA_MAXIMA = 1024000; //  1024 Kilobytes = 1024000  bytes

void main(){
    printf("===========================================\n");
    printf("Seja bem-vinda ao compilador da Flavia\n");
    printf("===========================================\n\n");
    
    char acumulador[UCHAR_MAX];
    char caracter;
    int nuLinha = 1;
    int ascii;
    int count = 0;

    calcularMemoria(1, sizeof(palavraReservada));
    calcularMemoria(1, sizeof(acumulador));
    calcularMemoria(1, sizeof(nuLinha));
    calcularMemoria(1, sizeof(ascii));
    calcularMemoria(1, sizeof(count));

    // Limpando lixo de memoria.
    limparConteudoString(acumulador);

    // Ler arquivo e verificar se não existe
    char url_arquivo[]="arquivo_teste.txt";
    FILE *arquivo;
    arquivo = fopen(url_arquivo, "r");

    calcularMemoria(1, sizeof(url_arquivo));
    calcularMemoria(1, sizeof(arquivo));
 
    if (arquivo == NULL) {
        printf("Erro, favor verificar a existência deste arquivo.\n");
        exit(0);
    }

    while((caracter = fgetc(arquivo)) != EOF) {
        ascii = (int) caracter;
        

        if (!isCondicaoParada(ascii)) {
            acumulador[count] = caracter;
            count ++;
            //printf("Entrou aqui\n");
            //printf("Linha->%d - %d - %c - %s \n", nuLinha, ascii, caracter, acumulador);
        
        } else {
            
            if (isPalavraReservada(acumulador)) {
                // Validar ler

                // Validar escrever

                // Validar testar

                // Validar repetir

                // Validar verdadeiro

                // Validar falso
                
                // Validar inteiro

                // Validar caracter

                // Validar real


                
            } else {
                // Verifica se o acumulador esta vazio.
                if (strlen(acumulador) > 0) {
                    // Nao e uma palavra reservada.
                    exibirError(acumulador, 1, nuLinha);
                }
            }

            // Final da palavra encontrada
            count = 0;
            limparConteudoString(acumulador);

        }
        printf("--> Linha->%d - %d - %s \n", nuLinha, ascii, acumulador);

        //puts(acumulador);


        // Validar condicao de parada


        //printf("Linha->%d - %d - %c - %s \n", nuLinha, ascii, caracter, acumulador);
        // Verifica se é uma quebra de linha.
        if (isQuebraLinha(ascii)) {
            nuLinha = nuLinha + 1;
        }

        if (isQuebraLinha(ascii)) {
            count = 0;
            limparConteudoString(acumulador);
        }
    }

    apresentarMemoriaConsumida();
    fclose(arquivo);

    printf("\n\n");
    system("pause");
}

int isQuebraLinha(int ascii) {
    calcularMemoria(1, sizeof(ascii));
    if (ascii == 10 || ascii == 13) {
        return 1;
    }
    return 0;
}

int isCondicaoParada(int ascii) {
    calcularMemoria(1, sizeof(ascii));
    if (
        (ascii != 10) && // \0 -> 10
        (ascii != 32) && // espaco -> 32
        (ascii != 40) && // ( -> 40 
        (ascii != 41) && // ) -> 41
        (ascii != 59) && // ; -> 59
        (ascii != 123) && // { -> 123
        (ascii != 125) && // } -> 125
        (ascii != 44) && // , -> 44
        (ascii != 36) && // $ -> 36
        (ascii != 33) && // ! -> 33
        (ascii != 58) && // : -> 58
        (ascii != 10) && // Line Feed - LF (Windows) -> 10
        (ascii != 13) // Enter - CR (Unix) -> 13
    ) {
        return 0;
    }
    return 1;
}

int isPalavraReservada(char *palavra) {
    int i;

    calcularMemoria(1, sizeof(i));

    for (i = 0; i < 12; i++) {
		if (strcmp(palavra, palavraReservada[i]) == 0) {
			return 1;
		}		
	}
    return 0;
}

void limparConteudoString(char palavra[]) {
	int i = 0;
    calcularMemoria(1, sizeof(i));

	while (i < UCHAR_MAX) {
		palavra[i] = '\0';
		i ++;
	}
}

void exibirError(char *palavra, int tipoError, int nuLinha) {
    switch(tipoError) {
        case 1:
            printf("Linha[%d] - o valor nao e identificado - (%s).\n", nuLinha, palavra);
            exit(0);
        break;

        default:
            printf("O tipo de erro informado nao existe.\n");
        break; 
    }
}
// Tipo 1 adiciona memoria.
void calcularMemoria(int tipo, int valor) {
    if (tipo == 1) {
		MEMORIA_CONSUMIDA = MEMORIA_CONSUMIDA + valor;
	} else {
		MEMORIA_CONSUMIDA = MEMORIA_CONSUMIDA - valor;
	}

	float porcentagem = 0;
	if (MEMORIA_MAXIMA > 0) {
		porcentagem = (MEMORIA_CONSUMIDA * 100) / MEMORIA_MAXIMA;
	}

	if (porcentagem > 90 && porcentagem < 99) {
		printf("Sua memoria esta entre 90 %% a 99 %% do total disponível, memoria atual: %.2f %%\n\n", porcentagem);
	}

	if (MEMORIA_CONSUMIDA > MEMORIA_MAXIMA) {
        printf ("Memoria ultrapassou o limite disponivel.\n");

        apresentarMemoriaConsumida();
        exit(0);
	}
}

void apresentarMemoriaConsumida() {
	printf("\nCONSUMO DE MEMORIA: %d bytes\n\n", MEMORIA_CONSUMIDA);
	float porcentagem = 0;
	if (MEMORIA_MAXIMA > 0) {
		porcentagem = (MEMORIA_CONSUMIDA * 100) / MEMORIA_MAXIMA;
	}	 

	printf("Porcentagem consumida => %.2f %% de %i bytes\n\n" , porcentagem, MEMORIA_MAXIMA);
}

