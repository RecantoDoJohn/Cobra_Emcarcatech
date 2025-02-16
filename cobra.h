#include <stdio.h>

struct parteCobra
{
  int x;
  int y;
};

struct cobraCompleta
{
    struct parteCobra* cobraPedaco[25];
    int tamanho;
    int direcao;
};



void moverCima(struct parteCobra* cobra) {
    cobra->y++;
}

void moverBaixo(struct parteCobra* cobra){
    cobra->y--;
}

void moverDireita(struct parteCobra* cobra){
    cobra->x++;
}

void moverEsquerda(struct parteCobra* cobra){
    cobra->x--;
}

void crescer(struct cobraCompleta* cobra) {
    cobra->tamanho++;
}


void inicializarCobra(struct cobraCompleta* cobra) {
    for (int i = 0; i < 25; i++) {
        cobra->cobraPedaco[i] = (struct parteCobra*)malloc(sizeof(struct parteCobra));
        if (cobra->cobraPedaco[i] == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
    }
    cobra->tamanho = 4;  
    cobra->direcao = 0;  
    cobra->cobraPedaco[0]->x = 0;
    cobra->cobraPedaco[0]->y = 0;
    
}


void decidirDirecao(struct cobraCompleta* cobra) {
    switch (cobra->direcao)
    {
    case 0:
        moverDireita(cobra->cobraPedaco[0]);
        break;
    case 1:
        moverCima(cobra->cobraPedaco[0]);
        break;
    case 2:
        moverEsquerda(cobra->cobraPedaco[0]);
        break;
    case 3:
        moverBaixo(cobra->cobraPedaco[0]);
        break;
    
    default:
        break;
    }
}


void mover(struct cobraCompleta *cobra) {
    

    for (int i = cobra->tamanho; i >= 0; i--) {
        if (i == 0) {
            decidirDirecao(cobra);

            // parede direita
            if (cobra->cobraPedaco[i]->x == 5) {
                cobra->cobraPedaco[i]->x = 0;

            // parede inferior
            } else if (cobra->cobraPedaco[i]->y == 5) {
                cobra->cobraPedaco[i]->y = 0;
            } 

            // parede superior
            else if (cobra->cobraPedaco[i]->y == -1) {
                cobra->cobraPedaco[i]->y = 4;

            // parede esquerda
            } else if (cobra->cobraPedaco[i]->x == -1) {
                cobra->cobraPedaco[i]->x = 4;
            }

            

        } else {
            cobra->cobraPedaco[i]->x = cobra->cobraPedaco[i-1]->x;
            cobra->cobraPedaco[i]->y = cobra->cobraPedaco[i-1]->y;
        }
    }
}

