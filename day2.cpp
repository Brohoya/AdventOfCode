/**
 * Solution for 2024 Day 2
 * https://adventofcode.com/2024/day/2
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

// Overload << for vector
template <typename S>
ostream& operator<<(ostream& os,
    const vector<S>& vector) {

    // Printing all the elements using <<
    for (auto i : vector) os << i << " ";
    return os;
}

vector<int> parse_report(const string& line) {
    istringstream iss(line);
    vector<int> report;
    int number;

    while (iss >> number) report.push_back(number);
    return report;
}

bool is_lvl_bad(int current, int next, bool positive_trend) {
    return (
        // Verify the trend through the report
        (current <= next && !positive_trend) || (current >= next && positive_trend) ||
        // Verify the gaps between levels
        abs(current - next) > 3
    );
}

bool is_report_safe(vector<int> report) {
    assert(report.size() >= 2);
    bool positive_trend = report[0] < report[1];
    bool safe = true;

    for (int lvl = 0; lvl < report.size() - 1; lvl++) {
        if (is_lvl_bad(report[lvl], report[lvl + 1], positive_trend)) {
            safe = false;
            break;
        }
    }

    return safe;
}

int count_safe_reports(vector<vector<int>>& report_list) {
    int safe_count = 0;

    for (vector<int> report : report_list) {
        if (is_report_safe(report)) safe_count++;
    }

    return safe_count;
}

int count_safe_reports_with_problem_dampener(vector<vector<int>>& report_list) {
    int safe_count = 0;

    for (vector<int> report : report_list) {
        if (is_report_safe(report)) safe_count++;
        else {
            // If the report is not safe, we investigate if removing one of the levels turns it safe
            assert(report.size() >= 2);

            for (int lvl = 0; lvl < report.size(); lvl++) {
                vector<int> temp_report = report;
                temp_report.erase(temp_report.begin() + lvl);

                // If the report is safe after removal of the current lvl, we detected the only bad level that was making the report unsafe
                if (
                    is_report_safe(temp_report) &&
                    // Checking the duplicate adjacent numbers
                    (report[max(0, lvl - 1)] != report[lvl] || report[lvl] != report[min((int)report.size() - 1, lvl + 1)])
                    ) {

                    safe_count++;
                    break;
                }
            }
        }
    }

    return safe_count;
}

int main() {
   ifstream input_file("input/day2.txt");
   if (!input_file.is_open()) {
       cerr << "Error: could not open input file." << endl;
       return 1;
   }

   string line;
   vector<vector<int>> report_list;

   while (getline(input_file, line)) {
       report_list.push_back(parse_report(line));
   }

   int safe_reports = count_safe_reports(report_list);
   cout << "Safe reports: " << safe_reports << endl;

   int safe_reports_with_problem_dampener = count_safe_reports_with_problem_dampener(report_list);
   cout << "Safe reports when Problem Dampener considered: " << safe_reports_with_problem_dampener << endl;

   input_file.close();

   return 0;
}