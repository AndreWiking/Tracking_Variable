cmake_minimum_required(VERSION 3.20)
project(Tracking_Numbers)

#-fno-elide-constructors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors" )
#set(CMAKE_CXX_FLAGS -fno-elide-constructors)

set(CMAKE_CXX_STANDARD 17)

#set(SOURCE_FILES main.cpp)

#include_directories("${GRAPHVIZ_INCLUDE_DIR}")

#set(gsl_INCLUDE_DIR /opt/homebrew/Cellar/graphviz/2.50.0/include/graphviz)
#include_directories(${gsl_INCLUDE_DIR})

add_executable(Tracking_Numbers Source/main.cpp Source/TrackingValue.cpp Source/TrackingValue.h Source/Algorithm/Algorithm.cpp Source/Algorithm/Algorithm.h Source/WorkFile/LogController.cpp Source/WorkFile/LogController.h Source/WorkFile/FunctionPrinter.cpp Source/WorkFile/FunctionPrinter.h Source/WorkFile/DotController.cpp Source/WorkFile/DotController.h)

#target_link_libraries(Tracking_Numbers /opt/homebrew/Cellar/graphviz/2.50.0/lib/graphviz)
