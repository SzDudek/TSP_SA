//
// Created by PC on 10/9/2023.
//

#ifndef PEA2_STATUSHELPER_H
#define PEA2_STATUSHELPER_H

#include <string>
#include "Status.h"

std::string toString(Status status) {
    switch (status) {
        case Status::SUCCESS:
            return "Success";
        case Status::GENERATOR_ERROR_UNEXPECTED:
            return "Error: Unexpected generator error";
        case Status::FILE_NOT_OPENED:
            return "Error: File did not open";
        case Status::SOLVER_ERROR:
            return "Error: Solver Error";
        case Status::READ_ERROR_DATA:
            return "Error: Read Error Data";
        case Status::READ_ERROR_HEADLINE:
            return "Error: Read Error Headline";
        case Status::READ_ERROR_TESTNAME:
            return "Error: Read Error Testname";
        case Status::READ_ERROR_OPTIMUM:
            return "Error: Read Error Optimum";
        case Status::READ_ERROR_UNEXPECTED:
            return "Error : Unexpected read error";
        case Status::FILE_NOT_FOUND:
            return "Error: File not found";
        case Status::MEMORY_ERROR_READ:
            return "Error: Memory usage read";
        case Status::MEMORY_ERROR_PARSE:
            return "Error: Memory usage parse";
        default:
            return "CO.";
    }
}

#endif //PEA2_STATUSHELPER_H
