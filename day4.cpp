/**
 * Solution for 2024 Day 4
 * https://adventofcode.com/2024/day/4
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

int count_xmas(const vector<string>& grid) {
    // Directions: horizontal, vertical, and diagonals (including backwards)
    const int dx[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
    const int dy[] = { 1, -1, 0, 0, 1, -1, -1, 1 };

    int count = 0;
    int rows = grid.size();

    if (rows == 0) return 0;
    int cols = grid[0].size();

    const string xmas = "XMAS";

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != 'X') continue;

            for (int d = 0; d < 8; ++d) {
                int x = i, y = j;
                bool found = true;

                for (auto c : xmas) {
                    if (x < 0 || x >= rows || y < 0 || y >= cols || grid[x][y] != c) {
                        found = false;
                        break;
                    }
                    x += dx[d];
                    y += dy[d];
                }

                if (found) count++;
            }
        }
    }

    return count;
}

bool is_inside_boundaries(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool is_mas_valid(char M, char A, char S) {
    return (M == 'M' && A == 'A' && S == 'S');
}

bool is_crossing_mas(const vector<string>& grid, int x, int y) {
    // Directions: four possible X shapes
    const int dx[] = { 1, 1, -1, -1 };
    const int dy[] = { 1, -1, -1, 1 };

    int valid_mas_count = 0;

    for (int d = 0; d < 4; ++d) {
        int x1 = x + dx[d], y1 = y + dy[d];
        int x2 = x - dx[d], y2 = y - dy[d];

        if (
            is_inside_boundaries(x1, y1, grid.size(), grid[0].size()) &&
            is_inside_boundaries(x2, y2, grid.size(), grid[0].size())
            ) {

            if (is_mas_valid(grid[x1][y1], grid[x][y], grid[x2][y2])) {
                valid_mas_count++;
            }
        }
    }

    if (valid_mas_count == 2) return true;
    else return false;
}

int count_crossing_mas(const vector<string>& grid) {
    int count = 0;
    int rows = grid.size();

    if (rows == 0) return 0;
    int cols = grid[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'A' && is_crossing_mas(grid, i, j)) count++;
        }
    }

    return count;
}

int main() {
    ifstream input_file("input/day4.txt");
    if (!input_file.is_open()) {
        cerr << "Error: could not open input file." << endl;
        return 1;
    }

    string line;
    vector<string> grid;

    while (getline(input_file, line)) {
        if (!line.empty()) grid.push_back(line);
    }

    int xmas_count = count_xmas(grid);
    cout << "XMAS count: " << xmas_count << endl;

    int crossing_mas_count = count_crossing_mas(grid);
    cout << "X-MAS count: " << crossing_mas_count << endl;

    input_file.close();

    return 0;
}