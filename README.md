# trajcSimilar

## introduction
This project mainly solves the sub-trajectory query problem and finds the exact sub-trajectory for the query trajectory within the time complexity of O(nm). The applicable distance functions in this project include but not limited to FD, DTW, EDR , ERP, etc. The code for solving the sub-trajectory problem under different distance functions is given [here](https://github.com/inabao/trajcSimilar/blob/master/similarTrajectory.cpp).
## run the demo
We wrote the function str2path to convert a string into a trajectory. On top of that you can use "efficientAlgorithm" (CMA) to solve for the optimal subtrajectory and "exactS" (ExactS) for the groud truth.

You can get a result by going to the trajcSimilar folder and running the following command.
```shell
./run_demo.sh
```
You can modify the query trajectory and the data trajectory in [main.cpp](https://github.com/inabao/trajcSimilar/blob/master/main.cpp), and in [distance.cpp](https://github.com/inabao/trajcSimilar/blob/master/distance.cpp) you can modify the distance function.
