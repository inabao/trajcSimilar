cmake_minimum_required(VERSION 3.18)
project(trajcSimilar)

set(CMAKE_CXX_STANDARD 11)

add_executable(trajcSimilar main.cpp constant.h distance.cpp distance.h similarTrajectory.cpp similarTrajectory.h utils.cpp utils.h exactS.cpp exactS.h pss.cpp pss.h experiment.cpp experiment.h mostSimilar.cpp mostSimilar.h)
