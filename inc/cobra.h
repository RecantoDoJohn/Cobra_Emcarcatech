#define COBRA_H

typedef struct 
{
  int x;
  int y;
} parteCobra;

typedef struct 
{
    parteCobra* cobraPedaco[25];
    int tamanho;
    int direcao;
} cobraCompleta;



void moverCima(parteCobra* cobra);

void moverBaixo(parteCobra* cobra);

void moverDireita(parteCobra* cobra);

void moverEsquerda(parteCobra* cobra);

void crescer(cobraCompleta* cobra);

void inicializarCobra(cobraCompleta* cobra);

void decidirDirecao(cobraCompleta* cobra);

void colicaoemsimesma(cobraCompleta *cobra);

void mover(cobraCompleta *cobra);



