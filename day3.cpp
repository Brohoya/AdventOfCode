/**
 * Solution for 2024 Day 3
 * https://adventofcode.com/2024/day/3
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

size_t find_next_mul(const string& input, size_t cursor_position, bool* instructions_enabled) {
    size_t next_do = input.find("do()", cursor_position);
    size_t next_dont = input.find("don't()", cursor_position);
    size_t next_mul = input.find("mul(", cursor_position);

    if (instructions_enabled != nullptr && min(next_do, next_dont) < next_mul) {
        if (next_do < next_dont) *instructions_enabled = true;
        else *instructions_enabled = false;
    }

    return next_mul;
};

vector<pair<int, int>> extract_instructions(const string& input, bool* instructions_enabled = nullptr) {
    vector<pair<int, int>> instructions;

    size_t start = 0;
    size_t end = find_next_mul(input, start, instructions_enabled);

    while (end != string::npos) {
        // Move past "mul("
        start = end + 4;
        end = input.find(")", start);

        // If no closing parenthesis found, stop the parsing
        if (end == string::npos) break;

        // If no closing parenthesis found within the window (2 numbers of max 3 digits + comma), look for the next "mul("
        size_t max_end = min(input.length(), start + 7);
        if (end > max_end) {
            end = find_next_mul(input, start, instructions_enabled);
            continue;
        }

        // Parse the the string between parenthesis to get the numbers and comma
        string numbers = input.substr(start, end - start);
        size_t comma = numbers.find(',');

        // If comma not found, look for the next "mul("
        if (comma == string::npos) {
            end = find_next_mul(input, start, instructions_enabled);
            continue;
        }

        // Convert the numbers to integers
        int x, y;
        istringstream(numbers.substr(0, comma)) >> x;
        istringstream(numbers.substr(comma + 1)) >> y;

        if(instructions_enabled  == nullptr || *instructions_enabled) instructions.emplace_back(x, y);
        end = find_next_mul(input, end, instructions_enabled);
    }

    return instructions;
}

long long compute_mults_with_instructions(vector<string> lines) {
    long long sum = 0;
    bool instructions_enabled = true;

    for (string& line : lines) {
        vector<pair<int, int>> instructions = extract_instructions(line, &instructions_enabled);

        for (pair<int, int> instruction : instructions) {
            sum += instruction.first * instruction.second;
        }
    }

    return sum;
}

long long compute_mults(vector<string> lines) {
    long long sum = 0;

    for (string& line : lines) {
        vector<pair<int, int>> instructions = extract_instructions(line);

        for (pair<int, int> instruction : instructions) {
            sum += instruction.first * instruction.second;
        }
    }

    return sum;
}

int main() {
   ifstream input_file("input/day3.txt");
   if (!input_file.is_open()) {
       cerr << "Error: could not open input file." << endl;
       return 1;
   }

   string line;
   vector<string> sections;

   while (getline(input_file, line)) {
       if (!line.empty()) sections.push_back(line);
   }

   int mults_result = compute_mults(sections);
   cout << "Sum of the multiplications: " << mults_result << endl;

   int mults_with_instructions_result = compute_mults_with_instructions(sections);
   cout << "Sum of the multiplications considering other instructions: " << mults_with_instructions_result << endl;

   input_file.close();

   return 0;
}