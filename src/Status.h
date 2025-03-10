//
// Created by PC on 10/9/2023.
//

#ifndef PEA2_STATUS_H
#define PEA2_STATUS_H

enum class Status {
    SUCCESS,
    GENERATOR_ERROR_UNEXPECTED,
    FILE_NOT_OPENED,
    FILE_NOT_FOUND,
    READ_ERROR_DATA,
    READ_ERROR_HEADLINE,
    READ_ERROR_TESTNAME,
    READ_ERROR_OPTIMUM,
    READ_ERROR_UNEXPECTED,
    MEMORY_ERROR_READ,
    MEMORY_ERROR_PARSE,
    SOLVER_ERROR
};
#endif //PEA2_STATUS_H
