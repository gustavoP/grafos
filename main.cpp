#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include <string>
#include "Graph.cpp"

using namespace std;    


int **d ;
int sum();
char fileName[200];
Graph *grafo;

/*
void printAdj(int** adj, int nodes){
    printf("\n Matriz de adjacencias");
    for(int i=0;i< nodes; i++){
        printf("\n|");
        for(int j=0;j< nodes; j++){
            printf("%d|",adj[i][j]);
        }
    }
} */


//-----------------------------------------------            
int main(int argc, char *argv[]) 
{ 
    if(argc==1){
        sprintf(fileName, "%s","Arquivos/G1.txt");
        printf("Lendo arquivo padrao: %s \n",fileName);
    }
    else{
        sprintf(fileName, "%s",argv[1]);
    }
    
   
    grafo = new Graph(fileName);
    //int nodes = grafo->getNumNodes();

    //grafo->setListaAdj();
    //Graph::Adj_node** listaAdj = grafo->getListaAdj();
    //grafo->printListaAdj();
    //printf("\n grau do noh %d: %d\n",5,grafo->nodeDegreeListAdj(5));
    //grafo->setAdjMatrix();
    //int **adj = grafo->getAdjMatrix();
    //grato->printAdj();//printAdj(adj,nodes);
    //printf("\n grau do noh %d: %d\n",5,grafo->nodeDegreeAdj(5));
    //print adj matrix
    
    
    grafo->printFile();
    printf("\nFIM\n");
    
    //grafo->prim();

    return 0; 
} 