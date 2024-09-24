#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"
#include "dados.h"

int main() {
	cotacao res;
	res.bitcoin = fracao_(1, 1);
	res.bitcoin_taxa_compra = fracao_(2, 100);
	res.bitcoin_taxa_venda = fracao_(3, 100);

	res.etherium = fracao_(1, 1);
	res.etherium_taxa_compra = fracao_(1, 100);
	res.etherium_taxa_venda = fracao_(2, 100);

	res.ripple = fracao_(1, 1);
	res.ripple_taxa_compra = fracao_(1, 100);
	res.ripple_taxa_venda = fracao_(1, 100);

	gravar_cotacao(res);	

    return 0;
}

