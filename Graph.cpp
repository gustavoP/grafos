#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
//#include "Graph.h"

using namespace std;

class Graph
{

  private:
    ifstream fileStream;
    int **arcs; //alocar espaço quando for construir
    int **adjMatrix; //matriz de adjacencias
    int n_arcs,n_nodes,bool_weight;
    

    typedef struct Adj_node{
        int node;
        Adj_node *next_node;
        int weight;
    }Adj_node;

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
        fscanf(file, "%d %d %d", &n_nodes, &n_arcs, &bool_weight);

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
        printf("\n n1|n2|peso : Grafo = %s \n",this->fileName);
        for(int i=0; i<this->n_arcs;i++){
            printf("|%d |%d |%d \n",this->arcs[i][0],this->arcs[i][1],this->arcs[i][2]);
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

    int getNumNodes(){
        return this->n_nodes;
    };

    //! Esse metodo retorna o grau de um noh a partir da matriz de adjacencias.
    /*! Esse metodo retorna o grau de um noh considerando um grafo nao direcional.
        A matriz de adjacencias deve estar instanciada com o metodo getAdjMatrix();

        \param node: numero do no, primeiro noh=1.
        \return numero: grau do no. caso retorne -1 entao o noh nao existe
    */
    int nodeDegreeAdj(int node){
        if(node>this->n_nodes){
            return -1;
        }
        int degree=0;
        for(int i=0;i<this->n_nodes;i++){
            degree+=this->adjMatrix[i][node-1];
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
            n1=this->arcs[i][0] -1; //passar a começar do zero para indice ser = noh
            n2=this->arcs[i][1] -1;
            w=this->arcs[i][2];
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

    //void incidencia();
};