all:  test_s
test_s: main.cpp
	g++ -std=c++11 main.cpp erdos_renyi.cpp graph.cpp graph_algorithms.cpp utils.hpp plotting_utils.hpp -o main

clean:
	echo
	/bin/rm main
	