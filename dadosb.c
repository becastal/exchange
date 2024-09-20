#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"

typedef struct fracao fracao;
typedef struct movimento movimento;
typedef struct registro registro;

// mudando pro arquivo binário
void ler_registro(registro* a, FILE* base) {
    fread(a->cpf, sizeof(a->cpf), 1, base);
    fread(a->senha, sizeof(a->senha), 1, base);
    fread(a->nome, sizeof(a->nome), 1, base);
    
    freceber(base, &a->reais);
    freceber(base, &a->bitcoin);
    freceber(base, &a->etherium);
    freceber(base, &a->ripple);

    fread(&a->quantidade_movimentos, sizeof(a->quantidade_movimentos), 1, base);
    a->movimentos = malloc(a->quantidade_movimentos * sizeof(movimento));

    for (int i = 0; i < a->quantidade_movimentos; i++) {
        fread(a->movimentos[i].data, sizeof(a->movimentos[i].data), 1, base);
        fread(a->movimentos[i].descricao, sizeof(a->movimentos[i].descricao), 1, base);
        freceber(base, &a->movimentos[i].reais);
        freceber(base, &a->movimentos[i].bitcoin);
        freceber(base, &a->movimentos[i].etherium);
        freceber(base, &a->movimentos[i].ripple);
    }
}

// le a base toda do arquivo binário
registro* ler_base(int* quantidade_registros) {
    FILE* base = fopen("base_registros.bin", "rb");
    if (base == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fread(quantidade_registros, sizeof(int), 1, base);
    registro* registros = malloc(*quantidade_registros * sizeof(registro));
    if (registros == NULL) {
        perror("Erro ao alocar memória");
        fclose(base);
        return NULL;
    }

    for (int i = 0; i < *quantidade_registros; i++) {
        ler_registro(&registros[i], base);
    }

    fclose(base);
    return registros;
}

// grava um único registro no arquivo binário
void gravar_registro(registro* a, FILE* base) {
    fwrite(a->cpf, sizeof(a->cpf), 1, base);
    fwrite(a->senha, sizeof(a->senha), 1, base);
    fwrite(a->nome, sizeof(a->nome), 1, base);
    
    fprintar(base, a->reais, '\0');  // Assumindo que fprintar já escreve em binário
    fprintar(base, a->bitcoin, '\0');
    fprintar(base, a->etherium, '\0');
    fprintar(base, a->ripple, '\0');
    
    fwrite(&a->quantidade_movimentos, sizeof(a->quantidade_movimentos), 1, base);
    for (int i = 0; i < a->quantidade_movimentos; i++) {
        fwrite(a->movimentos[i].data, sizeof(a->movimentos[i].data), 1, base);
        fwrite(a->movimentos[i].descricao, sizeof(a->movimentos[i].descricao), 1, base);
        fprintar(base, a->movimentos[i].reais, '\0');
        fprintar(base, a->movimentos[i].bitcoin, '\0');
        fprintar(base, a->movimentos[i].etherium, '\0');
        fprintar(base, a->movimentos[i].ripple, '\0');
    }
}

// grava tudo no arquivo binário
void gravar_base(registro* registros, int quantidade_registros) {
    FILE* base = fopen("base_registros.bin", "wb");
    if (base == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    fwrite(&quantidade_registros, sizeof(int), 1, base);
    for (int i = 0; i < quantidade_registros; i++) {
        gravar_registro(&registros[i], base);
    }

    for (int i = 0; i < quantidade_registros; i++) {
        free(registros[i].movimentos);
    }
    free(registros);
    fclose(base);
}
