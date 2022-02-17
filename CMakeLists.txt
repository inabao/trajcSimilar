cmake_minimum_required(VERSION 3.18)
project(trajcSimilar)

set(CMAKE_CXX_STANDARD 14)

add_executable(trajcSimilar main.cpp distance.cpp distance.h similarTrajectory.cpp similarTrajectory.h utils.cpp utils.h exactS.cpp exactS.h constant.h pss.cpp pss.h experiment.cpp experiment.h mostSimilar.cpp mostSimilar.h)
