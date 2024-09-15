#ifndef dados_h
#define dados_h
#include <stdlib.h>

// guarda o movimento de uma conta, os valores que aparecem quando se consulta o seu extrato;
typedef struct movimento movimento;
struct movimento {
	char data[12];
	char descricao[100];
    fracao reais, bitcoin, etherium, ripple;
};

// guarda os valores referentes a uma conta;
typedef struct registro registro;
struct registro {
    char cpf[13];
    char senha[8];
    char nome[100];
    fracao reais, bitcoin, etherium, ripple;
	int quantidade_movimentos;
	movimento* movimentos;
};

void ler_registro(registro* a, FILE* base);
registro* ler_base(int* quantidade_registros);

void gravar_registro(registro* a, FILE* base);
void gravar_base(registro* registros, int quantidade_registros);

#endif

