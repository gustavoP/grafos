#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <numeric>
//#include "Graph.h"

using namespace std;

class Graph
{


  public:
    typedef struct Adj_node{
        int node;
        Adj_node *next_node;
        int weight;
    }Adj_node;

  private:
    ifstream fileStream;
    int **arcs; //alocar espaço quando for construir
    int **adjMatrix; //matriz de adjacencias
    int n_arcs,n_nodes,bool_weight;
    


    Adj_node **Adj_list_node; //lista de adjacencias

    char fileName[];

    int readFile(char file[])
    {
        strcpy(this->fileName, file);
        //sprintf(this->fileName, "%s",file);
        printf("file name of object is: %s", this->fileName);

        //if everything is ok
        this->makeGraph();
        return 1;
    };

    void makeGraph()
    {
        //this->fileStream.open(this->fileName);
        FILE *file;
        file = fopen(this->fileName, "r");
        if (!this->fileStream)
        {
            printf("Unable to open file");
            exit(1); // terminate with error
        }
        int i=0;
        fscanf(file, "%d %d %d\n", &n_nodes, &n_arcs, &bool_weight);

        //alocando memória
        int col =3;// 3 colunas, [nó 1, nó 2, peso]
        this->arcs = (int **)malloc(sizeof(int *) * n_arcs);
        arcs[0] = (int *)malloc(sizeof(int) * col * n_arcs); 
        for(i = 0; i < n_arcs; i++){
            this->arcs[i] = (*this->arcs + col * i); //n_arcs
        }

        //lendo valores
        for (i = 0; i < n_arcs; i++){
            if(bool_weight==0){
                fscanf(file,"%d %d",&(this->arcs[i][0]),&(this->arcs[i][1]));
                this->arcs[i][2]=1;
            }
            else{
                fscanf(file,"%d %d %d",&(this->arcs[i][0]),&(this->arcs[i][1]),&(this->arcs[i][2]));
            }
        }
    };

  public:
    
    Graph(char file[])
    {
        readFile(file);
    };

    void printFile(){
        printf("\nn1->n2|peso : Grafo = %s \n",this->fileName);
        for(int i=0; i<this->n_arcs;i++){
            printf("%d->%d |%d \n",this->arcs[i][0],this->arcs[i][1],this->arcs[i][2]);
        }
    };

    void setAdjMatrix(){
        this->adjMatrix = (int **)malloc(sizeof(int *) * n_nodes);
        adjMatrix[0] = (int *)malloc(sizeof(int) * n_nodes * n_nodes); 
        for(int i = 0; i < n_nodes; i++){
            this->adjMatrix[i] = (*this->adjMatrix + n_nodes * i); //n_arcs
        }
        //alocando zero em cada posição (deve ter uma maneira melhor de fazer isso)
        for(int i = 0; i < n_nodes; i++){
            for(int j = 0; j < n_nodes; j++){
                this->adjMatrix[i][j]=0;
            }          
        }

        int n1=0;
        int n2=0;
        int w=0;
        for(int i = 0; i < n_arcs; i++){
            n1=this->arcs[i][0] -1; //passar a começar do zero para indice ser = noh
            n2=this->arcs[i][1] -1;
            w=this->arcs[i][2];

            if(n1!=n2){
                this->adjMatrix[n1][n2]+=w;
                this->adjMatrix[n2][n1]+=w; //assumindo não direcional
            }
            else{
                this->adjMatrix[n1][n2]+=w; //self loop
            }
        }
    }

    int** getAdjMatrix(){
        return adjMatrix;
    };

    void printAdj(){
        printf("\n Matriz de adjacencias");
        for(int i=0;i< this->n_nodes; i++){
            printf("\n|");
            for(int j=0;j< this->n_nodes; j++){
                printf("%d|",this->adjMatrix[i][j]);
            }
        }
    }

    int getNumNodes(){
        return this->n_nodes;
    };

    //! Esse metodo retorna o grau de um noh a partir da matriz de adjacencias.
    /*! Esse metodo retorna o grau de um noh considerando um grafo nao direcional.
        A matriz de adjacencias deve estar instanciada com o metodo getAdjMatrix();

        \param node: numero do no, primeiro noh=0.
        \return numero: grau do no. caso retorne -1 entao o noh nao existe
    */
    int nodeDegreeAdj(int node){
        if(node>=this->n_nodes){
            return -1;
        }
        int degree=0;
        for(int i=0;i<this->n_nodes;i++){
            degree+=this->adjMatrix[i][node];
        }
        return degree;
    }

    void setListaAdj(){
        this->Adj_list_node = (Adj_node **)malloc(sizeof(Adj_node*) * this->getNumNodes());
        
        //adicionando primeiros nós na lista, como eh soh para referencia vamos adicionar o peso zero
        for(int i =0; i<n_nodes; i++){
            this->Adj_list_node[i] = (Adj_node *)malloc(sizeof(Adj_node*));
            this->Adj_list_node[i]->node=i; //{.node = i, .next_node=NULL, .weight = 0};
            this->Adj_list_node[i]->next_node=NULL;
            this->Adj_list_node[i]->weight=0;
        }

        
        int n1=0;
        int n2=0;
        int w=0;
        Adj_node *dest;
        Adj_node *aux;
        

        for(int i = 0; i < n_arcs; i++){

            for(int j=0;j<2;j++){ //ida e volta 1->2 e 2->1
                if(j==0){ //ida
                    n1=this->arcs[i][0] -1; //passar a começar do zero para indice ser = noh
                    n2=this->arcs[i][1] -1;
                    w=this->arcs[i][2];
                }
                if(j==1){ //volta
                    n2=this->arcs[i][0] -1; //passar a começar do zero para indice ser = noh
                    n1=this->arcs[i][1] -1;
                    w=this->arcs[i][2];
                }
                

                aux = this->Adj_list_node[n1];
                
                while(aux->next_node!=NULL){
                    aux = aux->next_node;
                }
                dest = (Adj_node *)malloc(sizeof(Adj_node*));
                dest->node=n2;
                dest->next_node=NULL;
                dest->weight=w;
                
                aux->next_node = dest;
            }
        }
    }

    Adj_node** getListaAdj(){
        return Adj_list_node;
    }
    //! Esse metodo retorna o grau de um noh a partir da Lista de adjacencias.
    /*! Esse metodo retorna o grau de um noh considerando um grafo nao direcional.
        A Lista de adjacencias deve estar instanciada com o metodo getListAdj();

        \param node: numero do no, primeiro noh=0.
        \return numero: grau do no. caso retorne -1 entao o noh nao existe
    */
    int nodeDegreeListAdj(int node){
        if(node>=this->n_nodes){
            return -1;
        }
        Adj_node *aux;
        int degree=0;
        aux = this->Adj_list_node[node];

        do{
            degree+=aux->weight;
            aux = aux->next_node;
        }while(aux!=NULL);

        return degree;
    }

    void printListaAdj(){
        Adj_node *aux;
        printf("\n Lista de Adjacencias (|noh peso|)");
        for(int i=0; i<n_nodes; i++){
            printf("\n|%d|",i);
            aux = this->Adj_list_node[i]->next_node;
            while(aux!=NULL){
                printf("%d %d|",aux->node,aux->weight);
                aux=aux->next_node;
            }
        }
    }

    void prim(){
        //inicializando
        printf("iniciando Prim \n");

        //lista com os nós, começa no 1 sempre em ordem crescente.
        vector<int> remainingNodes(this->n_nodes);
        iota(remainingNodes.begin(), remainingNodes.end(), 1); //remainingNodes._M_impl._M_start[0]
        printf("capacidade|size %d %d\n",remainingNodes.size(),remainingNodes.capacity());
        //lista dos nós que já foram visitados, inicialmente vazio
        vector<int> visitedNodes(this->n_nodes);
        printf("capacidade|size %d %d\n",visitedNodes.size(),visitedNodes.capacity());
        //duplicando lista de arcos.
        //listArcs vector com os arcos, é utilizado vector pois é mais fácil de manipular
        vector< vector<int>> listArcs(this->n_arcs, vector<int>(3)); //listArcs._M_impl._M_start[i]._M_impl._M_start[j]
        for(int i = 0; i <this->n_arcs; i++){
            listArcs[i][0] = this->arcs[i][0];
            listArcs[i][1] = this->arcs[i][1];
            listArcs[i][2] = this->arcs[i][2];
        }
        printf("capacidade|size %d %d\n",listArcs.size(),listArcs.capacity());
        printf("capacidade|size %d %d\n",listArcs[0].size(),listArcs[0].capacity());
        //alocando memória para resposta final, dimensão é a quantidade de nos-1 já que é uma árvore
        int col =3;// 3 colunas, [nó 1, nó 2, peso]
        int **mst = (int **)malloc(sizeof(int *) * n_nodes-1);
        mst[0] = (int *)malloc(sizeof(int) * col * n_nodes-1); 
        for(int i = 0; i < n_nodes-1; i++){
            mst[i] = (*mst + col * i); //n_arcs
        }

        //alogoritmo
        for(int i =0;i<remainingNodes.size();i++){
            printf("%d|%d\n",i,remainingNodes[i]);
        }
        for(int i =0;i<visitedNodes.size();i++){
            printf("%d|%d\n",i,visitedNodes[i]);
        }
        int i = 2;
        visitedNodes.push_back(remainingNodes[i]);
        remainingNodes.erase(remainingNodes.begin()+i);
        printf("\n end\n");
        for(int i =0;i<remainingNodes.size();i++){
            printf("%d|%d\n",i,remainingNodes[i]);
        }

        for(int i =0;i<visitedNodes.size();i++){
            printf("%d|%d\n",i,visitedNodes[i]);
        }

    }
};