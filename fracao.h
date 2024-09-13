#ifndef fracao_h
#define fracao_h

typedef struct fracao fracao;

struct fracao {
	int numerador, denominador;	
};

fracao fracao_(int numerador_, int denominador_);

fracao inverter_(fracao a);
void inverter(fracao* a);

fracao negar_(fracao a);
void negar(fracao* a);

fracao somar_(fracao a, fracao b);
void somar(fracao* a, fracao b);

fracao subtrair_(fracao a, fracao b);
void subtrair(fracao* a, fracao b);

fracao multiplicar_(fracao a, fracao b);
void multiplicar(fracao* a, fracao b);  // Fixed to take a pointer to 'fracao'

fracao dividir_(fracao a, fracao b);
void dividir(fracao* a, fracao b);

fracao exponenciar_(fracao a, int n);
void exponenciar(fracao* a, int n);

void printar(fracao a, char fim);
void receber(fracao* a);

#endif

