//
// Created by PC on 10/9/2023.
//
#include <string>
#include "MemoryChecker.h"
#include "Result.h"
#include "windows.h"
#include "psapi.h"

namespace Memory {

    SIZE_T memoryUsage() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
        return pmc.WorkingSetSize;
    }

    std::string toString() {
        size_t usage = memoryUsage();
        size_t megaBytes = usage / 1000000;
        size_t kiloBytes = (usage - megaBytes * 1000000) / 1000;
        size_t bytes = usage - megaBytes * 1000000 - kiloBytes * 1000;
        return std::to_string(megaBytes) + "MB " + std::to_string(kiloBytes) + "kB " + std::to_string(bytes) + "B\n";

    }
}