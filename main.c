#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fracao.h"
#include "dados.h"

registro* login(registro* registros, int quantidade_registros) {
    registro* usuario = NULL;
    while (1) {
        char cpf_informado[12];
        printf("[?] informe o seu cpf: ");
        scanf("%11s", cpf_informado);
		getchar();

        for (int i = 0; i < quantidade_registros && usuario == NULL; i++) {
            if (strcmp(registros[i].cpf, cpf_informado) == 0) {
                usuario = &registros[i];
            }
        }

        if (usuario != NULL) break;
        else puts("[e] cpf nao encontrado, tente novamente.");
    }

    int ok = 0;
    for (int tentativa = 1; tentativa <= 3 && !ok; tentativa++) {
        char senha_informada[6];
        printf("[?] (%d/3) informe a sua senha: ", tentativa);
		scanf("%6s", senha_informada);
		getchar();

        if (strcmp(senha_informada, usuario->senha) == 0) ok = 1;
        else if (tentativa < 3) puts("[e] senha incorreta, tente novamente.");
    }

    if (!ok) return NULL;
    return usuario;
}

registro* novo_usuario(registro** registros, int* quantidade_registros) {
    registro novo;

    int cpf_ok = 0;
    while (!cpf_ok) {
        printf("[?] informe o novo cpf: ");
        scanf("%11s", novo.cpf);
        getchar();

        cpf_ok = 1;
        for (int i = 0; i < 11 && cpf_ok; i++) {
            cpf_ok &= (novo.cpf[i] >= '0' && novo.cpf[i] <= '9');
        }

        if (!cpf_ok) puts("[e] valor invalido! o cpf deve ter 11 digitos numericos!");
    }

    int senha_ok = 0;
    while (!senha_ok) {
        printf("[?] informe a nova senha: ");
        scanf("%6s", novo.senha);

        senha_ok = 1;
        for (int i = 0; i < 6 && senha_ok; i++) {
            senha_ok &= (novo.senha[i] >= '0' && novo.senha[i] <= '9');
        }

        if (!senha_ok) puts("[e] valor invalido! a senha deve ter 6 digitos numericos!");
    }

    printf("[?] informe o novo nome: ");
    getchar();
    fgets(novo.nome, sizeof(novo.nome), stdin);

    novo.reais = fracao_(0, 1);
    novo.bitcoin = fracao_(0, 1);
    novo.etherium = fracao_(0, 1);
    novo.ripple = fracao_(0, 1);
    novo.quantidade_movimentos = 0;
    novo.movimentos = NULL;

    *registros = realloc(*registros, (*quantidade_registros + 1) * sizeof(registro));
    
    (*registros)[*quantidade_registros] = novo;
    (*quantidade_registros)++;    

    return &(*registros)[(*quantidade_registros) - 1];
}

void consultar_saldo(registro* usuario) {
	printf("[i] saldo atual de: %s", usuario->nome);
	printf("    .reais: "), printar(usuario->reais, '\n');
	printf("    .bitcoin: "), printar(usuario->bitcoin, '\n');
	printf("    .etherium: "), printar(usuario->etherium, '\n');
	printf("    .ripple: "), printar(usuario->ripple, '\n');
}

void consultar_extrato(registro* usuario) {
	printf("[i] extrato atual de: %s", usuario->nome);
	printf("[i] quantidade de movimentos: %d\n", usuario->quantidade_movimentos);

	for (int i = 0; i < usuario->quantidade_movimentos; i++) {
		printf("[i] movimento em %s:\n", usuario->movimentos[i].data);
		printf("    .descricao: %s\n", usuario->movimentos[i].descricao);
		printf("    .reais: "), printar(usuario->movimentos[i].reais, '\n');
		printf("    .bitcoin: "), printar(usuario->movimentos[i].bitcoin, '\n');
		printf("    .etherium: "), printar(usuario->movimentos[i].etherium, '\n');
		printf("    .ripple: "), printar(usuario->movimentos[i].ripple, '\n');
	}
}

void depositar_reais(registro** usuario) {
	puts("depositar");
}

void sacar_reais(registro** usuario) {
	puts("sacar");
}

int main() {
	int quantidade_registros;
    registro* registros = ler_base(&quantidade_registros);
	registro* usuario;

	puts("[+] menu inicial!");
	puts("[1] logar");
	puts("[2] novo usuario\n");

	int logado = 0;
	while (!logado) {
		printf("[?] selecione uma das opcoes: ");	
		int selecao;
		scanf("%d", &selecao);

		switch (selecao) {
			case 1:
				usuario = login(registros, quantidade_registros);
				if (usuario == NULL) {
					puts("[e] impossivel logar! fim do programa!");
					return 0;
				}
				logado = 1;
				break;
			case 2:
				usuario = novo_usuario(&registros, &quantidade_registros);
				logado = 1;
				break;
			default:
				puts("[e] selecao invalida! informe um inteiro que pertence a [1, 2]");
		}
	}

	printf("[i] logado como: %s\n", usuario->nome);

	puts("[+] menu principal!");
	puts("[1] consultar saldo");
	puts("[2] consultar extrato");
	puts("[3] depositar reais");
	puts("[4] sacar reais");
	puts("[5] comprar criptomoedas");
	puts("[6] vender criptomoedas");
	puts("[7] atualizar cotacao");
	puts("[8] sair");

	int sair = 0;
	while (!sair) {
		printf("[?] selecione uma das opcoes: ");	
		int selecao;
		scanf("%d", &selecao);

		switch (selecao) {
			case 1:
				consultar_saldo(usuario);
				break;
			case 2:
				consultar_extrato(usuario);
				break;
			case 3:
				depositar_reais(&usuario);
				break;
			case 4:
				sacar_reais(&usuario);
				break;
			case 8:
				sair = 1;
				break;
			default:
				puts("[e] selecao invalida! informe um inteiro que pertence a [1, 8]");
		}
	}

	gravar_base(registros, quantidade_registros);
    return 0;
}
