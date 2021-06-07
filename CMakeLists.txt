cmake_minimum_required(VERSION 3.13)
project(goc_cpp)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
include_directories(include 
                    "/gpfs/group/vvs3/default/Weinan/rapidjson/rapidjson-1.1.0/include"
                    "/gpfs/group/vvs3/default/Weinan/ipopt/Ipopt-3.12.13/install/include/coin"
                    "/gpfs/group/vvs3/default/Weinan/boost/boost_1_76_0")
find_library(IPOPT_LIB
    NAMES ipopt sipopt ipopt.3 
    PATHS /gpfs/group/vvs3/default/Weinan/ipopt/Ipopt-3.12.13/install/lib)
find_package(ifopt
    PATHS /gpfs/group/vvs3/default/Weinan/ifopt/install/usr/local/share/ifopt/cmake)
file(GLOB SOURCES "src/*.cpp" 
                  "src/constraints/*.cpp" 
                  "src/constraints_con/*.cpp" 
                  "src/cost/*.cpp" 
                  "src/cost_con/*.cpp" 
                  "src/variables/*.cpp" 
                  "src/variables_con/*.cpp")
add_executable(test ${SOURCES})
target_link_libraries(test PUBLIC ifopt::ifopt_ipopt)
