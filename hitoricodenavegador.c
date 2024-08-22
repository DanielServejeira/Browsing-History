//Daniel Servejeira - Aluno de Bacharel em Ciência da Computação - FCT Unesp

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define max 128

typedef struct links {
    char pagina[max];
}Links;

typedef struct vetorDeLinks {
    Links vetPaginas[4];
}VetorDeLinks;

typedef struct no {
    char dado[max];
    struct no *proximo;
}No;

No *topoVisitadas;
No *topoRemovidas;

VetorDeLinks *inicializarLinks() {
    VetorDeLinks *vlinks = (VetorDeLinks*) malloc(sizeof(VetorDeLinks));
    return vlinks;
}

void definirLinks(VetorDeLinks *vlinks) {
    strcpy(vlinks->vetPaginas[0].pagina, "https://www.uol.com.br/");
    strcpy(vlinks->vetPaginas[1].pagina, "https://www.globo.com/");
    strcpy(vlinks->vetPaginas[2].pagina, "https://www.folha.uol.com.br/");
    strcpy(vlinks->vetPaginas[3].pagina, "https://www.estadao.com.br/");
}

void exibirLinks(No *topo) {
    setlocale(LC_ALL, "Portuguese");
    while(topo) {
        printf("%s\n",topo->dado);
        topo = topo->proximo;
    }
}

void abrirNovoLink(VetorDeLinks *vlinks, int i) {
    setlocale(LC_ALL, "Portuguese");

    No *pVisitadas = (No*) malloc(sizeof(No));

    if(i>3) {
        printf("\n\tNão há mais sites disponíveis.\n");
    }
    else{
        strcpy(pVisitadas->dado, vlinks->vetPaginas[i].pagina);

        if(topoVisitadas){
            pVisitadas->proximo = topoVisitadas;
            topoVisitadas = pVisitadas;
        }
        else{
            topoVisitadas = pVisitadas;
            pVisitadas->proximo = NULL;
        }
    }
}

void voltar() {
    setlocale(LC_ALL, "Portuguese");

    No *p = (No*) malloc(sizeof(No));

    if(topoVisitadas) {
        p = topoVisitadas;
        topoVisitadas = topoVisitadas->proximo;

        if(topoRemovidas){
            p->proximo = topoRemovidas;
            topoRemovidas = p;
        }
        else{
            topoRemovidas = p;
            p->proximo = NULL;
        }

    }
    else{
        printf("\n\tNão há mais sites para retornar\n");
    }
}

void avancar() {
    setlocale(LC_ALL, "Portuguese");

    No *p = (No*) malloc(sizeof(No));

    if(topoRemovidas) {
        p = topoRemovidas;
        topoRemovidas = topoRemovidas->proximo;

        if(topoVisitadas) {
            p->proximo = topoVisitadas;
            topoVisitadas = p;
        }
        else{
            topoVisitadas = p;
            p->proximo = NULL;
        }
    }
    else{
        printf("\n\tNão há mais sites para avançar\n");
    }
}



int main() {
    setlocale(LC_ALL, "Portuguese");

    int menu, i=0;

    VetorDeLinks *vlinks = inicializarLinks();
    definirLinks(vlinks);

    do {
        printf("\n\tMENU\n\n");
        printf("0 - Sair\n");
        printf("1 - Abrir novo link\n");
        printf("2 - Voltar\n");
        printf("3 - Avançar\n\n");
        scanf("%d",&menu);
        fflush(stdin);
        system("cls");

        switch(menu) {
            case 0:
                return 0;
            case 1:
                abrirNovoLink(vlinks, i++);
                break;
            case 2:
                voltar();
                break;
            case 3:
                avancar();
                break;
            default:
                printf("\n\tInsira uma opção válida\n\n");
                break;
        }
        printf("\nPágina atual: %s\n",topoVisitadas->dado);
        printf("\n\tLinks de retorno\n\n");
        exibirLinks(topoVisitadas);
        printf("\n\tLinks de avanço\n\n");
        exibirLinks(topoRemovidas);
    } while(menu!=0);
}
