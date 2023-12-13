//
// Created by PC on 10/14/2023.
//

#ifndef PEA2_SOLVER_H
#define PEA2_SOLVER_H

#include "Result.h"
#include <vector>
#include <cmath>

namespace Solver {

    void printSolution(std::vector<int> solution);

    double countPersentage(int solutionCost, int optimum);

    std::vector<int> generateRandomSolution(int size);

    std::vector<int> generateGreedyRandomSolution(std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph);

    double calculateStartingTemp(double p,std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph);

    std::vector<int> swap(std::vector<int> solution);

    std::vector<int> opt2(std::vector<int> solution);

    std::vector<int> insertCity(std::vector<int> &solution);

    int calculateSolutionCost(std::vector<int> &solution, std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph);

    bool acceptSolution(int &currentBest, int &solution, double &temperature);

    void geometricCooling(double &temperature, double alfa);

    void cauchyCooling(double &temperature, double constant);

    Result<int>
    tsp(std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph, int optimum, double p, double stopT,
        int ageLength, bool print = false);
}
#endif //PEA2_SOLVER_H
