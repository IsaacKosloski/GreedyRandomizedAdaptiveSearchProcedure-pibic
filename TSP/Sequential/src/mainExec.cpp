/*Greedy Randomized Adaptive Search Procedures
 *
 * g++ node.cpp scanner.cpp functions.cpp main.cpp -o TspSeq2 -Wall -pedantic
 * ./TspSeq2 ../Benchmarks/a280.tsp/a280.tsp ../Solutions/Sequential/a280.sol
 * ./TspSeq2 ../Benchmarks/d198.tsp/d198.tsp ../Solutions/Sequential/d198two.sol
 * */

#include "scanner.h"
#include "functions.h"
#define MAX_ITERATION 1000

/* First section: Global variables */

/* Second  section: main function */
int main(int argc,char **argv)
{
    /*First subsection: variables and data structs declaration (and some default definition)*/
    int iteration = 0;
    long i, j;
    double alpha = 0.5, costTour, costBestTour;
    bool *graphNodes;
    Node *tour, *bestTour, *candidateSet;

    for(int exec = 0; exec < 30; exec++)
    {
        /* Second subsection: data input*/
        Scanner *tsp = new Scanner(argv[1]);

        //Memory allocation
        tour         = new Node[tsp->dimensionOfNodes];
        bestTour     = new Node[tsp->dimensionOfNodes];
        candidateSet = new Node[tsp->dimensionOfNodes];
        graphNodes   = new bool[tsp->dimensionOfNodes * tsp->dimensionOfNodes];

        for (i = 0; i < tsp->dimensionOfNodes; i++)
            for (j = 0; j < tsp->dimensionOfNodes; j++)
                graphNodes[(i * tsp->dimensionOfNodes) + j] = tsp->nodesDistance[(i * tsp->dimensionOfNodes) + j].eligible;

        //Get the current time before the algorithm starts
        auto start = chrono::high_resolution_clock::now();

        /*Initial tour*/
        greedyTSP(tsp, tour);
        memcpy(bestTour, tour, tsp->dimensionOfNodes * sizeof(Node));


        /*Third subsection: GRASP procedure*/
        while (iteration < MAX_ITERATION)
        {
            /*Greedy Randomized Construction*/
            //greedyRandomized(tsp->nodesDistance, tsp->nodes, tour, candidateSet, alpha, tsp->dimensionOfNodes);
            greedyRandomized2(tsp->nodesDistance, tsp->nodes, tour, alpha, tsp->dimensionOfNodes);

            /*Setting all nodes as available to visit*/
            for (int i = 0; i < tsp->dimensionOfNodes; i++)
                tsp->nodes[i].eligible = true;

            /*Local Search*/
            twoOpt(tsp, tour, tour, tsp->dimensionOfNodes);

            /*Update Solution*/
            costTour     = tourCost(tour, tsp->nodesDistance, tsp->dimensionOfNodes);
            costBestTour = tourCost(bestTour, tsp->nodesDistance, tsp->dimensionOfNodes);

            if (costTour < costBestTour)
                memcpy(bestTour, tour, tsp->dimensionOfNodes * sizeof(Node));

            iteration++;
        }

        //Get the current time after the algorithm ends
        auto finish = chrono::high_resolution_clock::now();

        /*Seventh subsection: Print the results*/
        /*cout << "Best tour cost: "<< tourCost(tour, tsp->nodesDistance, tsp->dimensionOfNodes) << endl;
        cout << "Best tour: ";
        for (i = 0; i < tsp->dimensionOfNodes; i++)
            cout << "[" << tour[i].ID << "] ";*/

        //Calculate the time duration by subtracting the start time from the finish time
        chrono::duration<double> elapsed = finish - start;

        //Print the time duration
        //cout << "Elapsed time: " << elapsed.count() << " s\n";

        string dimension(argv[2]);
        string outputFile1 = "../../Solutions/Yoga/Sequential/" + dimension + "/" + dimension + "i3GDBO2B" + to_string(exec) + ".sol" ;
        char const *outputFileC = outputFile1.c_str();

        double bestSolutionCost = tourCost(bestTour, tsp->nodesDistance, tsp->dimensionOfNodes);
        printResult(bestTour, outputFileC, elapsed.count(), bestSolutionCost, tsp->dimensionOfNodes, MAX_ITERATION);

        //Memory deallocation
        delete[] tour;
        delete[] bestTour;
        delete[] candidateSet;
        delete[] graphNodes;
        delete[] tsp->nodes;
        delete[] tsp->nodesDistance;
        delete tsp;
    }
    return 0;
}


