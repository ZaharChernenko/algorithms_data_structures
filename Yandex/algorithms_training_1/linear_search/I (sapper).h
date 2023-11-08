#pragma once
#include <iostream>
#include <vector>
#include <tuple>


void createMap(std::vector<std::vector<int>>& map, const std::vector<std::tuple<int, int>>& mines_map) {
    int x_arr[8] {0, 1, 1, 1, 0, -1, -1, -1};
    int y_arr[8] {-1, -1, 0, 1, 1, 1, 0, -1};

    for (const auto& elem: mines_map) {
        for (char i = 0; i != 8; ++i) {
            ++map[std::get<0>(elem) + x_arr[i]][std::get<1>(elem) + y_arr[i]];
        }
    }

    for (const auto& elem: mines_map) map[std::get<0>(elem)][std::get<1>(elem)] = -1;
}


int inputI() {
    int n_rows, n_cols, n_mines;
    std::cin >> n_rows >> n_cols >> n_mines;

    std::vector<std::vector<int>> map(n_rows + 2, std::vector<int>(n_cols + 2, 0));
    std::vector<std::tuple<int, int>> mines_map(n_mines);

    for (auto& elem: mines_map) {
        std::cin >> std::get<0>(elem) >> std::get<1>(elem);
    }

    createMap(map, mines_map);
    for (int i = 1; i != map.size() - 1; ++i) {
        for (int j = 1; j != map[0].size() - 1; ++j) {
            if (map[i][j] != -1) std::cout << map[i][j];
            else std::cout << '*';
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}