//
// Created by PC on 10/14/2023.
//
#include <memory>
#include <iostream>
#include <limits>
#include <random>
#include "Solver.h"
#include "Result.h"

namespace Solver {

    int INF = std::numeric_limits<int>::max();

    void printSolution(std::vector<int> solution) {
        for (auto elem: solution) {
            std::cout << elem << " ";
        }
        std::cout << solution[0];
        std::cout << "\n";
    }

    double countPersentage(int solutionCost, int optimum) {
        return abs(optimum - solutionCost) * 100 / optimum;
    }

    std::vector<int> generateRandomSolution(int size) {
        std::vector<int> solution;
        solution.reserve(size);
        std::vector<bool> visited(size, false);
        int vertex;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);
        while (not std::all_of(visited.begin(), visited.end(), [](bool visit) { return visit; })) {
            vertex = distrib(gen);
            if (!visited[vertex]) {
                solution.emplace_back(vertex);
                visited[vertex] = true;
            }
        }
        return solution;
    }

    std::vector<int> generateGreedyRandomSolution(std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph) {
        int size = graph[0]->size();
        std::vector<int> solution;
        solution.reserve(size);
        std::vector<bool> visited(size, false);
        int vertex;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);
        vertex = distrib(gen);
        solution.emplace_back(vertex);
        visited[vertex] = true;
        int nextVertex;
        int costNextPath;
        while (not std::all_of(visited.begin(), visited.end(), [](bool visit) { return visit; })) {
            nextVertex = 0;
            costNextPath = INF;
            for (int i = 0; i < size; ++i) {
                if (visited[i]) continue;
                if ((*graph[vertex])[i] < costNextPath) {
                    nextVertex = i;
                    costNextPath = (*graph[vertex])[i];
                }
            }
            visited[nextVertex] = true;
            solution.emplace_back(nextVertex);
            vertex = nextVertex;
        }
        return solution;

    }


    double calculateStartingTemp(double p, std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph) {
        int sum = 0;
        int x, y;
        double avrg;
        std::vector<int> solution;
        for (int i = 0; i < 10000; ++i) {
            solution = generateRandomSolution(graph[0]->size());
            x = calculateSolutionCost(solution, graph);
            solution = generateRandomSolution(graph[0]->size());
            y = calculateSolutionCost(solution, graph);
            sum += abs(x - y);
        }
        avrg = sum / 10000;
        return -avrg / log(p);
    }

    std::vector<int> swap(std::vector<int> solution) {
        int i1, i2;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, solution.size() - 1);
        i1 = distrib(gen);
        do {
            i2 = distrib(gen);
        } while (i1 == i2);
        int temp = solution[i1];
        solution[i1] = solution[i2];
        solution[i2] = temp;
        return solution;
    }

    std::vector<int> opt2(std::vector<int> solution) {
        std::vector<int> newSolution;
        newSolution.reserve(solution.size());
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, solution.size() - 1);
        int i1, i2;
        int start, end;
        i1 = distrib(gen);
        do {
            i2 = distrib(gen);
        } while (i1 == i2);
        if (i1 < i2) {
            start = i1;
            end = i2;
        } else {
            start = i2;
            end = i1;
        }
        for (int i = 0; i <= start; ++i) {
            newSolution.emplace_back(solution[i]);
        }

        for (int i = end; i > start; --i) {
            newSolution.emplace_back(solution[i]);
        }

        for (int i = end + 1; i < solution.size(); ++i) {
            newSolution.emplace_back(solution[i]);
        }

        return newSolution;
    }

    std::vector<int> insertCity(std::vector<int> &solution) {
        int pick, dest;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, solution.size() - 1);
        pick = distrib(gen);
        do {
            dest = distrib(gen);
        } while (pick == dest);
        int temp = solution[pick];
        solution.erase(solution.begin() + pick);
        solution.insert(solution.begin() + dest, temp);
        return solution;
    }

    int calculateSolutionCost(std::vector<int> &solution, std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph) {
        int cost = 0;
        for (int i = 0; i < solution.size(); ++i) {
            if (i == solution.size() - 1) {
                cost += (*graph[solution[i]])[solution[0]];
            } else {
                cost += (*graph[solution[i]])[solution[i + 1]];
            }
        }
        return cost;
    }

    bool acceptSolution(int &currentBest, int &solution, double &temperature) {
        if (solution <= currentBest) return true;
        double probability = exp((currentBest - solution) / temperature);
        std::random_device rd;
        std::mt19937 gen(rd());
        auto random = std::generate_canonical<double, 10>(gen);
        return random < probability;
    }

    void geometricCooling(double &temperature, double alfa) {
        temperature = temperature * alfa;
    }

    void cauchyCooling(double &temperature, double constant) {
        temperature = temperature / (1 + constant * temperature);
    }

    Result<int>
    tsp(std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &graph, int optimum, double p, double stopT,
        int ageLength, bool print) {
        int minCost;
        int curMinCost;
        int curCost;
        double temp = calculateStartingTemp(p, graph);
        std::vector<int> minSolution;
        minSolution.reserve(graph[0]->size());
        std::vector<int> curMinSolution;
        std::vector<int> curSolution;
        curSolution.reserve(graph[0]->size());
        curMinSolution.reserve(graph[0]->size());
        curSolution = Solver::generateGreedyRandomSolution(graph);
        curMinSolution = curSolution;
        minCost = calculateSolutionCost(curSolution, graph);
        curMinCost = minCost;
        std::cout << "Greedy: " << minCost << "\n";
        printSolution(curSolution);

        while (temp > stopT) {
            for (int i = 0; i < ageLength; ++i) {
                curSolution = swap(curMinSolution);
                curCost = Solver::calculateSolutionCost(curSolution, graph);
                if (curCost < minCost) {
                    minCost = curCost;
                    minSolution = curSolution;
                }
                if (curCost < curMinCost || acceptSolution(curMinCost, curCost, temp)) {
                    curMinCost = curCost;
                    curMinSolution = curSolution;
                }
            }
            geometricCooling(temp, 0.99);
        }
        if (print) {
            std::cout << "The solution with " << countPersentage(minCost, optimum)
                      << " % error:\n";
            printSolution(minSolution);
            std::cout << "Cost of solution found: " << minCost << " Optimal cost: " << optimum << "\n\n";
        }
        return minCost;
    }
}