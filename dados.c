#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"
typedef struct fracao fracao;
typedef struct movimento movimento;
typedef struct registro registro;

// le um unico registro do arquivo base;
void ler_registro(registro* a, FILE* base) {
    fread(a->cpf, sizeof(char), 12, base);
    fread(a->senha, sizeof(char), 7, base);
    fread(a->nome, sizeof(char), sizeof(a->nome), base);
    
    freceber(base, &a->reais);
    freceber(base, &a->bitcoin);
    freceber(base, &a->etherium);
    freceber(base, &a->ripple);
    
    fread(&a->quantidade_movimentos, sizeof(int), 1, base);
    a->movimentos = malloc(a->quantidade_movimentos * sizeof(movimento));

    for (int i = 0; i < a->quantidade_movimentos; i++) {
        fread(a->movimentos[i].data, sizeof(char), 12, base);
        fread(a->movimentos[i].descricao, sizeof(char), sizeof(a->movimentos[i].descricao), base);
        freceber(base, &a->movimentos[i].reais);
        freceber(base, &a->movimentos[i].bitcoin);
        freceber(base, &a->movimentos[i].etherium);
        freceber(base, &a->movimentos[i].ripple);
    }
}

// le a base toda em binario;
registro* ler_base(int* quantidade_registros) {
    FILE* base = fopen("base_registros.bin", "rb");

    fread(quantidade_registros, sizeof(int), 1, base);
    registro* registros = malloc(*quantidade_registros * sizeof(registro));

    for (int i = 0; i < *quantidade_registros; i++) {
        ler_registro(&registros[i], base);
    }

    fclose(base);
    return registros;
}

// grava um unico registro no arquivo base;
void gravar_registro(registro* a, FILE* base) {
    fwrite(a->cpf, sizeof(char), 12, base);
    fwrite(a->senha, sizeof(char), 7, base);
    fwrite(a->nome, sizeof(char), sizeof(a->nome), base);
    
    fprintar(base, a->reais);
    fprintar(base, a->bitcoin);
    fprintar(base, a->etherium);
    fprintar(base, a->ripple);
    
    fwrite(&a->quantidade_movimentos, sizeof(int), 1, base);
    for (int i = 0; i < a->quantidade_movimentos; i++) {
        fwrite(a->movimentos[i].data, sizeof(char), 12, base);
        fwrite(a->movimentos[i].descricao, sizeof(char), sizeof(a->movimentos[i].descricao), base);
        fprintar(base, a->movimentos[i].reais);
        fprintar(base, a->movimentos[i].bitcoin);
        fprintar(base, a->movimentos[i].etherium);
        fprintar(base, a->movimentos[i].ripple);
    }
}

// grava a base toda em binario;
void gravar_base(registro* registros, int quantidade_registros) {
    FILE* base = fopen("base_registros.bin", "wb");

    fwrite(&quantidade_registros, sizeof(int), 1, base);
    for (int i = 0; i < quantidade_registros; i++) {
        gravar_registro(&registros[i], base);
    }

    fclose(base);
}

cotacao ler_cotacao() {
	FILE* base_cotacao = fopen("base_cotacao.bin", "rb");
	cotacao	resposta;

	freceber(base_cotacao, &resposta.bitcoin);
	freceber(base_cotacao, &resposta.bitcoin_taxa_compra);
	freceber(base_cotacao, &resposta.bitcoin_taxa_venda);

	freceber(base_cotacao, &resposta.etherium);
	freceber(base_cotacao, &resposta.etherium_taxa_compra);
	freceber(base_cotacao, &resposta.etherium_taxa_venda);

	freceber(base_cotacao, &resposta.ripple);
	freceber(base_cotacao, &resposta.ripple_taxa_compra);
	freceber(base_cotacao, &resposta.ripple_taxa_venda);
	return resposta;
}

void gravar_cotacao(cotacao cotacao_atual) {
	FILE* base_cotacao = fopen("base_cotacao.bin", "wb");

	fprintar(base_cotacao, cotacao_atual.bitcoin);
	fprintar(base_cotacao, cotacao_atual.bitcoin_taxa_compra);
	fprintar(base_cotacao, cotacao_atual.bitcoin_taxa_venda);

	fprintar(base_cotacao, cotacao_atual.etherium);
	fprintar(base_cotacao, cotacao_atual.etherium_taxa_compra);
	fprintar(base_cotacao, cotacao_atual.etherium_taxa_venda);

	fprintar(base_cotacao, cotacao_atual.ripple);
	fprintar(base_cotacao, cotacao_atual.ripple_taxa_compra);
	fprintar(base_cotacao, cotacao_atual.ripple_taxa_venda);
}
