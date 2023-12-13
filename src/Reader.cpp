#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <memory>
#include "Reader.h"
#include "Status.h"

namespace FileReader {
    Status
    read(const std::string &filename, std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &map, std::string &testName,
         int& optimum, bool print) {
        try {
            std::ifstream file;
            std::string path = SOURCE_FILES_DIR;
            path += ('/');
            path += filename;
            file.open(path);
            if (file.is_open()) {
                int mapSize, linkCost;
                file >> mapSize;
                if (file.fail()) return Status::READ_ERROR_HEADLINE;
                map = std::shared_ptr<std::shared_ptr<std::vector<int>>[]>(
                        new std::shared_ptr<std::vector<int>>[mapSize]);

                file >> testName;
                if (file.fail()) return Status::READ_ERROR_TESTNAME;
                file >> optimum;
                if (file.fail()) return Status::READ_ERROR_OPTIMUM;

                for (int j = 0; j < mapSize; ++j) {
                    map[j] = std::make_shared<std::vector<int>>();
                    map[j]->reserve(mapSize);
                    for (int k = 0; k < mapSize; ++k) {
                        file >> linkCost;
                        if (file.fail()) return Status::READ_ERROR_DATA;
                        map[j]->emplace_back(linkCost);
                    }
                }
            } else {
                return Status::FILE_NOT_FOUND;
            }
            file.close();
//            if (print && map[0]->size()<50) {
//                std::cout << "\nPath: " << path << "\n";
//                std::cout << "----- MAP -----\n";
//                for (int i = 0; i < map[0]->size(); ++i) {
//                    for (int j = 0; j < map[0]->size(); ++j) {
//                        std::cout << (*map[i])[j] << " ";
//                    }
//                    std::cout << "\n";
//                }
//            }
            return Status::SUCCESS;
        } catch (std::exception &e) {
            return Status::READ_ERROR_UNEXPECTED;
        }
    }

}