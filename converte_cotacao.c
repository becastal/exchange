#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"

int main() {
    FILE* base_txt = fopen("base_cotacao.txt", "r");
    FILE* base_bin = fopen("base_cotacao.bin", "wb");

	cotacao res;
	res.bitcoin = fracao_(1, 1);
	res.etherium = fracao_(1, 1);
	res.ripple = fracao_(1, 1);

	gravar_cotacao(res);	

    fclose(base_txt);
    fclose(base_bin);

    return 0;
}

