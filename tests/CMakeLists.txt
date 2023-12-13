add_executable(
        Testing
        example.cc
        mierzwa.cc internetExamples.cc)

target_link_libraries(
        Testing
        GTest::gtest_main
        Result
        FileService
)

target_link_directories(
        Testing
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(Testing)