# trajcSimilar

## introduction
This project mainly solves the sub-trajectory query problem and finds the exact sub-trajectory for the query trajectory within the time complexity of O(nm). The applicable distance functions in this project include but not limited to FD, DTW, EDR , ERP, etc. The code for solving the sub-trajectory problem under different distance functions is given [here](https://github.com/inabao/trajcSimilar/blob/master/similarTrajectory.cpp).
## run the demo
We wrote the function str2path to convert a string into a trajectory. On top of that you can use "efficientAlgorithm" to solve for the optimal subtrajectory and "exactS" for the groud truth.
