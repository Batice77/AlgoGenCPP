project(AlgoGenCPP)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O0 -g")

add_executable(test AlgoGenCPP_Test/AlgoGenCPP_Test.cpp
    AlgoGenCPP_Test/TravelingSalesmanProblemEvaluator.cpp
    AlgoGenCPP_Test/TravelingSalesmanProblemGenerator.cpp)
