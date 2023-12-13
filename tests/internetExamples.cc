#include<gtest/gtest.h>
#include "../src/Status.h"
#include "../src/Reader.h"
#include "../src/Result.h"
#include "../src/Solver.h"

TEST(internetTests, test1) {
    auto map = std::shared_ptr<std::shared_ptr<std::vector<int>>[]>();
    Status readStatus = FileReader::read("internetExmpl1.txt", map, false);
    ASSERT_EQ(readStatus,Status::SUCCESS);
    Result<int> solveStatus = Solver::tsp(map, false);
    ASSERT_EQ(solveStatus.hasValue(), true);
    EXPECT_EQ(solveStatus.value(),32);
}