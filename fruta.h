#include <stdlib.h>

struct fruta
{
    int x;
    int y;
    
};



bool verificarSobreposicao(struct cobraCompleta* cobra, struct fruta *fruta, int x, int y) {
    for (int i = cobra->tamanho; i >= 0; i--) {
        if (cobra->cobraPedaco[0]->x = x && cobra->cobraPedaco[0]->y == y ) {
            return false;
            break;
        } 
    }
    return true;
}


void gerarFruta(struct fruta *fruta, struct cobraCompleta* cobra) {
    int min = 0, max = 4;

    int posX = min + rand() % (max - min + 1);
    int posY = min + rand() % (max - min + 1);

    if (verificarSobreposicao(cobra, fruta, posX, posY)) {
        fruta->y = posY;
        fruta->x = posX;
    }
    else {
        gerarFruta( fruta, cobra);
    }
}