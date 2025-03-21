#include <stdio.h>
#include <stdlib.h>
#include "inc/cobra.h"


void moverCima(parteCobra* cobra) {
    cobra->y++;
}

void moverBaixo(parteCobra* cobra){
    cobra->y--;
}

void moverDireita(parteCobra* cobra){
    cobra->x++;
}

void moverEsquerda(parteCobra* cobra){
    cobra->x--;
}

void crescer(cobraCompleta* cobra) {
    cobra->tamanho++;
}

// responsavel por definir os valores iniciais da cobra
void inicializarCobra(cobraCompleta* cobra) {
    for (int i = 0; i < 25; i++) {
        cobra->cobraPedaco[i] = (parteCobra*)malloc(sizeof(parteCobra));
        if (cobra->cobraPedaco[i] == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
    }
    cobra->tamanho = 2;  
    cobra->direcao = 0;  
    cobra->cobraPedaco[0]->x = 0;
    cobra->cobraPedaco[0]->y = 0;
    
}

// verifica a direcao da cobra
void decidirDirecao(cobraCompleta* cobra) {
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

// verifica a colisao na propria cobra
void colicaoemsimesma(cobraCompleta *cobra) {
    for (int i = cobra->tamanho; i >= 1; i--) {
        
        if (cobra->cobraPedaco[0]->x == cobra->cobraPedaco[i]->x && cobra->cobraPedaco[0]->y == cobra->cobraPedaco[i]->y) {
            inicializarCobra(cobra);
            break;
        } 
    }
}

// faz a cobra se mover
void mover(cobraCompleta *cobra) {
    for (int i = cobra->tamanho; i > -1; i--) {
        if (i == 0) { 
            decidirDirecao(cobra);
            colicaoemsimesma(cobra);

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
        }
         else {
            cobra->cobraPedaco[i]->x = cobra->cobraPedaco[i-1]->x;
            cobra->cobraPedaco[i]->y = cobra->cobraPedaco[i-1]->y;
        }
    }

}



