#ifndef ITERATEDLOCALSEARCH_FUNCTIONS_H
#define ITERATEDLOCALSEARCH_FUNCTIONS_H
#include "scanner.h"
#include "node.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>


/*Pure Greedy Procedure to generate initial tour*/
void greedyTSP(Scanner* &tsp, Node* &tour);

/*Greedy Randomized Procedure*/
void greedyRandomized(Node* &nodesDistance, Node* &nodes, Node* &tour, Node* &candidateSet, double alpha, int tourDimension);
void greedyRandomized2(Node* &graph, Node* &graphNodes, Node* &tour, double alpha, int tourDimension);
void twoOpt(Scanner* tsp, Node* &tour, Node* &bestTour, int tourDimension);

/**********************************************************************************************************************/
/*(v) Auxiliary methods*/
double tourCost(Node* &tour, Node* &nodesDistance, int tourDimension);
void setMatrixEligible(Node* &nodesDistance, int tourDimension);
void copyArray(Node* &destination, Node* &source, int size);
void printResult(Node* bestSolution, const char* fileName, double elapsedTime, double cost, int dimensionOfNodes, int iterations);
/**********************************************************************************************************************/
/*(vi) Debug methods*/
void printTableOfNode(Node *matrix, int tourDimension);
void printListOfNode(Node *list, int tourDimension);
void printListOfNodeWeight(Node *list, int tourDimension);
void printListOfDouble(double *list, int tourDimension);
void printTableOfDouble(double* matrix, int tourDimension);
void printListOfInt(int *list, int tourDimension);

#endif //ITERATEDLOCALSEARCH_FUNCTIONS_H









