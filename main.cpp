#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
double PCFreq = 0.0;
__int64 CounterStart = 0;

using namespace std;

//=============================================== ESTRUTURA GLOBAIS

struct dado{
    int room_id;
    int host_id;
    char room_type[50];
    char country[50];
    char city[50];
    char neighborhood[50];
    char reviews[50];
    char overall_satisfaction[50];
    char accommodates[50];
    char bedrooms[50];
    int price;
    char property_type[50];
};

void StartCounter(){
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        printf("QueryPerformanceFrequency Failed.\n");
    PCFreq = (double)(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - CounterStart) / PCFreq;
}

dado *openFile(int n, int op){


    char cabecalho1[50];
    char cabecalho2[50];
    char cabecalho3[50];
    char cabecalho4[50];
    char cabecalho5[50];
    char cabecalho6[50];
    char cabecalho7[50];
    char cabecalho8[50];
    char cabecalho9[50];
    char cabecalho10[50];
    char cabecalho11[50];
    char cabecalho12[50];

    dado *airbnb = (dado*)calloc(n, sizeof(dado));

    if(airbnb == NULL){
        cout << "não há memoria suficiente";
    } else {
        //inicia abertura do arquivo em modo leitura
        FILE *arq;
        switch(op){
            case 1:
                arq = fopen("dados_airbnb_crescente.txt", "r");
            break;

            case 2:
                arq = fopen("dados_airbnb.txt", "r");
            break;
        }
        int i = 0;

        for(int a = 0; a <= n; a++){
            //na primeira repetição atribui os valores de cabeçalho
            if(a == 0){
                fscanf
                    ( arq,
                        "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
                        &cabecalho1, &cabecalho2, &cabecalho3,
                        &cabecalho4, &cabecalho5, &cabecalho6,
                        &cabecalho7, &cabecalho8, &cabecalho9,
                        &cabecalho10,&cabecalho11, &cabecalho12
                    );
            }
            //depois da primeira repetição lê os valores e quarda na Struct
            if(a != 0 ){
                fscanf
                    ( arq, "%i\t%i\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%i.0\t%[^\n]\n",
                        &airbnb[i].room_id, &airbnb[i].host_id, &airbnb[i].room_type,
                        &airbnb[i].country, &airbnb[i].city, &airbnb[i].neighborhood,
                        &airbnb[i].reviews, &airbnb[i].overall_satisfaction, &airbnb[i].accommodates,
                        &airbnb[i].bedrooms, &airbnb[i].price, &airbnb[i].property_type
                    );

                i++;
            }
        }
        fclose(arq);

    }
    return airbnb;
}

void Imprimir_pesquisa(dado airbnb){
printf("Dados da pesquisa:\nRoom_id: %i\nHost_id: %i\nRoom_type: %s\nCountry: %s\nCity: %s\nNeighborhood: %s\nReviews: %s\nOverall_satisfaction: %s\nAccommodates: %s\nBedrooms: %s\nPrice: %i\nProperty_type: %s\t\n",
                    airbnb.room_id, airbnb.host_id, airbnb.room_type,
                    airbnb.country, airbnb.city, airbnb.neighborhood,
                    airbnb.reviews, airbnb.overall_satisfaction, airbnb.accommodates,
                    airbnb.bedrooms, airbnb.price, airbnb.property_type);

}

//===============================================

//=============================================== ESTRUTURA ARVORE

struct No{
    dado dado;
    No *pai, *esq, *dir;
};

struct ArvBin{
    No *raiz;
    int tam;
};

void Inicializa(ArvBin *arvore){
    arvore->raiz = NULL;
    arvore->tam = 0;
}

bool Insere(ArvBin *arvore, dado dado){

    No *temp = (No*)malloc(sizeof(No));
    temp->dado = dado;
    temp->pai = temp->esq = temp->dir = NULL;

    if(arvore->raiz == NULL){
        arvore->raiz = temp;
        arvore->tam++;
    }else{

        No *raiz = arvore->raiz;

        while(raiz!=NULL){

            if(dado.room_id < raiz->dado.room_id){
                if(raiz->esq == NULL){
                    raiz->esq = temp;
                    temp->pai = raiz;
                    arvore->tam++;
                    return true;
                }else
                    raiz = raiz->esq;
            }
            else if(dado.room_id > raiz->dado.room_id){
                if(raiz->dir == NULL){
                    raiz->dir = temp;
                    temp->pai = raiz;
                    arvore->tam++;
                    return true;
                }else
                    raiz = raiz->dir;
            }
            else{
                free(temp);
                return false;
            }
        }
    }
}

void Imprimir_Arvore(No *no){
    if(no != NULL){
        printf("%Room_id: %i\n", no->dado.room_id);
        Imprimir_Arvore(no->esq);
        Imprimir_Arvore(no->dir);
    }
}

dado Pesquisar(ArvBin *arvore, int chave){
dado falso ={0,0,0,0,0,0,0,0,0,0,0,0};
    int contpesq=0;
    No *temp = arvore->raiz;
    while(temp!=NULL){
        contpesq++;
        if(temp->dado.room_id == chave){
            cout<<"Buscas necessárias: "<<contpesq<<endl;
            return temp->dado;
        }else{

            if(chave < temp->dado.room_id)
                temp = temp->esq;
            else
                temp = temp->dir;
        }
    }
    cout<<"Buscas necessárias: "<<contpesq<<endl;
    return falso;
}

//===============================================

//=============================================== FUNCOES DE PESQUISA SEQUENCIAL E BINARIA

dado Pesquisa_sequencial(dado *v, int chave){
dado falso ={0,0,0,0,0,0,0,0,0,0,0,0};
int contpesq=0;
    for(int i=0; i<128001; i++){
        contpesq++;
        if(v[i].room_id==chave){
            cout<<"Registro encontrado!\n";
            cout<<"Buscas necessárias: "<<contpesq<<endl;
            return v[i];
        }
    }
cout<<"Registro nao encontrado";
cout<<"Buscas necessárias: "<<contpesq<<endl;
return falso;
}

int Pesquisa_sequencial_cidade(dado *v, char *chave, int& maior){
int cont=0;
int contpesq=0;
int ma=v[0].price;
int me=v[0].price;

    for(int i=0; i<128001; i++){

        contpesq++;

        if(strcmp(v[i].city,chave)==0){
/*
            if (cont==0){
                ma=v[i].price;
                me=v[i].price;
                cont++;
            }
*/
            if(ma<v[i].price)
                ma=v[i].price;

            if(me>v[i].price)
                me=v[i].price;
        }
    }

maior=ma;
cout<<"Buscas necessárias: "<<contpesq<<endl;

return me;
}

dado Pesquisa_binaria(dado *v,int n, int chave){
dado falso ={0,0,0,0,0,0,0,0,0,0,0,0};
    int inicio = 0, fim = n-1, meio;
    int contpesq=0;

    while(inicio <= fim){
        contpesq++;
        meio=(inicio+fim)/2;

        if(chave == v[meio].room_id){
        cout<<"Registro encontrado!\n";
        cout<<"Buscas necessárias: "<<contpesq<<endl;
            return v[meio];
        }

        if(chave < v[meio].room_id){
            fim = meio-1;
        }
        else{
            inicio = meio+1;
        }
    }
    cout<<"Buscas necessárias: "<<contpesq<<endl;
    return falso;
}

//===============================================

//=============================================== FUNCOES DE PESQUISA NUMERO QUARTOS NAS CIDADES

struct celula_cidade{
    char nome[50];
    int repeticao;
    celula_cidade * prox;
};

struct lista_de_cidades{
    celula_cidade * ultimo, * primeiro;
    int tam;
};

void inicializa_lista_cidade(lista_de_cidades * l){
    l->primeiro = (celula_cidade *)malloc(sizeof(celula_cidade));
    l->primeiro->prox = NULL;
    l->ultimo = l->primeiro;
    l->tam = 0;
}

void imprime_cidades(lista_de_cidades * l){
    celula_cidade * aux = (celula_cidade*) malloc(sizeof(celula_cidade));
    cout << "\n LISTA DE CIDADES \n";
    aux = l->primeiro->prox;
    while(aux != NULL){
        printf("%s: %i quartos \n", aux->nome, aux->repeticao);
        aux = aux->prox;
    }
}

void insere_cidade(lista_de_cidades * l, char nome[50] ){
    celula_cidade * aux = (celula_cidade*) malloc(sizeof(celula_cidade));
    celula_cidade * toFind = (celula_cidade*) malloc(sizeof(celula_cidade));
    if(l->tam > 0){
        for(toFind = l->primeiro->prox; toFind != NULL; toFind = toFind->prox){

            if(strcmp(toFind->nome, nome) == 0){
                toFind->repeticao++;
                return ;
            }
        }
    }

    strcpy(aux->nome, nome);
    aux->repeticao = 1;
    aux->prox=NULL;
    l->ultimo->prox = aux;
    l->ultimo = aux;
    l->tam++;
    return ;

}

void Contador_de_cidades(dado *v, lista_de_cidades * l, int n){
    //celula_cidade * aux = (celula_cidade*) malloc(sizeof(celula_cidade));
    char nome[50];
    for(int i = 0; i < n; i++){
        strcpy(nome, v[i].city);
        insere_cidade(l, nome);

    }
    imprime_cidades(l);

}

//===============================================

//=============================================== PROCEDIMENTOS PARA HASH

struct CelulaH{
    dado data;
    CelulaH *prox;
};

struct ListaH{
    CelulaH *inicio, *fim;
    int tam;
};

void InicializarH(ListaH *lista){

    lista->inicio = (CelulaH*) malloc(sizeof(CelulaH));
    lista->inicio->prox = NULL;

    lista->fim = lista->inicio;

    lista->tam = 0;
}

bool VaziaH(ListaH *lista){
    return lista->inicio == lista->fim;
}

void InserirH(ListaH *lista, dado x){


    CelulaH *temp = (CelulaH*) malloc(sizeof(CelulaH));
    temp->data = x;
    temp->prox = NULL;

    lista->fim->prox = temp;
    lista->fim = temp;


    lista->tam++;
}

void ImprimirH(ListaH *lista){
    for(CelulaH *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        printf(" %i -", temp->data.room_id);
    }
    printf("\n");
}

int TamanhoH(ListaH *lista){
    return lista->tam;
}

dado PesquisarH(ListaH *lista, int X){
dado falso ={0,0,0,0,0,0,0,0,0,0,0,0};
    int contpesq=0;
    for(CelulaH *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        contpesq++;
        if(temp->data.room_id == X)
            cout<<"Buscas necessárias na lista: "<<contpesq<<endl;
            return temp->data;
    }
    return falso;
}

int FuncaoHash(int X, int N){
    return X % N;
}

void InicializarHash(ListaH *tabela[], int N){

    for(int i=0; i<N; i++){
       tabela[i] = (ListaH*)malloc(sizeof(ListaH));
       InicializarH(tabela[i]);
    }
}

void InserirHash(ListaH *tabela[], int N, dado x){

    int pos = FuncaoHash(x.room_id , N);
    InserirH(tabela[pos], x);

}

dado PesquisarHash(ListaH *tabela[], int N, int X){
    int contpesq=0;
    int pos = FuncaoHash(X,N);
    dado consulta = PesquisarH(tabela[pos], X);
    contpesq++;
    cout<<"Buscas necessárias na tabela: "<<contpesq<<endl;
    return consulta;/*
    if(consulta != {0,0,0,0,0,0,0,0,0,0,0,0})
        return pos;

    return -1;
*/
}

void ImprimirHash(ListaH *tabela[], int N){
    int j=0;
    for(int i=0; i<N; i++){
        printf("%i|\t", i);
        ImprimirH(tabela[i]);
    }
    printf("\n====================\n");
}

//===============================================


int main(){

setlocale(LC_ALL,"");

    lista_de_cidades * cidades = (lista_de_cidades*) malloc(sizeof(lista_de_cidades));
    inicializa_lista_cidade(cidades);

    int fator=65521;    // potencia de 2 abaixo do tamanho total (total= 12800 -> potencia de 2 mais proxima 65536 -> numero primo abaixo 65521), como Sedgewick sugere
    ListaH **TabelaHash = (ListaH **)calloc(fator,sizeof(ListaH *));
    InicializarHash(TabelaHash, fator);

    ArvBin *arvore = (ArvBin*)malloc(sizeof(ArvBin));
    Inicializa(arvore);

    int  op=0, chave,ma=0, me, pos, continuar;
    char chavosa[50];
    dado *v, aux;
    double tempoEmMilissegundo = 0.0000000;

    do{
        cout<<"\t---------> Opcoes disponiveis:\n";
        cout<<"[1] -> Pesquisar as informações de um quarto, usando uma pesquisa sequencial.\n";
        cout<<"[2] -> Pesquisar as informações de um quarto, usando uma pesquisa binária.\n";
        cout<<"[3] -> Pesquisar as informações de um quarto, usando uma árvore binária.\n";
        cout<<"[4] -> Pesquisar as informações de um quarto, usando uma tabela Hash.\n";
        cout<<"[5] -> Contabilizar a quantidade de quartos disponíveis para cada uma das cidades. \n";
        cout<<"[6] -> Pesquisar o quarto mais caro e mais barato de uma determinada cidade.\n";
        cout<<"[7] -> Sair.\n";
        cout<<"Entrada:  ";
        cin>>op;

            if(op==7){
                break;
            }

            if(op < 1 || op > 6){
                cout<<"\t\tOpcao invalida, digite novamente...\n";
            }

        switch(op){
            case 1:
                cout<<"\n\tPESQUISA SEQUENCIAL:\n";
                do{

                cout<<"Room_id? ";
                cin>>chave;
                v = openFile(128001, 2);
                StartCounter();
                aux=Pesquisa_sequencial(v, chave);
                tempoEmMilissegundo = GetCounter();
                    if(aux.room_id!=0){
                        Imprimir_pesquisa(aux);
                    }
                cout<<"\nTempo para realizar a pesquisa (MS): "<<tempoEmMilissegundo;
                cout<<endl;
                cout<<"\nPesquisar novamente (Sequencial)? [1] Sim; [2] Nao. ";

                do{
                    cout<<"\nEntrada:  ";
                    cin>>continuar;
                    if(((continuar < 1) || (continuar > 2))){
                        cout<<"Opçao invalida, digite novamente...";
                    }
                    }while((continuar < 1) || (continuar > 2));
                }while(continuar!=2);

                cout<<endl<<endl;
            break;

            case 2:
                cout<<"\n\tPESQUISA BINARIA:\n";
                do{

                cout<<"Room_id? ";
                cin>>chave;
                v = openFile(128001, 1);
                StartCounter();
                aux=Pesquisa_binaria(v, 128001, chave);
                tempoEmMilissegundo = GetCounter();
                    if(aux.room_id!=0){
                        Imprimir_pesquisa(aux);
                    }
                cout<<"\nTempo para realizar a pesquisa (MS): "<<tempoEmMilissegundo;
                cout<<endl;
                cout<<"\nPesquisar novamente (Binaria)? [1] Sim; [2] Nao. ";

                do{
                    cout<<"\nEntrada:  ";
                    cin>>continuar;
                    if(((continuar < 1) || (continuar > 2))){
                        cout<<"Opçao invalida, digite novamente...";
                    }
                    }while((continuar < 1) || (continuar > 2));
                }while(continuar!=2);

                cout<<endl<<endl;
            break;

            case 3:
                cout<<"\n\tPESQUISA EM ARVORE BINARIA\n";
                do{

                cout<<"Room_id? ";
                cin>>chave;
                v = openFile(128001, 2);
                    for(int i=0; i<128001; i++){
                        Insere(arvore, v[i]);
                    }
                //Imprimir_Arvore(arvore->raiz);
                StartCounter();
                aux=Pesquisar(arvore, chave);
                tempoEmMilissegundo = GetCounter();
                    if(aux.room_id!=0){
                        Imprimir_pesquisa(aux);
                    }
                cout<<"\nTempo para realizar a pesquisa (MS): "<<tempoEmMilissegundo;
                cout<<endl;
                cout<<"\nPesquisar novamente (Arvore)? [1] Sim; [2] Nao. ";

                do{
                    cout<<"\nEntrada:  ";
                    cin>>continuar;
                    if(((continuar < 1) || (continuar > 2))){
                        cout<<"Opçao invalida, digite novamente...";
                    }
                    }while((continuar < 1) || (continuar > 2));
                }while(continuar!=2);

                cout<<endl<<endl;
            break;

            case 4:
                cout<<"\n\tPESQUISA EM TABELA HASH\n";
                do{

                cout<<"Room_id? ";
                cin.ignore();
                cin>>chave;
                v = openFile(128001, 2);
                for(int i=0; i< 128001; i++){
                    InserirHash(TabelaHash, fator, v[i]);
                }
                StartCounter();
                aux=PesquisarHash(TabelaHash, fator, chave);
                //pos=PesquisarHash(TabelaHash, fator, chave);
                tempoEmMilissegundo = GetCounter();
                    if(aux.room_id==0){
                        cout<<"Elemento nao encontrado.\n";
                    } else {
                        Imprimir_pesquisa(aux);
                    }
                cout<<"\nTempo para realizar a pesquisa (MS): "<<tempoEmMilissegundo;
                cout<<endl;
                cout<<"\nPesquisar novamente (Hash)? [1] Sim; [2] Nao. ";

                do{
                    cout<<"\nEntrada:  ";
                    cin>>continuar;
                    if(((continuar < 1) || (continuar > 2))){
                        cout<<"Opçao invalida, digite novamente...";
                    }
                    }while((continuar < 1) || (continuar > 2));
                }while(continuar!=2);

                cout<<endl<<endl;
            break;

            case 5:
                cout<<"\n\t QUANTIDADE QUARTOS DISPONIVEIS EM UMA CIDADE\n";
                v = openFile(128001, 1);
                Contador_de_cidades(v, cidades, 128000);

                cout<<endl<<endl;
            break;

            case 6:

                cout<<"\n\tQUARTO MAIS CARO E MAIS BARATO DE DETERMINADA CIDADE\n";
                do{

                cout<<"Cidade?\n-> ";
                cin.ignore();
                gets(chavosa);
                v = openFile(128001,2);
                StartCounter();
                me=Pesquisa_sequencial_cidade(v,chavosa,ma);
                tempoEmMilissegundo = GetCounter();
                cout<<"Mais Caro  = "<<ma<<endl
                    <<"Mais Barato= "<<me<<endl;

                cout<<"\nPesquisar novamente (Quarto)? [1] Sim; [2] Nao. ";
                do{
                    cout<<"\nEntrada:  ";
                    cin>>continuar;
                    if(((continuar < 1) || (continuar > 2))){
                        cout<<"Opçao invalida, digite novamente...";
                    }
                    }while((continuar < 1) || (continuar > 2));
                }while(continuar!=2);

                cout<<endl<<endl;
            break;

        }
    }while(op!=7);

    free(TabelaHash);
    free(arvore);
    free(v);
    return 0;
}
