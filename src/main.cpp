#include <iostream>
#include <vector>
#include <ctime>
#include "Graph.h"
#include "vehicle.h"
#include "colony.h"
#include "fileloader.h"

int main(int argc, char const *argv[]) {
    // Uncomment and modify the following block if you want to handle command-line arguments
    /*
    if (argc < 2) {
        std::cerr << "argc: " << argc << " should be >= 2";
        return -1;
    }
    */

    freopen("out1.txt", "w", stdout);

    const clock_t start_time = clock();

    std::vector<std::vector<int>> param;
    std::vector<std::vector<double>> param1;
    int car_capacity, num_car, num_depot, num_bike, bike_capacity = 0;
    car_capacity = 0;
    num_car = 0;

    file_loader("probs/Multi_depot/ThucNghiem/C107.txt", param, car_capacity, bike_capacity, num_car, num_bike, num_depot, param1);

    // Uncomment and modify the following block if you want to use the Graph class
    /*
    Graph* graph = new Graph(param, car_capacity, bike_capacity, num_car, num_bike, num_depot, param1);
    graph->run_GreedyAlgorithm();
    graph->show_each_car_tour();
    graph->show_node_info();
    graph->show_distance_matrix();
    delete graph;
    graph = nullptr;
    */

    Colony* colony = new Colony(param, car_capacity, bike_capacity, num_car, num_bike, num_depot, param1);
    colony->run_ACO();
    // colony->show_distance_matrix();

    delete colony;
    colony = nullptr;

    const clock_t end_time = clock();
    std::cout << (end_time - start_time) / double(CLOCKS_PER_SEC) << "sec" << std::endl;

    return 0;
}
