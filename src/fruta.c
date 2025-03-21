#include <stdlib.h>
#include <stdbool.h>
#include "inc/cobra.h"

typedef struct 
{
    int x;
    int y;
    
} fruta;


// verifica se a posicao da fruta nao esta em conflito com alguma parte da cobra
bool verificarSobreposicao(cobraCompleta* cobra, fruta *fruta) {
    for (int i = cobra->tamanho; i >= 0; i--) {
        if (cobra->cobraPedaco[0]->x == fruta->x && cobra->cobraPedaco[0]->y == fruta->y ) {
            return false;
            break;
        } 
    }
    return true;
}

// gera a fruta
void gerarFruta(fruta *fruta, cobraCompleta* cobra) {
    int min = 0, max = 4;

    int posX = min + rand() % (max - min + 1);
    int posY = min + rand() % (max - min + 1);

    fruta->y = posY;
    fruta->x = posX;

    if (verificarSobreposicao(cobra, fruta)) {
        return;
    }
    else {
        gerarFruta( fruta, cobra);
    }
}

// verifica se a cabeca da cobra esta na mesma posicao da fruta 
void verificarComida(cobraCompleta* cobra, fruta *fruta ) {
    if (cobra->cobraPedaco[0]->x == fruta->x && cobra->cobraPedaco[0]->y == fruta->y ) {
        crescer(cobra);
        gerarFruta(fruta, cobra);
    }
}