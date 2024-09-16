#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"
typedef struct fracao fracao;
typedef struct movimento movimento;
typedef struct registro registro;

// le um unico registro do arquivo base;
void ler_registro(registro* a, FILE* base) {
    fscanf(base, "%11s", a->cpf); fgetc(base);
    fscanf(base, "%6s", a->senha); fgetc(base);
    fgets(a->nome, sizeof(a->nome), base);

    freceber(base, &a->reais);
    freceber(base, &a->bitcoin);
    freceber(base, &a->etherium);
    freceber(base, &a->ripple);

	fscanf(base, "%d", &a->quantidade_movimentos);
	a->movimentos = malloc(a->quantidade_movimentos * sizeof(movimento));

	for (int i = 0; i < a->quantidade_movimentos; i++) {
		fscanf(base, "%11s", a->movimentos[i].data);
		fgetc(base);
		fgets(a->movimentos[i].descricao, sizeof(a->movimentos[i].descricao), base);
		freceber(base, &a->movimentos[i].reais);
		freceber(base, &a->movimentos[i].bitcoin);
		freceber(base, &a->movimentos[i].etherium);
		freceber(base, &a->movimentos[i].ripple);
	}
}

// le a base toda;
registro* ler_base(int* quantidade_registros) {
    FILE* base = fopen("base_registros.txt", "r");

    fscanf(base, "%d", quantidade_registros);
    registro* registros = malloc(*quantidade_registros * sizeof(registro));

    for (int i = 0; i < *quantidade_registros; i++) {
        ler_registro(&registros[i], base);
    }

    fclose(base);
    return registros;
}

// grava um unico registro no arquivo base;
void gravar_registro(registro* a, FILE* base) {
	fprintf(base, "%s\n", a->cpf);
	fprintf(base, "%s\n", a->senha);
	fprintf(base, "%s", a->nome);
	fprintar(base, a->reais, '\n');
	fprintar(base, a->bitcoin, '\n');
	fprintar(base, a->etherium, '\n');
	fprintar(base, a->ripple, '\n');
	fprintf(base, "%d\n", a->quantidade_movimentos);
	for (int i = 0; i < a->quantidade_movimentos; i++) {
		fprintf(base, "%s\n", a->movimentos[i].data);
		fprintf(base, "%s", a->movimentos[i].descricao);
		fprintar(base, a->movimentos[i].reais, '\n');
		fprintar(base, a->movimentos[i].bitcoin, '\n');
		fprintar(base, a->movimentos[i].etherium, '\n');
		fprintar(base, a->movimentos[i].ripple, '\n');
	}
}

// grava a base toda;
void gravar_base(registro* registros, int quantidade_registros) {
	FILE* base = fopen("base_registros.txt", "w");

	fprintf(base, "%d\n", quantidade_registros);
	for (int i = 0; i < quantidade_registros; i++) {
		gravar_registro(&registros[i], base);
	}

	for (int i = 0; i < quantidade_registros; i++) {
		free(registros[i].movimentos);
	}
    free(registros);
	fclose(base);
}

cotacao ler_cotacao() {
	FILE* base_cotacao = fopen("base_cotacao.txt", "r");
	cotacao	resposta;

	freceber(base_cotacao, &resposta.bitcoin);
	freceber(base_cotacao, &resposta.etherium);
	freceber(base_cotacao, &resposta.ripple);
	return resposta;
}

void gravar_cotacao(cotacao cotacao_atual) {
	FILE* base_cotacao = fopen("base_cotacao.txt", "w");
	cotacao	resposta;

	fprintar(base_cotacao, cotacao_atual.bitcoin, '\n');
	fprintar(base_cotacao, cotacao_atual.etherium, '\n');
	fprintar(base_cotacao, cotacao_atual.ripple, '\n');
}
