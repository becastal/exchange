#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"

int main() {
	int quantidade_registros;
    registro* registros = ler_base(&quantidade_registros);


	gravar_base(registros, quantidade_registros);
    return 0;
}
