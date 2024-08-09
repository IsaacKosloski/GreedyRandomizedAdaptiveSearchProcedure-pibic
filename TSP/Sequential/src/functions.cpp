#include "functions.h"

/*Pure Greedy Procedure to generate initial tour*/
void greedyTSP(Scanner* &tsp, Node* &tour)
{
    //Start with the first random node
    // Seed the random number generator
    srand(time(0));
    //Generate a random node between 0 and tourDimension
    int currentNode = rand() % tsp->dimensionOfNodes;
    tour[0].ID = currentNode;
    tsp->nodes[currentNode].eligible = false;

    //For each node, consider the nearest node that is still eligible
    for (int i = 1; i < tsp->dimensionOfNodes; i++)
    {
        double minDistance = numeric_limits<double>::max();
        int nearestNode = 0;
        for (int j = 0; j < tsp->dimensionOfNodes; j++)
        {
            if (tsp->nodesDistance[(currentNode * tsp->dimensionOfNodes) + j].distanceValue < minDistance &&
                tsp->nodes[j].eligible)
            {
                minDistance = tsp->nodesDistance[(currentNode * tsp->dimensionOfNodes) + j].distanceValue;
                nearestNode = j;
            }
        }
        tour[i].ID = nearestNode;
        tour[i].distanceValue = minDistance;
        for (int j = 0; j < tsp->dimensionOfNodes; j++)
            tsp->nodesDistance[(j * tsp->dimensionOfNodes) + i].eligible = false;
        currentNode = nearestNode;
        tsp->nodes[currentNode].eligible = false;
    }
    for (int i = 0; i < tsp->dimensionOfNodes; i++)
        tsp->nodes[i].eligible = true;
}

/*Greedy Randomized Procedure 2*/
void greedyRandomized2(Node* &graph, Node* &graphNodes, Node* &tour, double alpha, int tourDimension)
{
    int i, k, currentNode, rcsDimension;
    double minCost, maxCost, cost;

    int *newTour, *candidateSet, *recentCandidateSet;
    double *incrementalCostSet;

    newTour            = new int[tourDimension];
    candidateSet       = new int[tourDimension];
    recentCandidateSet = new int[tourDimension];
    incrementalCostSet = new double[tourDimension];

    srand(time(0));

    for (i = 0; i < tourDimension; i++)
    {
        candidateSet[i] = tour[i].ID;
        recentCandidateSet[i] = 0;
        newTour[i] = 0;
    }

    auto randNum = rand();

    currentNode = abs((rand() + randNum)  % tourDimension);
    //cout << "CurrentNode: " << currentNode << endl;
    newTour[0] = currentNode;
    //cout << "newTour[0]: " << newTour[0] << endl;
    graphNodes[currentNode].eligible = false;
    //cout << "NT[" << k << "]: " << newTour[k] << endl;

    /*printListOfInt(newTour, tourDimension);
    printListOfInt(recentCandidateSet, tourDimension);
    printListOfInt(candidateSet, tourDimension);*/
    //cout << "linha 146" << endl;
    for (k = 1; k < tourDimension; k++)
    {
        //cout << "linha 149 " << k << endl;
        minCost = DBL_MAX;
        maxCost = DBL_MIN;
        rcsDimension = 0;
        //cout << "linha 153" << endl;
        /*Evaluating the minCost in graph*/
        for (i = 0; i < tourDimension; i++)
        {
            /*cout << "graph edge[" << currentNode << "][" << i << "]: " << graph[(currentNode * tourDimension) + i].distanceValue <<endl;
            cout << "graph edge[" << currentNode << "][" << i << "]: " << graphNodes[i].eligible << endl;*/
            //cout << "linha 159 " << i << endl;
            if (graph[(currentNode * tourDimension) + i].distanceValue < minCost && graphNodes[i].eligible)
                minCost = graph[(currentNode * tourDimension) + i].distanceValue;
            else if(graph[(currentNode * tourDimension) + i].distanceValue > maxCost && graphNodes[i].eligible)
                maxCost = graph[(currentNode * tourDimension) + i].distanceValue;
            //cout << "linha 164 " << i << endl;
            /*cout << "Cost(m)[" << i <<"]: " << minCost << endl;
            cout << "Cost(M)[" << i <<"]: " << maxCost << endl;*/
        }
        /*cout << "Cost(mf): " << minCost << endl;
        cout << "Cost(Mf): " << maxCost << endl;
        cout << endl;*/

        /*Constructing the RCL*/
        cost = minCost + (alpha * (maxCost - minCost));
        //cout << "linha 174" << endl;
        for (i = 0; i < tourDimension; i++)
        {
            //cout << "(RCL) graph edge[" << currentNode << "][" << i << "]: " << graph[(newTour[currentNode] * tourDimension) + i].distanceValue << endl;
            if (graph[(newTour[currentNode] * tourDimension) + i].distanceValue <= cost && graphNodes[i].eligible)
            {
                recentCandidateSet[rcsDimension] = i;
                rcsDimension++;
            }
            //cout << "linha 183 " << i << endl;
        }
        if (!rcsDimension)
            for (i = 0; i < tourDimension; i++)
                if (graphNodes[i].eligible)
                {
                    recentCandidateSet[0] = i;
                    rcsDimension++;
                    i = tourDimension;
                }
        /*/cout << endl;
        //cout << "|RCL| = " << rcsDimension << endl;
        for (i = 0; i < rcsDimension; i++)
            cout << "RCL[" << i << "]: " << recentCandidateSet[i] << endl;
        cout << endl;*/


        currentNode = abs((rand() + randNum)  % rcsDimension);

        //cout << "CurrentNode: " << currentNode << endl;

        //cout << "linha 192" << endl;

        //cout << "New node: " << recentCandidateSet[currentNode] << endl;

        newTour[k] = recentCandidateSet[currentNode];
        //cout << "linha 197" << endl;

        //cout << "NT[" << k << "]: " << newTour[k] << endl;
        graphNodes[recentCandidateSet[currentNode]].eligible = false;
        for (i = 0; i < tourDimension; i++)
            recentCandidateSet[i] = 0;
    }

    for (i = 0; i < tourDimension; i++)
        tour[i].ID = newTour[i];





    delete[] newTour;
    delete[] candidateSet;
    delete[] recentCandidateSet;
    delete[] incrementalCostSet;
}



/**********************************************************************************************************************/
/*(iii) Local search methods*/
void twoOpt(Scanner* tsp, Node* &tour, Node* &bestTour, int tourDimension)
{
    Node* newSolution = new Node[tourDimension];
    memcpy(bestTour, tour, tourDimension * sizeof(Node));

    double newCost;
    bool   improvement = true;
    double bestCost    = tourCost(bestTour, tsp->nodesDistance, tourDimension);

    while(improvement)
    {
        improvement = false;
        for (int i = 1; i < tourDimension - 2; i++)
            for (int j = i + 1; j < tourDimension; j++)
            {
                memcpy(newSolution, bestTour, tourDimension * sizeof(Node));
                reverse(newSolution + i, newSolution + j);
                newCost = tourCost(newSolution, tsp->nodesDistance, tourDimension);
                if (newCost < bestCost)
                {
                    memcpy(bestTour, newSolution, tourDimension * sizeof(Node));
                    bestCost = newCost;
                    improvement = true;
                }
            }
    }
    delete[] newSolution;
}

/**********************************************************************************************************************/
/*(v) Auxiliary methods*/
double tourCost(Node* &tour, Node* &nodesDistance, int tourDimension)
{
    double cost = 0;
    for (int i = 0; i < tourDimension - 1; i++)
        cost += nodesDistance[(tour[i].ID * tourDimension) + tour[i + 1].ID].distanceValue;
    cost += nodesDistance[(tour[tourDimension - 1].ID * tourDimension) + tour[0].ID].distanceValue;
    return cost;
}

void setMatrixEligible(Node* &nodesDistance, int tourDimension)
{
    for (int i = 0; i < tourDimension; i++)
        for (int j = 0; j < tourDimension; j++)
            j != i ? nodesDistance[(i * tourDimension) + j].eligible = false : nodesDistance[(i * tourDimension) + j].eligible = true;
}

void copyArray(Node* &destination, Node* &source, int size)
{
    for (int i = 0; i < size; i++)
        destination[i] = source[i];
}

void printResult(Node* bestSolution, const char* fileName, double elapsedTime, double cost, int dimensionOfNodes, int iterations)
{
    //Writing the last result in the file
    ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        outputFile << "Iterations: " << iterations;
        outputFile << " Time: " << fixed << setprecision(4) << elapsedTime << " sec - " << elapsedTime/60 << " min - " << elapsedTime/3600 << " horas" << endl;
        outputFile << floor(elapsedTime/3600) << " h " << ((elapsedTime/3600) - floor(elapsedTime/3600)) * 60 << " min" << endl ;
        outputFile << "Problem dimension: " << dimensionOfNodes << endl;
        outputFile << "\nTotal distance: " << cost << endl;

        for (int i = 0; i < dimensionOfNodes; i++)
            outputFile << "[" << bestSolution[i].ID << "] ";
    }
    outputFile.close();
}

/**********************************************************************************************************************/
/*(vi) Debug methods*/
void printTableOfDouble(double *matrix, int tourDimension) {
    for (int in = 0; in < tourDimension; in++)
    {
        for (int jn = 0; jn < tourDimension; jn++)
        {
            if (matrix[(in * tourDimension) + jn] < 10)
                cout << "|0" << fixed << setprecision(4) << matrix[(in * tourDimension) + jn] << "|  ";
            else
                cout << "|" << fixed << setprecision(4) << matrix[(in * tourDimension) + jn] << "|  ";
        }
        cout << endl;
    }
    cout << endl;
}

void printTableOfNode(Node *matrix, int tourDimension) {
    for (int in = 0; in < tourDimension; in++)
    {
        for (int jn = 0; jn < tourDimension; jn++)
        {
            if (matrix[(in * tourDimension) + jn].distanceValue < 10)
                cout << "|0" << fixed << setprecision(4) << matrix[(in * tourDimension) + jn].distanceValue << "|  ";
            else
                cout << "|" << fixed << setprecision(4) << matrix[(in * tourDimension) + jn].distanceValue << "|  ";
        }
        cout << endl;
    }
    cout << endl;
}

void printListOfNode(Node *list, int tourDimension)
{

    for (int in = 0; in < tourDimension; in++)
        cout << "[" << list[in].ID << "] ";

    cout << endl;

}

void printListOfNodeWeight(Node *list, int tourDimension)
{

    for (int in = 0; in < tourDimension; in++)
    {
        cout << "[" << list[in].ID << "]-> " << list[in].distanceValue << " " << endl;
    }
    cout << endl;

}

void printListOfDouble(double *list, int tourDimension)
{

    for (int in = 0; in < tourDimension; in++)
        cout << "[" << list[in] << "] ";
    cout << endl;

}

void printListOfInt(int *list, int tourDimension)
{

    for (int in = 0; in < tourDimension; in++)
        cout << "[" << list[in] << "] ";
    cout << endl;
}

