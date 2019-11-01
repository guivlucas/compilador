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
int isAspasDuploBalanceamentValido(char *palavra);
void removerQuebraLinha(char* palavra);
int isPalavraReservadaPrincipal(char *palavra);
int isTipoDeVariavel(char *palavra);
int isVerificaDeclaracaoVariavel(char *palavra, int nuLinha);


char palavraReservada[12][11] = {"funcao", "principal", "retorno", "ler", "escrever", "testar", "falso", "verdadeiro", "repetir", "inteiro", "caracter", "real"};
int MEMORIA_CONSUMIDA = 0;
int MEMORIA_MAXIMA = 1024000; //  1024 Kilobytes = 1024000  bytes

// Estrutura baseada no site: https://programacaodescomplicada.wordpress.com/complementar/
typedef struct simbolo {
	char tipo_dado[UCHAR_MAX];
    char nome_variavel[UCHAR_MAX];
    char possivel_valor[UCHAR_MAX];
    char funcao_modulo[UCHAR_MAX];
} Simbolo;

typedef struct elemSimbolo {
    struct elemSimbolo *ant;
    Simbolo dados;
    struct elemSimbolo *prox;
} ElemSimbolo;

typedef struct elemSimbolo* TabelaSimbolo;

TabelaSimbolo* criaListaTabelaSimbolo();
int insereFinalTabelaSimbolo(TabelaSimbolo* lista, Simbolo simbolo);
int tamanhoTabelaSimbolo(TabelaSimbolo* lista);
int isVazioTabelaSimbolo(TabelaSimbolo* lista); 
void imprimeTabelaSimbolo(TabelaSimbolo* lista);


void main(){
    printf("===========================================\n");
    printf("Seja bem-vinda ao compilador da Flavia\n");
    printf("===========================================\n\n");
    
    char acumulador[UCHAR_MAX];
    char caracter;
    int nuLinha = 1;
    int ascii;
    int count = 0; 
    int countLinha = 0;
    int quantidadeParenteses = 0;
    char acumuladorLinha[UCHAR_MAX];
    char nomeTipoVariavel[UCHAR_MAX];
    char nomeTipoFuncao[UCHAR_MAX];
    char nomeVariavel[UCHAR_MAX];
    int quantidadeColchete = 0;
    int quantidadeChaves = 0;
    int isAspasValidas = 0;
    int isPrincipalExistente =0;
    int isPossuiDeclaracaoVariavel =0;
    int isVariavelValida =0;



    calcularMemoria(1, sizeof(palavraReservada));
    calcularMemoria(1, sizeof(acumulador));
    calcularMemoria(1, sizeof(nuLinha));
    calcularMemoria(1, sizeof(ascii));
    calcularMemoria(1, sizeof(count));
    calcularMemoria(1, sizeof(acumuladorLinha));
    calcularMemoria(1, sizeof(countLinha));

    // Limpando lixo de memoria.
    limparConteudoString(acumulador);
    limparConteudoString(acumuladorLinha);
    limparConteudoString(nomeTipoVariavel);
    limparConteudoString(nomeTipoFuncao);
    limparConteudoString(nomeVariavel);

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

   
    TabelaSimbolo* novaTabelaSimbolos = criaListaTabelaSimbolo();
    /*
    Simbolo novoSimbolo;
    strcpy(novoSimbolo.tipo_dado, "inteiro");
    strcpy(novoSimbolo.nome_variavel, "$quantidade");
    strcpy(novoSimbolo.possivel_valor, "190");
    strcpy(novoSimbolo.funcao_modulo, "principal");

    Simbolo novoSimbolo2;
    strcpy(novoSimbolo2.tipo_dado, "caracter");
    strcpy(novoSimbolo2.nome_variavel, "$nome");
    strcpy(novoSimbolo2.possivel_valor, "teste");
    strcpy(novoSimbolo2.funcao_modulo, "principal");

    insereFinalTabelaSimbolo(novaTabelaSimbolos, novoSimbolo);
    insereFinalTabelaSimbolo(novaTabelaSimbolos, novoSimbolo2);

    imprimeTabelaSimbolo(novaTabelaSimbolos);

    exit(0);
    */
    // -----------------------------------------------------------------------------------

    while((caracter = fgetc(arquivo)) != EOF) {
        ascii = (int) caracter;
        acumuladorLinha[countLinha] = caracter;
        countLinha ++;

        // Verifica abertura de parenteses
        if (ascii == 40) {
            quantidadeParenteses ++;
        }

        // Verifica fechamento de parenteses
        if (ascii == 41) {
            quantidadeParenteses --;
        }       

        // Verifica abertura de colchetes
        if (ascii == 91) {
            quantidadeColchete ++;
        }

        // Verifica fechamento de colchetes
        if (ascii == 93) {
            quantidadeColchete --;
        }       

        // Verifica abertura de Chaves
        if (ascii == 123) {
            quantidadeChaves ++;
        }

        // Verifica fechamento de Chaves
        if (ascii == 125) {
            quantidadeChaves --;
        }
  
        if (!isCondicaoParada(ascii)) {
            acumulador[count] = caracter;
            count ++;
            //printf("Entrou aqui\n");
            //printf("Linha->%d - %d - %c - %s \n", nuLinha, ascii, caracter, acumulador);
        
        } else {
            printf("Condicao de parada %d - (%c)\n", ascii, caracter);
            if (isPalavraReservada(acumulador)) {
                // Validar principal
                if (isPalavraReservadaPrincipal(acumulador)) {
                    strcpy(nomeTipoFuncao, acumulador);
                    isPrincipalExistente++; 
                }

                // Validar tipo de dado
                if (isTipoDeVariavel(acumulador)) {
                    isPossuiDeclaracaoVariavel++;
                    strcpy(nomeTipoVariavel, acumulador);
                    printf("Tipo variável. (%s) - (%s)\n ", nomeTipoVariavel, nomeTipoFuncao);
                }

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
                    // Verifica se é um tipo de variável válido.

                    isVariavelValida = isVerificaDeclaracaoVariavel(acumulador, nuLinha);

                    if (!isVariavelValida) {
                        // Nao e uma palavra reservada.
                        exibirError(acumulador, 1, nuLinha);
                    }else{
                        // Variavel valida
                        strcpy(nomeVariavel, acumulador);


                        // Salvando a tabela de símbolos
                        Simbolo novoSimbolo;
                        strcpy(novoSimbolo.tipo_dado, nomeTipoVariavel);
                        strcpy(novoSimbolo.nome_variavel, nomeVariavel);
                       // strcpy(novoSimbolo.possivel_valor, "teste");
                        strcpy(novoSimbolo.funcao_modulo, nomeTipoFuncao);

                        insereFinalTabelaSimbolo(novaTabelaSimbolos, novoSimbolo);

                    }
                }
            }

            // Final da palavra encontrada
            count = 0;
            limparConteudoString(acumulador);

        }
        printf("--> Linha->%d - %d - %s \n", nuLinha, ascii, acumulador);


        // Verifica "$"
        if (ascii == 36) {
            acumulador[count] = caracter;
            count ++; 
        }

        //puts(acumulador);

        

        //printf("Linha->%d - %d - %c - %s \n", nuLinha, ascii, caracter, acumulador);
        // Verifica se é uma quebra de linha.
        if (isQuebraLinha(ascii)) {
            
            if (quantidadeParenteses != 0) {
                exibirError(acumuladorLinha, 2, nuLinha);
            }

            if (quantidadeColchete != 0) {
                exibirError(acumuladorLinha, 3, nuLinha);
            }

            // Verificar duplo balanceamento de aspas.
            isAspasValidas = isAspasDuploBalanceamentValido(acumuladorLinha);
			if (!isAspasValidas) {
				exibirError(acumuladorLinha, 5, nuLinha);
			}

            // Verifica se existe mais de uma declaracao de principal
            if (isPrincipalExistente > 1) {
                char a[] = {""};
                exibirError(a, 6, 0);
            }

            isPossuiDeclaracaoVariavel =0;
            limparConteudoString(nomeTipoVariavel);    
            isVariavelValida =0;
            limparConteudoString(nomeVariavel);

            nuLinha = nuLinha + 1;
        }

        if (isQuebraLinha(ascii)) {
            count = 0;
            countLinha = 0;
            limparConteudoString(acumulador);
            limparConteudoString(acumuladorLinha);
        }
    } // Final do While

    if(isPrincipalExistente ==0){
        char a[] = {""};
        exibirError(a, 7, 0);
    }

    if (quantidadeChaves != 0) {
        char a[] = {""};
        exibirError(a, 4, 0);
    }

    imprimeTabelaSimbolo(novaTabelaSimbolos);
    apresentarMemoriaConsumida();

    // Limpando memoria consumida.
    calcularMemoria(0, sizeof(palavraReservada));
    calcularMemoria(0, sizeof(acumulador));
    calcularMemoria(0, sizeof(nuLinha));
    calcularMemoria(0, sizeof(ascii));
    calcularMemoria(0, sizeof(count));
    calcularMemoria(0, sizeof(url_arquivo));
    calcularMemoria(0, sizeof(arquivo));

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
        (ascii != 9) && // tab -> 32
        (ascii != 32) && // espaco -> 32
        (ascii != 40) && // ( -> 40 
        (ascii != 41) && // ) -> 41
        (ascii != 59) && // ; -> 59
        (ascii != 123) && // { -> 123
        (ascii != 125) && // } -> 125
        (ascii != 91) && // [ -> 91
        (ascii != 93) && // ] -> 93
        (ascii != 44) && // , -> 44
        (ascii != 36) && // $ -> 36
        (ascii != 33) && // ! -> 33
        (ascii != 58) && // : -> 58
        (ascii != 34) && // : -> 34
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
        
        case 2:
            printf("Linha[%d] - o duplo balanceamento de parenteses esta incorreto - (%s).\n", nuLinha, palavra);
            exit(0);
        break;

        case 3:
            printf("Linha[%d] - o duplo balanceamento de colchete esta incorreto - (%s).\n", nuLinha, palavra);
            exit(0);
        break;

        case 4:
            printf("O duplo balanceamento de chave esta incorreto. Favor verificar.\n");
            exit(0);
        break;

        case 5:
            removerQuebraLinha(palavra);
            printf("Linha[%d] - o duplo balanceamento de aspas esta incorreto. - (%s).\n", nuLinha, palavra);
            exit(0);
        break;

        case 6:
            printf("Ja foi declarado anteriormente a funcao principal. \n");
            exit(0);
        break;

        case 7:
            printf("Modulo principal inexistente.\n");
            exit(0);
        break;

        case 8:
            printf("Linha[%d] - a declaracao da variavel e invalida. - (%s).\n", nuLinha, palavra);
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

int isAspasDuploBalanceamentValido(char *palavra) {
	int i, ascii, hasAspas = 0;

	if (strlen(palavra) == 0) {
		return 1;
	}

	for (i = 0; i < strlen(palavra); i++) {
		ascii = (int) palavra[i];
		// se for igual " -> 34
		if (ascii == 34 && hasAspas > 0) {
			hasAspas--;
			continue;
		}

		// se for igual " -> 34
		if (ascii == 34 && hasAspas == 0) {
			hasAspas++;
			continue;
		}
	}

	if (hasAspas == 0) {
		return 1;
	}
	return 0;
}

void removerQuebraLinha(char* palavra) {
	int i, valorAscii, count = 0;
	char palavraTemporaria[UCHAR_MAX];
	limparConteudoString(palavraTemporaria);

	for (i = 0; i < strlen(palavra); i++) {
		valorAscii = (int) palavra[i];

		// Line Feed = LF (Windows) => 10
		// Enter = CR (Unix) => 13
		if ((valorAscii != 13) && (valorAscii != 10)) {
			palavraTemporaria[count] = palavra[i];
			count++;
		}
	}

	strcpy(palavra, palavraTemporaria);

	calcularMemoria(sizeof(i), 1);
	calcularMemoria(sizeof(valorAscii), 1);
	calcularMemoria(sizeof(count), 1);
	calcularMemoria(sizeof(palavraTemporaria), 1);
}

int isPalavraReservadaPrincipal(char *palavra) {
    if (strcmp(palavra, palavraReservada[1]) == 0) {
        return 1;
    }
    return 0;
}

int isTipoDeVariavel(char *palavra) {
    // Verifica inteiro
    if (strcmp(palavra, palavraReservada[9])) {
        return 1;
    }

    // Verifica caracter
    if (strcmp(palavra, palavraReservada[10])) {
        return 1;
    }

    // Verificar real
    if (strcmp(palavra, palavraReservada[11])) {
        return 1;
    }

    return 0;
}

int isVerificaDeclaracaoVariavel(char *palavra, int nuLinha) {
    int isValido = 0, i, ascii;

	ascii = (int) palavra[0];

	// verifica se a palavra inicializa com $ = 36
	if (ascii == 36) {
		// apenas a-z
		if ((int) palavra[1] >= 97 && (int) palavra[1] <= 122) {
			isValido = 1;
		} else {
			exibirError(palavra, 8, nuLinha);
            return 0;
		}

		for (i = 2; i < strlen(palavra); i++) {
			ascii = (int) palavra[i];

			// permiter apenas a-z, 0-9, A-Z, [, ], .
			if (! (
                (ascii >= 97 && ascii <= 122) || 
                (ascii >= 48 && ascii <= 57) || 
                (ascii >= 65 && ascii <= 90) ||
                (ascii == 91 || ascii == 93 || ascii == 46))
            )
            {
				isValido = 0;
				// printf("\n[Declaracao variavel]\n");
			    exibirError(palavra, 8, nuLinha);
			}
		}
	}

	return isValido;
}
// ------------------------------------------------------------

TabelaSimbolo* criaListaTabelaSimbolo() {
    TabelaSimbolo* lista = (TabelaSimbolo*) malloc(sizeof(TabelaSimbolo));

    if (lista != NULL) {
        *lista = NULL;
    }

    return lista;
}

void liberaListaTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista != NULL) {
        ElemSimbolo* no;

        while ((*lista) != NULL) {
            no = *lista;
            *lista = (*lista)->prox;
            free(no);
        }

        free(lista);
    }
}

int insereFinalTabelaSimbolo(TabelaSimbolo* lista, Simbolo simbolo) {
    if (lista == NULL) {
        return 0;
    }

    ElemSimbolo *no;
    no = (ElemSimbolo*) malloc(sizeof(ElemSimbolo));
    if (no == NULL) {
        return 0;
    }

    no->dados = simbolo;
    no->prox = NULL;

    // lista vazia: insere inicio
    if ((*lista) == NULL) {
        no->ant = NULL;
        *lista = no;
    } else {
        ElemSimbolo *aux;
        aux = *lista;

        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int tamanhoTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista == NULL) {
        return 0;
    }

    int cont = 0;
    ElemSimbolo* no = *lista;

    while (no != NULL) {
        cont++;
        no = no->prox;
    }

    return cont;
}

int isVazioTabelaSimbolo(TabelaSimbolo* lista) {
	int isVazio = 0;

    if (lista == NULL) {
        isVazio = 1;
    }

    if (*lista == NULL) {
        isVazio = 1;
    }

    return isVazio;
}

void imprimeTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista == NULL) {
        return;
    }

    printf("====================================================================\n");
    printf("# TABELA DE SIMBOLOS \n");
    printf("====================================================================\n");
    
    ElemSimbolo* no = *lista;

    if (isVazioTabelaSimbolo(lista)) {
    	printf("# A TABELA DE SIMBOLOS ESTA VAZIA.\n");
    	printf("====================================================================\n\n");
	}

    while (no != NULL) {
        printf("Funcao/modulo: %s \n", no->dados.funcao_modulo);
        printf("Tipo de dado: %s \n", no->dados.tipo_dado);
        printf("Nome da variavel: %s \n", no->dados.nome_variavel);
        printf("Possivel valor: %s \n", no->dados.possivel_valor);
        printf("====================================================================\n");
        no = no->prox;
    }
}




