#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"

int main() {
    FILE* base_txt = fopen("base_registros.txt", "r");
    FILE* base_bin = fopen("base_registros.bin", "wb");

    int quantidade_registros;
    fscanf(base_txt, "%d", &quantidade_registros);
    fwrite(&quantidade_registros, sizeof(int), 1, base_bin);

    registro temp;
    for (int i = 0; i < quantidade_registros; i++) {
        fscanf(base_txt, "%11s", temp.cpf); fgetc(base_txt);
        fscanf(base_txt, "%6s", temp.senha); fgetc(base_txt);
        fgets(temp.nome, sizeof(temp.nome), base_txt);
        
        temp.reais = fracao_(0, 1);
        temp.bitcoin = fracao_(0, 1);
        temp.etherium = fracao_(0, 1);
        temp.ripple = fracao_(0, 1);
        
        temp.quantidade_movimentos = 0;
        temp.movimentos = NULL;

        gravar_registro(&temp, base_bin);
    }

    fclose(base_txt);
    fclose(base_bin);

    return 0;
}

