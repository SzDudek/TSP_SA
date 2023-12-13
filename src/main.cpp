#include <iostream>
#include "Menu.h"

int main() {

    int option = 0;
    Status algorithm;
    Status measurement;

    while (true) {
        std::cout << "----- TSP: Simulated Annealing -----\n";
        std::cout << "1. Run the algorithm on your own .txt file, placed in sourceFiles directory\n";
        std::cout << "2. Run time and memory measurements for the algorithm\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;
        switch (option) {
            case 1:
                algorithm = Menu::optionAlgorithm();
                if (algorithm != Status::SUCCESS) {
                    std::cout << toString(algorithm);
                    return 1;
                }
                break;
            case 2:
                measurement = Menu::optionMeasurement();
                if (measurement != Status::SUCCESS) {
                    std::cout << toString(measurement);
                    return 1;
                }
                break;
            case 3:
                return 0;
            default:
                std::cout << "Wrong input. Please try again!\n";
        }
    }
}
