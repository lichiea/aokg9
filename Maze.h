#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <stdexcept> // for std::invalid_argument

using namespace std;
class MazeGenerator {
public:
    static std::vector<std::vector<int>> generate(unsigned width, unsigned height) {
        if (width < 1 || height < 1) {
            throw std::invalid_argument("Width and height must be at least 1.");
        }

        //Simplified overflow check.  More robust checks might be needed for extremely large inputs.
        if (width > 10000 || height > 10000) {
            throw std::invalid_argument("Width and height are too large.");
        }


        const unsigned output_height = height * 2 + 1;
        const unsigned output_width = width * 2 + 1;
        std::vector<std::vector<int>> maze(output_height, std::vector<int>(output_width));
        int wallCount = 0;
        // Initialize maze with walls and paths
        for (unsigned i = 0; i < output_height; ++i) {
            for (unsigned j = 0; j < output_width; ++j) {
                if ((i % 2 == 1) && (j % 2 == 1)) {
                    maze[i][j] = 0; // Path
                }
                else if (((i % 2 == 1 && j % 2 == 0 && j != 0 && j != output_width - 1) ||
                    (j % 2 == 1 && i % 2 == 0 && i != 0 && i != output_height - 1))) {
                    maze[i][j] = 0; // Path (already exists)
                }
                else {
                    maze[i][j] = 2; // Wall
                    wallCount++;


                }
            }
        }

        std::vector<unsigned> row_set(width, 0);
        unsigned set = 1;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 2);

        //The rest of the maze generation algorithm remains largely unchanged.
        for (unsigned i = 0; i < height; ++i) {
            for (unsigned j = 0; j < width; ++j) {
                if (row_set[j] == 0) {
                    row_set[j] = set++;
                }
            }
            for (unsigned j = 0; j < width - 1; ++j) {
                const auto right_wall = dist(mt);
                if (right_wall == 1 || row_set[j] == row_set[j + 1]) {
                    maze[i * 2 + 1][j * 2 + 2] = 2;

                }
                else {
                    const auto changing_set = row_set[j + 1];
                    for (unsigned l = 0; l < width; ++l) {
                        if (row_set[l] == changing_set) {
                            row_set[l] = row_set[j];
                        }
                    }
                }
            }
            for (unsigned j = 0; j < width; ++j) {
                const auto bottom_wall = dist(mt);
                unsigned int count_current_set = 0;
                for (unsigned l = 0; l < width; ++l) {
                    if (row_set[j] == row_set[l]) {
                        count_current_set++;
                    }
                }
                if (bottom_wall == 1 && count_current_set != 1) {
                    maze[i * 2 + 2][j * 2 + 1] = 2;
                }
            }
            if (i != height - 1) {
                for (unsigned j = 0; j < width; ++j) {
                    unsigned count_hole = 0;
                    for (unsigned l = 0; l < width; ++l) {
                        if (row_set[l] == row_set[j] && maze[i * 2 + 2][l * 2 + 1] == 0) {
                            count_hole++;
                        }
                    }
                    if (count_hole == 0) {
                        maze[i * 2 + 2][j * 2 + 1] = 0;
                    }
                }
                for (unsigned j = 0; j < width; ++j) {
                    if (maze[i * 2 + 2][j * 2 + 1] == 2) {
                        row_set[j] = 0;
                    }
                }
            }
        }
        for (unsigned int j = 0; j < width - 1; ++j) {
            if (row_set[j] != row_set[j + 1]) {
                maze[output_height - 2][j * 2 + 2] = 0;
            }
        }

        int numOnes = static_cast<int>(wallCount * 0.1);
        std::random_device rrnd;
        std::mt19937 gen(rrnd()); // Создаем генератор с использованием rd()
        std::uniform_int_distribution<> distrib(0, wallCount - 1);
        int random_number = distrib(gen);
        vector<pair<int, int>> wallCoordinates;
        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                if (maze[i][j] == 2) {
                    wallCoordinates.push_back({ i, j });
                }
            }
        }

        for (int i = 0; i < numOnes; ++i) {
            int index = distrib(gen);
            if (index >= wallCoordinates.size()) continue; //Handle potential out of bound exception
            int row = wallCoordinates[index].first;
            int col = wallCoordinates[index].second;
            maze[row][col] = 1;
        }




        return maze;
    }

    static void print(const std::vector<std::vector<int>>& maze) {
        for (const auto& row : maze) {
            for (int val : row) {
                std::cout << val;
            }
            std::cout << std::endl;
        }
    }
};