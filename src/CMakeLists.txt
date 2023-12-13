add_library(
        FileService
        STATIC
        Reader.cpp
        SourceFileGenerator.cpp
        Menu.h)

add_library(
        MeasurementTools
        STATIC
        MemoryChecker.cpp
        Timer.cpp
)

add_library(Result STATIC "")

target_sources(
        Result
        PUBLIC
        Result.h
        Solver.cpp
        StatusHelper.h
        Status.h
)

add_executable(
        Main
        main.cpp
)

target_link_libraries(
        Main
        FileService
        MeasurementTools
        Result
)