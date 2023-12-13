#include <memory>
#include <vector>
#include "Status.h"

namespace FileReader {

    Status
    read(const std::string &filename, std::shared_ptr<std::shared_ptr<std::vector<int>>[]> &map, std::string &testName,
         int &optimum, bool print);

}