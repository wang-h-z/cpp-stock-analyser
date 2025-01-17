cmake_minimum_required(VERSION 3.10)
project(StockAnalyser)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/include)

add_executable(app main.cpp stock_analyser.cpp)
