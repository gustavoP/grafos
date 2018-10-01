#include <stdio.h>
#include <stdlib.h>

class Graph{

    private:
        int size;

    public:
        Graph();
        Graph(int size);
        void setSize(int newSize);
        int getSize();
        void printSize();

};