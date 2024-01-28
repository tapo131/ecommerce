#include "fileloader.h"
#include <iostream>
#include <vector>
#include <xlnt/xlnt.hpp>

void file_loader(const char *filename,
                 std::vector<std::vector<int>> &param,
                 int &car_capacity, int &bike_capacity,
                 int &num_car, int &num_bike,
                 int &num_depot, std::vector<std::vector<double>> &param1) {
    xlnt::workbook wb;
    try {
        wb.load(filename);
    } catch (const std::exception &e) {
        std::cerr << "Error loading XLSX file: " << e.what() << std::endl;
        return;
    }

    xlnt::worksheet ws = wb.active_sheet();

    num_car = ws.cell("A1").value<int>();
    car_capacity = ws.cell("B1").value<int>();
    num_depot = ws.cell("C1").value<int>();
    num_bike = ws.cell("D1").value<int>();
    bike_capacity = ws.cell("E1").value<int>();

    for (xlnt::row r : ws.rows(true)) {
        std::vector<int> tmp_vec;
        for (xlnt::cell c : r) {
            tmp_vec.push_back(c.value<int>());
        }
        param.push_back(tmp_vec);
    }
}

int main() {
    const char *filename = "node.xlsx";
    
    std::vector<std::vector<int>> param;
    int car_capacity, bike_capacity, num_car, num_bike, num_depot;
    std::vector<std::vector<double>> param1;

    file_loader(filename, param, car_capacity, bike_capacity, num_car, num_bike, num_depot, param1);

    // The rest of your main code...

    return 0;
}
