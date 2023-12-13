//
// Created by Szymon on 2023-04-22.
//

#include "SourceFileGenerator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <memory>

namespace SourceFileGenerator {
    Status generateFile(const int &size, const bool symmetric) {

        try{
            std::string filename = SOURCE_FILES_DIR;
            filename += "\\test.txt";
            std::ofstream file;
            file.open(filename);
            if (!file.is_open()) {
                return Status::FILE_NOT_OPENED;
            }

            int value;
            std::random_device rand_dev;
            std::mt19937 gen(rand_dev());
            std::uniform_int_distribution<> dis(1, 9);


            auto map = std::make_shared<std::vector<std::shared_ptr<std::vector<int>>>>();
            map->reserve(size);
            for (int i = 0; i < size; ++i) {
                map->push_back(std::make_shared<std::vector<int>>());
            }
            for (int i = 0; i < size; ++i) {
                (*map)[i]->reserve(size);
            }

            if (symmetric) {
                for (int i = 0; i < size; ++i) {
                    for (int j = i; j < size; ++j) {
                        value = dis(gen);
                        if (i != j) {
                            (*(*map)[i])[j] = value;
                            (*(*map)[j])[i] = value;
                        } else {
                            (*(*map)[i])[j] = -1;
                        }
                    }
                }
            } else {
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        value = dis(gen);
                        if (i != j) {
                            (*(*map)[i])[j] = value;
                        } else {
                            (*(*map)[i])[j] = -1;
                        }
                    }
                }
            }

            file << size << "\n";
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    file << (*(*map)[i])[j];
                    if (j != size - 1) file << " ";
                }

                if (i != size - 1)file << "\n";
            }
            file.close();
            return Status::SUCCESS;
        }catch(std::exception &e){
            std::cout<<e.what()<<"\n";
            return Status::GENERATOR_ERROR_UNEXPECTED;
        }
    }
}
