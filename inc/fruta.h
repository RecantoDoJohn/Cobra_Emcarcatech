#define FRUTA_H

typedef struct {
    int x;
    int y;
    
} fruta;

bool verificarSobreposicao(cobraCompleta* cobra, fruta *fruta, int x, int y);

void gerarFruta(fruta *fruta, cobraCompleta* cobra);