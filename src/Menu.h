//
// Created by PC on 10/31/2023.
//

#ifndef PEA2_MENU_H
#define PEA2_MENU_H

#include "Status.h"
#include "StatusHelper.h"
#include "Reader.h"
#include "Result.h"
#include "Solver.h"
#include "SourceFileGenerator.h"
#include "Timer.h"
#include "MemoryChecker.h"
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

namespace Menu {
    Status optionAlgorithm() {
        std::string fileName;
        std::string testName;
        int optimum;
        auto map = std::shared_ptr<std::shared_ptr<std::vector<int>>[]>();
        std::cout << "Enter the name of your .txt/ .ini file in sourceFiles directory to execute the algorithm: ";
        Status readStatus;
        while (true) {
            std::cin >> fileName;
            readStatus = FileReader::read(fileName, map, testName, optimum, true);
            if (readStatus != Status::FILE_NOT_FOUND) break;
            std::cout << "\n" << toString(readStatus) << "\n";
            std::cout << "Incorrect file name or file not in the sourceFiles directory!\nPlease try again: ";
        }

        if (readStatus != Status::SUCCESS) {
            return readStatus;
        }

        double p, tempStop;
        int ageLength;
        Result<int> solveStatus{Status::SUCCESS};
        std::cout << "---------------\n";
        std::cout << "Enter the probability of acceptance of the worse solution: ";
        std::cin >> p;
        std::cout << "---------------\n";
        std::cout << "Enter the stop temperature: ";
        std::cin >> tempStop;
        std::cout << "---------------\n";
        std::cout << "Enter the length of age: ";
        std::cin >> ageLength;
        std::cout << "---------------\n\n";
        solveStatus = Solver::tsp(map, optimum, p, tempStop, ageLength, true);
        if (!solveStatus.hasValue()) return solveStatus.status();
        return Status::SUCCESS;
    }

    Status optionMeasurement() {

        Result<int> solver{0};
        int SAMPLE_RATE;
        std::string fileName;

        std::cout << "----- MEASUREMENT -----\n";
        std::cout << "Enter the sample rate: ";
        while (true) {
            std::cin >> SAMPLE_RATE;
            if (!std::cin) {
                std::cout << "Not an integer. Try to enter sample rate again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else break;
        }
        std::cout << "\n";
        auto map = std::shared_ptr<std::shared_ptr<std::vector<int>>[]>();
        int optimum;
        int ageLength;
        double p,tempStop;

        std::cout << "\nEnter the name of the file to be tested: ";
        std::cin >> fileName;
        std::cout << "---------------\n";
        std::cout << "Enter the probability of acceptance of the worse solution: ";
        std::cin >> p;
        std::cout << "\n---------------\n";
        std::cout << "Enter the stop temperature: ";
        std::cin >> tempStop;
        std::cout << "---------------\n";
        std::cout << "Enter the length of age: ";
        std::cin >> ageLength;
        std::cout << "\n---------------\n";


        std::string testName;
        FileReader::read(fileName, map, testName, optimum, false);
        std::ofstream file;
        std::string path = OUTPUT_FILES_DIR;
        path += "/SimulatedAnnealing_";
        path += testName;
        path += ".csv";
        std::cout << path;
        file.open(path);
        if (file.is_open()) std::cout << " - open, testing in progress...\n";
        file << testName << "; optimum: " << optimum << "; size: " << map[0]->size() << "; samples: " << SAMPLE_RATE
             << "; age length: " << ageLength << "\n";
        file << "time [microsec]; error\n";

        Timer timer;

        for (int i = 0; i < SAMPLE_RATE; ++i) {

            timer.start();
            solver = Solver::tsp(map, optimum, p, tempStop, ageLength, false);
            timer.stop();
            if (solver.hasError()) {
                return solver.status();
            }

            auto time = timer.microsecs();

            file << time << "; " << Solver::countPersentage(solver.value().value(), optimum) << "%\n";
        }
        file.close();

        std::cout << "\nMeasurement done. \nThe results can be found in .csv files in outputFiles directory.\n";
        return Status::SUCCESS;
    }
}
#endif //PEA2_MENU_H
