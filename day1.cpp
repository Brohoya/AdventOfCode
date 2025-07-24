/**
 * Solution for 2024 Day 1
 * https://adventofcode.com/2024/day/1
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream> 
#include <cstdlib>
#include <string>
#include <unordered_map>

using namespace std;

void parse_line_into_lists(const string& line, vector<int>& left_list, vector<int>& right_list) {
    istringstream iss(line);
    int number;

    if (iss >> number) left_list.push_back(number);
    if (iss >> number) right_list.push_back(number);
}

int calculate_distance(vector<int>& left_list, vector<int>& right_list) {
    /************************************************************************/
    /* I used existing sorting algorithms as I did not know at which degree */
    /* all the code has to be written by myself (like in Leetcode problems) */
    /************************************************************************/
    sort(left_list.begin(), left_list.end());
    sort(right_list.begin(), right_list.end());

    int distance = 0;
    int min_length = min(left_list.size(), right_list.size());

    for (int i = 0; i < min_length; i++) {
        distance += abs(left_list[i] - right_list[i]);
    }

    return distance;
}

int calculate_similarity_score(vector<int>& left_list, vector<int>& right_list) {
    unordered_map<int, int> right_map;
    int score = 0;

    for (const int r : right_list) {
        if (right_map.find(r) == right_map.end()) right_map[r] = r;
        else right_map[r] += r;
    }

    for (const int l : left_list) {
        if (right_map.find(l) != right_map.end()) {
            score += right_map[l];
        }
    }

    return score;
}

int main() {
   ifstream input_file("input/day1.txt");
   if (!input_file.is_open()) {
       cerr << "Error: could not open input file." << endl;
       return 1;
   }

   string line;
   vector<int> left_list, right_list;

   while (getline(input_file, line)) {
       parse_line_into_lists(line, left_list, right_list);
   }

   int distance = calculate_distance(left_list, right_list);
   cout << "Total distance: " << distance << endl;

   int similarity_score = calculate_similarity_score(left_list, right_list);
   cout << "Similarity score: " << similarity_score << endl;

   input_file.close();

   return 0;
}